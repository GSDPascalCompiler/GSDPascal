#include "codegeneration.h"

void generateFileHeader();
void generateFileFooter();

void generateCode(vector<Quad> inst) {
	generateFileHeader();
	for (int i = 0; i < inst.size(); i++) {
		switch (inst[i].op) {
		case OP_RD: break;
		case OP_GT: break;
		case OP_IF_F: break;
		case OP_ASN: break;
		case OP_LAB: break;
		case OP_MUL: break;
		case OP_SUB: break;
		case OP_EQ: break;
		case OP_WRI: break;
		case OP_HALT: break;
		}
	}
	generateFileFooter();
}

void writeAsm(string str) {
	cout << str << endl;
}

void generateFileHeader() {
	freopen("GC.asm", "w", stdout);
	writeAsm(".386");
	writeAsm(".model flat,stdcall");
	writeAsm("option casemap:none");
	writeAsm("include masm32\\include\\msvcrt.inc");
	writeAsm("includelib msvcrt.lib");

	writeAsm("printf  proto C:dword,:dword");

	writeAsm(".data");
	writeAsm("lb_write_int db '%d',0");
	writeAsm("lb_writeln_int db '%d',0ah,0dh,0");
	writeAsm("lb_write_real db '%lf',0");
	writeAsm("lb_writeln_real db '%lf',0ah,0dh,0");
	writeAsm("lb_tmp db 0, 0, 0, 0, 0, 0, 0, 0");
	writeAsm("lb_read_int db '%d',0");
	writeAsm("lb_read_real db '%f',0");

	writeAsm(".code");
	freopen("CON", "w", stdout);
}

void generateFileFooter() {
	freopen("GC.asm", "a", stdout);
	//writeAsm("add esp, " + paraSize);
	writeAsm("ret");
	writeAsm("main ENDP");
	writeAsm("END main");
	freopen("CON", "w", stdout);
}
