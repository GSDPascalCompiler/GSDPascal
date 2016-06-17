#include "savedTable.h"

SavedTable savedTable;

SavedTable::SavedTable()
{
}

SavedTable::~SavedTable()
{
}

void SavedTable::saveATable(string name, map<string, SymbolItem*> *table)
{
	staticSymtable[name] = table;
}

void SavedTable::saveTheParent(string name, string parent)
{
	parentNameMap[name] = parent;
}

bool SavedTable::isGlobal(string funcName, string varName)
{
	return true;
}