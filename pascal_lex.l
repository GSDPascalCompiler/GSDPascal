%{
/*@brief A lex program that doing pascal scan
*@Author: wang_kejie@foxmail.com
*@Date: 2016/6/3
*/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "global.h"
#include "y.tab.h"
#include <initializer_list>
#include <string>
#include <map>

int lineno = 1;
int column = 0;
std::map<std::string, SysConVal> sysConValMap = {
  {"false",CON_FALSE},
  {"maxint",CON_MAXINT},
  {"true",CON_TRUE},
};
std::map<std::string, SysFunctVal> sysFunctValMap = {
  {"abs", FUNCT_ABS},
  {"chr", FUNCT_CHR},
  {"odd", FUNCT_ODD},
  {"pred", FUNCT_PRED},
  {"sqr", FUNCT_SQR},
  {"sqrt",FUNCT_SQRT},
  {"succ",FUNCT_SUCC},
};
std::map<std::string, SysProcVal> sysProcValMap = {
  {"write", PROC_WRITE},
  {"writeln", PROC_WRITELN},
};
std::map<std::string, SysTypeVal> sysTypeValMap = {
  {"boolean", TYPE_BOOLEAN},
  {"char", TYPE_CHAR},
  {"integer",TYPE_INTEGER},
  {"real", TYPE_REAL},
};
%}

%option noyywrap
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
"read"        {printf("READ");		  yylval.tokenType=T_READ;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return READ;}
"type"        {printf("TYPE");		  yylval.tokenType=T_TYPE;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return TYPE;}
"("           {printf("LP");		    yylval.tokenType=T_LP;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return LP;}
")"           {printf("RP");		    yylval.tokenType=T_RP;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return RP;}
"["           {printf("LB");		    yylval.tokenType=T_LB;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return LB;}
"]"           {printf("RB");		    yylval.tokenType=T_RB;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return RB;}
"+"           {printf("PLUS");		  yylval.tokenType=T_PLUS;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return PLUS;}
"-"           {printf("MINUS");		  yylval.tokenType=T_MINUS;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return MINUS;}
"*"           {printf("MUL");		    yylval.tokenType=T_MUL;		  	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return MUL;}
"/"           {printf("DIV");		    yylval.tokenType=T_DIV;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return DIV;}
"mod"         {printf("MOD");		    yylval.tokenType=T_MOD;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return MOD;}
"and"         {printf("AND");		    yylval.tokenType=T_AND;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return AND;}
"or"          {printf("OR");		    yylval.tokenType=T_OR;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return OR;}
"not"         {printf("NOT");		    yylval.tokenType=T_NOT;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return NOT;}
":="          {printf("ASSIGN");	  yylval.tokenType=T_ASSIGN;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return ASSIGN;}
">="          {printf("GE");		    yylval.tokenType=T_GE;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return GE;}
">"           {printf("GT");		    yylval.tokenType=T_GT;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return GT;}
"<="          {printf("LE");		    yylval.tokenType=T_LE;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return LE;}
"<"           {printf("LT");		    yylval.tokenType=T_LT;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return LT;}
"="           {printf("EQUAL");		  yylval.tokenType=T_EQUAL;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return EQUAL;}
"<>"          {printf("UNEQUAL");	  yylval.tokenType=T_UNEQUAL;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return UNEQUAL;}
{integer}     {printf("INTEGER");	  yylval.tokenType=T_INTEGER;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);  yylval.data.i=atoi(yytext);	  return INTEGER;}
{real}        {printf("REAL");		  yylval.tokenType=T_REAL;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.r=atof(yytext);    return REAL;}
{char}        {printf("CHAR");		  yylval.tokenType=T_CHAR;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.c=*yytext;         return CHAR;}
{string}      {printf("STRING");	  yylval.tokenType=T_STRING;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	snprintf(yylval.data.s, strlen(yytext)-2, yytext+1); return STRING;}
"const"       {printf("CONST");		  yylval.tokenType=T_CONST;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return CONST;}
"array"       {printf("ARRAY");		  yylval.tokenType=T_ARRAY;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return ARRAY;}
{sys_con}     {printf("SYS_CON");	  yylval.tokenType=T_SYS_CON;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.sysConVal = sysConValMap[std::string(yytext)]; return SYS_CON;}
{sys_type}    {printf("SYS_TYPE");	yylval.tokenType=T_SYS_TYPE;	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.sysTypeVal = sysTypeValMap[std::string(yytext)];return SYS_TYPE;}
{sys_proc}    {printf("SYS_PROC");	yylval.tokenType=T_SYS_PROC;	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.sysProcVal = sysProcValMap[std::string(yytext)];return SYS_PROC;}
{sys_funct}   {printf("SYS_FUNCT");	yylval.tokenType=T_SYS_FUNCT;	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	yylval.data.sysFunctVal = sysFunctValMap[std::string(yytext)];return SYS_FUNCT;}
"program"     {printf("PROGRAM");	  yylval.tokenType=T_PROGRAM;	  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return PROGRAM;}
"function"    {printf("FUNCTION");	yylval.tokenType=T_FUNCTION;	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return FUNCTION;}
"procedure"   {printf("PROCEDURE");	yylval.tokenType=T_PROCEDURE;	yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return PROCEDURE;}
"record"      {printf("RECORD");	  yylval.tokenType=T_RECORD;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return RECORD;}
"var"         {printf("VAR");   	  yylval.tokenType=T_VAR;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return VAR;}
"."           {printf("DOT");		    yylval.tokenType=T_DOT;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return DOT;}
";"           {printf("SEMI");		  yylval.tokenType=T_SEMI;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return SEMI;}
":"           {printf("COLON");		  yylval.tokenType=T_COLON;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return COLON;}
","           {printf("COMMA");		  yylval.tokenType=T_COMMA;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return COMMA;}
"of"          {printf("OF");		    yylval.tokenType=T_OF;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return OF;}
"begin"       {printf("BEGIN");	    yylval.tokenType=T_BEG;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return BEG;}
"end"         {printf("END");		    yylval.tokenType=T_END;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return END;}
"to"          {printf("TO");		    yylval.tokenType=T_TO;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return TO;}
"downto"      {printf("DOWNTO");	  yylval.tokenType=T_DOWNTO;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return DOWNTO;}
"if"          {printf("IF");		    yylval.tokenType=T_IF;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return IF;}
"then"        {printf("THEN");		  yylval.tokenType=T_THEN;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return THEN;}
"else"        {printf("ELSE");		  yylval.tokenType=T_ELSE;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return ELSE;}
"repeat"      {printf("REPEAT");	  yylval.tokenType=T_REPEAT;		yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return REPEAT;}
"until"       {printf("UNTIL");		  yylval.tokenType=T_UNTIL;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return UNTIL;}
"while"       {printf("WHILE");		  yylval.tokenType=T_WHILE;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return WHILE;}
"do"          {printf("DO");		    yylval.tokenType=T_DO;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return DO;}
"for"         {printf("FOR");		    yylval.tokenType=T_FOR;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return FOR;}
"goto"        {printf("GOTO");		  yylval.tokenType=T_GOTO;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return GOTO;}
"case"        {printf("CASE");		  yylval.tokenType=T_CASE;			yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	return CASE;}
{id}          {printf("ID");		    yylval.tokenType=T_ID;			  yylval.lineno=lineno;	yylval.column=column; column+=strlen(yytext);	strcpy(yylval.data.s, yytext); return ID;}
" "           {printf("%s", yytext);}
"\n"          {printf("%s", yytext);lineno++;column=0;}
"\t"          {printf("%s", yytext);}
.             {printf("%d", lineno);}
%%
#ifdef LOCAL_DEBUG
  freopen("in.txt", "r", stdin);
#endif