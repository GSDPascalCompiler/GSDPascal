package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionKind;
import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.TreeNode;

public class StmtWhileGenerator extends Generator {

    StmtWhileGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        TreeNode cond = node.getChildren().get(0);
        int alwaysTrue = OptimizationUtils.alwaysTrue(cond);

        //条件恒为假无需输出该语句
        if (alwaysTrue == OptimizationUtils.ALWAYS_FALSE)
            return;

        String startLabel = LabelManager.createLabel();
        String endLabel = LabelManager.createLabel();

        codeGenerator.writeCodeLine(startLabel + ":");

        if (alwaysTrue == OptimizationUtils.CANNOT_DETERMINE) {
            codeGenerator.generateCode(cond);
            codeGenerator.writeCodeLine("cmp eax, 0");
            codeGenerator.writeCodeLine("je " + endLabel);
        } else {
            //while条件恒为真则开始不需要判断跳出
        }

        codeGenerator.generateCode(node.getChildren().get(1));
        codeGenerator.writeCodeLine("jmp " + startLabel);
        codeGenerator.writeCodeLine(endLabel + ":");
    }
}
