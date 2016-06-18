%{
#include <stdio.h>
#include "intermedia.h"
#include "global.h"
#include "parsetree.h"
#include "util.h"
#include <vector>

extern int yylex();
extern SymbolItem *procFunc;
int yyerror(const char *s){
	printf("%s\n", s);
	return 0;
}

%}

%token READ TYPE
%token LP RP LB RB
%token PLUS MINUS MUL DIV MOD AND OR NOT ASSIGN
%token GE GT LE LT EQUAL UNEQUAL
%token INTEGER
%token REAL
%token CHAR
%token STRING
%token CONST ARRAY
%token SYS_CON SYS_TYPE SYS_PROC SYS_FUNCT
%token PROGRAM FUNCTION PROCEDURE RECORD
%token ID
%token VAR
%token DOT SEMI COLON COMMA
%token OF BEG END TO DOWNTO
%token IF THEN ELSE REPEAT UNTIL WHILE DO FOR GOTO CASE

%%
program 	: program_head routine DOT
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_PROGRAM, E_NONE);
	printTreeNodes($$.data.treeNode, 0);
	printVecTAC();
}
			;


program_head	: PROGRAM ID SEMI
{
	$$ = newTreeNode({$2}, NODE_STMT, S_PROGRAM_HEAD, E_NONE);
	computeAttrGrammar($$);
	symtable.showCurrentTable();
}
			;

routine		: routine_head routine_body
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_ROUTINE, E_NONE);
	symtable.leaveScope();
}
			;

sub_routine	: routine_head routine_body
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_SUB_ROUTINE, E_NONE);
}
			;




















routine_head	: label_part const_part type_part var_part routine_part
{
	$$ = newTreeNode({$1, $2, $3, $4, $5}, NODE_STMT, S_ROUTINE_HEAD, E_NONE);
}
				;

label_part	:
{
	$$ = newTreeNode({}, NODE_STMT, S_LABEL_PART_NULL, E_NONE);
}
			;

const_part	: CONST const_expr_list
{
	$$ = newTreeNode({$2}, NODE_STMT, S_CONST_PART, E_NONE);;
	symtable.showCurrentTable();
	showErrMsg();
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_CONST_PART_NULL, E_NONE);
}
			;

const_expr_list	: const_expr_list const_expr
{
	$$ = linkTreeNode($1, $2);
}
				| const_expr
{
	$$ = newTreeNode({$1}, NODE_STMT, S_CONST_EXPR_LIST, E_NONE);
}
				;

const_expr 	: ID EQUAL const_value SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_CONST_EXPR, E_NONE);
	if(computeAttrGrammar($$) == false)
		showErrMsg();
	
}
			;

const_value	: INTEGER
{
	$$ = newTreeNode({$1},NODE_STMT,S_CONST_VALUE_INT,E_NONE);
}
			| REAL
{
	$$ = newTreeNode({$1},NODE_STMT,S_CONST_VALUE_REAL,E_NONE);
}
			| CHAR
{
	$$ = newTreeNode({$1},NODE_STMT,S_CONST_VALUE_CHAR,E_NONE);
}
			| STRING
{
	$$ = newTreeNode({$1},NODE_STMT,S_CONST_VALUE_STRING,E_NONE);
}
			| SYS_CON
{
	$$ = newTreeNode({$1},NODE_STMT,S_CONST_VALUE_SYS_CON,E_NONE);
}
			;

type_part	: TYPE type_decl_list
{
	$$ = newTreeNode({$2}, NODE_STMT, S_TYPE_PART, E_NONE);
	symtable.showCurrentTable();
	showErrMsg();
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_TYPE_PART_NULL, E_NONE);
}
			;

type_decl_list	: type_decl_list type_definition
{
	$$ = linkTreeNode($1, $2);
}
				| type_definition
{
	$$ = newTreeNode({$1}, NODE_STMT, S_TYPE_DECL_LIST, E_NONE);;
}
				;

type_definition	: ID EQUAL type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_TYPE_DEFINITION, E_NONE);
	computeAttrGrammar($$);
}
				;

type_decl 	: simple_type_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_TYPE_DECL_SIMPLE, E_NONE);
}

			| array_type_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_TYPE_DECL_ARRAY, E_NONE);

}
			| record_type_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_TYPE_DECL_RECORD, E_NONE);

}
			;

simple_type_decl	: SYS_TYPE
{
	$$ = newTreeNode({$1}, NODE_STMT,S_SIMPLE_TYPE_DECL_SYS,E_NONE);
}
					| ID
{
	$$ = newTreeNode({$1}, NODE_STMT,S_SIMPLE_TYPE_DECL_ID,E_NONE);
}
					| LP name_list RP
{
	$$ = newTreeNode({$2}, NODE_STMT,S_SIMPLE_TYPE_DECL_NAME_LIST,E_NONE);
}
					| const_value DOT DOT const_value
{
	$$ = newTreeNode({$1, $4}, NODE_STMT, S_SIMPLE_TYPE_DECL_CDC, E_NONE);
}
					| MINUS const_value DOT DOT const_value
{
	$$ = newTreeNode({$2, $5}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDC, E_NONE);
}
					| MINUS const_value DOT DOT MINUS const_value
{
	$$ = newTreeNode({$2, $6}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDMC, E_NONE);
}
					| ID DOT DOT ID
{
	$$ = newTreeNode({$1, $4}, NODE_STMT, S_SIMPLE_TYPE_DECL_IDI, E_NONE);
}
					| const_value DOT DOT ID
{
	$$ = newTreeNode({$1, $4}, NODE_STMT, S_SIMPLE_TYPE_DECL_CDI, E_NONE);
}
					| ID DOT DOT const_value
{
	$$ = newTreeNode({$1, $4}, NODE_STMT, S_SIMPLE_TYPE_DECL_IDC, E_NONE);
}
					;

array_type_decl		: ARRAY LB simple_type_decl RB OF type_decl
{
	$$ = newTreeNode({$3, $6}, NODE_STMT, S_ARRAY_TYPE_DECL, E_NONE);
}
					;

record_type_decl	: RECORD field_decl_list END
{
	$$ = newTreeNode({$2}, NODE_STMT, S_RECORD_TYPE_DECL, E_NONE);
}
					;

field_decl_list		: field_decl_list field_decl
{
	$$ = linkTreeNode($1, $2);
}
					| field_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_FILED_DECL_LIST, E_NONE);
}
					;

field_decl 	: name_list COLON type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_FILED_DECL, E_NONE);
}
			;

name_list	: name_list COMMA name
{
	$$ = linkTreeNode($1, $3);
}
			| name
{
	$$ = newTreeNode({$1}, NODE_STMT, S_NAME_LIST,E_NONE);
}
			;

name:ID
{
$$ = newTreeNode({$1}, NODE_STMT, S_NAME,E_NONE);
}
;

var_part	: VAR var_decl_list
{
	$$ = newTreeNode({$2}, NODE_STMT, S_VAR_PART, E_NONE);
	symtable.showCurrentTable();
	showErrMsg();
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_VAR_PART_NULL, E_NONE);
}
			;

var_decl_list	: var_decl_list var_decl
{
	$$ = linkTreeNode($1, $2);
}
				| var_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_VAR_DECL_LIST, E_NONE);
}
				;

var_decl 	: name_list COLON type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_VAR_DECL, E_NONE);
	computeAttrGrammar($$);
}
			;




















routine_part	: routine_part function_decl
{
	$$ = linkTreeNode($1, $2);
}
				| routine_part procedure_decl
{
	$$ = linkTreeNode($1, $2);
}
				| function_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_ROUTINE_PART_FUNC_LIST, E_NONE);
}
				| procedure_decl
{
	$$ = newTreeNode({$1}, NODE_STMT, S_ROUTINE_PART_PROC_LIST, E_NONE);
}
				|
{
	$$ = newTreeNode({}, NODE_STMT, S_ROUTINE_NULL, E_NONE);
}
				;

function_decl	: function_head SEMI sub_routine SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_FUNCTION_DECL, E_NONE);
	procFunc = new SymbolItem();
	memcpy(procFunc, symtable.getFromSymtable($1.data.treeNode->leftChild->value.nodeId.id), sizeof(SymbolItem));
	symtable.leaveScope();
	computeAttrGrammar($$);
	symtable.showCurrentTable();
	showErrMsg();
}
				;

function_head	: FUNCTION ID parameters COLON simple_type_decl
{
	$$ = newTreeNode({$2, $3, $5}, NODE_STMT, S_FUNCTION_HEAD, E_NONE);
	symtable.setFuncName($$.data.treeNode->leftChild->value.nodeId.id);
	computeAttrGrammar($$);
	symtable.showCurrentTable();
}
				;

procedure_decl	: procedure_head SEMI sub_routine SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PROCEDURE_DECL, E_NONE);
	procFunc = new SymbolItem();
	memcpy(procFunc, symtable.getFromSymtable($1.data.treeNode->leftChild->value.nodeId.id), sizeof(SymbolItem));
	symtable.leaveScope();
	computeAttrGrammar($$);
	symtable.showCurrentTable();
	showErrMsg();
}
				;

procedure_head	: PROCEDURE ID parameters
{
	$$ = newTreeNode({$2, $3}, NODE_STMT, S_PROCEDURE_HEAD, E_NONE);
	symtable.setFuncName($$.data.treeNode->leftChild->value.nodeId.id);
	computeAttrGrammar($$);
	symtable.showCurrentTable();
	showErrMsg();
}
				;

parameters		: LP para_decl_list RP
{
	$$ = newTreeNode({$2}, NODE_STMT, S_PARAMETERS, E_NONE);
}
				|
{
	$$ = newTreeNode({}, NODE_STMT, S_PARAMETERS_NULL, E_NONE);
}
				;

para_decl_list	: para_decl_list SEMI para_type_list
{
	$$ = linkTreeNode($1, $3);
}
				| para_type_list
{
	$$ = newTreeNode({$1}, NODE_STMT, S_PARA_DECL_LIST, E_NONE);
}
				;

para_type_list	: var_para_list COLON simple_type_decl
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PARA_TYPE_LIST_VAR, E_NONE);
	computeAttrGrammar($$);
	symtable.showCurrentTable();
}
				| val_para_list COLON simple_type_decl
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PARA_TYPE_LIST_VAL, E_NONE);
	computeAttrGrammar($$);
	symtable.showCurrentTable();
}
				;

var_para_list	: VAR name_list
				{
					$$=newTreeNode({$2}, NODE_STMT, S_VAR_PARA_LIST, E_NONE);
				}
				;

val_para_list	: name_list
				{
					$$=newTreeNode({$1}, NODE_STMT, S_VAL_PARA_LIST, E_NONE);
				}
				;











routine_body	: compound_stmt
				{
					$$=newTreeNode({$1},NODE_STMT,S_ROUTINE_BODY,E_NONE);
				}
				;

compound_stmt	: BEG stmt_list END
				{
					$$=newTreeNode({$2},NODE_STMT,S_COMPOUND_STMT,E_NONE);
				}
				;

stmt_list	: stmt_list stmt SEMI
			{
				$$=linkTreeNode($1, $2);
			}
			|
			{
				$$=newTreeNode({}, NODE_STMT, S_STMT_LIST, E_NONE);
			}
			;

stmt 		: INTEGER COLON non_label_stmt
			{
				$$=newTreeNode({$1,$3},NODE_STMT,S_STMT,E_NONE);
				
			}
			| non_label_stmt
			{
				$$=newTreeNode({$1},NODE_STMT,S_STMT_NON,E_NONE);
			}
			;

non_label_stmt	: assign_stmt
				{
					$$=$1;
				}
				| proc_stmt
				{
					$$=$1;
				}
				| compound_stmt
				{
					$$=$1;
				}
				| if_stmt
				{
					$$=$1;
				}
				| repeat_stmt
				{
					$$=$1;
				}
				| while_stmt
				{
					$$=$1;
				}
				| for_stmt
				{
					$$=$1;
				}
				| case_stmt
				{
					$$=$1;
				}
				| goto_stmt
				{
					$$=$1;
				}
				;

assign_stmt 	: ID ASSIGN expression
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_ASSIGN,E_NONE);
					computeAttrGrammar($$);
					generateTAC($$);
				}
				| ID LB expression RB ASSIGN expression
				{
					$$=newTreeNode({$1,$3,$6},NODE_STMT,S_ASSIGN_ARRAY,E_NONE);
					computeAttrGrammar($$);
				}
				| ID DOT ID ASSIGN expression
				{
					$$=newTreeNode({$1,$3,$5},NODE_STMT,S_ASSIGN_RECORD,E_NONE);
					computeAttrGrammar($$);
				}
				;

proc_stmt		: ID
				{
					$$=newTreeNode({$1},NODE_STMT,S_PROC,E_NONE);
					computeAttrGrammar($$);
				}
				| ID LP args RP
				{
					$$=newTreeNode({$3},NODE_STMT,S_PROC_FUNC,E_NONE);
					computeAttrGrammar($$);
				}
				| SYS_PROC
				{
					$$=newTreeNode({$1},NODE_STMT,S_PROC_SYS,E_NONE);
				}
				| SYS_PROC LP expression_list RP
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_PROC_SYS_ARG,E_NONE);
				}
				| READ LP factor RP
				{
					$$=newTreeNode({$3},NODE_STMT,S_PROC_READ,E_NONE);
				}
				;

if_stmt			: IF expression THEN stmt else_clause
				{
					$$=newTreeNode({$2,$4,$5},NODE_STMT,S_IF,E_NONE);
					computeAttrGrammar($$);
				}
				;

else_clause		: ELSE stmt
				{
					$$=newTreeNode({$2},NODE_STMT,S_ELSE,E_NONE);
				}
				|
				;

repeat_stmt		: REPEAT stmt_list UNTIL expression
				{
					$$=newTreeNode({$2,$4},NODE_STMT,S_REPEAT,E_NONE);
					computeAttrGrammar($$);
				}
				;

while_stmt		: WHILE expression DO stmt
				{
					$$=newTreeNode({$2,$4},NODE_STMT,S_WHILE,E_NONE);
					computeAttrGrammar($$);
				}
				;

for_stmt		: FOR ID ASSIGN expression direction expression DO stmt
				{
					$$=newTreeNode({$2, $4,$5,$6,$8},NODE_STMT,S_FOR,E_NONE);
					computeAttrGrammar($$);
				}
				;

direction		: TO
				{
					$$=newTreeNode({$1},NODE_STMT,S_DIRECTION_TO,E_NONE);
				}
				| DOWNTO
				{
					$$=newTreeNode({$1},NODE_STMT,S_DIRECTION_DOWNTO,E_NONE);
				}
				;

case_stmt		: CASE expression OF case_expr_list END
				{
					$$=newTreeNode({$2,$4},NODE_STMT,S_CASE,E_NONE);
					computeAttrGrammar($$);
				}
				;

case_expr_list	: case_expr_list case_expr
				{
					$$=linkTreeNode($1, $2);
					computeAttrGrammar($$);
				}
				| case_expr
				{
					$$=newTreeNode({$1},NODE_STMT,S_CASE_EXPR_LIST,E_NONE);
					computeAttrGrammar($$);
				}
				;

case_expr 		: const_value COLON stmt SEMI
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_CASE_EXPR_CONST,E_NONE);
					computeAttrGrammar($$);
				}
				| ID COLON stmt SEMI
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_CASE_EXPR_ID,E_NONE);
					computeAttrGrammar($$);
				}
				;

goto_stmt		: GOTO INTEGER
				{
					$$=newTreeNode({$2},NODE_STMT,S_GOTO,E_NONE);
					computeAttrGrammar($$);
				}
				;

expression_list	: expression_list COMMA expression
				{
					$$=linkTreeNode($1, $3);
					computeAttrGrammar($$);
					generateTAC($$);
				}
				| expression
				{
					$$=newTreeNode({$1},NODE_STMT,S_EXPRESSION_LIST,E_NONE);
					computeAttrGrammar($$);
					generateTAC($$);
				}
				;

expression 		: expression GE expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_GE);
					computeAttrGrammar($$);
				}
				| expression GT expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_GT);
					computeAttrGrammar($$);
				}
				| expression LE expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_LE);
					computeAttrGrammar($$);
				}
				| expression LT expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_LT);
					computeAttrGrammar($$);
				}
				| expression EQUAL expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_EQUAL);
					computeAttrGrammar($$);
				}
				| expression UNEQUAL expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_UNEQUAL);
					computeAttrGrammar($$);
				}
				| expr
				{
					$$=$1;
				}
				;

expr 	: expr PLUS term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_PLUS);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| expr MINUS term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MINUS);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| expr OR term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_OR);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| term
		{
			$$=$1;
		}
		;

term	: term MUL factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MUL);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| term DIV factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_DIV);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| term MOD factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MOD);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| term AND factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_AND);
			computeAttrGrammar($$);
			generateTAC($$);
		}
		| factor
		{
			$$=$1;
		}
		;

factor	:SYS_FUNCT
		{
			$$=newTreeNode({$1},NODE_STMT,S_FACTOR_SYS,E_NONE);
			computeAttrGrammar($$);
		}
		| SYS_FUNCT LP args_list RP
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_SYS_ARG,E_NONE);
			computeAttrGrammar($$);
		}
		| const_value
		{
			$$=newTreeNode({$1}, NODE_STMT, S_FACTOR_CONST, E_NONE);
			computeAttrGrammar($$);
		}
		| LP expression RP
		{
			$$=$2;
		}
		| NOT factor
		{
			$$=newTreeNode({$2},NODE_STMT,S_FACTOR_NOT,E_NONE);
			computeAttrGrammar($$);
		}
		| MINUS factor
		{
			$$=newTreeNode({$2},NODE_STMT,S_FACTOR_MINUS,E_NONE);
			computeAttrGrammar($$);
		}
		| ID LB expression RB
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_ARRAY,E_NONE);
			computeAttrGrammar($$);
		}
		| ID LP args RP{/*new added*/}
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_FUNC,E_NONE);
			computeAttrGrammar($$);
		}
		| ID DOT ID
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_RECORD,E_NONE);
			computeAttrGrammar($$);
		}
		| ID
		{
			$$=newTreeNode({$1},NODE_STMT,S_FACTOR_ID,E_NONE);
			computeAttrGrammar($$);
		}
		;

args 		: args_list 
			{
				$$=newTreeNode({$1},NODE_STMT,S_ARGS,E_NONE);
				computeAttrGrammar($$);
			}
			|
			{
				$$=newTreeNode({},NODE_STMT,S_ARGS_NULL,E_NONE);
			}
			;

args_list	: args_list COMMA expression
			{
				$$=linkTreeNode($1, $3);
			}
			| expression
			{
				$$=newTreeNode({$1},NODE_STMT,S_ARGS_LIST,E_NONE);
			}
			;
%%
int main(){
	int ret = yyparse();
	savedTable.showAllTable();
	return ret;
}
