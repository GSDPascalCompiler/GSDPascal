package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.TreeNode;

public class StmtInputGenerator extends Generator {

    StmtInputGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        TreeNode child = node.getChildren().get(0);
        while (child != null) {
            codeGenerator.generateCode(child, false);

            codeGenerator.writeCodeLine("pusha");
            if (child.getRunTimeType() == ExpressionType.INT) {
                codeGenerator.writeCodeLine("invoke crt_scanf, addr lb_read_int, addr lb_tmp");
            } else if (child.getRunTimeType() == ExpressionType.REAL) {
                codeGenerator.writeCodeLine("invoke crt_scanf, addr lb_read_real, addr lb_tmp");
            }
            codeGenerator.writeCodeLine("popa");

            codeGenerator.writeCodeLine("mov eax, dword ptr lb_tmp");
            codeGenerator.writeCodeLine("mov [esi], eax");
            child = child.getSibling();
        }
    }
}
