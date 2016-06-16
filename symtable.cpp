#include <vector>
#include <string>
#include <iostream>
#include "symtable.h"
using namespace std;

Symtable symtable;

void Symtable::addIntoSymtable(Sym sym) {
  map<string, vector<Sym> >::iterator iter;
  if ((iter = table.find(sym.symbolName)) == table.end()) {
    vector<Sym> vec;
    vec.clear();
    vec.push_back(sym);
    table.insert(make_pair(sym.symbolName, vec));
  } else {
    // for (int i = 0; i < iter->second.size(); i++)
      // cout << iter->second[i].name << endl;
    iter->second.push_back(sym);
  }
}

Sym* Symtable::getSymFromSymtable(string symName) {
  map<string, vector<Sym> >::iterator iter;
  if ((iter = table.find(symName)) == table.end()) {
    return NULL;
  } else {
    if (iter->second.empty()) {
      return NULL;
    } else {
      return &(iter->second.back());
    }
  }
}

void Symtable::removeSymFromSymtable(string symName) {
  map<string, vector<Sym> >::iterator iter;
  if ((iter = table.find(symName)) == table.end()) {
    return;
  } else {
    if (!iter->second.empty())
      iter->second.pop_back();
  }
}
