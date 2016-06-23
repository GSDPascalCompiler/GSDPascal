package com.gsdpascal.codegen;

import com.gsdpascal.semantic.ProcedureDefinition;
import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.astree.TreeNode;

public class StmtProcIdGenerator extends StmtFuncAndProcGenerator {

    StmtProcIdGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {

        ProcedureDefinition PosalVar = SymbolTable.lookupProc((String)node.getAttribute());

        //参数列表
        CGPushParam(node.getChildren().get(0));
        //访问链
        codeGenerator.writeCodeLine("push ecx");
        codeGenerator.writeCodeLine("mov ecx, esp");
        //调用过程
        codeGenerator.writeCodeLine("call " + node.getAttribute());
        codeGenerator.writeCodeLine("pop ecx");
        if (PosalVar != null)
            CGPopParam(node.getChildren().get(0), PosalVar.paraList);
    }
}
