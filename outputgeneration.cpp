#include "outputgeneration.h"

const string write_format_int = "lb_write_int";
const string writeln_format_int = "lb_writeln_int";
const string write_format_real = "lb_write_real";
const string writeln_format_real = "lb_writeln_real";

string OutputGeneration::generateCode(TreeNode *tn)
{
	string ret = "";
	TreeNode* outputType = tn->leftChild;
	string outputFormat;
	if (outputType->value.nodeSysProcVal.sysProcVal == PROC_WRITE)
		outputFormat = write_format_int;
	else if (outputType->value.nodeSysProcVal.sysProcVal == PROC_WRITELN)
		outputFormat = writeln_format_int;
	TreeNode* expList = tn->leftChild->rightSibling->leftChild;
	while (expList != nullptr) {
		//if (expList->leftChild->value.nodeId.id)
		ret += "invoke ctr_printf, offset " + outputFormat + ", eax";
		expList = expList->rightSibling;
	}
	return ret;
}
