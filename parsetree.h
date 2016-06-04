#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include <string.h>
#include <exception>
#include <initializer_list>

YYSTYPE newTreeNode(const std::initialzer_list<YYSTYPE> &children,
                    const NodeType &nodeType,
                    const StmtType &stmtType,
                    const ExpType &expType);
#endif
