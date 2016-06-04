#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>

/*Non terminal nodes*/
/*Create a new program node*/
TreeNode *newProgramNode(TreeNode *program_head, TreeNode *routine)
{
  TreeNode *programNode = new TreeNode;
  programNode->nodeType = NODE_STMT;
  programNode->typeValue.stmtType = S_PROGRAM;
  programNode->value.nodeNonleaf.child =  new TreeNode[2];
  programNode->value.nodeNonleaf.child[0] = program_head;
  programNode->value.nodeNonleaf.child[1] = routine;
  return programNode;
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

/*Create a new case_expr node*/
YYSTYPE newCaseExprNode(YYSTYPE arg1,YYSTYPE arg2)
{
  YYSTYPE newNode;
  TreeNode *newTreeNode = new TreeNode;
  newTreeNode->nodeType=NODE_STMT;
  newTreeNode->typeValue.stmtType=S_CASE_EXP;
  newNode.data.treeNode=newTreeNode;
  newNode.lineno=arg1.lineno;
  newNode.column=arg1.column;
  return newNode;
}

YYSTYPE newCaseExprNodeID(YYSTYPE arg1,YYSTYPE arg2)
{
  YYSTYPE newNode;
  TreeNode *newTreeNode = new TreeNode;
  newTreeNode->nodeType=NODE_STMT;
  newTreeNode->typeValue.stmtType=S_CASE_EXP;
  newNode.data.treeNode=newTreeNode;
  newNode.lineno=arg1.lineno;
  newNode.column=arg1.column;
  TreeNode *leftTreeNode = new TreeNode;

  leftTreeNode->nodeType=NODE_TOKEN;
  leftTreeNode->typeValue.tokenType=T_ID;
  strcpy(leftTreeNode->data.s,arg1.data.s);

  newTreeNode->value.nodeNonleaf.child=new (TreeNode *)[2];
  newTreeNode->value.nodeNonleaf.child[0]=leftTreeNode;
  newTreeNode->value.nodeNonleaf.child[1]=rightTreeNode;
  return newNode;
}

#endif
