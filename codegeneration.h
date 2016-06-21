#pragma once
#include "global.h"
#include <map>
#include "generator.h"
#include <iostream>
#include "savedTable.h"
#include "symtable.h"

class CodeGeneration {
private:
	static map<int, Generator*> processor;
	static string headSeg, footSeg, dataSeg, codeSeg;

	static void generateHeadSeg();
	static void generateFootSeg();
	static void writeHeadSeg(string s);
	static void writeFootSeg(string s);
	static void writeDataSeg(string s);
	static void writeCodeSeg(string s);
	static void generateGlobalList();
public:
	static void init();
	static void generateCode(TreeNode* tn);
	static void endGeneration();
};
