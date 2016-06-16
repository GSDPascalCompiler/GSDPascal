#include "parsetree.h"

using namespace std;

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
		1 +1;
	//now p is the last sibling
	p->rightSibling = sibling.data.treeNode;
	return parent;
}

bool computeAttrGrammar(YYSTYPE &root)
{
  switch(root.data.treeNode->nodeType){
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
	case 1:;
	}
	return true;
}

bool computeStmt(YYSTYPE &root)
{
	switch (root.data.treeNode->typeValue.stmtType) {
	case S_CASE: return computeStmtCase(root);
	case S_CASE_EXPR_LIST: return computeStmtCaseExprList(root);
	case S_CASE_EXPR_ID:return computeStmtCaseExprId(root);
	case S_FUNCTION_HEAD: return computeStmtFunctionHead(root);
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
	auto caseExprList= root.data.treeNode->leftChild;
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
	
	return false;
}

bool computeStmtCaseExprConst(YYSTYPE & root)
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
			sym->symbolType = tn->attribute.attrType;
		} else {
			if (tn->leftChild != nullptr) {
				tn = tn->leftChild;
				while (tn != nullptr) {
					dealParaDeclList(tn->leftChild, sym);
					tn = tn->rightSibling;
				}
			}
		}
	}
	//symtable.addIntoSymtable();
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
SymbolItem* dealSimpleTypeDecl(TreeNode* tn) {

}

vector<string> dealNameList(TreeNode* tn, vector<string> vec) {
	
	while (tn != nullptr) {
		dealName(tn->leftChild, vec);
		tn = tn->rightSibling;
	}
}

void dealName(TreeNode* tn, vector<string> vec) {
	dealId(tn->leftChild, vec);
}

void dealId(TreeNode* tn, vector<string> vec) {
	vec.push_back(tn->value.nodeId.id);
}

