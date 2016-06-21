#include "ifgeneration.h"

void IfGeneration::generateCode(TreeNode * tn)
{
	auto equal = tn->leftChild;
	auto stmt = equal->rightSibling;
	auto elseclause = stmt->rightSibling;
	CodeGeneration::generateCode(equal);
	CodeGeneration::writeCodeSeg(".IF eax==1");
	CodeGeneration::generateCode(stmt->leftChild);
	CodeGeneration::writeCodeSeg(".ELSE");
	CodeGeneration::generateCode(elseclause->leftChild);
	CodeGeneration::writeCodeSeg(".ENDIF");
	return;
}
