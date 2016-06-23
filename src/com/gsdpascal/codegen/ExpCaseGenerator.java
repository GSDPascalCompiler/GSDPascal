package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class ExpCaseGenerator extends Generator {

    ExpCaseGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        String nextCaseLabel = LabelManager.createLabel();
        codeGenerator.generateCode(node.getChildren().get(0));
        codeGenerator.writeCodeLine("pop ebx");
        codeGenerator.writeCodeLine("cmp ebx, eax");
        codeGenerator.writeCodeLine("jne " + nextCaseLabel);
        codeGenerator.generateCode(node.getChildren().get(1));
        codeGenerator.writeCodeLine(nextCaseLabel + ":");
        if (node.getSibling() != null) {
            codeGenerator.writeCodeLine("push ebx");
        }
    }
}
