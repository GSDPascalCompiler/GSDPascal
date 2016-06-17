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
	savedTable[name] = table;
}

void SavedTable::saveTheParent(string name, string parent)
{
	parentNameMap[name] = parent;
}

