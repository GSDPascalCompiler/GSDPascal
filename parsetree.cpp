#include "parsetree.h"

using namespace std;

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
	else if (n == 1)
		p = p->leftChild;
	else
	{
		while (n--)
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

bool computeStmt(YYSTYPE &root)
{
	switch (root.data.treeNode->typeValue.stmtType)
	{
		case S_ASSIGN:
		{
			string idStr = getID(getNthChild(root, 1));
			SymbolItem* symbolOfID = symtable.getFromSymtable(idStr);
			if (symbolOfID == nullptr)
			{
				//TODO 
			//unknown id
			}
			else if (symbolOfID->symbolType != getNthChild(root, 2)->attribute.attrType)
			{
				//TODO 
			//assign type unmatched
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
		case S_CASE: return computeStmtCase(root);
		case S_CASE_EXPR_LIST: return computeStmtCaseExprList(root);
		case S_CASE_EXPR_ID:return computeStmtCaseExprId(root);
		case S_EXPRESSION_LIST:return computeStmtExpressionList(root);
		case S_FACTOR_SYS:
		case S_FACTOR_SYS_ARG:return computeStmtFactorSysFunct(root);
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
	return true;
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
	return true;
}
