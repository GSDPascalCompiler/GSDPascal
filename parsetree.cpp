#include "parsetree.h"

using namespace std;

TreeNode *newALeafNode(YYSTYPE &child)
{
	TreeNode *childTreeNode = new TreeNode;
	childTreeNode->nodeType = NODE_TOKEN;
	childTreeNode->typeValue.tokenType = child.tokenType;
	childTreeNode->lineno = child.lineno;
	childTreeNode->column = child.column;
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

	for (int i = 0; i < MAX_CHILD_NUM; ++i)
	{
		treeNode->value.nodeNonleaf.leftChild = nullptr;
		treeNode->value.nodeNonleaf.rightSibling = nullptr;
	}

	int i = 0;
	for (auto child : children)
	{
		//first child, insert into the child
		if (i == 0)
		{
			if (child.tokenType == T_NONLEAF)
				treeNode->value.nodeNonleaf.leftChild = child.data.treeNode;
			else
				treeNode->value.nodeNonleaf.leftChild = newALeafNode(child);
			
		}
		else
		{
			if (child.tokenType == T_NONLEAF)
				treeNode->value.nodeNonleaf.rightSibling = child.data.treeNode;
			else
				treeNode->value.nodeNonleaf.rightSibling = newALeafNode(child);
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
	if (parent.data.treeNode->value.nodeNonleaf.leftChild == nullptr)
	{
		parent.data.treeNode->value.nodeNonleaf.leftChild = sibling.data.treeNode;
		return;
	}

	TreeNode *p;
	for ( p= parent.data.treeNode->value.nodeNonleaf.leftChild; p->value.nodeNonleaf.rightSibling != nullptr;p = p->value.nodeNonleaf.rightSibling);
	//now p is the last sibling
	p->value.nodeNonleaf.rightSibling = sibling.data.treeNode;
}