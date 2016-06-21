#include "codegeneration.h"
#include "assigngeneration.h"
#include "outputgeneration.h"
#include "ifgeneration.h"
#include "stringutils.h"

const int CG_ASSIGN = 0;
const int CG_OUTPUT = 1;
const int CG_IF = 2;

const string fileName = "cg.asm";

map<int, Generator*> CodeGeneration::processor;
string CodeGeneration::headSeg = "";
string CodeGeneration::footSeg = "";
string CodeGeneration::dataSeg = "";
string CodeGeneration::codeSeg = "";
string CodeGeneration::currentPath = "";

void CodeGeneration::init() {
	headSeg = footSeg = dataSeg = codeSeg = currentPath = "";
	processor.clear();
	processor.insert(make_pair(CG_ASSIGN, new AssignGeneration()));
	processor.insert(make_pair(CG_OUTPUT, new OutputGeneration()));
	processor.insert(make_pair(CG_IF, new IfGeneration()));
	generateHeadSeg();
	generateFootSeg();
	currentPath = "$main/";
}

void CodeGeneration::generateCode(TreeNode* tn) {
	switch (tn->typeValue.stmtType) {
	case S_ASSIGN:
	case S_ASSIGN_ARRAY:
	case S_ASSIGN_RECORD:
		processor[CG_ASSIGN]->generateCode(tn);
		break;
	case S_PROC:
		break;
	case S_PROC_FUNC:
		break;
	case S_PROC_SYS_ARG:
		processor[CG_OUTPUT]->generateCode(tn);
		break;
	case S_PROC_READ:
		break;
	case S_IF:
		processor[CG_IF]->generateCode(tn);
		break;
	}
}

void CodeGeneration::writeHeadSeg(string s) {
	headSeg += s;
}

void CodeGeneration::writeFootSeg(string s) {
	footSeg += s;
}

void CodeGeneration::writeDataSeg(string s) {
	dataSeg += s;
}

void CodeGeneration::writeCodeSeg(string s) {
	codeSeg += s;
}

void CodeGeneration::generateGlobalList() {
	for (auto item : *(symtable.getAllGlobal())) {
		dataSeg += globalParaName(item.second->symbolName) + "DD 0\n";
	}
}

void CodeGeneration::generateHeadSeg() {
	writeHeadSeg(".386");
	writeHeadSeg(".model flat,stdcall");
	//writeHeadSeg("option casemap:none");
	writeHeadSeg("include msvcrt.inc");
	writeHeadSeg("includelib msvcrt.lib");
	//writeHeadSeg("printf  proto C:dword,:dword");
	writeHeadSeg(".const");
	writeHeadSeg("lb_write_int db '%d',0");
	writeHeadSeg("lb_writeln_int db '%d',0ah,0dh,0");
	writeHeadSeg("lb_write_real db '%lf',0");
	writeHeadSeg("lb_writeln_real db '%lf',0ah,0dh,0");
	writeHeadSeg("lb_tmp db 0, 0, 0, 0, 0, 0, 0, 0");
	writeHeadSeg("lb_read_int db '%d',0");
	writeHeadSeg("lb_read_real db '%f',0");
}

void CodeGeneration::generateFootSeg() {
	writeFootSeg("end main");
}

void CodeGeneration::endGeneration() {
	freopen(fileName.c_str(), "w", stdout);
	cout << headSeg << endl;
	cout << dataSeg << endl;
	cout << codeSeg << endl;
	cout << footSeg << endl;
	freopen("CON", "w", stdout);
}