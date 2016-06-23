package com.gsdpascal.codegen;

import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.semantic.VariableDefinition;
import com.gsdpascal.astree.TreeNode;

public class StmtAssignGenerator extends Generator {

    StmtAssignGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        codeGenerator.generateCode(node.getChildren().get(1));
        codeGenerator.writeCodeLine("push eax");

        VariableDefinition varInfo = SymbolTable.lookupVar((String) node.getChildren().get(0).getAttribute());
        if (varInfo == null) {
            codeGenerator.error(node.getLineNumber(), "Undefined variable: " + node.getChildren().get(0).getAttribute());
        }
        if (varInfo.isConst){
            codeGenerator.error(node.getLineNumber(), "Attempt to assign a const variable.");
        }
        codeGenerator.generateCode(node.getChildren().get(0));
        codeGenerator.writeCodeLine("pop eax");
        codeGenerator.writeCodeLine("mov [esi-0], eax");
        node.getChildren().get(0).setRunTimeType(node.getChildren().get(1).getRunTimeType());
    }
}
