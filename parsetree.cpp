#include "parsetree.h"
#include <algorithm>
#include <iterator>
using namespace std;
struct ErrMsg{
	int lineno;
	int column;
	string msg;
};
vector<ErrMsg> errMsg;
SymbolItem *procFunc;
int getInteger(TreeNode* treenode)
{
	return treenode->value.nodeInteger.i;
}

double getDouble(TreeNode* treenode)
{
	return treenode->value.nodeReal.r;
}

char getChar(TreeNode* treenode)
{
	return treenode->value.nodeChar.c;
}
std::string getStr(TreeNode* treenode)
{
	return std::string(treenode->value.nodeString.s);
}
std::string getID(TreeNode* treenode)
{
	return std::string(treenode->value.nodeId.id);
}

TreeNode* getNthChild(const YYSTYPE &root, int n)
{
	TreeNode* p = root.data.treeNode;
	if (n == 0);
	else
	{
		p = p->leftChild;
		while (--n)
			p = p->rightSibling;
	}
	return p;
}

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
	case E_OR:
	case E_MUL:
	case E_DIV:
	case E_MOD:
	case E_AND: return computeStmtExpressionArithmetic(root);
	}
	return true;
}

vector<SymbolItem*> args;

bool computeStmt(YYSTYPE &root)
{
	switch (root.data.treeNode->typeValue.stmtType)
	{
		case S_ASSIGN:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
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
			else if (symbolOfID->symbolType != getNthChild(root, 2)->attribute.attrType)
			{
				//TODO 
			//assign type unmatched
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->lineno;
				msg.column = root.data.treeNode->leftChild->column;
				msg.msg = "Unmatched type";
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
				//TODO 
			//unknown id
			}
			if (getNthChild(root, 2)->attribute.attrType != T_INTEGER)
			{
				//The index of array is not integer
			}
			else if (symbolOfID->arrayItemType->symbolType != getNthChild(root, 3)->attribute.attrType)
			{
				//TODO
			//assign type unmatched
			}
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
			}
			else if (symbolOfID->recordDef.find(idRecEleStr) == symbolOfID->recordDef.end())	//undefined record element
			{
				//TODO
			//record has no this element
			}
			else if (symbolOfID->recordDef[idRecEleStr]->symbolType != getNthChild(root, 3)->attribute.attrType)
			{
				//TODO
			//assign type unmatched
			}
			Debug("S_ASSIGN_RECORD type check ok");
			break;
		}
		case S_PROC:
		case S_PROC_FUNC:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
			if (symbolOfID == nullptr)	//undefined id
			{
				//TODO 
			//unknown id
			}
			Debug("S_PROC/S_PROC_FUNC type check ok");
			break;
		}
		case S_IF:
		case S_WHILE:
		{
			if (getNthChild(root, 1)->attribute.attrType != A_BOOLEAN)
			{
				//unmatch type
			}
			Debug("S_IF/S_WHILE type check ok");
			break;
		}
		case S_REPEAT:
		{
			if (getNthChild(root, 2)->attribute.attrType != A_BOOLEAN)
			{
				//unmatch type
			}
			Debug("S_REPEAT type check ok");
			break;
		}
		case S_FOR:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
			if (symbolOfID == nullptr)	//undefined id
			{
				//TODO 
			//unknown id
			}
			else if (symbolOfID->symbolType != getNthChild(root, 2)->attribute.attrType)
			{
				//unmatch type
			}
			else if (symbolOfID->symbolType != getNthChild(root, 4)->attribute.attrType)
			{
				//unmatch type
			}
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
				case S_CONST_VALUE_INT: sym->symbolType = A_INTEGER; break;
				case S_CONST_VALUE_REAL: sym->symbolType = A_REAL; break;
				case S_CONST_VALUE_CHAR: sym->symbolType = A_CHAR; break;
				case S_CONST_VALUE_STRING: sym->symbolType = A_STRING; break;
				case S_CONST_VALUE_SYS_CON:
				{
					switch (root.data.treeNode->leftChild->rightSibling->leftChild->value.nodeSysConVal.sysConVal)
					{
					case CON_FALSE: case CON_TRUE: sym->symbolType = A_BOOLEAN; break;
					case CON_MAXINT: sym->symbolType = A_INTEGER; break;
					case CON_PI: sym->symbolType = A_REAL; break;
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
				ErrMsg msg;
				msg.lineno = root.data.treeNode->leftChild->rightSibling->lineno;
				msg.column = root.data.treeNode->leftChild->rightSibling->column;
				msg.msg = "Unknown type";
				errMsg.push_back(msg);
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
					ErrMsg msg;
					msg.lineno = nameList->rightSibling->lineno;
					msg.column = nameList->rightSibling->column;
					msg.msg = "Unknown type";
					errMsg.push_back(msg);
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
					ErrMsg msg;
					msg.lineno = root.data.treeNode->leftChild->lineno;
					msg.column = root.data.treeNode->leftChild->column;
					msg.msg = "Unknown type or too difficult type";
					errMsg.push_back(msg);
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
				root.data.treeNode->attribute.attrType = A_INTEGER; 
				char str[256];
				sprintf(str, "%d", root.data.treeNode->leftChild->leftChild->value.nodeInteger.i);
				root.data.treeNode->leftChild->attribute.attrName = str;
				break;
			}
			case S_CONST_VALUE_REAL:
			{
				root.data.treeNode->attribute.attrType = A_REAL; 
				char str[256];
				sprintf(str, "%f", root.data.treeNode->leftChild->leftChild->value.nodeReal.r);
				root.data.treeNode->leftChild->attribute.attrName = str;
				break;
			}
			case S_CONST_VALUE_CHAR:
			{
				root.data.treeNode->attribute.attrType = A_CHAR;
				root.data.treeNode->leftChild->attribute.attrName = root.data.treeNode->leftChild->leftChild->value.nodeChar.c;
				break;
			}
			case S_CONST_VALUE_STRING:
			{
				root.data.treeNode->attribute.attrType = A_STRING;
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
			
		}
		case S_FACTOR_ARRAY:return computeStmtFactorArray(root);
		case S_FACTOR_FUNC:return computeStmtFactorFunc(root);
		case S_FACTOR_RECORD:return computeStmtFactorRecord(root);
		case S_FACTOR_ID:return computeStmtFactorID(root);
		case S_ARGS:
		case S_ARGS_NULL:
		case S_GOTO:
		case S_FACTOR_NOT:
		case S_FACTOR_MINUS:
			return computeStmtAssignToParent(root);
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
	if (caseType == A_STRING)
	{
		Debug("Invalid type in case expression");
		return false;
	}
	if (expression->rightSibling->attribute.attrType != caseType)
	{
		Debug("Type doesn't match in case expression");
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
	return false;
}

bool computeStmtFunctionHead(YYSTYPE & root)
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
	for (int i = 0; i < vec.size(); i++) {
		if (sym->recordDef.find(vec[i]) != sym->recordDef.end())
			Debug("DealValParaList: redefined");
		sym->recordDef.insert(make_pair(vec[i], s));
	}
 }

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
	if (leftOperand->attribute.attrType != rightOperand->attribute.attrType)
	{
		Debug("Left hand side operand does not match right hand side operand");
		return false;
	}
	root.data.treeNode->attribute.attrType = A_BOOLEAN;
	return true;
}

bool computeStmtExpressionArithmetic(YYSTYPE &root)
{
	auto leftOperand = root.data.treeNode->leftChild;
	auto rightOperand = root.data.treeNode->leftChild->rightSibling;
	if (leftOperand->attribute.attrType != rightOperand->attribute.attrType)
	{
		Debug("Left hand side operand does not match right hand side operand");
		return false;
	}
	root.data.treeNode->attribute.attrType = leftOperand->attribute.attrType;
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
	return true;
}

bool computeStmtFactorFunc(YYSTYPE & root)
{
	return true;
}

bool computeStmtFactorRecord(YYSTYPE & root)
{
	return true;
}

bool computeStmtFactorID(YYSTYPE & root)
{
	SymbolItem *id = symtable.getFromSymtable(root.data.treeNode->leftChild->value.nodeId.id);
	if (id == nullptr){
		Debug("id not found");
		return false;
	}
	root.data.treeNode->leftChild->attribute.attrName = root.data.treeNode->leftChild->value.nodeId.id;
	root.data.treeNode->leftChild->attribute.attrType = id->symbolType;
	root.data.treeNode->attribute.attrType = id->symbolType;
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
		sym = new SymbolItem();
		sym->symbolType = A_ARRAY;
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
	/*case S_ARRAY_TYPE_DECL:
	{
		sym = new SymbolItem();
		sym->symbolType = A_ARRAY;
		sym->arrayItemType = computeVarType(type->leftChild->rightSibling);
		break;
	}
	case S_RECORD_TYPE_DECL:
	{
		sym = new SymbolItem();
		sym->symbolType = A_RECORD;
		for (TreeNode *p = type->leftChild->leftChild; p != nullptr; p = p->rightSibling)
		{

			for (TreeNode *pname = p->leftChild->leftChild; pname != nullptr; pname = pname->rightSibling)
			{
				SymbolItem *stype = computeVarType(p->leftChild->rightSibling);
				stype->symbolName = pname->leftChild->value.nodeId.id;
				sym->recordDef[pname->leftChild->value.nodeId.id] = stype;
			}
		}
		break;
	}*/
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
			sym = new SymbolItem();
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			sym->typeDef->symbolType = A_ARRAY;
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
	}
	return sym;
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