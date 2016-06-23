package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.OperationKind;
import com.gsdpascal.astree.TreeNode;

public class ExpOpGenerator extends Generator {

    ExpOpGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {

        if (node.getChildren().get(0) != null && node.getChildren().get(1) != null) {

            TreeNode child1 = node.getChildren().get(0);
            TreeNode child2 = node.getChildren().get(1);

            codeGenerator.generateCode(child1);
            codeGenerator.writeCodeLine("push eax");
            codeGenerator.generateCode(child2);
            codeGenerator.writeCodeLine("push eax");

            if (child1.getRunTimeType() != child2.getRunTimeType()) {
                codeGenerator.error(node.getLineNumber(), "The type of the two operands are not same.");
            }

            node.setRunTimeType(child1.getRunTimeType());

        } else if (node.getChildren().get(0) != null) {
            codeGenerator.writeCodeLine("push 0");
            codeGenerator.generateCode(node.getChildren().get(0));
            codeGenerator.writeCodeLine("push eax");

            node.setRunTimeType(node.getChildren().get(0).getRunTimeType());

        } else {
            codeGenerator.error(node.getLineNumber(), "Operator with unsupported number of operand.");
        }

        OperationKind OperationKind = (OperationKind)node.getAttribute();
        if (node.getRunTimeType() != ExpressionType.REAL) {
            codeGenerator.writeCodeLine("pop ebx");
            codeGenerator.writeCodeLine("pop eax");
            String endLabel = LabelManager.createLabel();
            String shiftLabel2 = LabelManager.createLabel();
            String shiftLabel = LabelManager.createLabel();
            switch (OperationKind) {
                case PLUS:
                    codeGenerator.writeCodeLine("add eax, ebx");
                    break;
                case MINUS:
                    codeGenerator.writeCodeLine("sub eax, ebx");
                    break;
                case MUL:
                    //增加其中任意一个乘数为2时转为移位的优化
                    codeGenerator.writeCodeLine("xor edx, edx");
                    codeGenerator.writeCodeLine("cmp ebx, 2");
                    codeGenerator.writeCodeLine("je " + shiftLabel);
                    codeGenerator.writeCodeLine("cmp eax, 2");
                    codeGenerator.writeCodeLine("je" + shiftLabel2);
                    codeGenerator.writeCodeLine("imul ebx");
                    codeGenerator.writeCodeLine("jmp " + endLabel);
                    codeGenerator.writeCodeLine(shiftLabel + ":");
                    codeGenerator.writeCodeLine("sal eax, 1");
                    codeGenerator.writeCodeLine("jmp " + endLabel);
                    codeGenerator.writeCodeLine(shiftLabel2 + ":");
                    codeGenerator.writeCodeLine("sal ebx, 1");
                    codeGenerator.writeCodeLine(endLabel + ":");
                    break;
                case DIV:
                    //增加了除数为2的移位优化
                    codeGenerator.writeCodeLine("xor edx, edx");
                    codeGenerator.writeCodeLine("cmp ebx, 2");
                    codeGenerator.writeCodeLine("je " + shiftLabel);
                    codeGenerator.writeCodeLine("idiv ebx");
                    codeGenerator.writeCodeLine("jmp " + endLabel);
                    codeGenerator.writeCodeLine(shiftLabel + ":");
                    codeGenerator.writeCodeLine("sar eax, 1");
                    codeGenerator.writeCodeLine(endLabel + ":");
                    break;
                case MOD:
                    codeGenerator.writeCodeLine("xor edx, edx");
                    codeGenerator.writeCodeLine("idiv ebx");
                    codeGenerator.writeCodeLine("mov eax,edx");
                    break;
                case LT:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setl al");
                    break;
                case LE:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setng al");
                    break;
                case GT:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setg al");
                    break;
                case GE:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setnl eax");
                    break;
                case EQUAL:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("sete al");
                    break;
                case UNEQUAL:
                    codeGenerator.writeCodeLine("cmp eax, ebx");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setne al");
                    break;
            }
        } else {
            if (OperationKind == OperationKind.PLUS || OperationKind == OperationKind.MINUS || OperationKind == OperationKind.MUL || OperationKind == OperationKind.DIV) {
                codeGenerator.writeCodeLine("fld dword ptr [esp+4]");
                codeGenerator.writeCodeLine("fld dword ptr [esp]");
            }
            else {
                codeGenerator.writeCodeLine("fld dword ptr [esp]");
                codeGenerator.writeCodeLine("fld dword ptr [esp+4]");
            }
            codeGenerator.writeCodeLine("pop eax");
            codeGenerator.writeCodeLine("pop eax");
            switch(OperationKind){
                case PLUS:
                    codeGenerator.writeCodeLine("fadd");
                    break;
                case MINUS:
                    codeGenerator.writeCodeLine("fsub");
                    break;
                case MUL:
                    codeGenerator.writeCodeLine("fmul");
                    break;
                case DIV:
                    codeGenerator.writeCodeLine("fdiv");
                    break;
                case LT:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setb al");
                    break;
                case LE:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setna al");
                    break;
                case GT:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("seta al");
                    break;
                case GE:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setnb eax");
                    break;
                case EQUAL:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("sete al");
                    break;
                case UNEQUAL:
                    codeGenerator.writeCodeLine("fcomi st(0), st(1)");
                    codeGenerator.writeCodeLine("mov eax, 0");
                    codeGenerator.writeCodeLine("setne al");
                    break;
            }
            if (OperationKind == OperationKind.PLUS || OperationKind == OperationKind.MINUS || OperationKind == OperationKind.MUL || OperationKind == OperationKind.DIV) {
                codeGenerator.writeCodeLine("sub esp,4");
                codeGenerator.writeCodeLine("fstp dword ptr [esp]");
                codeGenerator.writeCodeLine("pop eax");
            }
        }
    }
}
