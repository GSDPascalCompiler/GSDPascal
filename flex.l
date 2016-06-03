%{
#include <string.h>
#include "y.tab.h"
int lineno=0;
%}
digit [0-9]
real {digit}+\.{digit}+
integer {digit}+
char [a-zA-Z]
identifier {char}({char}|{digit}|_)*
newline \n
whitespace [ \t]+
char \'.\'
string \".*\"

%%
"program"   {printf("program\n"); return PROGRAM;}
"if"        {printf("if\n"); return IF;}
"then"      {printf("then\n"); return THEN;}
"else"      {printf("else\n"); return ELSE;}
"repeat"    {printf("repeat\n"); return REPEAT;}
"until"     {printf("until\n"); return UNTIL;}
"while"     {printf("while\n"); return WHILE;}
"do"        {printf("do\n"); return DO;}
"case"      {printf("case\n"); return CASE;}
"to"        {printf("to\n"); return TO;}
"downto"    {printf("downto\n"); return DOWNTO;}
"for"       {printf("for\n"); return FOR;}
"read"      {printf("read\n"); return READ;}
"goto"      {printf("goto\n"); return GOTO;}
"type"      {printf("type\n"); return TYPE;}
"array"     {printf("array\n"); return ARRAY;}
"of"        {printf("of\n"); return OF;}
"record"    {printf("record\n"); return RECORD;}
"begin"     {printf("begin\n"); return TOKEN_BEGIN;}
"end"       {printf("end\n"); return TOKEN_END;}
"const"     {printf("const\n"); return CONST;}
"var"       {printf("var\n"); return VAR;}
"function"  {printf("function\n"); return FUNCTION;}
"procedure" {printf("procedure\n"); return PROCEDURE;}

"write"     {printf("write\n"); return SYS_PROC;}
"writeln"   {printf("writeln\n"); return SYS_PROC;}
"abs"       {printf("abs\n"); return SYS_FUNC;}
"chr"       {printf("chr\n"); return SYS_FUNC;}
"odd"       {printf("odd\n"); return SYS_FUNC;}
"ord"       {printf("ord\n"); return SYS_FUNC;}
"pred"      {printf("pred\n"); return SYS_FUNC;}
"sqr"       {printf("sqr\n"); return SYS_FUNC;}
"sqrt"      {printf("sqrt\n"); return SYS_FUNC;}
"succ"      {printf("succ\n"); return SYS_FUNC;}
"boolean"   {printf("boolean\n"); return SYS_TYPE;}
"char"      {printf("char\n"); return SYS_TYPE;}
"integer"   {printf("integer\n"); return SYS_TYPE;}
"real"      {printf("real\n"); return SYS_TYPE;}
"false"     {printf("false\n"); return SYS_CON;}
"maxint"    {printf("maxint\n"); return SYS_CON;}
"true"      {printf("true\n"); return SYS_CON;}

"["         {printf("LB\n"); return LB;}
"]"         {printf("RB\n"); return RB;}
";"         {printf("SEMI\n"); return SEMI;}
".."        {printf("DOTDOT\n"); return DOTDOT;}
"."         {printf("DOT\n"); return DOT;}
"("         {printf("LP\n"); return LP;}
")"         {printf("RP\n"); return RP;}
","         {printf("COMMA\n"); return COMMA;}
":"         {printf("COLON\n"); return COLON;}
":="        {printf("ASSIGN\n"); return ASSIGN;}
"="         {printf("EQUAL\n"); return EQUAL;}
"+"         {printf("PLUS\n"); return PLUS;}
"-"         {printf("MINUS\n"); return MINUS;}
"or"        {printf("OR\n"); return OR;}
"<>"        {printf("UNEQUAL\n"); return UNEQUAL;}
">="        {printf("GE\n"); return GE;}
">"         {printf("GT\n"); return GT;}
"<="        {printf("LE\n"); return LE;}
"<"         {printf("LT\n"); return LT;}
"*"         {printf("MUL\n"); return MUL;}
"/"         {printf("DIV\n"); return DIV;}
"mod"       {printf("MOD\n"); return MOD;}
"and"       {printf("AND\n"); return AND;}
"not"       {printf("NOT\n"); return NOT;}

{integer}    {yylval.num = atoi(yytext); printf("integer:%d\n",yylval.num); return INTEGER;}
{real}      {yylval.fnum = atof(yytext); printf("real:%lf\n",yylval.fnum); return REAL;}
{char}      {yylval.ch = yytext[1]; printf("char:%c\n",yylval.ch); return CHAR;}
{string}    {yytext[strlen(yytext)-1] = '\0'; yylval.name = strdup(yytext+1); printf("string:%s\n",yylval.name); return STRING;}
{identifier} {yylval.name = strdup(yytext); printf("id:%s\n",yylval.name); return ID;}
{newline}   {lineno++;}
{whitespace}    {}
%%
