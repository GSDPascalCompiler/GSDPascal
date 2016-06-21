#pragma once
#include "generator.h"

class AssignGeneration : public Generator{
public:
	string generateCode(TreeNode*);
};