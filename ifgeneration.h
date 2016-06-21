#pragma once
#include "generator.h"

class IfGeneration :public Generator
{
public:
	string generateCode(TreeNode *tn);
};