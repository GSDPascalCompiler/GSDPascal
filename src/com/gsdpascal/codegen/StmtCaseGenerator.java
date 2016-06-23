package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class StmtCaseGenerator extends Generator {

    StmtCaseGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        codeGenerator.generateCode(node.getChildren().get(0));
        codeGenerator.writeCodeLine("push eax");
        codeGenerator.generateCode(node.getChildren().get(1));
    }
}
