%{
/*@brief A lex program interprete pascal
*@Author: wang_kejie@foxmail.com
*@Date: 2016/6/3
*/
#include <stdio.h>
#include "y.tab.h"
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
"read"        {printf("READ"); return READ;}
"("           {printf("LP"); return LP;}
")"           {printf("RP"); return RP;}
"["           {printf("LB"); return LB;}
"]"           {printf("RB"); return RB;}
"+"           {printf("PLUS"); return PLUS;}
"-"           {printf("MINUS"); return MINUS;}
"*"           {printf("MUL"); return MUL;}
"/"           {printf("DIV"); return DIV;}
"mod"         {printf("MOD"); return MOD;}
"and"         {printf("AND"); return AND;}
"or"          {printf("OR"); return OR;}
"not"         {printf("NOT"); return NOT;}
":="          {printf("ASSIGN"); return ASSIGN;}
">"=          {printf("GE"); return GE;}
">"           {printf("GT"); return GT;}
"<="          {printf("LE"); return LE;}
"<"           {printf("LT"); return LT;}
"="           {printf("EQUAL"); return EQUAL;}
"<>"          {printf("UNEQUAL"); return UNEQUAL;}
{integer}     {printf("INTEGER"); return INTEGER;}
{real}        {printf("REAL"); return REAL;}
{char}        {printf("CHAR"); return CHAR;}
{string}      {printf("STRING"); return STRING;}
"const"       {printf("CONST"); return CONST;}
"array"       {printf("ARRAY"); return ARRAY;}
{sys_con}     {printf("SYS_CON"); return SYS_CON;}
{sys_type}    {printf("SYS_TYPE"); return SYS_TYPE;}
{sys_proc}    {printf("SYS_PROC"); return SYS_PROC;}
{sys_funct}   {printf("SYS_FUNCT"); return SYS_FUNCT;}
"program"     {printf("PROGRAM"); return PROGRAM;}
"function"    {printf("FUNCTION"); return FUNCTION;}
"procedure"   {printf("PROCEDURE"); return PROCEDURE;}
"record"      {printf("RECORD"); return RECORD;}
"name"        {printf("NAME"); return NAME;}
"var"         {printf("VAR"); return VAR;}
"."           {printf("DOT"); return DOT;}
";"           {printf("SEMI"); return SEMI;}
":"           {printf("COLON"); return COLON;}
","           {printf("COMMA"); return COMMA;}
"of"          {printf("OF"); return OF;}
"begin"       {printf("BEGIN1"); return BEGIN1;}
"end"         {printf("END"); return END;}
"to"          {printf("TO"); return TO;}
"downto"      {printf("DOWNTO"); return DOWNTO;}
"if"          {printf("IF"); return IF;}
"then"        {printf("THEN"); return THEN;}
"else"        {printf("ELSE"); return ELSE;}
"repeat"      {printf("REPEAT"); return REPEAT;}
"until"       {printf("UNTIL"); return UNTIL;}
"while"       {printf("WHILE"); return WHILE;}
"do"          {printf("DO"); return DO;}
"for"         {printf("FOR"); return FOR;}
"goto"        {printf("GOTO"); return GOTO;}
"case"        {printf("CASE"); return CASE;}
{id}          {printf("ID"); return ID;}
" "           {printf("%s", yytext);}
"\n"           {printf("%s", yytext);}
"\t"           {printf("%s", yytext);}

%%
main()
{
    do{
        yylex();
    }while(1);
}
