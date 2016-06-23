package com.gsdpascal.codegen;

import com.gsdpascal.semantic.SimpleType;
import com.gsdpascal.astree.TreeNode;

import java.util.LinkedList;

public abstract class StmtFuncAndProcGenerator extends Generator {

    StmtFuncAndProcGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    protected void CGPushParam(TreeNode node) {
        if (node.getSibling() != null) {
            CGPushParam(node.getSibling());
        }

        codeGenerator.generateCode(node, false);
        codeGenerator.writeCodeLine("push eax");
    }

    protected void CGPopParam(TreeNode node, LinkedList<SimpleType> paraList) {

        if (node == null || paraList == null || paraList.size() == 0)
            return;

        for (SimpleType para : paraList) {
            if (node == null) {
                break;
            }
            if (para.isVar) {
                codeGenerator.generateCode(node, false);
                codeGenerator.writeCodeLine("pop eax");
                codeGenerator.writeCodeLine("mov [esi],eax");
            }
            else {
                codeGenerator.writeCodeLine("pop eax");
            }
            node = node.getSibling();
        }

    }
}
