%%
%class scanner
%column
%line
%byaccj
%{
    private Parser yyparser;
    public scanner (java.io.Reader r, Parser yyparser) {
      this(r);
      this.yyparser = yyparser;
    }
    public int getLineNumber() {
        return yyline;
    }
%}

digit=[0-9]
letter=[a-zA-Z]
integer={digit}+
real={digit}+\.{digit}+
char=\'.\'
string=\'[^\']*\'
id=({letter}|\_)({digit}|{letter}|\_)*
newline=[\n\r]+
whitespace=[ \t]+

%%
"program"   {return Parser.T_PROGRAM;}
"const"     {return Parser.T_CONST;}
"type"      {return Parser.T_TYPE;}
"record"    {return Parser.T_RECORD;}

"var"       {return Parser.T_VAR;}
"integer"   {return Parser.T_INTEGER_TYPE;}
"boolean"   {return Parser.T_BOOLEAN_TYPE;}
"real"      {return Parser.T_REAL_TYPE;}
"char"      {return Parser.T_CHAR_TYPE;}
"array"     {return Parser.T_ARRAY;}
"of"        {return Parser.T_OF;}

"true"      {return Parser.T_TRUE;}
"false"     {return Parser.T_FALSE;}
"maxint"    {return Parser.T_MAXINT;}

"read"      {return Parser.T_READ;}
"write"     {return Parser.T_WRITE;}
"writeln"   {return Parser.T_WRITELN;}
"abs"       {return Parser.T_ABS;}
"odd"       {return Parser.T_ODD;}
"chr"       {return Parser.T_CHR;}
"ord"       {return Parser.T_ORD;}
"sqr"       {return Parser.T_SQR;}
"sqrt"      {return Parser.T_SQRT;}
"pred"      {return Parser.T_PRED;}
"succ"      {return Parser.T_SUCC;}

"begin"     {return Parser.T_BEGIN;}
"end"       {return Parser.T_END;}

"procedure" {return Parser.T_PROCEDURE;}
"function"  {return Parser.T_FUNCTION;}

"if"        {return Parser.T_IF;}
"then"      {return Parser.T_THEN;}
"else"      {return Parser.T_ELSE;}
"for"       {return Parser.T_FOR;}
"to"        {return Parser.T_TO;}
"downto"    {return Parser.T_DOWNTO;}
"while"     {return Parser.T_WHILE;}
"do"        {return Parser.T_DO;}
"repeat"    {return Parser.T_REPEAT;}
"until"     {return Parser.T_UNTIL;}
"case"      {return Parser.T_CASE;}
"goto"      {return Parser.T_GOTO;}


"["         {return Parser.T_LB;}
"]"         {return Parser.T_RB;}
";"         {return Parser.T_SEMI;}
".."        {return Parser.T_DOTDOT;}
"."         {return Parser.T_DOT;}
","         {return Parser.T_COMMA;}
":"         {return Parser.T_COLON;}

":="        {return Parser.T_ASSIGN;}
"("         {return Parser.T_LP;}
")"         {return Parser.T_RP;}
"+"         {return Parser.T_PLUS;}
"-"         {return Parser.T_MINUS;}
"*"         {return Parser.T_MUL;}
"/"         {return Parser.T_DIV;}
"="         {return Parser.T_EQUAL;}
"<>"        {return Parser.T_UNEQUAL;}
">="        {return Parser.T_GE;}
">"         {return Parser.T_GT;}
"<="        {return Parser.T_LE;}
"<"         {return Parser.T_LT;}
"not"       {return Parser.T_NOT;}
"mod"       {return Parser.T_MOD;}
"and"       {return Parser.T_AND;}
"or"        {return Parser.T_OR;}

{integer}   {yyparser.yylval = new ParserVal(Integer.parseInt(yytext())); return Parser.T_INT;}
{real}      {yyparser.yylval = new ParserVal(Double.parseDouble(yytext())); return Parser.T_REAL;}
{char}      {yyparser.yylval = new ParserVal(yytext()); return Parser.T_CHAR;}
{string}    {yyparser.yylval = new ParserVal(yytext()); return Parser.T_STRING;}
{id}        {yyparser.yylval = new ParserVal(yytext()); return Parser.T_ID;}
{newline}   {yyline++;}
{whitespace} {}
