#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include "global.h"

typedef SymbolItem Sym;

class Symtable {
	map<string, vector<Sym> > table;
public:
	Symtable() {
		table.clear();
	}
	void addIntoSymtable(Sym);
	Sym *getSymFromSymtable(string);
	void removeSymFromSymtable(string);
};

extern Symtable symtable;

#endif
