package com.gsdpascal.codegen;

import com.gsdpascal.astree.OperationKind;
import com.gsdpascal.astree.TreeNode;


public class StmtForGenerator extends Generator {

    StmtForGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        OperationKind OperationKind = (OperationKind)node.getAttribute();

        //检测若初始值大于终值且为to那么不输出该for,同理处理downto的情况.
        if (OptimizationUtils.compareForCond(node.getChildren().get(1), node.getChildren().get(2), node))
            return;

        String startLabel = LabelManager.createLabel();
        String endLabel = LabelManager.createLabel();

        codeGenerator.generateCode(node.getChildren().get(1));  // 计算初值
        codeGenerator.writeCodeLine("push eax");
        codeGenerator.generateCode(node.getChildren().get(0));  // 计算循环变量
        codeGenerator.writeCodeLine("pop eax");
        codeGenerator.writeCodeLine("mov [esi-0], eax");        // 给循环变量赋初值
        codeGenerator.generateCode(node.getChildren().get(2));  // 计算终值
        codeGenerator.writeCodeLine("push eax");


        codeGenerator.writeCodeLine(startLabel + ":");
        codeGenerator.generateCode(node.getChildren().get(0));  // 获取循环变量
        codeGenerator.writeCodeLine("pop ebx");
        codeGenerator.writeCodeLine("cmp eax, ebx");
        if (OperationKind == OperationKind.TO) {
            codeGenerator.writeCodeLine("ja " + endLabel);
        } else if (OperationKind == OperationKind.DOWNTO) {
            codeGenerator.writeCodeLine("jb " + endLabel);
        } else {
            codeGenerator.error(node.getLineNumber(), "This is not a valid for statement: " + OperationKind.getClass());
        }

        codeGenerator.generateCode(node.getChildren().get(3));  // 循环体

        // 循环变量+1或-1
        codeGenerator.generateCode(node.getChildren().get(0));
        if (OperationKind == OperationKind.TO) {
            codeGenerator.writeCodeLine("inc eax");
        } else {
            codeGenerator.writeCodeLine("dec eax");
        }
        codeGenerator.writeCodeLine("mov [esi-0], eax");        // 将+1/-1之后的值赋值回给循环变量
        codeGenerator.writeCodeLine("jmp " + startLabel);
        codeGenerator.writeCodeLine(endLabel + ":");
    }
}
