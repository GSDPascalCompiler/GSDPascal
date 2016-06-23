package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.OperationKind;
import com.gsdpascal.astree.TreeNode;

public class StmtOutputGenerator extends Generator {

    StmtOutputGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {
        TreeNode child = node.getChildren().get(0);
        while (child != null) {
            codeGenerator.generateCode(child, false);
            codeGenerator.writeCodeLine("pusha");
            //不同类型使用定义好的格式调用C函数输出
            if (child.getRunTimeType() == ExpressionType.REAL) {
                codeGenerator.writeCodeLine("push eax");
                codeGenerator.writeCodeLine("fld dword ptr [esp]");
                codeGenerator.writeCodeLine("sub esp, 4");
                codeGenerator.writeCodeLine("fstp qword ptr [esp]");
                if (node.getAttribute() == OperationKind.WRITELN) {
                    codeGenerator.writeCodeLine("push offset lb_writeln_real");
                } else {
                    codeGenerator.writeCodeLine("push offset lb_write_real");
                }
                codeGenerator.writeCodeLine("call printf");
                codeGenerator.writeCodeLine("add esp, 8");
                codeGenerator.writeCodeLine("pop eax");
            } else if (child.getRunTimeType() == ExpressionType.INT) {
                if (node.getAttribute() == OperationKind.WRITELN) {
                    codeGenerator.writeCodeLine("invoke printf,offset lb_writeln_int, eax");
                } else {
                    codeGenerator.writeCodeLine("invoke printf,offset lb_write_int, eax");
                }
            } else {
                codeGenerator.error(node.getLineNumber(), "Unknown type: " + child.getRunTimeType());
            }

            codeGenerator.writeCodeLine("popa");
            child = child.getSibling();
        }
    }
}
