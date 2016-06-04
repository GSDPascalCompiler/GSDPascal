%{
/*@brief A lex program that doing pascal scan
*@Author: wang_kejie@foxmail.com
*@Date: 2016/6/3
*/
#include <stdio.h>
#include "y.tab.h"
#include "global.h"
#include <initialzer_list>
#include <string>
#include <map>

int lineno = 1;
int column = 0;
std::map<std::string, SysConVal> sysConValMap = {
  "false":FALSE,
  "maxint":MAXINT,
  "true":TRUE
};
std::map<std::string, SysFunctVal> sysFunctValMap = {
  "abs": ABS,
  "chr": CHR,
  "odd": ODD,
  "pred": PRED,
  "sqr": SQR,
  "sqrt":SQRT,
  "succ":SUCC
};
std::map<std::string, SysProcVal> sysProcValMap = {
  "write": WRITE,
  "writeln": WRITELN
};
std::map<std::string, sysTypeVal> sysTypeValMap = {
  "boolean": BOOLEAN,
  "char": CHAR,
  "integer":INTEGER,
  "real": REAL
};
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
"read"        {printf("READ");		  yyval.tokeType=READ;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return READ;}
"type"        {printf("TYPE");		  yyval.tokeType=TYPE;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return TYPE;}
"("           {printf("LP");		    yyval.tokeType=LP;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LP;}
")"           {printf("RP");		    yyval.tokeType=RP;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RP;}
"["           {printf("LB");		    yyval.tokeType=LB;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LB;}
"]"           {printf("RB");		    yyval.tokeType=RB;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RB;}
"+"           {printf("PLUS");		  yyval.tokeType=PLUS;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PLUS;}
"-"           {printf("MINUS");		  yyval.tokeType=MINUS;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MINUS;}
"*"           {printf("MUL");		    yyval.tokeType=MUL;		  	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MUL;}
"/"           {printf("DIV");		    yyval.tokeType=DIV;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DIV;}
"mod"         {printf("MOD");		    yyval.tokeType=MOD;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return MOD;}
"and"         {printf("AND");		    yyval.tokeType=AND;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return AND;}
"or"          {printf("OR");		    yyval.tokeType=OR;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OR;}
"not"         {printf("NOT");		    yyval.tokeType=NOT;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return NOT;}
":="          {printf("ASSIGN");	  yyval.tokeType=ASSIGN;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ASSIGN;}
">="          {printf("GE");		    yyval.tokeType=GE;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GE;}
">"           {printf("GT");		    yyval.tokeType=GT;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GT;}
"<="          {printf("LE");		    yyval.tokeType=LE;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LE;}
"<"           {printf("LT");		    yyval.tokeType=LT;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return LT;}
"="           {printf("EQUAL");		  yyval.tokeType=EQUAL;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return EQUAL;}
"<>"          {printf("UNEQUAL");	  yyval.tokeType=UNEQUAL;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNEQUAL;}
{integer}     {printf("INTEGER");	  yyval.tokeType=INTEGER;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);  yyval.data.i=atoi(yytext);	  return INTEGER;}
{real}        {printf("REAL");		  yyval.tokeType=REAL;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.r=atof(yytext);    return REAL;}
{char}        {printf("CHAR");		  yyval.tokeType=CHAR;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.c=*yytext;         return CHAR;}
{string}      {printf("STRING");	  yyval.tokeType=STRING;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	snprintf(yyval.data.s, strlen(yytext)-2, yytext+1); return STRING;}
"const"       {printf("CONST");		  yyval.tokeType=CONST;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CONST;}
"array"       {printf("ARRAY");		  yyval.tokeType=ARRAY;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ARRAY;}
{sys_con}     {printf("SYS_CON");	  yyval.tokeType=SYS_CON;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.sysConVal = sysConValMap[std::string(yytext)]; return SYS_CON;}
{sys_type}    {printf("SYS_TYPE");	yyval.tokeType=SYS_TYPE;	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.sysFunctVal = sysFunctValMap[std::string(yytext)];return SYS_TYPE;}
{sys_proc}    {printf("SYS_PROC");	yyval.tokeType=SYS_PROC;	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.sysProcVal = sysProcValMap[std::string(yytext)];return SYS_PROC;}
{sys_funct}   {printf("SYS_FUNCT");	yyval.tokeType=SYS_FUNCT;	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	yyval.data.sysTypeVal = sysTypeValMap[std::string(yytext)];return SYS_FUNCT;}
"program"     {printf("PROGRAM");	  yyval.tokeType=PROGRAM;	  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROGRAM;}
"function"    {printf("FUNCTION");	yyval.tokeType=FUNCTION;	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FUNCTION;}
"procedure"   {printf("PROCEDURE");	yyval.tokeType=PROCEDURE;	yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return PROCEDURE;}
"record"      {printf("RECORD");	  yyval.tokeType=RECORD;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return RECORD;}
"var"         {printf("VAR");   	  yyval.tokeType=VAR;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return VAR;}
"."           {printf("DOT");		    yyval.tokeType=DOT;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOT;}
";"           {printf("SEMI");		  yyval.tokeType=SEMI;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return SEMI;}
":"           {printf("COLON");		  yyval.tokeType=COLON;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COLON;}
","           {printf("COMMA");		  yyval.tokeType=COMMA;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return COMMA;}
"of"          {printf("OF");		    yyval.tokeType=OF;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return OF;}
"begin"       {printf("BEGIN");	    yyval.tokeType=BEG;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return BEG;}
"end"         {printf("END");		    yyval.tokeType=END;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return END;}
"to"          {printf("TO");		    yyval.tokeType=TO;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return TO;}
"downto"      {printf("DOWNTO");	  yyval.tokeType=DOWNTO;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DOWNTO;}
"if"          {printf("IF");		    yyval.tokeType=IF;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return IF;}
"then"        {printf("THEN");		  yyval.tokeType=THEN;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return THEN;}
"else"        {printf("ELSE");		  yyval.tokeType=ELSE;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return ELSE;}
"repeat"      {printf("REPEAT");	  yyval.tokeType=REPEAT;		yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return REPEAT;}
"until"       {printf("UNTIL");		  yyval.tokeType=UNTIL;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return UNTIL;}
"while"       {printf("WHILE");		  yyval.tokeType=WHILE;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return WHILE;}
"do"          {printf("DO");		    yyval.tokeType=DO;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return DO;}
"for"         {printf("FOR");		    yyval.tokeType=FOR;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return FOR;}
"goto"        {printf("GOTO");		  yyval.tokeType=GOTO;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return GOTO;}
"case"        {printf("CASE");		  yyval.tokeType=CASE;			yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	return CASE;}
{id}          {printf("ID");		    yyval.tokeType=ID;			  yyval.lineno=lineno;	yyval.column=column; column+=strlen(yytext);	strcpy(yyval.data.s, yytext); return ID;}" "           {printf("%s", yytext);}
"\n"          {printf("%s", yytext);lineno++;column=0;}
"\t"          {printf("%s", yytext);}
.             {printf("%d");}
%%
int main()
{
    do{
        yylex();
    }while(1);
}
