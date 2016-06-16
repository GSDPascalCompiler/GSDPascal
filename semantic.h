#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "global.h"

bool checkArrayTypes(SymbolItem* t1, SymbolItem *t2);
bool checkRecordTypes(SymbolItem* t1, SymbolItem* t2);
bool checkTypes(SymbolItem* t1, SymbolItem* t2);

#endif 