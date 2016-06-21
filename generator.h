#pragma once
#include "global.h"

class Generator {
public:
	virtual string generateCode(TreeNode* tn) = 0;
};