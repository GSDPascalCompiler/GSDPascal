#ifndef _SAVEDTABLE_H_
#define _SAVEDTABLE_H_

#include "symtable.h"

class SavedTable
{
private:
	map<string, map<string, SymbolItem*>*> staticSymtable;
	map<string, string> parentNameMap;
public:
	SavedTable();
	~SavedTable();
	void saveATable(string, map<string, SymbolItem*> *table);
	void saveTheParent(string name, string parent);
	map<string, int> getParamsOffset(string funcName);
	bool isGlobal(string funcName, string varName);
};

extern Symtable symtable;
extern SavedTable savedTable;

#endif
