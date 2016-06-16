#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include "symtable.h"
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


extern Symtable symtable;

bool computeAttrGrammar(YYSTYPE &root);

bool computeStmt(YYSTYPE &root);

bool computeExp(YYSTYPE &root);

bool computeToken(YYSTYPE &root);

//Statment Call
bool computeStmtCase(YYSTYPE &root);
bool computeStmtCaseExprList(YYSTYPE &root);
bool computeStmtCaseExprId(YYSTYPE &root);
bool computeStmtCaseExprConst(YYSTYPE &root);
bool computeStmtExpressionList(YYSTYPE &root);
bool computeStmtExpressionCompare(YYSTYPE &root);
bool computeStmtExpressionArithmetic(YYSTYPE &root);
bool computeStmtFactorSysFunct(YYSTYPE &root);
bool computeStmtAssignToParent(YYSTYPE &root);
bool computeStmtFactorArray(YYSTYPE &root);
bool computeStmtFactorFunc(YYSTYPE &root);
bool computeStmtFactorRecord(YYSTYPE &root);
bool computeStmtFactorID(YYSTYPE &root);

#endif
