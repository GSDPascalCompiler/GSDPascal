package com.gsdpascal.codegen;

import com.gsdpascal.astree.TreeNode;

public abstract class Generator {

    CodeGenerator codeGenerator;

    Generator(CodeGenerator codeGenerator) {
        this.codeGenerator = codeGenerator;
    }

    abstract void generateCode(TreeNode node);

}
