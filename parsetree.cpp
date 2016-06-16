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
  switch(root.data.treeNode->typeValue.stmtType){
    case S_PROGRAM_HEAD:
    {
    	SymbolItem *sym = new SymbolItem();
    	sym->symbolType = T_VOID;
    	sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
    	sym->leftable = false;
    	symtable.addIntoSymtable(sym);
    	break;
    }
    case S_CONST_EXPR: //need modify
    {
    	SymbolItem *sym = new SymbolItem();
    	switch(root.data.treeNode->leftChild->rightSibling.typeValue.stmtType)
    	{
    		case S_CONST_VALUE_INT: sym->symbolType = T_INTEGER; break;
    		case S_CONST_VALUE_REAL: sym->symbolType = T_REAL; break;
    		case S_CONST_VALUE_CHAR: sym->symbolType = T_CHAR; break;
    		case S_CONST_VALUE_STRING: sym->symbolType = T_STRING; break;
    		case S_CONST_VALUE_SYS_CON: sym->symbolType = T_CONST; break;
    	}
    	sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
    	sym->leftable = false;
    	symtable.addIntoSymtable(sym);
    	break;
    }
    case S_TYPE_DEFINITION:
    {
    	SymbolItem *sym = computeType(root.data.treeNode->leftChild->rightSibling->leftChild);
    	sym->symbolName = root.data.treeNode->leftChild->value.nodeId.id;
    	sym->leftable = false;
    	symtable.addIntoSymtable(sym);
    	break;
    }
    case S_VAR_DECL:
    {
    	TreeNode *nameList = root.data.treeNode->leftChild;
    	for(TreeNode *p = namelist->leftChild; p != nullptr; p = p->rightSibling)
    	{
    		SymbolItem *sym = computeType(namelist->rightSibling);
    		sym->symbolName = p->leftChild->value.nodeId.id;
    		sym->leftable = true;
    		symtable.addIntoSymtable(sym);
    	}
    	break;
    }
  }
}

SymbolItem* computeType(TreeNode *type){
	SymbolItem *sym = new SymbolItem();
	switch(type->leftChild->typeValue.stmtType)
	{
		case S_SIMPLE_TYPE_DECL_SYS:
		{
			switch(type->leftChild.value.nodeSysTypeVal.sysTypeVal)
			{
				case TYPE_BOOLEAN: sym->symbolType = A_BOOLEAN; break;
				case TYPE_CHAR: sym->symbolTYpe = A_CHAR; break;
				case TYPE_INTEGER: sym->symbolType = A_INTEGER; break;
				case TYPE_REAL: sym->symbolType = A_REAL; break;
			}
			break;
		}
		case S_SIMPLE_TYPE_DECL_ID:
		{
			sym->symbolType = A_TYPE;
			sym->typeDef = new SymbolItem();
			*(sym->typeDef) = *(symtable.getSymFromSymtable(type->value.nodeId.id)->typeDef);
			break;
		}
		case S_ARRAY_TYPE_DECL:
		{
			sym->symbolType = A_ARRAY;
			sym->arrayItemType = computeType(type->leftChild->leftChild->rightSibling);
		}
		case S_RECORD_TYPE_DECL:
		{
			sym->symbolType = A_RECORD;
			for(TreeNode *p = type->leftChild->leftChild->leftChild; p != nullptr; p = p->rightSibling)
			{
				
				for(TreeNode *pname = p->leftChild->leftChild; pname != nullptr; pname = pname->rightSibling)
				{
					SymbolItem *stype = computeType(p->leftChild->rightSibling);
					stype->symbolName = pname->leftChild.value.nodeId.id;
					sym->recordDef[pname->leftChild.value.nodeId.id] = stype;
				}
			}
			break;
		}
	}
	return sym;
}