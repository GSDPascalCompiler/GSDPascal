package com.gsdpascal.codegen;

import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.astree.TreeNode;

public class FuncDeclGenerator extends Generator {

    FuncDeclGenerator (CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {

        TreeNode child1 = node.getChildren().get(0);
        TreeNode child2 = node.getChildren().get(1);
        SymbolTable.addProcOrFunc(child1);

        child2.setAttribute(child1.getAttribute());
        codeGenerator.generateCode(child2);

        int sizeParam = SymbolTable.leaveScope();
        codeGenerator.writeCodeLine("add esp, " + sizeParam);
        codeGenerator.writeCodeLine("ret");
    }
}
