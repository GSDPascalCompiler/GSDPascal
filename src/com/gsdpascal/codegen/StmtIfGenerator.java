package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class StmtIfGenerator extends Generator {

    StmtIfGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        TreeNode cond = node.getChildren().get(0);
        int alwaysTrue = OptimizationUtils.alwaysTrue(cond);

        String elseLabel = LabelManager.createLabel();
        String exitLabel = "";
        if (node.getChildren().get(2) != null)
            exitLabel = LabelManager.createLabel();

        if (alwaysTrue == OptimizationUtils.CANNOT_DETERMINE) {
            codeGenerator.generateCode(cond);
            codeGenerator.writeCodeLine("cmp eax, 0");
            codeGenerator.writeCodeLine("je " + elseLabel);
        } else if (alwaysTrue == OptimizationUtils.ALWAYS_TRUE) {
            //恒为真则直接继续执行
        } else if (alwaysTrue == OptimizationUtils.ALWAYS_FALSE) {
            //恒为假则直接跳转到else段
            if (node.getChildren().get(2) != null)
                codeGenerator.writeCodeLine("jmp " + elseLabel);
        }
        codeGenerator.generateCode(node.getChildren().get(1));
        if (node.getChildren().get(2) != null) {
            codeGenerator.writeCodeLine("jmp " + exitLabel);
            codeGenerator.writeCodeLine(elseLabel + ":");
            codeGenerator.generateCode(node.getChildren().get(2));
            codeGenerator.writeCodeLine(exitLabel + ":");
        }
    }
}
