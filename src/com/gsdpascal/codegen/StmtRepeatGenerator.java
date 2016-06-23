package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class StmtRepeatGenerator extends Generator {

    StmtRepeatGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        TreeNode cond = node.getChildren().get(1);
        int alwaysTrue = OptimizationUtils.alwaysTrue(cond);

        if (alwaysTrue != OptimizationUtils.ALWAYS_TRUE) {
            String startLabel = LabelManager.createLabel();
            codeGenerator.writeCodeLine(startLabel + ":");
            codeGenerator.generateCode(node.getChildren().get(0));

            if (alwaysTrue == OptimizationUtils.CANNOT_DETERMINE) {
                codeGenerator.generateCode(cond);
                codeGenerator.writeCodeLine("cmp eax, 0");
                codeGenerator.writeCodeLine("je " + startLabel);
            } else {
                //若until条件恒为假,则无需判断直接跳转
                codeGenerator.writeCodeLine("jmp" + startLabel);
            }
        } else {
            //若until中条件恒为真,则相当于只执行repeat-until过程体一次
            codeGenerator.generateCode(node.getChildren().get(0));
        }
    }
}
