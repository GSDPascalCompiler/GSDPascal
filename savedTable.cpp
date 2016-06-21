#include "savedTable.h"
#include <iostream>

using namespace std;

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
	//while (staticSymtable.find(funcName) != staticSymtable.end()) {
	//	if (staticSymtable[funcName]->find(varName) != staticSymtable[funcName]->end()) {
	//		if (funcName == "main/")
	//			return true;
	//		else
	//			return false;
	//	}
	//	else {
	//		funcName = parentNameMap[funcName];
	//	}
	//}
	//return false;
	return false;
}

void print(AttrType type)
{
	switch (type)
	{
	case A_VOID:	cout << "void";		break;
	case A_BOOLEAN: cout << "bool";		break;
	case A_INTEGER: cout << "integer";	break;
	case A_CHAR:	cout << "char";		break;
	case A_REAL:	cout << "real";		break;
	case A_STRING:  cout << "string";	break;
	default: break;
	}
}

void printSymItem(SymbolItem * item)
{
	//cout << item->symbolName << ": ";
	switch (item->symbolType)
	{
	case A_VOID:
	case A_BOOLEAN:
	case A_INTEGER: 
	case A_CHAR:
	case A_REAL:
	case A_STRING:
		print(item->symbolType);
		break;
	case A_ARRAY: 
		cout << "Array";
		//cout << "from " << item->arrayItemType->beginIndex << " to" << item->arrayItemType->endIndex;
		cout << " of ";	
		printSymItem(item->arrayItemType);
		break;
	case A_TYPE:
		printSymItem(item->typeDef);
		break;
	case A_RECORD:	
		cout << "Record" << endl;
		break;
	case A_FUNC:
		cout << "function return with ";
		printSymItem(item->returnType);
		break;
	default:
		break;
	}
}
void SavedTable::showAllTable()
{
	for (auto m : staticSymtable)
	{
		cout << "---------------------------------------------" << endl;
		cout << "In function " << m.first << ":" << endl;
		auto v = *m.second;
		for (auto v : *m.second)
		{
			cout << v.first << ": ";
			printSymItem(v.second);
			cout << endl;
		}
		cout << "------------------------------------------" << endl;
		cout << endl;
	}
}