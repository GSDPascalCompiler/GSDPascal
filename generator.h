#pragma once
#include "global.h"

class Generator {
public:
	virtual void generateCode(TreeNode* tn) = 0;
};