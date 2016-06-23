package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public class StmtLabelGenerator extends Generator {

    StmtLabelGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        int value = (int)node.getAttribute();
        String label = LabelManager.buildCodeLabel(value);
        codeGenerator.writeCodeLine(label + ":");
        codeGenerator.generateCode(node.getChildren().get(0));
    }
}
