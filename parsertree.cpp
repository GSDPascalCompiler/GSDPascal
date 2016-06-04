#include "parsetree.h"

using namespace std;

YYSTYPE newTreeNode(const initialzer_list<YYSTYPE> &children,
                    const NodeType &nodeType,
                    const StmtType &stmtType,
                    const ExpType &expType)
{
  YYSTYPE newNode;
  TreeNode *treeNode = new TreeNode;
  treeNode->nodeType =nodeType;
  if(nodeType == NODE_STMT)
    treeNode->typeValue.stmtType = stmtType;
  if(nodeType == NODE_EXP)
    treeNode->typeValue.expType = expType;

  for(int i=0;i<MAX_CHILD_NUM;++i)
      treeNode->value.nodeNonleaf.child[i] = nullptr;

  int i=0;
  for(auto child : children)
  {
    if(tokenType == T_NONLEAF)
      treeNode->value.nodeNonleaf.child[i] = child.data.treeNode;
    else
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
          strcpy(childTreeNode->value.nodeId.s, child.data.s);
          break;
        case T_SYS_CON:
          childTreeNode->value.nodeSysConVal = child.data.sysConVal;
          break;
        case T_SYS_FUNCT:
          childTreeNode->value.nodeSysFunctVal = child.data.sysFunctVal;
          break;
        case T_SYS_PROC:
          childTreeNode->value.nodeSysProcVal = child.data.sysProcVal;
          break;
        case T_SYS_TYPE:
          childTreeNode->value.nodeSysTypeVal = child.data.sysTypeVal;
          break;
        default:
          ;
      }
      treeNode->value.nodeNonleaf.child[i] = childTreeNode;
    }
    ++i;
  }

  return newNode;
}
