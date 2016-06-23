package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.TreeNode;

public class ExpConstGenerator extends Generator {

    ExpConstGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {

        if (node.getExpType() != ExpressionType.REAL) {
            int value;
            if (node.getExpType() == ExpressionType.CHAR) {
                value = (char)node.getNodeType();
            } else {
                value = (int)node.getAttribute();
            }
            codeGenerator.writeCodeLine("mov eax, " + value);
            node.setRunTimeType(ExpressionType.INT);
        } else {
            double value = (Double)node.getAttribute();
            String realDataLabel = LabelManager.getDataLabel(value, codeGenerator);
            codeGenerator.writeCodeLine("mov eax, " + realDataLabel);
            node.setRunTimeType(ExpressionType.REAL);
        }
    }
}
