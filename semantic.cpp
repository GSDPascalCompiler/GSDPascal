#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "semantic.h"
using namespace std;

bool checkTypes(SymbolItem* t1, SymbolItem* t2) {
  if (t1 == nullptr || t2 == nullptr)
	  return false;
  if (t1->symbolType != t2->symbolType)
	  return false;
  else {
	  if (t1->symbolType == T_ARRAY) {
		  return checkArrayTypes(t1, t2);
	  }
	  else if (t1->symbolType == T_RECORD) {
		  return checkRecordTypes(t1, t2);
	  }
  }
  return true;
}

bool checkArrayTypes(SymbolItem* t1, SymbolItem *t2) {
	if (t1->beginIndex != t2->beginIndex) {
		return false;
	}
	if (t1->endIndex != t2->endIndex) {
		return false;
	}
	return checkTypes(t1->arrayItemType, t2->arrayItemType);
}

bool checkRecordTypes(SymbolItem* t1, SymbolItem* t2) {
	if (t1->recordDef.size() != t2->recordDef.size()) {
		return false;
	}
	map<string, SymbolItem*>::iterator iter;
	for (auto field : t1->recordDef) {
		iter = t2->recordDef.find(field.first);
		if (iter == t2->recordDef.end())
			return false;
		if (!checkTypes(field.second, iter->second))
			return false;
	}
	return true;
}
