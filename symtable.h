#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include "global.h"
#include <vector>

class Symtable {
private:
	vector<map<string, SymbolItem*>*> table;
public:
	void clear();
	void enterNewScope();
	void leaveScope();
	void addIntoSymtable(SymbolItem*);
	SymbolItem* getFromSymtable(string);
	void showCurrentTable();
	void setFuncName(string name);
	string getAUniqueFuncName(string funcName);
};
#endif
