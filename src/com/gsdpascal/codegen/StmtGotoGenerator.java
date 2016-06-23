package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class StmtGotoGenerator extends Generator {

    StmtGotoGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        int value = (Integer)node.getAttribute();
        String label = LabelManager.buildCodeLabel(value);
        codeGenerator.writeCodeLine("jmp " + label);
    }
}
