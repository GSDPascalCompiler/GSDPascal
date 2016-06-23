package com.gsdpascal.codegen;

import com.gsdpascal.semantic.FunctionDefinition;
import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.astree.TreeNode;

public class ExpFuncIdGenerator extends StmtFuncAndProcGenerator {

    ExpFuncIdGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        FunctionDefinition PosalVar = SymbolTable.lookupFunc((String) node.getAttribute());

        // 压入返回值
        codeGenerator.writeCodeLine("push eax");

        CGPushParam(node.getChildren().get(0));


        codeGenerator.writeCodeLine("push ecx");
        codeGenerator.writeCodeLine("mov ecx, esp");

        codeGenerator.writeCodeLine("call " + node.getAttribute());

        codeGenerator.writeCodeLine("pop ecx");


        CGPopParam(node.getChildren().get(0), PosalVar.paraList);

        codeGenerator.writeCodeLine("pop eax");
    }
}
