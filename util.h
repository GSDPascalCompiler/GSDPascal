#ifndef _UTIL_H_
#define _UTIL_H_
#include "global.h"
#include <stdio.h>

void printTreeNodes(TreeNode *root, int level);

int getInteger(TreeNode* treenode);

double getDouble(TreeNode* treenode);

char getChar(TreeNode* treenode);

std::string getStr(TreeNode* treenode);

std::string getID(TreeNode* treenode);

AttrType getAttrType(TreeNode* treenode);

string getAttrName(TreeNode* treenode);

TreeNode* getNthChild(const YYSTYPE &root, int n);

#endif
