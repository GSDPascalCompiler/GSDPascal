#include "assigngeneration.h"
#include "codegeneration.h"
#include "stringutils.h"

void AssignGeneration::generateCode(TreeNode *tn) {
	string ret = "";
	TreeNode* id = tn->leftChild;
	TreeNode* type = tn->rightSibling->leftChild;
	switch (type->typeValue.stmtType) {
	case S_CONST_VALUE_INT:
		ret += "mov eax," + int2string(type->leftChild->value.nodeInteger.i) + "\n";
		break;
	case S_CONST_VALUE_REAL:
		break;
	}
}