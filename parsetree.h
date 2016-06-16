#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>
#include <iostream>
#include <exception>
#include <initializer_list>
using namespace std;

TreeNode *newALeafNode(YYSTYPE &child);

YYSTYPE newTreeNode(const std::initializer_list<YYSTYPE> &children, \
                    const NodeType nodeType, \
                    const StmtType stmtType, \
                    const ExpType expType);
YYSTYPE linkTreeNode(YYSTYPE &parent, YYSTYPE &sibling);

bool computeAttrGrammar(YYSTYPE &root);

bool computeStmt(YYSTYPE &root);

bool computeExp(YYSTYPE &root);

bool computeToken(YYSTYPE &root);

//Statment Call
bool computeStmtCase(YYSTYPE &root);
bool computeStmtCaseExprList(YYSTYPE &root);
bool computeStmtCaseExprId(YYSTYPE &root);
bool computeStmtCase
#endif
