#include "codegeneration.h"
#include "savedTable.h"

void generateFileHeader();
void generateFileFooter();
void generateOpCal(Quad quad);
void generateGlobalList();

string headStr = "", dataStr = "", footerStr = "", codeStr = "";

map<string, int> offset;
int tot = 0;

void generateCode(vector<Quad*> inst) {
	offset.clear();
	generateFileHeader();
	generateGlobalList();
	for (int i = 0; i < inst.size(); i++) {
		switch (inst[i]->op) {
		case OP_PLUS: 
		case OP_MUL: 
		case OP_MINUS: 
		case OP_DIV: generateOpCal(*(inst[i])); break;
		case OP_GT: break;
		//case OP_WRI: generateOutput(inst[i]); break;
		}
	}
	generateFileFooter();
	freopen("GC.asm", "w", stdout);
	cout << headStr << endl;
	cout << dataStr << endl;
	cout << codeStr << endl;
	cout << footerStr << endl;
	freopen("CON", "w", stdout);
}

void writeHeadStr(string str) {
	headStr += str;
	headStr += "\n";
}

void writeDataStr(string str) {
	dataStr += str;
	dataStr += "\n";
}

void writeFooterStr(string str) {
	footerStr += str;
	footerStr += "\n";
}

void writeCodeStr(string str) {
	codeStr += str;
	codeStr += "\n";
}

void generateFileHeader() {
	writeHeadStr(".386");
	writeHeadStr(".model flat,stdcall");
	writeHeadStr("option casemap:none");
	writeHeadStr("include masm32\\include\\msvcrt.inc");
	writeHeadStr("includelib msvcrt.lib");

	writeHeadStr("printf  proto C:dword,:dword");

	writeDataStr(".data");
	writeDataStr("lb_write_int db '%d',0");
	writeDataStr("lb_writeln_int db '%d',0ah,0dh,0");
	writeDataStr("lb_write_real db '%lf',0");
	writeDataStr("lb_writeln_real db '%lf',0ah,0dh,0");
	writeDataStr("lb_tmp db 0, 0, 0, 0, 0, 0, 0, 0");
	writeDataStr("lb_read_int db '%d',0");
	writeDataStr("lb_read_real db '%f',0");
	writeDataStr("beginSP dd 0");

	writeCodeStr(".code");
	writeCodeStr("main:");
	writeCodeStr("mov beginSP, esp");
}

void generateFileFooter() {
	//writeAsm("add esp, " + paraSize);
	writeFooterStr("ret");
	//writeFooterStr("main ENDP");
	writeFooterStr("END main");
}

void generateGlobalList() {
	map<string, SymbolItem*>::iterator iter;
	map<string, SymbolItem*>* tMap = symtable.getAllGlobal();
	for (iter = tMap->begin(); iter != tMap->end(); iter++) {
		if (iter->second->symbolType == A_INTEGER) {
			writeDataStr(iter->first + " dd 0");
		}
	}
}

void loadVarInto(Attribute vName, string rName) {
	if (vName.attrType == A_CONST_INTEGER) {
		string tInst = "mov ";
		tInst += rName + ", " + vName.attrName;
		writeCodeStr(tInst);
		return;
	}
	if (vName.attrName[0] != '$') {
		if (savedTable.isGlobal("$main", vName.attrName)) {
			string tInst = "mov " + rName + ", " + vName.attrName;
			writeCodeStr(tInst);
			return;
		}
	} 
	else {
		offset.insert(make_pair(vName.attrName, tot));
		writeCodeStr("sub esp, 4");
		int p = tot++;
		p *= 4;
		char num2[16];
		_itoa(p, num2, 10);
		string s(num2);
		string tInst = "mov " + rName + ", [esp+" + s;
		tInst += "]";
		writeCodeStr(tInst);
	}
}

void storeInto(string rName, string vName) {
	if (vName[0] != '$') {
		if (savedTable.isGlobal("$main", vName)) {
			string tInst = "mov ";
			tInst += vName + ", " + rName;
			writeCodeStr(tInst);
			return;
		}
	}
	else {
		if (offset.find(vName) != offset.end()) {
			int p = (tot - offset.find(vName)->second) * 4;
			char num2[16];
			_itoa(p, num2, 10);
			string s(num2);
			string tInst = "mov [esp+" + s;
			tInst += "]," + rName;
			writeCodeStr(tInst);
		}
		else {
			offset.insert(make_pair(vName, tot));
			writeCodeStr("sub esp, 4");
			int p = tot++;
			p *= 4;
			char num2[16];
			_itoa(p, num2, 10);
			string s(num2);
			string tInst = "mov [esp+" + s;
			tInst += "]," + rName;
			writeCodeStr(tInst);
		}
	}
}

void storeConstIntInto(string vName, int x) {
	char num1[16];
	_itoa(x, num1, 10);
	string num(num1);
	if (vName[0] != '$') {
		if (savedTable.isGlobal("$main", vName)) {
			string tInst = "mov " + vName + ", " + num;
			writeCodeStr(tInst);
		}
	}
	else {
		if (offset.find(vName) != offset.end()) {
			int p = (tot - offset.find(vName)->second) * 4;
			char num2[16];
			_itoa(p, num2, 10);
			string s(num2);
			string tInst = "mov [esp+" + s;
			tInst += "]," + num;
			writeCodeStr(tInst);
		} else {
			offset.insert(make_pair(vName, tot));
			writeCodeStr("sub esp, 4");
			int p = tot++;
			p *= 4;
			char num2[16];
			_itoa(p, num2, 10);
			string s(num2);
			string tInst = "mov [esp+" + s;
			tInst += "]," + num;
			writeCodeStr(tInst);
		}
	}
}

void generateOpCal(Quad quad) {
	AttrType a1, a2, a3;
	a1 = quad.addr1.attrType;
	a2 = quad.addr2.attrType;
	if (a1 == A_CONST_INTEGER && a2 == A_CONST_INTEGER) {
		int o1 = atoi(quad.addr1.attrName.c_str());
		int o2 = atoi(quad.addr2.attrName.c_str());
		switch (quad.op) {
		case OP_PLUS: o1 += o2; break;
		case OP_MINUS: o1 -= o2; break;
		case OP_MUL: o1 *= o2; break;
		case OP_DIV: o1 /= o2; break;
		}
		storeConstIntInto(quad.addr3.attrName, o1);
	}
	else if (a1 == A_INTEGER || a2 == A_INTEGER) {
		loadVarInto(quad.addr1, "eax");
		loadVarInto(quad.addr2, "ebx");
		switch (quad.op) {
		case OP_PLUS: writeCodeStr("add eax, ebx"); break;
		case OP_MINUS: writeCodeStr("sub eax, ebx"); break;
		case OP_MUL: writeCodeStr("xor edx, edx"); writeCodeStr("mul ebx"); break;
		case OP_DIV: writeCodeStr("xor edx, edx"); writeCodeStr("div ebx"); break;
		}
	}
}

void generateOutput(Quad quad) {
	Attribute a = quad.addr1;
	loadVarInto(a, "eax");
	if (a.attrType == A_INTEGER) {
		writeCodeStr("invoke printf,offset lb_writeln_int, eax");
	}
}

void generateGT(Quad quad) {
	
}


