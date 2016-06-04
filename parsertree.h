#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>
#include <exception>


void treeNodeInit(TreeNode* treeNode, int childNum);

TreeNode *integerNodeInit(int value);

TreeNode *realNodeInit(double value);

TreeNode *charNodeInit(char value);

TreeNode *stringNodeInit(char* value);


/*Non terminal nodes*/
/*Create a new program node*/
YYSTYPE newProgramNode(YYSTYPE arg1, YYSTYPE arg2);
/*Create a new program_head node*/
YYSTYPE newProgramHeadNode(YYSTYPE arg1);
/*Create a new const_value node*/
YYSTYPE newConstValueNode(YYSTYPE arg1);

//Kuan Lu Part
/*Create a new goto_stmt node*/
YYSTYPE newGoToStmtNode(YYSTYPE arg1);
#endif
