#include <vector>
#include <string>
#include <iostream>
#include "symtable.h"
using namespace std;

Symtable symtable;

void Symtable::clear() {
	table.clear();
}

void Symtable::enterNewScope() {
	map<string, SymbolItem* > *tMap = new map<string, SymbolItem* >;
	tMap->clear();
	table.push_back(tMap);
}

void Symtable::leaveScope() {
	map<string, SymbolItem* >::iterator iter;
	map<string, SymbolItem* > *tMap = table[table.size() - 1];
	for (iter = tMap->begin(); iter != tMap->end(); iter++) {
		delete iter->second;
	}
	delete tMap;
	table.pop_back();
}

void Symtable::addIntoSymtable(SymbolItem* sym) {
	map<string, SymbolItem* >::iterator iter;
	map<string, SymbolItem* > *tMap = table[table.size() - 1];
	if ((iter = tMap->find(sym->symbolName)) == tMap->end()) {
		tMap->insert(make_pair(sym->symbolName, sym));
	} else {
		Debug("the symbol has existed.");
	}
}

SymbolItem* Symtable::getFromSymtable(string symbolName) {
	for (int i = table.size() - 1; i >= 0; i--) {
		map<string, SymbolItem* > *tMap = table[i];
		if (tMap->find(symbolName) != tMap->end())
			return tMap->find(symbolName)->second;
	}
	return nullptr;
}