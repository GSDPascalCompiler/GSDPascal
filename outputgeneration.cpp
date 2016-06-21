#include "outputgeneration.h"
#include "stringutils.h"
#include "codegeneration.h"

const string write_format_int = "lb_write_int";
const string writeln_format_int = "lb_writeln_int";
const string write_format_real = "lb_write_real";
const string writeln_format_real = "lb_writeln_real";

void OutputGeneration::generateCode(TreeNode *tn)
{
	string ret = "";
	TreeNode* outputType = tn->leftChild;
	string outputFormat;
	bool ln = false;
	if (outputType->value.nodeSysProcVal.sysProcVal == PROC_WRITE)
		ln = false;
	else if (outputType->value.nodeSysProcVal.sysProcVal == PROC_WRITELN)
		ln = true;
	TreeNode* factor = tn->leftChild->rightSibling->leftChild;
	while (factor != nullptr) {
		TreeNode* factorChild = factor->leftChild;
		if (factorChild->typeValue.stmtType == S_CONST_VALUE_INT) {
			ret += "invoke ctr_printf, offset " + outputFormat + ", " + int2string(factorChild->leftChild->value.nodeInteger.i);
		} else if (factorChild->typeValue.stmtType == S_FACTOR_ID) {
			//if (savedTable.isGlobal())
			ret += "invoke ctr_printf, offset " + outputFormat + ", eax";
		}
		factor = factor->rightSibling;
	}
}
