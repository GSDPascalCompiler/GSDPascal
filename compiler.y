%{
#include "global.h"
#include "parsetree.h"
#include <stdio.h>

extern int yylex();
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
}
			;


program_head	: PROGRAM ID SEMI
{
	$$ = newTreeNode({$2}, NODE_STMT, S_PROGRAM_HEAD, E_NONE);
}
			;

routine		: routine_head routine_body
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_ROUTINE, E_NONE);
}
			;

sub_routine	: routine_head routine_body
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_ROUTINE, E_NONE);
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
	$$ = $1;
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_CONST_PART_NULL, E_NONE);
}
			;

const_expr_list	: const_expr_list ID EQUAL const_value SEMI
{
	$$ = newTreeNode({$1, $2, $4}, NODE_STMT, S_CONST_EXPR_MULT_LIST, E_NONE);
}
				| ID EQUAL const_value SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_CONST_EXPR_LIST, E_NONE);
}
				;

const_value	: INTEGER
{
	$$ = $1;
}
			| REAL
{
	$$ = $1;
}
			| CHAR
{
	$$ = $1;
}
			| STRING
{
	$$ = $1;
}
			| SYS_CON
{
	$$ = $1;
}
			;

type_part	: TYPE type_decl_list
{
	$$ = newTreeNode({$2}, NODE_STMT, S_TYPE_PART, E_NONE);
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_TYPE_PART_NULL, E_NONE);
}
			;

type_decl_list	: type_decl_list type_definition
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_TYPE_DECL_LIST, E_NONE);
}
				| type_definition
{
	$$ = $1;
}
				;

type_definition	: ID EQUAL type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_TYPE_DEFINITION, E_NONE);
}
				;

type_decl 	: simple_type_decl
{
	$$ = $1;
}
			| array_type_decl
{
	$$ = $1;
}
			| record_type_decl
{
	$$ = $1;
}
			;

simple_type_decl	: SYS_TYPE
{
	$$ = $1;
}
					| ID
{
	$$ = $1;
}
					| LP name_list RP
{
	$$ = $2;
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
					;

array_type_decl		: ARRAY LB simple_type_decl RB OF type_decl
{
	$$ = newTreeNode({$3, $6}, NODE_STMT, S_ARRAY_TYPE_DECL, E_NONE);
}
					;

record_type_decl	: RECORD field_decl_list END
{
	$$ = $1;
}
					;

field_decl_list		: field_decl_list field_decl
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_FILED_DECL_LIST, E_NONE);
}
					| field_decl
{
	$$ = $1;
}
					;

field_decl 	: name_list COLON type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_FILED_DECL, E_NONE);
}
			;

name_list	: name_list COMMA ID
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_NAME_LIST, E_NONE);
}
			| ID
{
	$$ = $1;
}
			;

var_part	: VAR var_decl_list
{
	$$ = $1;
}
			|
{
	$$ = newTreeNode({}, NODE_STMT, S_VAR_PART_NULL, E_NONE);
}
			;

var_decl_list	: var_decl_list var_decl
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_VAR_DECL_LIST, E_NONE);
}
				| var_decl
{
	$$ = $1;
}
				;

var_decl 	: name_list COLON type_decl SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_VAR_DECL, E_NONE);
}
			;



















routine_part	: routine_part function_decl
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_ROUTINE_PART_FUNC_LIST, E_NONE);
}
				| routine_part procedure_decl
{
	$$ = newTreeNode({$1, $2}, NODE_STMT, S_ROUTINE_PART_PROC_LIST, E_NONE);
}
				| function_decl
{
	$$ = $1;
}
				| procedure_decl
{
	$$ = $1;
}
				|
{
	$$ = newTreeNode({}, NODE_STMT, S_ROUTINE_NULL, E_NONE);
}
				;

function_decl	: function_head SEMI sub_routine SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_FUNCTION_DECL, E_NONE);
}
				;

function_head	: FUNCTION ID parameters COLON simple_type_decl
{
	$$ = newTreeNode({$2, $3, $5}, NODE_STMT, S_FUNCTION_HEAD, E_NONE);
}
				;

procedure_decl	: procedure_head SEMI sub_routine SEMI
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PROCEDURE_DECL, E_NONE);
}
				;

procedure_head	: PROCEDURE ID parameters
{
	$$ = newTreeNode({$2, $3}, NODE_STMT, S_PROCEDURE_HEAD, E_NONE);
}
				;

parameters		: LP para_decl_list RP
{
	$$ = $1;
}
				|
{
	$$ = newTreeNode({}, NODE_STMT, S_PARAMETERS_NULL, E_NONE);
}
				;

para_decl_list	: para_decl_list SEMI para_type_list
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PARA_DECL_MULTI_LIST, E_NONE);
}
				| para_type_list
{
	$$ = $1;
}
				;

para_type_list	: var_para_list COLON simple_type_decl
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PARA_TYPE_LIST_VAR, E_NONE);
}
				| val_para_list COLON simple_type_decl
{
	$$ = newTreeNode({$1, $3}, NODE_STMT, S_PARA_TYPE_LIST_VAL, E_NONE);
}
				;

var_para_list	: VAR name_list
				{
					$$=$2;
				}
				;

val_para_list	: name_list
				{
					$$=$1;
				}
				;












routine_body	: compound_stmt
				{
					$$=$1;
				}
				;

compound_stmt	: BEG stmt_list END
				{
					$$=newTreeNode({$2},NODE_STMT,S_COMPOUND_STMT,E_NONE);
				}
				;

stmt_list	: stmt_list stmt SEMI
			{
				$$=newTreeNode({$1,$2},NODE_STMT,S_STMT_LIST,E_NONE);
			}
			|
			;

stmt 		: INTEGER COLON non_label_stmt
			{
				$$=newTreeNode({$1,$3},NODE_STMT,S_STMT,E_NONE);
			}
			| non_label_stmt
			{
				$$=$1;
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
				}
				| ID LB expression RB ASSIGN expression
				{
					$$=newTreeNode({$1,$3,$6},NODE_STMT,S_ASSIGN_ARRAY,E_NONE);
				}
				| ID DOT ID ASSIGN expression
				{
					$$=newTreeNode({$1,$3,$5},NODE_STMT,S_ASSIGN_RECORD,E_NONE);
				}
				;

proc_stmt		: ID
				{
					$$=newTreeNode({$1},NODE_STMT,S_PROC,E_NONE);
				}
				| ID LP args RP
				{
					$$=newTreeNode({$3},NODE_STMT,S_PROC_FUNC,E_NONE);
				}
				| SYS_PROC
				{
					$$=newTreeNode({$1},NODE_STMT,S_PROC_SYS,E_NONE);
				}
				| SYS_PROC LP expression_list RP
				{
					$$=newTreeNode({$1,$2},NODE_STMT,S_PROC_SYS_ARG,E_NONE);
				}
				| READ LP factor RP
				{
					$$=newTreeNode({$3},NODE_STMT,S_PROC_READ,E_NONE);
				}
				;

if_stmt			: IF expression THEN stmt else_clause
				{
					$$=newTreeNode({$2,$4,$5},NODE_STMT,S_IF,E_NONE);
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
				}
				;

while_stmt		: WHILE expression DO stmt
				{
						$$=newTreeNode({$2,$4},NODE_STMT,S_WHILE,E_NONE);
				}
				;

for_stmt		: FOR ID ASSIGN expression direction expression DO stmt
				{
					$$=newTreeNode({$4,$5,$6,$8},NODE_STMT,S_FOR,E_NONE);
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
				}
				;

case_expr_list	: case_expr_list case_expr
				{
					$$=newTreeNode({$1,$2},NODE_STMT,S_CASE_EXPR_LIST,E_NONE);
				}
				| case_expr
				{
					$$=$1;
				}
				;

case_expr 		: const_value COLON stmt SEMI
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_CASE_EXPR_CONST,E_NONE);
				}
				| ID COLON stmt SEMI
				{
					$$=newTreeNode({$1,$3},NODE_STMT,S_CASE_EXPR_ID,E_NONE);
				}
				;

goto_stmt		: GOTO INTEGER
				{
					$$=newTreeNode({$2},NODE_STMT,S_GOTO,E_NONE);
				}
				;

expression_list	: expression_list COMMA expression
				{
					$$=newTreeNode({$1, $3},NODE_STMT,S_EXPRESSION_LIST,E_NONE);
				}
				| expression
				{
					$$=$1;
				}
				;

expression 		: expression GE expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_GE);
				}
				| expression GT expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_GT);
				}
				| expression LE expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_LE);
				}
				| expression LT expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_LT);
				}
				| expression EQUAL expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_EQUAL);
				}
				| expression UNEQUAL expr
				{
					$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_UNEQUAL);
				}
				| expr
				{
					$$=$1;
				}
				;

expr 	: expr PLUS term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_PLUS);
		}
		| expr MINUS term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MINUS);
		}
		| expr OR term
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_OR);
		}
		| term
		{
			$$=$1;
		}
		;

term	: term MUL factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MUL);
		}
		| term DIV factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_DIV);
		}
		| term MOD factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_MOD);
		}
		| term AND factor
		{
			$$=newTreeNode({$1, $3},NODE_EXP,S_NONE,E_AND);
		}
		| factor
		{
			$$=$1;
		}
		;

factor	:SYS_FUNCT
		{
			$$=newTreeNode({$1},NODE_STMT,S_FACTOR_SYS,E_NONE);
		}
		| SYS_FUNCT LP args_list RP
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_SYS_ARG,E_NONE);
		}
		| const_value
		{
			$$=$1;
		}
		| LP expression RP
		{
			$$=$2;
		}
		| NOT factor
		{
			$$=newTreeNode({$2},NODE_STMT,S_FACTOR_NOT,E_NONE);
		}
		| MINUS factor
		{
			$$=newTreeNode({$2},NODE_STMT,S_FACTOR_MINUS,E_NONE);
		}
		| ID LB expression RB
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_ARRAY,E_NONE);
		}
		| ID LP args RP{/*new added*/}
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_FUNC,E_NONE);
		}
		| ID DOT ID
		{
			$$=newTreeNode({$1,$3},NODE_STMT,S_FACTOR_RECORD,E_NONE);
		}
		| ID
		{
			$$=newTreeNode({$1},NODE_STMT,S_FACTOR_ID,E_NONE);
		}
		;

args 		: args_list {/*new added*/}
			{
				$$=newTreeNode({$1},NODE_STMT,S_ARGS,E_NONE);
			}
			|
			;

args_list	: args_list COMMA expression
			{
				$$=newTreeNode({$1, $3},NODE_STMT,S_ARGS_LIST,E_NONE);
			}
			| expression
			{
				$$=newTreeNode({$1},NODE_STMT,S_ARGS_LIST_EXP,E_NONE);
			}
			;
%%
int main(){
	return yyparse();
}
