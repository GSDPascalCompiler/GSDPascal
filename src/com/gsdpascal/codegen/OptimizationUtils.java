package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionKind;
import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.OperationKind;
import com.gsdpascal.astree.TreeNode;

public class OptimizationUtils {
    public static int ALWAYS_TRUE = 0;
    public static int ALWAYS_FALSE = 1;
    public static int CANNOT_DETERMINE = 2;
    public static int alwaysTrue(TreeNode cond) {
        int ret = CANNOT_DETERMINE;
        if (!(cond.getExpType() == null))
            return ret;
        if (cond.getExpType() == ExpressionType.BOOL) {
            //while条件恒为假则无需生成该段代码
            if ((int)cond.getAttribute() == 0) {
                ret = ALWAYS_FALSE;
            } else {
                ret = ALWAYS_TRUE;
            }
        }
        return ret;
    }
    public static boolean compareForCond(TreeNode cond1, TreeNode cond2, TreeNode op) {
        if (!(cond1.getNodeType() instanceof ExpressionKind))
            return false;
        if (!(cond2.getNodeType() instanceof ExpressionKind))
            return false;
        if (cond1.getNodeType() != ExpressionKind.CONST || cond2.getNodeType() != ExpressionKind.CONST)
            return false;
        if (cond1.getExpType() != ExpressionType.INT && cond1.getExpType() != ExpressionType.CHAR)
            return false;
        if (cond2.getExpType() != ExpressionType.INT && cond2.getExpType() != ExpressionType.CHAR)
            return false;
        int startVal, endVal;
        startVal = (int)cond1.getAttribute();
        endVal = (int)cond2.getAttribute();
        OperationKind OperationKind = (OperationKind) op.getAttribute();
        if (OperationKind == OperationKind.TO && startVal > endVal)
            return true;
        if (OperationKind == OperationKind.DOWNTO && startVal < endVal)
            return true;
        return false;
    }
}
