#include "parsetree.h"
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;

struct ErrMsg{
	int lineno;
	int column;
	string msg;
};
set<int> labels;
vector<ErrMsg> errMsg;
SymbolItem *procFunc;
int tmpSymCount = 0;

TreeNode *newALeafNode(YYSTYPE &child)
{
	TreeNode *childTreeNode = new TreeNode;
	childTreeNode->nodeType = NODE_TOKEN;
	childTreeNode->typeValue.tokenType = child.tokenType;
	childTreeNode->lineno = child.lineno;
	childTreeNode->column = child.column;
	childTreeNode->leftChild = nullptr;
	childTreeNode->rightSibling = nullptr;
	switch (child.tokenType)
	{
	case T_INTEGER:
		childTreeNode->value.nodeInteger.i = child.data.i;
		break;
	case T_REAL:
		childTreeNode->value.nodeReal.r = child.data.r;
		break;
	case T_CHAR:
		childTreeNode->value.nodeChar.c = child.data.c;
		break;
	case T_STRING:
		strcpy(childTreeNode->value.nodeString.s, child.data.s);
		break;
	case T_ID:
		strcpy(childTreeNode->value.nodeId.id, child.data.s);
		break;
	case T_SYS_CON:
		childTreeNode->value.nodeSysConVal.sysConVal = child.data.sysConVal;
		break;
	case T_SYS_FUNCT:
		childTreeNode->value.nodeSysFunctVal.sysFunctVal = child.data.sysFunctVal;
		break;
	case T_SYS_PROC:
		childTreeNode->value.nodeSysProcVal.sysProcVal = child.data.sysProcVal;
		break;
	case T_SYS_TYPE:
		childTreeNode->value.nodeSysTypeVal.sysTypeVal = child.data.sysTypeVal;
		break;
	default:
		;
	}
	return childTreeNode;
}

YYSTYPE newTreeNode(const initializer_list<YYSTYPE> &children, \
	const NodeType nodeType, \
	const StmtType stmtType, \
	const ExpType expType)
{
	YYSTYPE newNode;
	TreeNode *treeNode = new TreeNode;
	treeNode->nodeType = nodeType;
	if (nodeType == NODE_STMT)
		treeNode->typeValue.stmtType = stmtType;
	if (nodeType == NODE_EXP)
		treeNode->typeValue.expType = expType;

	treeNode->leftChild = nullptr;
	treeNode->rightSibling = nullptr;

	int i = 0;
	TreeNode *lastSibling = nullptr;
	for (auto child : children)
	{
		//first child, insert into the child
		if (i == 0)
		{
			if (child.tokenType == T_NONLEAF)
				treeNode->leftChild = child.data.treeNode;
			else
				treeNode->leftChild = newALeafNode(child);
			lastSibling = treeNode->leftChild;
		}
		else	//insert the lastSibling
		{
			if (child.tokenType == T_NONLEAF)
				lastSibling->rightSibling = child.data.treeNode;
			else
				lastSibling->rightSibling = newALeafNode(child);
			lastSibling = lastSibling->rightSibling;
		}
		++i;
	}
	newNode.data.treeNode = treeNode;
	newNode.tokenType = T_NONLEAF;
	if (children.size()){
		newNode.data.treeNode->lineno = newNode.lineno = children.begin()->lineno;
		newNode.data.treeNode->column = newNode.column = children.begin()->column;
	}
	return newNode;
}


YYSTYPE linkTreeNode(YYSTYPE &parent, YYSTYPE &sibling)
{
	if (parent.data.treeNode->leftChild == nullptr)
	{
		parent.data.treeNode->leftChild = sibling.data.treeNode;
		return parent;
	}

	TreeNode *p;
	for (p = parent.data.treeNode->leftChild;
		p->rightSibling != nullptr;
		p = p->rightSibling)
		1 + 1;
	//now p is the last sibling
	p->rightSibling = sibling.data.treeNode;
	return parent;
}

bool computeAttrGrammar(YYSTYPE &root)
{
	switch (root.data.treeNode->nodeType){
	case NODE_TOKEN: return computeToken(root);
	case NODE_EXP: return computeExp(root);
	case NODE_STMT: return computeStmt(root);
	default: return false;
	}
}

bool computeToken(YYSTYPE &root)
{
	return true;
}

bool computeExp(YYSTYPE &root)
{
	switch (root.data.treeNode->typeValue.expType) {
	case E_GE:
	case E_GT:
	case E_LE:
	case E_LT:
	case E_EQUAL:
	case E_UNEQUAL: return computeStmtExpressionCompare(root);
	case E_PLUS:
	case E_MINUS:
	case E_MUL:
	case E_DIV:return computeStmtExpressionArithmetic(root);
	case E_OR:
	case E_MOD:
	case E_AND: return computeStmtExpressionArithmeticInt(root);
	}
	return true;
}

vector<SymbolItem*> args;

bool computeStmt(YYSTYPE &root)
{
	switch (root.data.treeNode->typeValue.stmtType)
	{
		case S_STMT:{
			labels.insert(root.data.treeNode->leftChild->value.nodeInteger.i);
			return true;
		}
		case S_ASSIGN:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
			getNthChild(root, 1)->attribute.attrName = string(getNthChild(root, 1)->value.nodeId.id);
			getNthChild(root, 1)->attribute.attrType = symbolOfID->symbolType;
			getNthChild(root, 0)->attribute.attrType = symbolOfID->symbolType;
			TreeNode *t = getNthChild(root, 2);
			if (symbolOfID == nullptr)
			{
				//TODO 
				//unknown id
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				return false;
			}
			else if (symbolOfID->leftable == false){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' cannot be a left value";
				errMsg.push_back(msg);
				return false;
			}
			else if (testType(symbolOfID->symbolType, getNthChild(root, 2)->attribute.attrType) == false)
			{
				//TODO 
			//assign type unmatched
				TreeNode *t = getNthChild(root, 2);

				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Unmatched type to assign";
				errMsg.push_back(msg);
				return false;
			}
			Debug("S_ASSIGN type check ok");
			break;
		}
		case S_ASSIGN_ARRAY:
		{
			string idArrayStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idArrayStr);
			if (symbolOfID == nullptr)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				return false;
			}
			if (symbolOfID->symbolType != A_ARRAY)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' isn't an array";
				errMsg.push_back(msg);
				return false;
			}
			int flag = 0;
			if (getNthChild(root, 2)->attribute.attrType != A_INTEGER
				&& getNthChild(root, 2)->attribute.attrType != A_CONST_INTEGER)
			{
				//The index of array is not integer
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Index isn't in correct type";
				errMsg.push_back(msg);
				flag = 1;
			}
			if (!testType(symbolOfID->arrayItemType->symbolType, getNthChild(root, 3)->attribute.attrType))
			{
				//TODO
			//assign type unmatched
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Unmatched type to assign";
				errMsg.push_back(msg);
				flag = 1;
			}
			if (flag) return false;
			Debug("S_ASSIGN_ARRAY type check ok");
			break;
		}
		case S_ASSIGN_RECORD:
		{
			string idRecordStr = getID(getNthChild(root, 1));
			string idRecEleStr = getID(getNthChild(root, 2));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idRecordStr);
			if (symbolOfID == nullptr)	//undefined id
			{
				//TODO 
			//unknown id
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				return false;
			}
			else if (symbolOfID->symbolType != A_RECORD){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				return false;
			}
			else if (symbolOfID->recordDef.find(idRecEleStr) == symbolOfID->recordDef.end())	//undefined record element
			{
				//TODO
			//record has no this element
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = string("\'") + root.data.treeNode->leftChild->rightSibling->value.nodeId.id + "\' isn't in the record";
				errMsg.push_back(msg);
				return false;
			}
			else if (!testType(symbolOfID->recordDef[idRecEleStr]->symbolType, getNthChild(root, 3)->attribute.attrType))
			{
				//TODO
			//assign type unmatched
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Unmatched type to assign";
				errMsg.push_back(msg);
				return false;
			}
			Debug("S_ASSIGN_RECORD type check ok");
			break;
		}
		case S_PROC:
		case S_PROC_FUNC:
		{
			SymbolItem *sym = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
			if (sym == nullptr){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				return false;
			}
			if (sym->symbolType != A_PROC){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' isn't a function";
				errMsg.push_back(msg);
				return false;
			}
			root.data.treeNode->attribute.attrType = sym->returnType->symbolType;
			if (sym->argList.size() != 0 && root.data.treeNode->leftChild->rightSibling == nullptr){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Wrong number of arguments";
				errMsg.push_back(msg);
				return false;
			}
			TreeNode *args = root.data.treeNode->leftChild->rightSibling->leftChild;
			TreeNode *p = nullptr;
			if (args) p = args->leftChild;
			int flag = 0;
			for (int i = 0; i < sym->argList.size(); ++i){
				if (args == nullptr){
					ErrMsg msg;
					msg.lineno = root.data.treeNode->leftChild->lineno;
					msg.column = root.data.treeNode->leftChild->column;
					msg.msg = "Wrong number of arguments";
					errMsg.push_back(msg);
					return false;
				}
				if (p == nullptr){
					ErrMsg msg;
					msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
					msg.column = root.data.treeNode->leftChild->rightSibling->column;
					msg.msg = "Wrong number of arguments";
					errMsg.push_back(msg);
					return false;
				}
				if (sym->argList[i]->symbolType != p->attribute.attrType
					&& !(sym->argList[i]->symbolType == A_INTEGER && p->attribute.attrType == A_CONST_INTEGER)
					&& !(sym->argList[i]->symbolType == A_REAL && p->attribute.attrType == A_CONST_REAL)
					&& !(sym->argList[i]->symbolType == A_CHAR && p->attribute.attrType == A_CONST_CHAR)
					&& !(sym->argList[i]->symbolType == A_STRING && p->attribute.attrType == A_CONST_STRING)){
					ErrMsg msg;
					msg.lineno = p->lineno;
					msg.column = p->column;
					msg.msg = "Wrong type of argument";
					errMsg.push_back(msg);
					flag = 1;
				}
				p = p->rightSibling;
			}
			if (p){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Wrong number of arguments";
				errMsg.push_back(msg);
				return false;
			}
			if (flag == 1) return false;

			return true;
		}
		case S_PROC_SYS:{
			ErrMsg msg;
			msg.lineno = root.data.treeNode->leftChild->lineno;
			msg.column = root.data.treeNode->leftChild->column;
			msg.msg = "Wrong number of arguments";
			errMsg.push_back(msg);
			return false;
		}
		case S_PROC_SYS_ARG:
		{
			
			
			TreeNode *args = root.data.treeNode->leftChild->rightSibling->leftChild;
			
			int flag = 0;
			for (; args; args = args->rightSibling){
				
				if (args->attribute.attrType != A_INTEGER && args->attribute.attrType != A_CONST_INTEGER
					&& args->attribute.attrType != A_REAL && args->attribute.attrType != A_CONST_REAL
					&& args->attribute.attrType != A_CHAR && args->attribute.attrType != A_CONST_CHAR
					&& args->attribute.attrType != A_STRING && args->attribute.attrType != A_CONST_STRING){
					ErrMsg msg;
					msg.lineno = args->lineno;
					msg.column = args->column;
					msg.msg = "Argument in wrong type";
					errMsg.push_back(msg);
					flag = 1;
				}
			}
		
			if (flag == 1) return false;

			return true;
		}
		case S_IF:
		case S_WHILE:
		{
			if (getNthChild(root, 1)->attribute.attrType != A_BOOLEAN)
			{
				//unmatch type
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Expressiong type isn't BOOLEAN";
				errMsg.push_back(msg);
				return false;
			}
			Debug("S_IF/S_WHILE type check ok");
			break;
		}
		case S_REPEAT:
		{
			if (getNthChild(root, 2)->attribute.attrType != A_BOOLEAN)
			{
				//unmatch type
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Expressiong type isn't BOOLEAN";
				errMsg.push_back(msg);
				return false;
			}
			Debug("S_REPEAT type check ok");
			break;
		}
		case S_FOR:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
			int flag = 0;
			if (symbolOfID == nullptr)	//undefined id
			{
				//TODO 
			//unknown id
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
				errMsg.push_back(msg);
				flag = 1;
			}
			else{
				if (symbolOfID){
					getNthChild(root, 1)->attribute.attrName = string(getNthChild(root, 1)->value.nodeId.id);
					getNthChild(root, 1)->attribute.attrType = symbolOfID->symbolType;
				}
				if (symbolOfID->symbolType != A_INTEGER
					&& symbolOfID->symbolType != A_CONST_INTEGER){
					ErrMsg msg;
					msg.lineno = root.data.treeNode->leftChild->lineno;
					msg.column = root.data.treeNode->leftChild->column;
					msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' should be an integer";
					errMsg.push_back(msg);
					flag = 1;
				}
			}
			
			if (getNthChild(root, 2)->attribute.attrType != A_INTEGER
				&& getNthChild(root, 2)->attribute.attrType != A_CONST_INTEGER)
			{
				//unmatch type
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Expression should be integer";
				errMsg.push_back(msg);
				flag = 1;
			}
			if (getNthChild(root, 4)->attribute.attrType != A_INTEGER
				&& getNthChild(root, 4)->attribute.attrType != A_CONST_INTEGER)
			{
				//unmatch type
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->rightSibling->column;
				msg.msg = "Expression should be integer";
				errMsg.push_back(msg);
				flag = 1;
			}
			if (flag) return false;
			Debug("S_FOR type check ok");
			break;
		}

		case S_PROGRAM_HEAD:
		{
			SymbolItem *sym = new SymbolItem();
			sym->symbolType = A_VOID;
			sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
			sym->leftable = false;
			symtable.addIntoSymtable(sym);
			break;
		}
		case S_CONST_EXPR: 
		{
			SymbolItem *sym = new SymbolItem();
			switch(root.data.treeNode->leftChild->rightSibling->typeValue.stmtType)
			{
				case S_CONST_VALUE_INT: 
					sym->symbolType = A_CONST_INTEGER;
					sym->constValue.i = root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeInteger.i;
					break;
				case S_CONST_VALUE_REAL: 
					sym->symbolType = A_CONST_REAL;
					sym->constValue.r = root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeReal.r;
					break;
				case S_CONST_VALUE_CHAR:
					sym->symbolType = A_CONST_CHAR;
					sym->constValue.c = root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeChar.c;
					break;
				case S_CONST_VALUE_STRING: 
					sym->symbolType = A_CONST_STRING;
					sym->constValue.s = root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeString.s;
					break;
				case S_CONST_VALUE_SYS_CON:
				{
					switch (root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeSysConVal.sysConVal)
					{
					case CON_FALSE:
						sym->symbolType = A_BOOLEAN;
						sym->constValue.i = false;
						break;
					case CON_TRUE: 
						sym->symbolType = A_BOOLEAN;
						sym->constValue.i = true;
						break;
					case CON_MAXINT: 
						sym->symbolType = A_CONST_INTEGER;
						sym->constValue.i = 0x7fffffff;
						break;
					case CON_PI: 
						sym->symbolType = A_CONST_REAL;
						sym->constValue.r = atan2(0, -1);
						break;
					}
					break;
				}
			}
			sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
			sym->leftable = false;
			if (symtable.addIntoSymtable(sym) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_TYPE_DEFINITION:
		{
			SymbolItem *sym = computeType(root.data.treeNode->leftChild->rightSibling);
			if (sym == nullptr)
			{
				return false;
			}
			sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
			sym->leftable = false;
			if (symtable.addIntoSymtable(sym) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_VAR_DECL: 
		{
			TreeNode *nameList = root.data.treeNode->leftChild;
			bool flag = true;
			for(TreeNode *p = nameList->leftChild; p != nullptr; p = p->rightSibling)
			{
				SymbolItem *sym = computeVarType(nameList->rightSibling);
				if (sym == nullptr)
				{
					return false;
				}
				sym->symbolName = p->leftChild->value.nodeId.id;
				sym->leftable = true;
				if (symtable.addIntoSymtable(sym) == 0)
				{
					ErrMsg msg;
					msg.lineno = p->leftChild->lineno;
					msg.column = p->leftChild->column;
					msg.msg = string("ID \'") + p->leftChild->value.nodeId.id + "\' already used";
					errMsg.push_back(msg);
					flag = false;
				}
				
			}
			return flag;
		}
		case S_PARA_TYPE_LIST_VAR: case S_PARA_TYPE_LIST_VAL:
		{
			TreeNode *nameList = root.data.treeNode->leftChild->leftChild;
			bool flag = true;
			for (TreeNode *p = nameList->leftChild; p != nullptr; p = p->rightSibling)
			{
				SymbolItem *sym = computeVarSimpleType(root.data.treeNode->leftChild->rightSibling);
				if (sym == nullptr)
				{
					return false;
				}
				sym->symbolName = p->leftChild->value.nodeId.id;
				sym->leftable = true;
				if (symtable.addIntoSymtable(sym) == 0)
				{
					ErrMsg msg;
					msg.lineno = p->leftChild->lineno;
					msg.column = p->leftChild->column;
					msg.msg = string("ID \'") + p->leftChild->value.nodeId.id + "\' already used";
					errMsg.push_back(msg);
					flag = false;
				}
				args.push_back(sym);
			}
			return flag;
		}
		case S_PROCEDURE_HEAD:
		{
			SymbolItem *sym = new SymbolItem();
			sym->symbolType = A_PROC;
			sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
			sym->leftable = false;
			copy(args.begin(), args.end(), back_inserter(sym->argList));
			args.clear();
			if (symtable.addIntoSymtable(sym) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_PROCEDURE_DECL:
		{
			if (procFunc == nullptr || procFunc->symbolType != A_PROC)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->leftChild->column;
				msg.msg = "procedure not correclty built";
				errMsg.push_back(msg);
				return false;
			}
			if (symtable.addIntoSymtable(procFunc) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_FUNCTION_HEAD:
		{
			SymbolItem *sym = new SymbolItem();
			sym->symbolType = A_FUNC;
			sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
			sym->leftable = false;
			copy(args.begin(), args.end(), back_inserter(sym->argList));
			args.clear();
			sym->returnType = computeVarSimpleType(root.data.treeNode->leftChild->rightSibling->rightSibling);
			if (sym->returnType == nullptr)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->rightSibling->column;
				msg.msg = "Unknown type or too difficult type";
				errMsg.push_back(msg);
				return false;
			}
			if (symtable.addIntoSymtable(sym) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_FUNCTION_DECL:
		{
			if (procFunc == nullptr || procFunc->symbolType != A_FUNC)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->leftChild->column;
				msg.msg = "function not correclty built";
				errMsg.push_back(msg);
				return false;
			}
			if (symtable.addIntoSymtable(procFunc) == 0)
			{
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->leftChild->column;
				msg.msg = string("ID \'") + root.data.treeNode->leftChild->leftChild->value.nodeId.id + "\' already used";
				errMsg.push_back(msg);
				return false;
			}
			return true;
		}
		case S_CASE: return computeStmtCase(root);
		case S_CASE_EXPR_LIST: return computeStmtCaseExprList(root);
		case S_CASE_EXPR_ID:return computeStmtCaseExprId(root);
		case S_CASE_EXPR_CONST:return computeStmtCaseExprConst(root);
		//case S_FUNCTION_HEAD: return computeStmtFunctionHead(root);
		case S_EXPRESSION_LIST:return computeStmtExpressionList(root);
		case S_FACTOR_SYS:
		case S_FACTOR_SYS_ARG:return computeStmtFactorSysFunct(root);
		case S_FACTOR_CONST:
		{
			switch (root.data.treeNode->leftChild->typeValue.stmtType)
			{
			case S_CONST_VALUE_INT:
			{
				root.data.treeNode->attribute.attrType = A_CONST_INTEGER; 
				char str[256];
				sprintf(str, "%d", root.data.treeNode->leftChild->leftChild->value.nodeInteger.i);
				root.data.treeNode->leftChild->attribute.attrName = str;
				root.data.treeNode->attribute.attrName = str;
				break;
			}
			case S_CONST_VALUE_REAL:
			{
				root.data.treeNode->attribute.attrType = A_CONST_REAL; 
				char str[256];
				sprintf(str, "%f", root.data.treeNode->leftChild->leftChild->value.nodeReal.r);
				root.data.treeNode->leftChild->attribute.attrName = str;
				break;
			}
			case S_CONST_VALUE_CHAR:
			{
				root.data.treeNode->attribute.attrType = A_CONST_CHAR;
				root.data.treeNode->leftChild->attribute.attrName = root.data.treeNode->leftChild->leftChild->value.nodeChar.c;
				break;
			}
			case S_CONST_VALUE_STRING:
			{
				root.data.treeNode->attribute.attrType = A_CONST_STRING;
				root.data.treeNode->leftChild->attribute.attrName = root.data.treeNode->leftChild->leftChild->value.nodeString.s;
				break;
			}
			case S_CONST_VALUE_SYS_CON:
			{
				switch (root.data.treeNode->leftChild->leftChild->value.nodeSysConVal.sysConVal)
				{
				case CON_FALSE:
				{
					root.data.treeNode->attribute.attrType = A_BOOLEAN;
					root.data.treeNode->leftChild->attribute.attrName = "false";
					break;
				}
				case CON_TRUE:
				{
					root.data.treeNode->attribute.attrType = A_BOOLEAN; 
					root.data.treeNode->leftChild->attribute.attrName = "true";
					break;
				}
				case CON_MAXINT:
				{
					root.data.treeNode->attribute.attrType = A_INTEGER;
					root.data.treeNode->leftChild->attribute.attrName = "maxint";
					break;
				}
				case CON_PI:
				{
					root.data.treeNode->attribute.attrType = A_REAL; 
					root.data.treeNode->leftChild->attribute.attrName = "pi";
					break;
				}
				}
				break;
			}
			}
			root.data.treeNode->leftChild->attribute.attrType = root.data.treeNode->attribute.attrType;
			return true;
			break;
		}
		case S_GOTO:{
			if (labels.find(root.data.treeNode->leftChild->value.nodeInteger.i) == labels.end()){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Unknown label";
				errMsg.push_back(msg);
				return false;
			}
			return false;
		}
		case S_FACTOR_ARRAY:return computeStmtFactorArray(root);
		case S_FACTOR_FUNC:return computeStmtFactorFunc(root);
		case S_FACTOR_RECORD:return computeStmtFactorRecord(root);
		case S_FACTOR_ID:return computeStmtFactorID(root);
		case S_ARGS:
		case S_ARGS_NULL:
		
		case S_FACTOR_NOT:
		case S_FACTOR_MINUS:
			return computeStmtAssignToParent(root);

		case S_CONST_VALUE_INT:{
			root.data.treeNode->attribute.attrType = A_CONST_INTEGER;
			return true;;
		}
		case S_CONST_VALUE_REAL:{
			root.data.treeNode->attribute.attrType = A_CONST_REAL;
			return true;
		}
		case S_CONST_VALUE_CHAR:{
			root.data.treeNode->attribute.attrType = A_CONST_CHAR;
			return true;
		}
		case S_CONST_VALUE_STRING:{
			root.data.treeNode->attribute.attrType = A_CONST_STRING;
			return true;
		}
		case S_CONST_VALUE_SYS_CON:{
			switch (root.data.treeNode->value.nodeSysConVal.sysConVal){
			case CON_FALSE: case CON_TRUE: root.data.treeNode->attribute.attrType = A_BOOLEAN; break;
			case CON_MAXINT: root.data.treeNode->attribute.attrType = A_CONST_INTEGER; break;
			case CON_PI: root.data.treeNode->attribute.attrType = A_CONST_REAL; break;
			}
			return true;
		}
	}
	if (root.data.treeNode->leftChild!=nullptr)
		return computeStmtAssignToParent(root);
	else return true;
}

bool computeStmtCase(YYSTYPE &root)
{
	//case_stmt		: CASE expression OF case_expr_list END
	auto expression = root.data.treeNode->leftChild;
	auto caseType = expression->attribute.attrType;
	if (caseType != A_INTEGER && caseType != A_CONST_INTEGER
		&& caseType != A_CHAR && caseType != A_CONST_CHAR
		&& caseType != A_BOOLEAN)
	{
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = "Expressiong type isn't BOOLEAN/CHAR/INTEGER";
		errMsg.push_back(msg);
		return false;
	}
	TreeNode *p = expression->rightSibling->leftChild;
	int flag = 0;
	for (; p; p = p->rightSibling){
		if (!testType(p->leftChild->attribute.attrType, caseType)
			&& !testType(caseType, p->leftChild->attribute.attrType)){
			ErrMsg msg;
			msg.lineno = p->lineno;
			msg.column = p->column;
			msg.msg = "Case type doesn't match";
			errMsg.push_back(msg);
			flag = 1;
		}
	}
	if (flag)
	{
		return false;
	}
	return true;
}

bool computeStmtCaseExprList(YYSTYPE &root)
{
	//case_expr_list: case_expr_list case_expr
	auto caseExprList = root.data.treeNode->leftChild;
	auto caseExpr = root.data.treeNode->leftChild->rightSibling;
	if (caseExpr->attribute.attrType != caseExprList->attribute.attrType)
	{
		Debug("Type doesn't match between cases in case expression");
		return false;
	}
	return true;
}

bool computeStmtCaseExprId(YYSTYPE & root)
{
	//case_expr 		: ID COLON stmt SEMI
	auto Id = root.data.treeNode->leftChild;
	auto IdType = symtable.getFromSymtable(Id->value.nodeId.id);
	if (IdType)
	{
		Debug("String in case is not supported");
		return false;
	}
	root.data.treeNode->attribute.attrType = IdType->symbolType;
	return true;
}

bool computeStmtCaseExprConst(YYSTYPE & root)
{
	//case_expr 		: const_value COLON stmt SEMI
	auto constValue = root.data.treeNode->leftChild;
	if (constValue->attribute.attrType == A_STRING)
	{
		Debug("String in case is not supported");
		return false;
	}
	root.data.treeNode->attribute.attrType = constValue->attribute.attrType;
	return true;
}

bool computeStmtExpressionList(YYSTYPE & root)
{
	//expression_list: expression_list COMMA expression
	auto expression = root.data.treeNode->leftChild;
	root.data.treeNode->attribute = expression->attribute;
	return false;
}

/*bool computeStmtFunctionHead(YYSTYPE & root)
{
	SymbolItem *sym = new SymbolItem;
	sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
	TreeNode* tn = root.data.treeNode->leftChild->rightSibling;
	sym->recordDef.clear();
	while (tn != nullptr) {
		if (tn->rightSibling == nullptr) {
			SymbolItem *t1 = dealSimpleTypeDecl(tn);
			sym->symbolType = t1->symbolType;
		} else {
			if (tn->leftChild != nullptr) {
				tn = tn->leftChild;
				while (tn != nullptr) {
					dealParaDeclList(tn->leftChild, sym);
					tn = tn->rightSibling;
				}
			}
		}
		tn = tn->rightSibling;
	}
	symtable.addIntoSymtable(sym);
	symtable.showCurrentTable();
	return false;
}

void dealParaDeclList(TreeNode* tn, SymbolItem* sym) {
	while (tn != nullptr) {
		dealParaTypeList(tn->leftChild, sym);
		tn = tn->rightSibling;
	}
}

void dealParaTypeList(TreeNode* tn, SymbolItem* sym) {
	while (tn != nullptr) {
		dealValParaList(tn->leftChild, sym);
		tn = tn->rightSibling;
	}
}

void dealValParaList(TreeNode* tn, SymbolItem* sym) {
	vector<string> vec;
	vec.clear();
	dealNameList(tn->leftChild, vec);
	SymbolItem* s = dealSimpleTypeDecl(tn->rightSibling);
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (sym->recordDef.find(vec[i]) != sym->recordDef.end())
			Debug("DealValParaList: redefined");
		sym->recordDef.insert(make_pair(vec[i], s));
	}
 }*/

SymbolItem* dealSimpleTypeDecl(TreeNode* type) {
	SymbolItem *sym = new SymbolItem();
	switch (type->typeValue.stmtType)
	{
	case S_SIMPLE_TYPE_DECL_SYS:
	{
		switch (type->leftChild->value.nodeSysTypeVal.sysTypeVal)
		{
		case TYPE_BOOLEAN: sym->symbolType = A_BOOLEAN; break;
		case TYPE_CHAR: sym->symbolType = A_CHAR; break;
		case TYPE_INTEGER: sym->symbolType = A_INTEGER; break;
		case TYPE_REAL: sym->symbolType = A_REAL; break;
		}
		break;
	}
	case S_SIMPLE_TYPE_DECL_ID:
	{
		SymbolItem *tmp = symtable.getFromSymtable(type->leftChild->value.nodeId.id);
		memcpy(sym, tmp, sizeof(SymbolItem));
		//*(sym->typeDef) = *(symtable.getFromSymtable(type->value.nodeId.id)->typeDef);
		break;
	}
	case S_ARRAY_TYPE_DECL:
	{
		sym->symbolType = A_ARRAY;
		sym->arrayItemType = computeType(type->leftChild->rightSibling);
		break;
	}
	case S_RECORD_TYPE_DECL:
	{
		sym->symbolType = A_RECORD;
		for (TreeNode *p = type->leftChild->leftChild; p != nullptr; p = p->rightSibling)
		{

			for (TreeNode *pname = p->leftChild->leftChild; pname != nullptr; pname = pname->rightSibling)
			{
				SymbolItem *stype = computeType(p->leftChild->rightSibling);
				stype->symbolName = pname->leftChild->value.nodeId.id;
				sym->recordDef[pname->leftChild->value.nodeId.id] = stype;
			}
		}
		break;
	}
	}
	return sym;
}

vector<string> dealNameList(TreeNode* tn, vector<string> vec) {
	
	while (tn != nullptr) {
		dealName(tn->leftChild, vec);
		tn = tn->rightSibling;
	}
	return vec;
}

void dealName(TreeNode* tn, vector<string> vec) {
	dealId(tn->leftChild, vec);
}

void dealId(TreeNode* tn, vector<string> vec) {
	vec.push_back(tn->value.nodeId.id);
}

bool computeStmtExpressionCompare(YYSTYPE & root)
{
	auto leftOperand = root.data.treeNode->leftChild;
	auto rightOperand = root.data.treeNode->leftChild->rightSibling;
	if (!testType(leftOperand->attribute.attrType, rightOperand->attribute.attrType)
		&& !testType(rightOperand->attribute.attrType, leftOperand->attribute.attrType))
	{
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Left hand side operand does not match right hand side operand";
		errMsg.push_back(msg);
		Debug("Left hand side operand does not match right hand side operand");
		return false;
	}
	root.data.treeNode->attribute.attrType = A_BOOLEAN;
	string tmpStr;
	stringstream ss;
	ss << tmpSymCount++;
	ss >> tmpStr;
	root.data.treeNode->attribute.attrName = "$t" + tmpStr;
	return true;
}

bool computeStmtExpressionArithmetic(YYSTYPE &root)
{
	auto leftOperand = root.data.treeNode->leftChild;
	auto rightOperand = root.data.treeNode->leftChild->rightSibling;
	int flag = 0;
	if (leftOperand->attribute.attrType != A_INTEGER && leftOperand->attribute.attrType != A_CONST_INTEGER
		&& leftOperand->attribute.attrType != A_REAL && leftOperand->attribute.attrType != A_CONST_REAL){
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = "Type not of INT/REAL cannot be calculated";
		errMsg.push_back(msg);
		flag = 1;
	}
	if (rightOperand->attribute.attrType != A_INTEGER && rightOperand->attribute.attrType != A_CONST_INTEGER
		&& rightOperand->attribute.attrType != A_REAL && rightOperand->attribute.attrType != A_CONST_REAL){
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Type not of INT/REAL cannot be calculated";
		errMsg.push_back(msg);
		flag = 1;
	}
	if (flag) return false;
	if ((!(leftOperand->attribute.attrType == A_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER
		|| leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_INTEGER
		|| leftOperand->attribute.attrType == A_INTEGER&&rightOperand->attribute.attrType == A_INTEGER
		|| leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER))
		&& !(leftOperand->attribute.attrType == A_REAL&&rightOperand->attribute.attrType == A_CONST_REAL
		|| leftOperand->attribute.attrType == A_CONST_REAL&&rightOperand->attribute.attrType == A_REAL
		|| leftOperand->attribute.attrType == A_REAL&&rightOperand->attribute.attrType == A_REAL
		|| leftOperand->attribute.attrType == A_CONST_REAL&&rightOperand->attribute.attrType == A_CONST_REAL))
	{
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Left hand side operand does not match right hand side operand";
		errMsg.push_back(msg);
		Debug("Left hand side operand does not match right hand side operand");
		return false;
	}
	
	if (leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER){
		switch (root.data.treeNode->typeValue.expType){
		case E_PLUS: leftOperand->leftChild->leftChild->value.nodeInteger.i += rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		case E_MINUS: leftOperand->leftChild->leftChild->value.nodeInteger.i -= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		case E_MUL: leftOperand->leftChild->leftChild->value.nodeInteger.i *= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		case E_DIV: 
			if (rightOperand->leftChild->leftChild->value.nodeInteger.i == 0){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Divisor cannot be zero";
				errMsg.push_back(msg);
				return false;
			}
			leftOperand->leftChild->leftChild->value.nodeInteger.i /= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		}
		leftOperand->rightSibling = nullptr;
		root.data.treeNode = leftOperand;
		return true;
	}
	if (leftOperand->attribute.attrType == A_CONST_REAL&&rightOperand->attribute.attrType == A_CONST_REAL){
		switch (root.data.treeNode->typeValue.expType){
		case E_PLUS: leftOperand->leftChild->leftChild->value.nodeReal.r += rightOperand->leftChild->leftChild->value.nodeReal.r; break;
		case E_MINUS: leftOperand->leftChild->leftChild->value.nodeReal.r -= rightOperand->leftChild->leftChild->value.nodeReal.r; break;
		case E_MUL: leftOperand->leftChild->leftChild->value.nodeReal.r *= rightOperand->leftChild->leftChild->value.nodeReal.r; break;
		case E_DIV:
			if (rightOperand->leftChild->leftChild->value.nodeReal.r == 0){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Divisor cannot be zero";
				errMsg.push_back(msg);
				return false;
			}
			leftOperand->leftChild->leftChild->value.nodeReal.r /= rightOperand->leftChild->leftChild->value.nodeReal.r; break;
		}
		leftOperand->rightSibling = nullptr;
		root.data.treeNode = leftOperand;
		return true;
	}
	root.data.treeNode->attribute.attrType = min(leftOperand->attribute.attrType, rightOperand->attribute.attrType);
	string tmpStr;
	stringstream ss;
	ss << tmpSymCount++;
	ss >> tmpStr;
	root.data.treeNode->attribute.attrName = "$t" + tmpStr;
	return true;
}

bool computeStmtExpressionArithmeticInt(YYSTYPE &root)
{
	auto leftOperand = root.data.treeNode->leftChild;
	auto rightOperand = root.data.treeNode->leftChild->rightSibling;
	int flag = 0;
	if (leftOperand->attribute.attrType != A_INTEGER && leftOperand->attribute.attrType != A_CONST_INTEGER){
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = "Type not of INT cannot be calculated";
		errMsg.push_back(msg);
		flag = 1;
	}
	if (rightOperand->attribute.attrType != A_INTEGER && rightOperand->attribute.attrType != A_CONST_INTEGER){
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Type not of INT cannot be calculated";
		errMsg.push_back(msg);
		flag = 1;
	}
	if (flag) return false;
	if ((!(leftOperand->attribute.attrType == A_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER
		|| leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_INTEGER
		|| leftOperand->attribute.attrType == A_INTEGER&&rightOperand->attribute.attrType == A_INTEGER
		|| leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER)))
	{
		root.data.treeNode->attribute.attrType = A_WRONG_TYPE;
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Left hand side operand does not match right hand side operand";
		errMsg.push_back(msg);
		Debug("Left hand side operand does not match right hand side operand");
		return false;
	}

	if (leftOperand->attribute.attrType == A_CONST_INTEGER&&rightOperand->attribute.attrType == A_CONST_INTEGER){
		switch (root.data.treeNode->typeValue.expType){
		case E_OR: leftOperand->leftChild->leftChild->value.nodeInteger.i |= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		case E_AND: leftOperand->leftChild->leftChild->value.nodeInteger.i &= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		case E_MOD:
			if (rightOperand->leftChild->leftChild->value.nodeInteger.i == 0){
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Divisor cannot be zero";
				errMsg.push_back(msg);
				return false;
			}
			leftOperand->leftChild->leftChild->value.nodeInteger.i %= rightOperand->leftChild->leftChild->value.nodeInteger.i; break;
		}
		leftOperand->rightSibling = nullptr;
		root.data.treeNode = leftOperand;
		return true;
	}
	
	root.data.treeNode->attribute.attrType = min(leftOperand->attribute.attrType, rightOperand->attribute.attrType);
	string tmpStr;
	stringstream ss;
	ss << tmpSymCount++;
	ss >> tmpStr;
	root.data.treeNode->attribute.attrName = "$t" + tmpStr;
	return true;
}

bool computeStmtFactorSysFunct(YYSTYPE & root)
{
	auto argsList = root.data.treeNode->leftChild->rightSibling;
	/*将返回值的类型赋给root*/
	switch (root.data.sysFunctVal)
	{
	case FUNCT_ABS:
		if (argsList->attribute.attrType == A_INTEGER || argsList->attribute.attrType == A_REAL)
		{
			root.data.treeNode->attribute.attrType = argsList->attribute.attrType;
		}
		else
		{
			Debug("Invalid parameter for sys abs");
			return false;
		}
		break;
	case FUNCT_CHR:
		if (argsList->attribute.attrType == A_INTEGER)
		{
			root.data.treeNode->attribute.attrType = A_CHAR;
		}
		else
		{
			Debug("Invalid parameter for sys chr");
			return false;
		}
		break;
	case FUNCT_ODD:
		if (argsList->attribute.attrType == A_INTEGER)
		{
			root.data.treeNode->attribute.attrType = A_BOOLEAN;
		}
		else
		{
			Debug("Invalid parameter for sys odd");
			return false;
		}
		break;
	case FUNCT_ORD:
		if (argsList->attribute.attrType == A_CHAR)
		{
			root.data.treeNode->attribute.attrType = A_INTEGER;
		}
		else
		{
			Debug("Invalid parameter for sys ord");
			return false;
		}
		break;
	case FUNCT_PRED:
		if (argsList->attribute.attrType == A_INTEGER || argsList->attribute.attrType == A_CHAR)
		{
			root.data.treeNode->attribute.attrType = argsList->attribute.attrType;
		}
		else
		{
			Debug("Invalid parameter for sys pred");
			return false;
		}
		break;
	case FUNCT_SQR:
		if (argsList->attribute.attrType == A_INTEGER || argsList->attribute.attrType == A_REAL)
		{
			root.data.treeNode->attribute.attrType = argsList->attribute.attrType;
		}
		else
		{
			Debug("Invalid parameter for sys sqr");
			return false;
		}
		break;
	case FUNCT_SQRT:
		if (argsList->attribute.attrType == A_INTEGER || argsList->attribute.attrType == A_REAL)
		{
			root.data.treeNode->attribute.attrType = argsList->attribute.attrType;
		}
		else
		{
			Debug("Invalid parameter for sys sqrt");
			return false;
		}
		break;
	case FUNCT_SUCC:
		if (argsList->attribute.attrType == A_INTEGER || argsList->attribute.attrType == A_CHAR)
		{
			root.data.treeNode->attribute.attrType = argsList->attribute.attrType;
		}
		else
		{
			Debug("Invalid parameter for sys pred");
			return false;
		}
		break;
	}
	return true;
}

bool computeStmtAssignToParent(YYSTYPE & root)
{
	//Assign the child's attribute to the parent
	root.data.treeNode->attribute.attrType = root.data.treeNode->leftChild->attribute.attrType;
	return true;
}

bool computeStmtFactorArray(YYSTYPE & root)
{
	SymbolItem *sym = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
	if (sym == nullptr){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
		errMsg.push_back(msg);
		return false;
	}
	if (sym->symbolType != A_ARRAY){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' isn't an array";
		errMsg.push_back(msg);
		return false;
	}
	if (root.data.treeNode->leftChild->rightSibling->attribute.attrType != A_INTEGER
		&& root.data.treeNode->leftChild->rightSibling->attribute.attrType != A_CONST_INTEGER){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Index isn't in correct type";
		errMsg.push_back(msg);
		return false;
	}
	root.data.treeNode->attribute.attrType = sym->arrayItemType->symbolType;
	return true;
}

bool computeStmtFactorFunc(YYSTYPE & root)
{
	SymbolItem *sym = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
	if (sym == nullptr){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
		errMsg.push_back(msg);
		return false;
	}
	if (sym->symbolType != A_FUNC){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' isn't a function";
		errMsg.push_back(msg);
		return false;
	}
	root.data.treeNode->attribute.attrType = sym->returnType->symbolType;
	TreeNode *args = root.data.treeNode->leftChild->rightSibling->leftChild;
	TreeNode *p = nullptr;
	if (args) p = args->leftChild;
	int flag = 0;
	for (int i = 0; i < sym->argList.size(); ++i){
		if (args == nullptr){
			ErrMsg msg;
			msg.lineno = root.data.treeNode->leftChild->lineno;
			msg.column = root.data.treeNode->leftChild->column;
			msg.msg = "Wrong number of arguments";
			errMsg.push_back(msg);
			return false;
		}
		if (p == nullptr){
			ErrMsg msg;
			msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
			msg.column = root.data.treeNode->leftChild->rightSibling->column;
			msg.msg = "Wrong number of arguments";
			errMsg.push_back(msg);
			return false;
		}
		if (sym->argList[i]->symbolType != p->attribute.attrType
			&& !(sym->argList[i]->symbolType == A_INTEGER && p->attribute.attrType == A_CONST_INTEGER)
			&& !(sym->argList[i]->symbolType == A_REAL && p->attribute.attrType == A_CONST_REAL)
			&& !(sym->argList[i]->symbolType == A_CHAR && p->attribute.attrType == A_CONST_CHAR)
			&& !(sym->argList[i]->symbolType == A_STRING && p->attribute.attrType == A_CONST_STRING)){
			ErrMsg msg;
			msg.lineno = p->lineno;
			msg.column = p->column;
			msg.msg = "Wrong type of argument";
			errMsg.push_back(msg);
			flag = 1;
		}
		p = p->rightSibling;
	}
	if (p){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = "Wrong number of arguments";
		errMsg.push_back(msg);
		return false;
	}
	if (flag == 1) return false;
	
	return true;
}

bool computeStmtFactorRecord(YYSTYPE & root)
{
	SymbolItem *sym = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
	if (sym == nullptr){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
		errMsg.push_back(msg);
		return false;
	}
	if (sym->symbolType != A_RECORD){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("\'") + root.data.treeNode->leftChild->value.nodeId.id + "\' isn't a record";
		errMsg.push_back(msg);
		return false;
	}
	if (sym->recordDef.find(root.data.treeNode->leftChild->rightSibling->value.nodeId.id) == sym->recordDef.end()){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
		msg.column = root.data.treeNode->leftChild->rightSibling->column;
		msg.msg = string("\'") + root.data.treeNode->leftChild->rightSibling->value.nodeId.id + "\' isn't in the record";
		errMsg.push_back(msg);
		return false;
	}
	SymbolItem *t = sym->recordDef[root.data.treeNode->leftChild->rightSibling->value.nodeId.id];
	root.data.treeNode->attribute.attrType = t->symbolType;
	return true;
}

bool computeStmtFactorID(YYSTYPE & root)
{
	SymbolItem *id = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
	if (id == nullptr){
		ErrMsg msg;
		msg.lineno = root.data.treeNode->leftChild->lineno;
		msg.column = root.data.treeNode->leftChild->column;
		msg.msg = string("Unknown ID \'") + root.data.treeNode->leftChild->value.nodeId.id + "\'";
		errMsg.push_back(msg);
		return false;
	}
	root.data.treeNode->leftChild->attribute.attrName = root.data.treeNode->leftChild->value.nodeId.id;
	root.data.treeNode->leftChild->attribute.attrType = id->symbolType;
	root.data.treeNode->attribute.attrType = id->symbolType;
	root.data.treeNode->attribute.attrName = id->symbolName;
	return true;
}

SymbolItem* computeVarType(TreeNode *type){
	SymbolItem *sym = nullptr;
	switch (type->leftChild->typeValue.stmtType)
	{
	case S_SIMPLE_TYPE_DECL_SYS:
	{
		sym = new SymbolItem();
		switch (type->leftChild->leftChild->value.nodeSysTypeVal.sysTypeVal)
		{
		case TYPE_BOOLEAN: sym->symbolType = A_BOOLEAN; break;
		case TYPE_CHAR: sym->symbolType = A_CHAR; break;
		case TYPE_INTEGER: sym->symbolType = A_INTEGER; break;
		case TYPE_REAL: sym->symbolType = A_REAL; break;
		}
		break;
	}
	case S_SIMPLE_TYPE_DECL_ID:
	{
		
		SymbolItem *tmp = symtable.getFromSymtable(type->leftChild->leftChild->value.nodeId.id);
		if (tmp == nullptr || tmp->symbolType != A_TYPE)
			break;
		sym = new SymbolItem();
		memcpy(sym, tmp->typeDef, sizeof(SymbolItem));
		//*(sym->typeDef) = *(symtable.getFromSymtable(type->value.nodeId.id)->typeDef);
		break;
	}
	case S_ARRAY_TYPE_DECL:
	{
		TreeNode *index = type->leftChild->leftChild;
		int low, high;
		int ret = computeArrayIndex(index, low, high);
		if (ret == 0){
			ErrMsg msg;
			msg.lineno = type->leftChild->leftChild->lineno;
			msg.column = type->leftChild->leftChild->column;
			msg.msg = "Wrong format of array index";
			errMsg.push_back(msg);
			break;
		}
		sym = new SymbolItem();
		sym->symbolType = A_ARRAY;
		sym->beginIndex = low;
		sym->endIndex = high;
		sym->arrayItemType = computeVarType(type->leftChild->leftChild->rightSibling);
		break;
	}
	case S_RECORD_TYPE_DECL:
	{
		sym = new SymbolItem();
		sym->symbolType = A_RECORD;
		for (TreeNode *p = type->leftChild->leftChild->leftChild; p != nullptr; p = p->rightSibling)
		{

			for (TreeNode *pname = p->leftChild->leftChild; pname != nullptr; pname = pname->rightSibling)
			{
				SymbolItem *stype = computeVarType(p->leftChild->rightSibling);
				stype->symbolName = pname->leftChild->value.nodeId.id;
				sym->recordDef[pname->leftChild->value.nodeId.id] = stype;
			}
		}
		break;
	}
	default:
	{
		ErrMsg msg;
		msg.lineno = type->lineno;
		msg.column = type->column;
		msg.msg = "Unknown type or too difficult type";
		errMsg.push_back(msg);
		break;
	}
	}
	return sym;
}

SymbolItem* computeVarSimpleType(TreeNode *type){
	SymbolItem *sym = nullptr;
	switch (type->typeValue.stmtType)
	{
	case S_SIMPLE_TYPE_DECL_SYS:
	{
		sym = new SymbolItem();
		switch (type->leftChild->value.nodeSysTypeVal.sysTypeVal)
		{
		case TYPE_BOOLEAN: sym->symbolType = A_BOOLEAN; break;
		case TYPE_CHAR: sym->symbolType = A_CHAR; break;
		case TYPE_INTEGER: sym->symbolType = A_INTEGER; break;
		case TYPE_REAL: sym->symbolType = A_REAL; break;
		}
		break;
	}
	case S_SIMPLE_TYPE_DECL_ID:
	{

		SymbolItem *tmp = symtable.getFromSymtable(type->leftChild->value.nodeId.id);
		if (tmp == nullptr || tmp->symbolType != A_TYPE)
			break;
		sym = new SymbolItem();
		memcpy(sym, tmp->typeDef, sizeof(SymbolItem));
		//*(sym->typeDef) = *(symtable.getFromSymtable(type->value.nodeId.id)->typeDef);
		break;
	}
	
	default:
	{
		ErrMsg msg;
		msg.lineno = type->lineno;
		msg.column = type->column;
		msg.msg = "Unknown type or too difficult type";
		errMsg.push_back(msg);
		break;
	}
	}
	return sym;
}

SymbolItem* computeType(TreeNode *type){
	SymbolItem *sym = nullptr;
	switch(type->leftChild->typeValue.stmtType)
	{
		case S_SIMPLE_TYPE_DECL_SYS:
		{
			sym = new SymbolItem();
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			switch(type->leftChild->leftChild->value.nodeSysTypeVal.sysTypeVal)
			{
			case TYPE_BOOLEAN: sym->typeDef->symbolType = A_BOOLEAN; break;
			case TYPE_CHAR: sym->typeDef->symbolType = A_CHAR; break;
			case TYPE_INTEGER: sym->typeDef->symbolType = A_INTEGER; break;
			case TYPE_REAL: sym->typeDef->symbolType = A_REAL; break;
			}
			break;
		}
		case S_SIMPLE_TYPE_DECL_ID:
		{
			
			SymbolItem *tmp = symtable.getFromSymtable(type->leftChild->leftChild->value.nodeId.id);
			if (tmp == nullptr || tmp->symbolType != A_TYPE)
				break;
			sym = new SymbolItem();
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			memcpy(sym->typeDef, tmp->typeDef, sizeof(SymbolItem));
			//*(sym->typeDef) = *(symtable.getFromSymtable(type->value.nodeId.id)->typeDef);
			break;
		}
		case S_ARRAY_TYPE_DECL:
		{
			TreeNode *index = type->leftChild->leftChild;
			int low, high;
			int ret = computeArrayIndex(index, low, high);
			if (ret == 0){
				ErrMsg msg;
				msg.lineno = type->leftChild->leftChild->lineno;
				msg.column = type->leftChild->leftChild->column;
				msg.msg = "Wrong format of array index";
				errMsg.push_back(msg);
				break;
			}
			sym = new SymbolItem();
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			sym->typeDef->symbolType = A_ARRAY;
			sym->typeDef->beginIndex = low;
			sym->typeDef->endIndex = high;
			sym->typeDef->arrayItemType = computeVarType(type->leftChild->leftChild->rightSibling);
			break;
		}
		case S_RECORD_TYPE_DECL:
		{
			sym = new SymbolItem();
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			sym->typeDef->symbolType = A_RECORD;
			for(TreeNode *p = type->leftChild->leftChild->leftChild; p != nullptr; p = p->rightSibling)
			{
				
				for(TreeNode *pname = p->leftChild->leftChild; pname != nullptr; pname = pname->rightSibling)
				{
					SymbolItem *stype = computeVarType(p->leftChild->rightSibling);
					stype->symbolName = pname->leftChild->value.nodeId.id;
					sym->typeDef->recordDef[pname->leftChild->value.nodeId.id] = stype;
				}
			}
			break;
		}
		default:
		{
			ErrMsg msg;
			msg.lineno = type->lineno;
			msg.column = type->column;
			msg.msg = "Unknown type or too difficult type";
			errMsg.push_back(msg);
			break;
		}
	}
	return sym;
}
 
int computeConstValue(TreeNode *constValue, int &res){
	switch (constValue->typeValue.stmtType){
	case S_CONST_VALUE_INT:{
		res = constValue->leftChild->value.nodeInteger.i;
		return 1;
	}
	case S_CONST_VALUE_SYS_CON:{
		if (constValue->value.nodeSysConVal.sysConVal == CON_MAXINT){
			res = 0x7fffffff;
			return 1;
		}
	}
	}
	return 0;
}

int computeConstId(TreeNode *constId, int &res){
	SymbolItem *id = symtable.getFromSymtable(constId->value.nodeId.id);
	if (id == nullptr){
		ErrMsg msg;
		msg.lineno = constId->lineno;
		msg.column = constId->column;
		msg.msg = string("Unknown ID \'") + constId->value.nodeId.id + "\'";
		errMsg.push_back(msg);
		return 0;
	}
	if (id->symbolType != A_CONST_INTEGER) return 0;
	res = id->constValue.i;
	return 1;
}

int computeArrayIndex(TreeNode *index, int &low, int &high){
	if (index->leftChild->rightSibling == nullptr)
		return 0;
	switch (index->typeValue.stmtType){
	case S_SIMPLE_TYPE_DECL_CDC:{
		int ret = computeConstValue(index->leftChild, low);
		if (ret == 0) return 0;
		ret = computeConstValue(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		if (low > high) return 0;
		break;
	}
	case S_SIMPLE_TYPE_DECL_MCDC:{
		int ret = computeConstValue(index->leftChild, low);
		if (ret == 0) return 0;
		low = -low;
		ret = computeConstValue(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		if (low > high) return 0;
		break;
	}
	case S_SIMPLE_TYPE_DECL_MCDMC:{
		int ret = computeConstValue(index->leftChild, low);
		if (ret == 0) return 0;
		low = -low;
		ret = computeConstValue(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		high = -high;
		if (low > high) return 0;
		break;
	}
	case S_SIMPLE_TYPE_DECL_IDI:{
		int ret = computeConstId(index->leftChild, low);
		if (ret == 0) return 0;
		ret = computeConstId(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		if (low > high) return 0;
		break;
	}
	case S_SIMPLE_TYPE_DECL_CDI:{
		int ret = computeConstValue(index->leftChild, low);
		if (ret == 0) return 0;
		ret = computeConstId(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		if (low > high) return 0;
		break;
	}
	case S_SIMPLE_TYPE_DECL_IDC:{
		int ret = computeConstId(index->leftChild, low);
		if (ret == 0) return 0;
		ret = computeConstValue(index->leftChild->rightSibling, high);
		if (ret == 0) return 0;
		if (low > high) return 0;
		break;
	}
	}
	return 1;
}

bool testType(AttrType a, AttrType b){
	if (a == b) return true;
	if (a == A_INTEGER && b == A_CONST_INTEGER) return true;
	if (a == A_REAL && b == A_CONST_REAL) return true;
	if (a == A_CHAR && b == A_CONST_CHAR) return true;
	if (a == A_STRING && b == A_CONST_STRING) return true;
	return false;
}

void showErrMsg()
{
	for (int i = 0; i < errMsg.size(); ++i)
	{
		cout << "[" << i + 1 << "]\t";
		cout << "line " << errMsg[i].lineno << ", column " << errMsg[i].column << ": ";
		cout << errMsg[i].msg << endl;
	}
}
