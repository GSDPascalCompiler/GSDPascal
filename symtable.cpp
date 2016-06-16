#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"
using namespace std;

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

// int main() {
//   Symtable symtable;
//   Sym sym1;
//   sym1.name = "a";
//   symtable.addIntoSymtable(sym1);
//   cout << symtable.getSymFromSymtable("a")->name << endl;
//   symtable.removeSymFromSymtable("a");
//   if (symtable.getSymFromSymtable("a") == NULL)
//     cout << "NULL" << endl;
//   return 0;
// }
