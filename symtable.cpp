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
	//Debug("EnterNewScope");
	map<string, SymbolItem* > *tMap = new map<string, SymbolItem* >;
	tMap->clear();
	table.push_back(tMap);
}

void Symtable::leaveScope() {
	/*map<string, SymbolItem* >::iterator iter;
	map<string, SymbolItem* > *tMap = table[table.size() - 1];
	for (iter = tMap->begin(); iter != tMap->end(); iter++) {
	delete iter->second;
	}
	delete tMap;*/
	string name = getUniqueName(table.size() - 1);
	map<string, SymbolItem*> *tMap = table.back();
	savedTable.saveATable(name, tMap);
	if (table.size() > 1)
	{
		string parentFuncName = getUniqueName(table.size() - 2);
		savedTable.saveTheParent(name, parentFuncName);
	}
	table.pop_back();
	funcName.pop_back();
}

int Symtable::addIntoSymtable(SymbolItem* sym) {
	map<string, SymbolItem* >::iterator iter;
	map<string, SymbolItem* > *tMap = table[table.size() - 1];
	if ((iter = tMap->find(sym->symbolName)) == tMap->end()) {
		tMap->insert(make_pair(sym->symbolName, sym));
	}
	else {
		Debug("the symbol has existed.");
		return 0;
	}
	return 1;
}

SymbolItem* Symtable::getFromSymtable(string symbolName) {
	for (int i = table.size() - 1; i >= 0; i--) {
		map<string, SymbolItem* > *tMap = table[i];
		if (tMap->find(symbolName) != tMap->end())
			return tMap->find(symbolName)->second;
	}
	return nullptr;
}

void Symtable::showCurrentTable() {
	Debug("Show Current Table");
	map<string, SymbolItem*> *tMap = table[table.size() - 1];
	map<string, SymbolItem*>::iterator iter;
	for (iter = tMap->begin(); iter != tMap->end(); iter++) {
		string res = iter->first;
		res += " : ";
		Debug(res);
		Debug(iter->second->symbolType);
	}
}

string Symtable::getUniqueName(int index)
{
	string name;
	if (index >= table.size())
	{
		Debug("ERROR: index out of the table!\n");
		return name;
	}
	for (int i = 0; i < index; i++)
		name += funcName[i] + "/";
	return name;
}

string Symtable::getAUniqueFuncName(string funcName)
{
	string name;
	for (int i = table.size() - 1; i >= 0; i--)
	{

		if ((*table[i]).find(funcName) != (*table[i]).end())
			name = getUniqueName(i);
	}
	return name;
}

void Symtable::setFuncName(string name)
{
	funcName.push_back(name);
}

map<string, SymbolItem*>* Symtable::getAllGlobal()
{
	return table[0];
}