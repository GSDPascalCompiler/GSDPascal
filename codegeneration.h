#pragma once
#include "global.h"
#include <map>
#include "generator.h"
#include <iostream>

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
public:
	static void init();
	static void generateCode(TreeNode* tn);
	static void endGeneration();
};
