#include "parsetree.h"

using namespace std;

TreeNode *integerNodeInit(YYSTYPE arg1)
{
  TreeNode *treeNode=new TreeNode;
  treeNode.value
}

TreeNode *realNodeInit(YYSTYPE arg1)
{

}

TreeNode *charNodeInit(YYSTYPE arg1)
{

}

TreeNode *stringNodeInit(YYSTYPE arg1)
{

}

void treeNodeInit(TreeNode* treeNode, int childNum)
{
  try
  {
    for(int i=0;i<MAX_CHILD_NUM;i++)
    {
      if(i<childNum)
        treeNode->value.nodeNonleaf.child[i] = new TreeNode;
      else
        treeNode->value.nodeNonleaf.child[i] = nullptr;
    }
  }
  catch(Exception &e)
  {
    throw(e);
  }
}

/*Non terminal nodes*/
/*Create a new program node*/
YYSTYPE newProgramNode(const YYSTYPE &arg1, const YYSTYPE &arg2)
{
  YYSTYPE newNode;
  TreeNode *programNode = new TreeNode;
  programNode->nodeType = NODE_STMT;
  programNode->typeValue.stmtType = S_PROGRAM;

  try
  {
    treeNodeInit(programNode, 2);
  }
  catch(Exception &e)
  {
    throw(e);
  }
  programNode->value.nodeNonleaf.child[0] = arg1.data.treeNode;
  programNode->value.nodeNonleaf.child[1] = arg2.data.treeNode;
  newNode.lineno = arg1.lineno;
  newNode.column = arg1.column;
  newNode.data.treeNode = programNode;

  return newNode;
}

/*Create a new program_head node*/
YYSTYPE newProgramHeadNode(YYSTYPE arg1)
{
  YYSTYPE newNode;
  TreeNode *programHeadNode = new TreeNode;
  programHeadNode->nodeType=NODE_TOKEN;
  programHeadNode->typeValue.tokenType=T_ID;
  strcpy(programHeadNode->value.nodeId.id,id);
  newNode.data.treeNode=programHeadNode;
  newNode.lineno=arg1.lineno;
  newNode.lineno=arg1.column;
  return newNode;
}
/*Create a new const_value node*/
YYSTYPE newConstValueNode(YYSTYPE arg1)
{
  YYSTYPE newNode;
  TreeNode *constValueNode = new TreeNode;
  constValueNode->nodeType=NODE_TOKEN;
  constValueNode->typeValue.tokenTyoe=T_INTEGER;
  constValueNode->value.nodeInteger.i=arg1.data.i;
  newNode.data.treeNode=constValueNode;
  newNode.lineno=arg1.lineno;
  newNode.column=arg1.column;
  return newNode;
}
/*Create a new goto_stmt node*/
YYSTYPE newGoToStmtNode(YYSTYPE arg1)
{
  YYSTYPE newNode;
  TreeNode *treeNode = new TreeNode;
  treeNode->nodeType = NODE_STMT;
  treeNode->typeValue.stmtType = S_GOTO;

  try
  {
    treeNodeInit(treeNode, 2);
  }
  catch(Exception &e)
  {
    throw(e);
  }

  treeNode->value.nodeNonleaf.child[0] = arg1.data.treeNode;
  treeNode->value.nodeNonleaf.child[1] = arg2.data.treeNode;
  newNode.lineno = arg1.lineno;
  newNode.column = arg1.column;
  newNode.data.treeNode = treeNode;

  return newNode;
}
