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
		case T_ID: printf("ID"); break;
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
		case S_PARAMETERS_NULL: case S_PARA_DECL_MULTI_LIST: printf("VAR_DECL_LIST"); break;
		case S_PARA_TYPE_LIST_VAR: case S_PARA_TYPE_LIST_VAL: printf("PARA_TYPE_LIST"); break;
		case S_COMPOUND_STMT: printf("COUNPOUND_STMT"); break;
		case S_STMT_LIST: case S_STMT_LIST_NULL: printf("STMT_LIST"); break;
		case S_STMT: printf("STMT");
		case S_ASSIGN: case S_ASSIGN_ARRAY: case S_ASSIGN_RECORD: printf("ASSIGN_STMT"); break;
		case S_PROC: case S_PROC_FUNC: case S_PROC_SYS: case S_PROC_SYS_ARG: case S_PROC_READ: printf("PROC_STMT"); break;
		case S_IF: printf("IF_STMT"); break;
		case S_ELSE: printf("ELSE_CLAUSE"); break;
		case S_REPEAT: printf("REPEATE_STMT"); break;
		case S_WHILE: printf("WHILE_STMT"); break;
		case S_FOR: printf("FOR_STMT"); break;
		case S_DIRECTION_TO: case S_DIRECTION_DOWNTO: printf("DIRECTION"); break;
		case S_CASE_EXPR_LIST: printf("CASE_EXPR_LIST"); break;
		case S_CASE_EXPR_CONST: case S_CASE_EXPR_ID: printf("CASE_EXPR"); break;
		case S_GOTO: printf("GOTO_STMT"); break;
		case S_EXPRESSION_LIST: printf("EXPRESSION_LIST"); break;
		case S_FACTOR_SYS: case S_FACTOR_SYS_ARG: case S_FACTOR_NOT: case S_FACTOR_MINUS: case S_FACTOR_ARRAY: case S_FACTOR_FUNC:
		case S_FACTOR_RECORD: case S_FACTOR_ID: printf("FACTOR"); break;
		case S_ARGS: printf("ARGS"); break;
		case S_ARGS_LIST: case S_ARGS_LIST_EXP: printf("ARGS_LIST"); break;
		case S_SIMPLE_TYPE_DECL_SYS: printf("S_SIMPLE_TYPE_DECL"); break;
		default: printf("OTHERS"); break;
	}
}

void Print(ExpType type){
	switch(type){
		case E_AND: printf("AND"); break;
		case E_MOD: printf("MOD"); break;
		case E_DIV: printf("DIV"); break;
		case E_MUL: printf("MUL"); break;
		case E_OR: printf("OR"); break;
		case E_MINUS: printf("MINUS"); break;
		case E_PLUS: printf("PLUS"); break;
		case E_UNEQUAL: printf("UNEQUAL"); break;
		case E_EQUAL: printf("EQUAL"); break;
		case E_LT: printf("LT"); break;
		case E_LE: printf("LE"); break;
		case E_GT: printf("GT"); break;
		case E_GE: printf("GE"); break;
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
		case T_SYS_TYPE:
			Print(root.typeValue.tokenType);
			switch (root.value.nodeSysTypeVal.sysTypeVal)
			{
			case TYPE_BOOLEAN:
				printf(" = %s\n", "BOOLEAN");
				break;
			case TYPE_CHAR:
				printf(" = %s\n", "CHAR");
				break;
			case TYPE_INTEGER:
				printf(" = %s\n", "INTEGER");
				break;
			case TYPE_REAL:
				printf(" = %s\n", "REAL");
				break;
			default:
				printf(" = %s\n", "OTHER");
				break;
			}
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
