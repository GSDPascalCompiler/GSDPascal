#pragma once
#include "generator.h"
#include "codegeneration.h"

class IfGeneration :public Generator
{
public:
	void generateCode(TreeNode *tn);
};