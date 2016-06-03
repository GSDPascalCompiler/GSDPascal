%{
/*@brief A lex program interprete pascal
*@Author: wang_kejie@foxmail.com
*@Date: 2016/6/3
*/
#include <stdio.h>
#include "y.tab.h"
int lineno = 1;
int column = 0;
%}

digit     [0-9]
letter    [a-zA-Z]
integer   {digit}+
real      {digit}+\.{digit}*
char      \'^\'\'
string    \'[^\']*\'
sys_con   pi|maxint|true|false
sys_type  boolean|char|integer|real
sys_proc  write|writeln
sys_funct abs|chr|odd|ord|pred|sqr|sqrt|succ
id        ({letter}|\_)({digit}|{letter}|\_)*

%%
"read"        {printf("READ");		    yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return READ;}
"("           {printf("LP");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LP;}
")"           {printf("RP");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RP;}
"["           {printf("LB");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LB;}
"]"           {printf("RB");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RB;}
"+"           {printf("PLUS");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PLUS;}
"-"           {printf("MINUS");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MINUS;}
"*"           {printf("MUL");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MUL;}
"/"           {printf("DIV");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DIV;}
"mod"         {printf("MOD");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MOD;}
"and"         {printf("AND");		      yyval.data=std::string(yytext);	     yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return AND;}
"or"          {printf("OR");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OR;}
"not"         {printf("NOT");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return NOT;}
":="          {printf("ASSIGN");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ASSIGN;}
">"=          {printf("GE");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GE;}
">"           {printf("GT");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GT;}
"<="          {printf("LE");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LE;}
"<"           {printf("LT");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LT;}
"="           {printf("EQUAL");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return EQUAL;}
"<>"          {printf("UNEQUAL");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNEQUAL;}
{integer}     {printf("INTEGER");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return INTEGER;}
{real}        {printf("REAL");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return REAL;}
{char}        {printf("CHAR");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CHAR;}
{string}      {printf("STRING");	    yyval.data=std::string(yytext);	     yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return STRING;}
"const"       {printf("CONST");		  	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CONST;}
"array"       {printf("ARRAY");		  	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ARRAY;}
{sys_con}     {printf("SYS_CON");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_CON;}
{sys_type}    {printf("SYS_TYPE");	 	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_TYPE;}
{sys_proc}    {printf("SYS_PROC");	 	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_PROC;}
{sys_funct}   {printf("SYS_FUNCT");	  yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_FUNCT;}
"program"     {printf("PROGRAM");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROGRAM;}
"function"    {printf("FUNCTION");	 	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FUNCTION;}
"procedure"   {printf("PROCEDURE");	  yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROCEDURE;}
"record"      {printf("RECORD");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RECORD;}
"name"        {printf("NAME");	     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return NAME;}
"var"         {printf("VAR");   	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return VAR;}
"."           {printf("DOT");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOT;}
";"           {printf("SEMI");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SEMI;}
":"           {printf("COLON");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COLON;}
","           {printf("COMMA");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COMMA;}
"of"          {printf("OF");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OF;}
"begin"       {printf("BEGIN1");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return BEG;}
"end"         {printf("END");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return END;}
"to"          {printf("TO");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return TO;}
"downto"      {printf("DOWNTO");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOWNTO;}
"if"          {printf("IF");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return IF;}
"then"        {printf("THEN");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return THEN;}
"else"        {printf("ELSE");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ELSE;}
"repeat"      {printf("REPEAT");	   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return REPEAT;}
"until"       {printf("UNTIL");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNTIL;}
"while"       {printf("WHILE");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return WHILE;}
"do"          {printf("DO");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DO;}
"for"         {printf("FOR");		     	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FOR;}
"goto"        {printf("GOTO");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GOTO;}
"case"        {printf("CASE");		   	yyval.data=std::string(yytext);      yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CASE;}
{id}          {printf("ID");		     	yyval.data=std::string(yytext);	     yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ID;}
" "           {printf("%s", yytext);lineno++;column=0;}
"\n"          {printf("%s", yytext);}
"\t"          {printf("%s", yytext);}
.             {printf("%d")}
%%
int main()
{
    do{
        yylex();
    }while(1);
}
