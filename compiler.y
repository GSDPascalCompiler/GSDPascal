%{
#include "global.h"
#include "parser.h"
#include <stdio.h>
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
%token NAME VAR
%token DOT SEMI COLON COMMA
%token OF BEG END TO DOWNTO
%token IF THEN ELSE REPEAT UNTIL WHILE DO FOR GOTO CASE

%%
program 	: program_head routine DOT
{

}
			;


program_head	: PROGRAM ID SEMI
{

}
			;

routine		: routine_head routine_body
			;

sub_routine	: routine_head routine_body
			;




















routine_head	: label_part const_part type_part var_part routine_part
				;

label_part	:
			;

const_part	: CONST const_expr_list
			|
			;

const_expr_list	: const_expr_list NAME EQUAL const_value SEMI
				| NAME EQUAL const_value SEMI
				;

const_value	: INTEGER
{

}
			| REAL
			| CHAR
			| STRING
			| SYS_CON
			;

type_part	: TYPE type_decl_list
			|
			;

type_decl_list	: type_decl_list type_definition
				| type_definition
				;

type_definition	: NAME EQUAL type_decl SEMI
				;

type_decl 	: simple_type_decl
			| array_type_decl
			| record_type_decl
			;

simple_type_decl	: SYS_TYPE
					| NAME
					| LP name_list RP
					| const_value DOT DOT const_value
					| MINUS const_value DOT DOT const_value
					| MINUS const_value DOT DOT MINUS const_value
					| NAME DOT DOT NAME
					;

array_type_decl		: ARRAY LB simple_type_decl RB OF type_decl
					;

record_type_decl	: RECORD field_decl_list END
					;

field_decl_list		: field_decl_list field_decl
					| field_decl
					;

field_decl 	: name_list COLON type_decl SEMI
			;

name_list	: name_list COMMA ID
			| ID
			;

var_part	: VAR var_decl_list
			|
			;

var_decl_list	: var_decl_list var_decl
				| var_decl
				;

var_decl 	: name_list COLON type_decl SEMI
			;



















routine_part	: routine_part function_decl
				| routine_part procedure_decl
				| function_decl
				| procedure_decl
				|
				;

function_decl	: function_head SEMI sub_routine SEMI
				;

function_head	: FUNCTION ID parameters COLON simple_type_decl
				;

procedure_decl	: procedure_head SEMI sub_routine SEMI
				;

procedure_head	: PROCEDURE ID parameters
				;

parameters		: LP para_decl_list RP
				|
				;

para_decl_list	: para_decl_list SEMI para_type_list
				| para_type_list
				;

para_type_list	: var_para_list COLON simple_type_decl
				| val_para_list COLON simple_type_decl
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
					$$=newTreeNode({$2,$4,$5,$6},NODE_STMT,S_ASSIGN_RECORD,E_NONE);
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
					$$=newTreeNode({$2,$4,$5,$6},NODE_STMT,S_IF,E_NONE);
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

factor	: ID
		{
			$$=newTreeNode({$1},NODE_STMT,S_FACTOR_ID,E_NONE);
		}
		| ID LP args_list RP
		{
			$$=newTreeNode({$3},NODE_STMT,S_FACTOR_SYS_ID_ARG,E_NONE);
		}
		| SYS_FUNCT
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
		| ID{/*new added*/}
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
extern int yylex();
int yyerror(const char *s){
	printf("%s\n", s);
	return 0;
}
int main(){
	return yyparse();
}
