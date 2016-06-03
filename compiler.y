%{
#include "define.h"
#include <stdio.h>
%}

%token READ TYPE //
%token LP RP LB RB //
%token PLUS MINUS MUL DIV MOD AND OR NOT ASSIGN //
%token GE GT LE LT EQUAL UNEQUAL //
%token INTEGER REAL CHAR STRING CONST ARRAY //Leaf
%token SYS_CON SYS_TYPE SYS_PROC SYS_FUNCT //
%token PROGRAM FUNCTION PROCEDURE RECORD ID NAME VAR//
%token DOT SEMI COLON COMMA//
%token OF BEG END TO DOWNTO//
%token IF THEN ELSE REPEAT UNTIL WHILE DO FOR GOTO CASE//



%%
program 	: program_head routine DOT
			;


program_head	: PROGRAM ID SEMI 
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
				;

val_para_list	: name_list
				;












routine_body	: compound_stmt 
				;

compound_stmt	: BEG stmt_list END
				;

stmt_list	: stmt_list stmt SEMI
			|
			;

stmt 		: INTEGER COLON non_label_stmt
			| non_label_stmt
			;

non_label_stmt	: assign_stmt
				| proc_stmt 
				| compound_stmt
				| if_stmt
				| repeat_stmt
				| while_stmt
				| for_stmt
				| case_stmt
				| goto_stmt
				;

assign_stmt 	: ID ASSIGN expression
				| ID LB expression RB ASSIGN expression
				| ID DOT ID ASSIGN expression
				;

proc_stmt		: ID
				| ID LP args RP 
				| SYS_PROC
				| SYS_PROC LP expression_list RP
				| READ LP factor RP
				;

if_stmt			: IF expression THEN stmt else_clause
				;

else_clause		: ELSE stmt
				|
				;

repeat_stmt		: REPEAT stmt_list UNTIL expression
				;

while_stmt		: WHILE expression DO stmt
				;

for_stmt		: FOR ID ASSIGN expression direction expression DO stmt
				;

direction		: TO
				| DOWNTO
				;

case_stmt		: CASE expression OF case_expr_list END
				;

case_expr_list	: case_expr_list case_expr
				| case_expr
				;

case_expr 		: const_value COLON stmt SEMI
				| ID COLON stmt SEMI
				;

goto_stmt		: GOTO INTEGER
				;

expression_list	: expression_list COMMA expression
				| expression
				;

expression 		: expression GE expr
				| expression GT expr
				| expression LE expr
				| expression LT expr
				| expression EQUAL expr
				| expression UNEQUAL expr
				| expr
				;

expr 	: expr PLUS term
		| expr MINUS term
		| expr OR term
		| term
		;

term	: term MUL factor
		| term DIV factor
		| term MOD factor
		| term AND factor
		| factor
		;

factor	: NAME
		| NAME LP args_list RP
		| SYS_FUNCT
		| SYS_FUNCT LP args_list RP
		| const_value
		| LP expression RP
		| NOT factor
		| MINUS factor
		| ID LB expression RB
		| ID LP args RP{/*new added*/}
		| ID DOT ID
		| ID{/*new added*/}
		;

args 		: args_list {/*new added*/}
			|
			;

args_list	: args_list COMMA expression
			| expression
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

