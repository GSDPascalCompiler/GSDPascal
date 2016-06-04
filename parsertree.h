#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>
#include <exception>


void treeNodeInit(TreeNode* treeNode, int childNum);

/*Non terminal nodes*/
/*Create a new program node*/
TreeNode *newProgramNode(YYSTYPE arg1, YYSTYPE arg2);
/*Create a new program_head node*/
YYSTYPE newProgramHeadNode(YYSTYPE arg1);

YYSTYPE newConstValueNode(YYSTYPE arg1);
#endif
