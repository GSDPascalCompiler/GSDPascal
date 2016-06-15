#include "util.h"
#include <cstdio>
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

const string indent = "    ";
#define MAXLEVEL  100
#define OUT stdout

void Print(NodeType type)
{
	switch (type)
	{
	NODE_TOKEN: cout << "TOKEN"; break;
	NODE_EXP:cout << "EXP"; break;
	NODE_STMT:cout << "STMT"; break;
	default:cout << "UNKNOWN"; break;
	}
}

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
		default: printf("OTHERS:%d",type); break;
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
		case S_CONST_EXPR_LIST: printf("CONST_EXPR_LIST"); break;
		case S_CONST_VALUE_INT: printf("CONST_VALUE_INT"); break;
		case S_CONST_VALUE_REAL: printf("CONST_VALUE_REAL"); break;
		case S_CONST_VALUE_CHAR: printf("CONST_VALUE_CHAR"); break;
		case S_CONST_VALUE_STRING: printf("CONST_VALUE_STRING"); break;
		case S_CONST_VALUE_SYS_CON: printf("CONST_VALUE_SYS_CON"); break;
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
		case S_PARAMETERS_NULL: printf("VAR_DECL_LIST"); break;
		case S_PARA_TYPE_LIST_VAR: case S_PARA_TYPE_LIST_VAL: printf("PARA_TYPE_LIST"); break;
		case S_COMPOUND_STMT: printf("COUNPOUND_STMT"); break;
		case S_STMT_LIST: printf("STMT_LIST"); break;
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
		default: printf("OTHERS:%d",type); break;
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

void PrintNode(TreeNode* node)
{
	switch (node->nodeType)
	{
	case NODE_TOKEN: Print(node->typeValue.tokenType); break;
	case NODE_EXP:	Print(node->typeValue.expType);	break;
	case NODE_STMT:	Print(node->typeValue.stmtType); break;
	default:cout << "UNKNOWN"; break;
	}
}

bitset<MAXLEVEL> parentIsLast;
void printTreeNodes(TreeNode *root, int level)
{
	if (level == 0)
		cout << endl << endl;
	if (root == nullptr)
		return;
	for (int i = 0; i < level; i++)
	{
		if (!parentIsLast[i])
			cout << "|";
		cout << indent;
	}
	cout << "|-";
	PrintNode(root);
	cout << endl;
	if (root->rightSibling == nullptr)
		parentIsLast.set(level);
	else
		parentIsLast.reset(level);
	TreeNode *p = root->leftChild;
	for (; p != nullptr; p = p->rightSibling)
		printTreeNodes(p, level + 1);
}



void printParseTree(TreeNode *root)
{
  
}
