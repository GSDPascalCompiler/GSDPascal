package com.gsdpascal.codegen;

import com.gsdpascal.astree.ExpressionKind;
import com.gsdpascal.astree.StatementKind;
import com.gsdpascal.semantic.SymbolTable;
import com.gsdpascal.astree.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class CodeGenerator {

    private StringBuilder dataSeg = new StringBuilder();
    private StringBuilder codeSeg = new StringBuilder();
    private static CodeGenerator instance;
    private static Map<Class, Map<Object, Generator> > generators = new HashMap<>();

    private CodeGenerator() {

        Map<Object, Generator> stmtGenerators = new HashMap<>();
        stmtGenerators.put(StatementKind.ASSIGN, new StmtAssignGenerator(this));
        stmtGenerators.put(StatementKind.IF, new StmtIfGenerator(this));
        stmtGenerators.put(StatementKind.FOR, new StmtForGenerator(this));
        stmtGenerators.put(StatementKind.WHILE, new StmtWhileGenerator(this));
        stmtGenerators.put(StatementKind.REPEAT, new StmtRepeatGenerator(this));
        stmtGenerators.put(StatementKind.CASE, new StmtCaseGenerator(this));
        stmtGenerators.put(StatementKind.GOTO, new StmtGotoGenerator(this));
        stmtGenerators.put(StatementKind.LABEL, new StmtLabelGenerator(this));
        stmtGenerators.put(StatementKind.PROC_ID, new StmtProcIdGenerator(this));
        stmtGenerators.put(StatementKind.PROC_SYS, new StmtProcSysGenerator(this));

        Map<Object, Generator> expGenerators = new HashMap<>();
        expGenerators.put(ExpressionKind.ID, new ExpIdGenerator(this));
        expGenerators.put(ExpressionKind.OP, new ExpOpGenerator(this));
        expGenerators.put(ExpressionKind.CONST, new ExpConstGenerator(this));
        expGenerators.put(ExpressionKind.CASE, new ExpCaseGenerator(this));
        expGenerators.put(ExpressionKind.FUNC_ID, new ExpFuncIdGenerator(this));

        Map<Object, Generator> declGenerators = new HashMap<>();
        declGenerators.put(DeclarationKind.ROUTINEHEAD, new RoutineHeadGenerator(this));
        declGenerators.put(DeclarationKind.FUNCTION, new FuncDeclGenerator(this));
        declGenerators.put(DeclarationKind.PROCEDURE, new ProcDeclGenerator(this));

        Map<Object, Generator> typeGenerators = new HashMap<>();// typeGenerators is empty

        generators.put(StatementKind.class, stmtGenerators);
        generators.put(ExpressionKind.class, expGenerators);
        generators.put(DeclarationKind.class, declGenerators);
        generators.put(TypeKind.class, typeGenerators);
    }

    public static CodeGenerator getCodeGenerator() {
        if (instance == null) {
            instance = new CodeGenerator();
        }
        return instance;
    }

    public void generate(TreeNode node) {
    	generate(node, "out.asm");
    }

    void writeDataLine(String line) {   	
        dataSeg.append(line).append('\n');   
    }

    void writeCodeLine(String line) {
        codeSeg.append(line).append('\n');
    }

    public void generate(TreeNode node, String fileName) {  	
    	beforeGC(node);
        generateCode(node);
        afterGC();
        writeFinalFile(fileName);
    }

    private void beforeGC(TreeNode node) {
        writeDataLine(".386");
        writeDataLine(".model flat,stdcall");
        writeDataLine("option casemap:none");
        writeDataLine("include msvcrt.inc");
        writeDataLine("includelib msvcrt.lib");

        writeDataLine("printf  proto C:dword,:dword");

        writeDataLine(".data");
        writeDataLine("lb_write_int db '%d',0");
        writeDataLine("lb_writeln_int db '%d',0ah,0dh,0");
        writeDataLine("lb_write_real db '%lf',0");
        writeDataLine("lb_writeln_real db '%lf',0ah,0dh,0");
        writeDataLine("lb_tmp db 0, 0, 0, 0, 0, 0, 0, 0");
        writeDataLine("lb_read_int db '%d',0");
        writeDataLine("lb_read_real db '%f',0");

        writeCodeLine(".code");
        SymbolTable.initScope();
        node.setAttribute("main");
        node.printTree(node);
    }

    private void afterGC() {
        int paraSize = SymbolTable.leaveScope();
        writeCodeLine("add esp, " + paraSize);
        writeCodeLine("ret");
        writeCodeLine("main ENDP");
        writeCodeLine("END main");
    }

    private void writeFinalFile(String fileName) {
        File file = new File(fileName);
        try {
            BufferedWriter out = new BufferedWriter(new FileWriter(file));
            out.write(dataSeg.toString());
            out.write(codeSeg.toString());
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void generateCode(TreeNode node){
    	generateCode(node, true);
    }

    protected void generateCode(TreeNode node, boolean travelSibling) {
        generators.get(node.getNodeType().getClass()).get(node.getNodeType()).generateCode(node);

        //若为false则只处理单颗的子树,主要用于某些同级并列的元素遍历,例如参数列表
        if (travelSibling) {
            if (node.getSibling() != null) {
                generateCode(node.getSibling(), true);
            }
        }
    }

    public void error(int lineNumber, String message) {
        lineNumber++;
        if (lineNumber > 0) {
            System.err.println("Code generation error(line " + lineNumber + "): " + message);
        }  else {
            System.err.println("Code generation error: " + message);
        }
        System.exit(1);
    }

//    public void warning(int lineNumber, String message) {
//        lineNumber++;
//        if (lineNumber > 0) {
//            System.err.println("Code generation warning(line " + lineNumber + "): " + message);
//        } else {
//            System.err.println("Code generation warning: " + message);
//        }
//    }
}
