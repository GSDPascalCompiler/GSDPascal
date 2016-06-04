#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>

/*Terminal nodes*/
/*Create a new integer node*/
// TreeNode *newIntegerNode(int value)
// {
//   TreeNode *integerNode = new TreeNode;
//   integerNode->nodeType = NODE_TOKEN;
//   integerNode->typeValue.tokenType = N_INTEGER;
//   integerNode->value.nodeInteger.i = value;
//   return integerNode;
// }
//
// /*Create a new real node*/
// TreeNode *newRealNode(double value)
// {
//   TreeNode *realNode = new TreeNode;
//   realNode->nodeType = NODE_TOKEN;
//   realNode->typeValue.tokenType = N_REAL;
//   realNode->value.nodeReal.r = value;
//   return readlNode;
// }
//
// /*Create a new char node*/
// TreeNode *newCharNode(char value)
// {
//   TreeNode *charNode = new TreeNode;
//   charNode->nodeType = NODE_TOKEN;
//   charNode->typeValue.tokenType = N_REAL;
//   charNode->value.nodeChar.c = value;
//   return charNode;
// }
//
// /*Create a new string node*/
// TreeNode *newStringNode(char *value)
// {
//   TreeNode *stringNode = new TreeNode;
//   stringNode->nodeType = NODE_TOKEN;
//   stringNode->typeValue.tokenType = N_STRING;
//   strcpy(stringNode->value.nodeString.s, value);
//   return stringNode;
// }
//
// /*Create a new id node*/
// TreeNode *newIdNode(char *value)
// {
//   TreeNode *idNode = new TreeNode;
//   idNode->nodeType = NODE_TOKEN;
//   idNode->typeValue.tokenType = N_ID;
//   strcpy(idNode->value.nodeId.id, value);
//   return idNode;
// }

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
TreeNode *newProgramHeadNode(YYSTYPE arg1)
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

#endif
