#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>
#include <exception>
#include <initializer_list>
#include <iostream>
#include "symtable.h"

TreeNode *newALeafNode(YYSTYPE &child);

YYSTYPE newTreeNode(const std::initializer_list<YYSTYPE> &children, \
                    const NodeType nodeType, \
                    const StmtType stmtType, \
                    const ExpType expType);
YYSTYPE linkTreeNode(YYSTYPE &parent, YYSTYPE &sibling);

extern Symtable symtable;
#endif
