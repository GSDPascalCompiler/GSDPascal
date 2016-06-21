#pragma once
#include "global.h"
#include "generator.h"

class OutputGeneration : public Generator {
public:
	string generateCode(TreeNode*);
};