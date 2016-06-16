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
  switch(root.tokenType){
    case NODE_TOKEN: return computeToken(root);
    case NODE_EXP: return computeExp(root); 
    case NODE_STMT: return computeStmt(root); 
    default: return false;
  }
}

bool computeToken(YYSTYPE &root)
{
}

bool computeExp(YYSTYPE &root)
{
  switch(root.data.treeNode->typeValue.expType){
    case
  }
}

bool computeStmt(YYSTYPE &root)
{
  switch(root.data.treeNode->typeValue.stmtType)
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
	  
	

	  
  }
}
