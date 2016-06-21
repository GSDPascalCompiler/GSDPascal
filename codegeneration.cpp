#include "codegeneration.h"
#include "assigngeneration.h"
#include "outputgeneration.h"



const string fileName = "cg.asm";

map<int, Generator*> CodeGeneration::processor;
string CodeGeneration::headSeg = "";
string CodeGeneration::footSeg = "";
string CodeGeneration::dataSeg = "";
string CodeGeneration::codeSeg = "";

void CodeGeneration::init() {
	processor.clear();
	processor.insert(make_pair(0, new AssignGeneration()));
	processor.insert(make_pair(1, new OutputGeneration()));
	generateHeadSeg();
	generateFootSeg();
}

void CodeGeneration::generateCode(TreeNode* tn) {
	switch (tn->typeValue.stmtType) {
	case S_ASSIGN:
	case S_ASSIGN_ARRAY:
	case S_ASSIGN_RECORD:
		processor[0]->generateCode(tn);
		break;
	case S_PROC:
		break;
	case S_PROC_FUNC:
		break;
	case S_PROC_SYS_ARG:
		processor[1]->generateCode(tn);
		break;
	case S_PROC_READ:
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