package com.gsdpascal.codegen;

import com.gsdpascal.semantic.ArrayDefinition;
import com.gsdpascal.semantic.LookupReturn;
import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.semantic.VariableDefinition;
import com.gsdpascal.astree.ExpressionType;
import com.gsdpascal.astree.TreeNode;

public class ExpIdGenerator extends Generator {

    ExpIdGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
    }

    @Override
    void generateCode(TreeNode node) {

        int level;
        int offset;
        int lower = 0;
        ExpressionType type;
        LookupReturn recordInfo = null;

        VariableDefinition varInfo = SymbolTable.lookupVar((String) node.getAttribute());
        if (varInfo == null) {
            codeGenerator.error(node.getLineNumber(), "Undefined variable: " + node.getAttribute());
        }

        type = varInfo.type;

        if (type == ExpressionType.ARRAY) {

            if (varInfo.pAttr == null) {
                codeGenerator.error(node.getLineNumber(), "Variable: " + node.getAttribute() + " is not an array.");
            }

            lower = (int)(((ArrayDefinition)varInfo.pAttr).subBound).LowerBound;
            level = varInfo.memPos.basePos;
            offset = varInfo.memPos.offset;

        } else if (type == ExpressionType.RECORD) {
            recordInfo = SymbolTable.lookupRecord((String)node.getAttribute(), (String)(node.getChildren().get(0).getAttribute()));
            level = recordInfo.jumpLevel;
            offset = recordInfo.totalOff;
        } else {
            level = varInfo.memPos.basePos;
            offset = varInfo.memPos.offset;
        }

        if (type == ExpressionType.ARRAY) {
            codeGenerator.generateCode(node.getChildren().get(0), false); 	// 计算数组下标的值
            codeGenerator.writeCodeLine("mov ebx, " + lower);
            codeGenerator.writeCodeLine("sub eax, ebx");
            codeGenerator.writeCodeLine("mov ebx, 4");
            codeGenerator.writeCodeLine("imul eax,ebx");
            codeGenerator.writeCodeLine("mov edi, " + offset);
            codeGenerator.writeCodeLine("add edi, eax");
        }
        else {
            codeGenerator.writeCodeLine("mov edi, " + offset);
        }

        if (type == ExpressionType.ARRAY) {
            type = ((ArrayDefinition)varInfo.pAttr).arrayType;
        } else if (type == ExpressionType.RECORD) {
            type = recordInfo.type;
        }

        codeGenerator.writeCodeLine("mov esi, ecx");
        while (level > 0){
            // 根据访问控制链模型向上层查找，[esi]处存放了其对应函数的fp
            codeGenerator.writeCodeLine("mov eax, [esi]");
            codeGenerator.writeCodeLine("mov esi, eax");
            level--;
        }
        codeGenerator.writeCodeLine("add esi, edi");


        if (type == ExpressionType.INT || type == ExpressionType.CHAR || type == ExpressionType.BOOL){
            codeGenerator.writeCodeLine("mov eax, [esi]; calculate ExpId ");
            node.setRunTimeType(ExpressionType.INT);
        }
        else if (type == ExpressionType.REAL){
            codeGenerator.writeCodeLine("mov eax, dword ptr [esi]; calculate ExpId(type: real)");
            node.setRunTimeType(ExpressionType.REAL);
        } else {
            codeGenerator.error(node.getLineNumber(), "Unknown running type: " + node.getChildren().get(0).getRunTimeType());
        }
    }
}
