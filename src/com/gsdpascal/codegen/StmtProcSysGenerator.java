package com.gsdpascal.codegen;

import com.gsdpascal.astree.OperationKind;
import com.gsdpascal.astree.TreeNode;

public class StmtProcSysGenerator extends Generator {

    private static StmtInputGenerator inputGenerator;

    private static StmtOutputGenerator outputGenerator;

    StmtProcSysGenerator(CodeGenerator codeGenerator) {
        super(codeGenerator);
        if (inputGenerator == null) {
            inputGenerator = new StmtInputGenerator(codeGenerator);
        }
        if (outputGenerator == null) {
            outputGenerator = new StmtOutputGenerator(codeGenerator);
        }
    }

    @Override
    void generateCode(TreeNode node) {
        if (!(node.getAttribute() instanceof  OperationKind)) {
            codeGenerator.error(node.getLineNumber(), "This is not a valid System call statement(READ OR WRITE): " + node.getAttribute().getClass());
        }
        if (node.getAttribute() == OperationKind.READ) {
            inputGenerator.generateCode(node);
        } else {
            outputGenerator.generateCode(node);
        }
    }
}
