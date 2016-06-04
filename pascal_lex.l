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
"read"        {printf("READ");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return READ;}
"("           {printf("LP");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LP;}
")"           {printf("RP");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RP;}
"["           {printf("LB");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LB;}
"]"           {printf("RB");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RB;}
"+"           {printf("PLUS");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PLUS;}
"-"           {printf("MINUS");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MINUS;}
"*"           {printf("MUL");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MUL;}
"/"           {printf("DIV");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DIV;}
"mod"         {printf("MOD");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MOD;}
"and"         {printf("AND");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return AND;}
"or"          {printf("OR");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OR;}
"not"         {printf("NOT");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return NOT;}
":="          {printf("ASSIGN");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ASSIGN;}
">"=          {printf("GE");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GE;}
">"           {printf("GT");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GT;}
"<="          {printf("LE");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LE;}
"<"           {printf("LT");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LT;}
"="           {printf("EQUAL");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return EQUAL;}
"<>"          {printf("UNEQUAL");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNEQUAL;}
{integer}     {printf("INTEGER");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);  yyval.data.i=atoi(yytext);	  return INTEGER;}
{real}        {printf("REAL");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.r=atof(yytext);    return REAL;}
{char}        {printf("CHAR");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.c=*yytext;         return CHAR;}
{string}      {printf("STRING");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	snprintf(yyval.data.s, strlen(yytext)-2, yytext+1); return STRING;}
"const"       {printf("CONST");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CONST;}
"array"       {printf("ARRAY");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ARRAY;}
{sys_con}     {printf("SYS_CON");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_CON;}
{sys_type}    {printf("SYS_TYPE");	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_TYPE;}
{sys_proc}    {printf("SYS_PROC");	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_PROC;}
{sys_funct}   {printf("SYS_FUNCT");	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SYS_FUNCT;}
"program"     {printf("PROGRAM");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROGRAM;}
"function"    {printf("FUNCTION");	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FUNCTION;}
"procedure"   {printf("PROCEDURE");	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROCEDURE;}
"record"      {printf("RECORD");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RECORD;}
"name"        {printf("NAME");	    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return NAME;}
"var"         {printf("VAR");   	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return VAR;}
"."           {printf("DOT");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOT;}
";"           {printf("SEMI");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SEMI;}
":"           {printf("COLON");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COLON;}
","           {printf("COMMA");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COMMA;}
"of"          {printf("OF");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OF;}
"begin"       {printf("BEGIN1");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return BEG;}
"end"         {printf("END");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return END;}
"to"          {printf("TO");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return TO;}
"downto"      {printf("DOWNTO");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOWNTO;}
"if"          {printf("IF");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return IF;}
"then"        {printf("THEN");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return THEN;}
"else"        {printf("ELSE");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ELSE;}
"repeat"      {printf("REPEAT");	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return REPEAT;}
"until"       {printf("UNTIL");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNTIL;}
"while"       {printf("WHILE");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return WHILE;}
"do"          {printf("DO");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DO;}
"for"         {printf("FOR");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FOR;}
"goto"        {printf("GOTO");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GOTO;}
"case"        {printf("CASE");		  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CASE;}
{id}          {printf("ID");		    yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	strcpy(yyval.data.s, yytext); return ID;}
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