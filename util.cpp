#include "util.h"
#include <stdio.h>

void Print(TokenType type){
	switch(type){
		case T_READ: printf("READ"); break;
		case T_TYPE: printf("TYPE"); break;
		case T_INTEGER: printf("INTEGER"); break;
		case T_REAL: printf("REAL"); break;
		case T_CHAR: printf("CHAR"); break;
		case T_STRING: printf("STRING"); break;
		case T_CONST: printf("CONST"); break;
		case T_ARRAY: printf("ARRAY"); break;
		case T_SYS_CON: printf("SYS_CON"); break;
		case T_SYS_TYPE: printf("SYS_TYPE"); break;
		case T_SYS_PROC: printf("SYS_PROC"); break;
		case T_SYS_FUNCT: printf("SYS_FUNC"); break;
		default: printf("OTHERS"); break;
	}
}

void Print(StmtType type){
	switch(type){
		case S_PROGRAM: printf("PROGRAM"); break;
		case S_PROGRAM_HEAD: printf("PROGRAM_HEAD"); break;
		case S_ROUTINE: printf("ROUTINE"); break;
		case S_ROUTINE_HEAD: printf("ROUTINE_HEAD"); break;
		case S_LABEL_PART_NULL: printf("LABEL_PART"); break;
		case S_CONST_PART_NULL: printf("CONST_PART"); break;
		case S_CONST_EXPR_MULT_LIST: case S_CONST_EXPR_LIST: printf("CONST_EXPR_LIST"); break;
		case S_TYPE_PART: case S_TYPE_PART_NULL: printf("TYPE_PART"); break;
		case S_TYPE_DECL_LIST: printf("TYPE_DECL_LIST"); break;
		case S_TYPE_DEFINITION: printf("TYPE_DEFINITION"); break;
		case S_FILED_DECL_LIST: case S_FILED_DECL: printf("FLED_DECL_LIST"); break;
		case S_NAME_LIST: printf("NAME_LIST"); break;
		case S_VAR_DECL_LIST: case S_VAR_DECL: case S_VAR_PART_NULL: printf("VAR_DECL_LIST"); break;
		case S_ROUTINE_PART_FUNC_LIST: case S_ROUTINE_PART_PROC_LIST: case S_ROUTINE_NULL: printf("ROUTINE_PART"); break;
		case S_FUNCTION_DECL: printf("FUNCTION_DECL"); break;
		case S_FUNCTION_HEAD: printf("FUNCTION_HEAD"); break;
		case S_PROCEDURE_DECL: printf("PROCEDURE_DECL"); break;
		case S_PROCEDURE_HEAD: printf("PROCEDURE_HEAD"); break;


		default: printf("OTHERS"); break;
	}
}

void Print(ExpType type){
	switch(type){
		E_AND: printf("AND"); break;
		E_MOD: printf("MOD"); break;
		E_DIV: printf("DIV"); break;
		E_MUL: printf("MUL"); break;
		E_OR: printf("OR"); break;
		E_MINUS: printf("MINUS"); break;
		E_PLUS: printf("PLUS"); break;
		E_UNEQUAL: printf("UNEQUAL"); break;
		E_EQUAL: printf("EQUAL"); break;
		E_LT: printf("LT"); break;
		E_LE: printf("LE"); break;
		E_GT: printf("GT"); break;
		E_GE: printf("GE"); break;
	}
}
void printTreeNodes(TreeNode root, int level){
	for(int i = 0; i < level; ++i)
      printf("----");
  if(root.nodeType == NODE_TOKEN){
    
    printf("token: "); 
    switch (root.typeValue.tokenType)
    {
        case T_INTEGER:
        	Print(root.typeValue.tokenType);
          printf(" = %d\n", root.value.nodeInteger.i);
          break;
        case T_REAL:
        Print(root.typeValue.tokenType);
          printf(" = %lf\n", root.value.nodeReal.r);
          break;
        case T_CHAR:
        Print(root.typeValue.tokenType);
          printf(" = %c\n", root.value.nodeChar.c);
          break;
        case T_STRING:
        Print(root.typeValue.tokenType);
          printf(" = %s\n", root.value.nodeString.s);
          break;
        case T_ID:
        Print(root.typeValue.tokenType);
          printf(" = %s\n", root.value.nodeId.id);
          break;
        default:
          Print(root.typeValue.tokenType); puts("");
          ;
    }
  }
  else{
  	if(root.nodeType == NODE_STMT){
  		printf("stmt: "); Print(root.typeValue.stmtType); printf("\n");
  	}
  	else if(root.nodeType == NODE_EXP){
  		printf("expr: ");  Print(root.typeValue.expType); printf("\n");
  	}
    for(int i = 0; i < 10; ++i){
      if(root.value.nodeNonleaf.child[i] != nullptr){
        printTreeNodes(*(root.value.nodeNonleaf.child[i]), level+1);
      }
    }
  }
}



void printParseTree(TreeNode *root)
{
  
}
