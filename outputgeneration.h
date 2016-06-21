#pragma once
#include "global.h"
#include "generator.h"

class OutputGeneration : public Generator {
public:
	void generateCode(TreeNode*);
};