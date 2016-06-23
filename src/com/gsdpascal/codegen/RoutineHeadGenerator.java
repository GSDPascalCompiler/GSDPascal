package com.gsdpascal.codegen;

import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.astree.TreeNode;

public class RoutineHeadGenerator extends Generator {

    RoutineHeadGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        int sizeParam = SymbolTable.enterNewScope(node);

        if (node.getChildren().get(3) != null)
            codeGenerator.generateCode(node.getChildren().get(3));

        if (!(node.getAttribute()).equals("main")){
            codeGenerator.writeCodeLine(node.getAttribute() + ":");
        }
        else {
            codeGenerator.writeCodeLine("main PROC");
            codeGenerator.writeCodeLine("mov ecx, esp");
        }

        codeGenerator.writeCodeLine("sub esp, " + sizeParam);
    }
}
