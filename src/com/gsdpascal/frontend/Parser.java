//### This file created by BYACC 1.8(/Java extension  1.15)
//### Java capabilities added 7 Jan 97, Bob Jamison
//### Updated : 27 Nov 97  -- Bob Jamison, Joe Nieten
//###           01 Jan 98  -- Bob Jamison -- fixed generic semantic constructor
//###           01 Jun 99  -- Bob Jamison -- added Runnable support
//###           06 Aug 00  -- Bob Jamison -- made state variables class-global
//###           03 Jan 01  -- Bob Jamison -- improved flags, tracing
//###           16 May 01  -- Bob Jamison -- added custom stack sizing
//###           04 Mar 02  -- Yuval Oren  -- improved java performance, added options
//###           14 Mar 02  -- Tomas Hurka -- -d support, static initializer workaround
//### Please send bug reports to tom@hukatronic.cz
//### static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";






//#line 2 "compiler.y"
package com.gsdpascal.frontend;
import java.io.*;
import com.gsdpascal.astree.*;
import com.gsdpascal.codegen.*;
//#line 21 "Parser.java"




public class Parser
{

boolean yydebug;        //do I want debug output?
int yynerrs;            //number of errors so far
int yyerrflag;          //was there an error?
int yychar;             //the current working character

//########## MESSAGES ##########
//###############################################################
// method: debug
//###############################################################
void debug(String msg)
{
  if (yydebug)
    System.out.println(msg);
}

//########## STATE STACK ##########
final static int YYSTACKSIZE = 500;  //maximum stack size
int statestk[] = new int[YYSTACKSIZE]; //state stack
int stateptr;
int stateptrmax;                     //highest index of stackptr
int statemax;                        //state when highest index reached
//###############################################################
// methods: state stack push,pop,drop,peek
//###############################################################
final void state_push(int state)
{
  try {
		stateptr++;
		statestk[stateptr]=state;
	 }
	 catch (ArrayIndexOutOfBoundsException e) {
     int oldsize = statestk.length;
     int newsize = oldsize * 2;
     int[] newstack = new int[newsize];
     System.arraycopy(statestk,0,newstack,0,oldsize);
     statestk = newstack;
     statestk[stateptr]=state;
  }
}
final int state_pop()
{
  return statestk[stateptr--];
}
final void state_drop(int cnt)
{
  stateptr -= cnt; 
}
final int state_peek(int relative)
{
  return statestk[stateptr-relative];
}
//###############################################################
// method: init_stacks : alPosate and prepare stacks
//###############################################################
final boolean init_stacks()
{
  stateptr = -1;
  val_init();
  return true;
}
//###############################################################
// method: dump_stacks : show n levels of the stacks
//###############################################################
void dump_stacks(int count)
{
int i;
  System.out.println("=index==state====value=     s:"+stateptr+"  v:"+valptr);
  for (i=0;i<count;i++)
    System.out.println(" "+i+"    "+statestk[i]+"      "+valstk[i]);
  System.out.println("======================");
}


//########## SEMANTIC VALUES ##########
//public class ParserVal is defined in ParserVal.java


String   yytext;//user variable to return contextual strings
ParserVal yyval; //used to return semantic vals from action routines
ParserVal yylval;//the 'lval' (result) I got from yylex()
ParserVal valstk[];
int valptr;
//###############################################################
// methods: value stack push,pop,drop,peek.
//###############################################################
void val_init()
{
  valstk=new ParserVal[YYSTACKSIZE];
  yyval=new ParserVal();
  yylval=new ParserVal();
  valptr=-1;
}
void val_push(ParserVal val)
{
  if (valptr>=YYSTACKSIZE)
    return;
  valstk[++valptr]=val;
}
ParserVal val_pop()
{
  if (valptr<0)
    return new ParserVal();
  return valstk[valptr--];
}
void val_drop(int cnt)
{
int ptr;
  ptr=valptr-cnt;
  if (ptr<0)
    return;
  valptr = ptr;
}
ParserVal val_peek(int relative)
{
int ptr;
  ptr=valptr-relative;
  if (ptr<0)
    return new ParserVal();
  return valstk[ptr];
}
final ParserVal dup_yyval(ParserVal val)
{
  ParserVal dup = new ParserVal();
  dup.ival = val.ival;
  dup.dval = val.dval;
  dup.sval = val.sval;
  dup.obj = val.obj;
  return dup;
}
//#### end semantic value section ####
public final static short T_PROGRAM=257;
public final static short T_CONST=258;
public final static short T_TYPE=259;
public final static short T_VAR=260;
public final static short T_FUNCTION=261;
public final static short T_PROCEDURE=262;
public final static short T_INT=263;
public final static short T_REAL=264;
public final static short T_ID=265;
public final static short T_CHAR=266;
public final static short T_STRING=267;
public final static short T_BEGIN=268;
public final static short T_END=269;
public final static short T_TRUE=270;
public final static short T_FALSE=271;
public final static short T_MAXINT=272;
public final static short T_READ=273;
public final static short T_WRITE=274;
public final static short T_WRITELN=275;
public final static short T_ABS=276;
public final static short T_CHR=277;
public final static short T_ODD=278;
public final static short T_ORD=279;
public final static short T_PRED=280;
public final static short T_SQR=281;
public final static short T_SQRT=282;
public final static short T_SUCC=283;
public final static short T_IF=284;
public final static short T_THEN=285;
public final static short T_ELSE=286;
public final static short T_REPEAT=287;
public final static short T_UNTIL=288;
public final static short T_WHILE=289;
public final static short T_DO=290;
public final static short T_CASE=291;
public final static short T_TO=292;
public final static short T_DOWNTO=293;
public final static short T_FOR=294;
public final static short T_EQUAL=295;
public final static short T_UNEQUAL=296;
public final static short T_GE=297;
public final static short T_GT=298;
public final static short T_LE=299;
public final static short T_LT=300;
public final static short T_ASSIGN=301;
public final static short T_PLUS=302;
public final static short T_MINUS=303;
public final static short T_MUL=304;
public final static short T_DIV=305;
public final static short T_OR=306;
public final static short T_AND=307;
public final static short T_NOT=308;
public final static short T_MOD=309;
public final static short T_LB=310;
public final static short T_RB=311;
public final static short T_LP=312;
public final static short T_RP=313;
public final static short T_SEMI=314;
public final static short T_DOT=315;
public final static short T_DOTDOT=316;
public final static short T_COMMA=317;
public final static short T_COLON=318;
public final static short T_INTEGER_TYPE=319;
public final static short T_BOOLEAN_TYPE=320;
public final static short T_CHAR_TYPE=321;
public final static short T_REAL_TYPE=322;
public final static short T_ARRAY=323;
public final static short T_OF=324;
public final static short T_RECORD=325;
public final static short T_GOTO=326;
public final static short ERROR=327;
public final static short YYERRCODE=256;
final static short yylhs[] = {                           -1,
    0,    1,    2,    3,    3,    3,    3,    3,    4,    5,
    6,    6,    7,    7,    8,    8,    9,   10,   11,   11,
   12,   12,   13,   14,   14,   15,   15,   16,   17,   17,
   17,   17,   17,   17,   17,   18,   18,   19,   19,   20,
   21,   21,   21,   22,   23,   23,   24,   25,   26,   26,
   26,   26,   26,   26,   26,   26,   26,   26,   27,   27,
   28,   29,   30,   31,   31,   49,   49,   32,   32,   32,
   32,   32,   32,   32,   32,   32,   33,   33,   33,   34,
   35,   36,   36,   37,   37,   47,   38,   39,   39,   40,
   40,   41,   41,   42,   42,   42,   42,   42,   42,   43,
   43,   48,   48,   48,   48,   48,   48,   48,   44,   44,
   44,   44,   45,   45,   45,   45,   45,   46,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
   46,   46,   46,
};
final static short yylen[] = {                            2,
    5,    2,    4,    0,    2,    2,    1,    1,    4,    5,
    0,    3,    3,    1,    4,    3,    4,    3,    0,    2,
    2,    1,    4,    0,    2,    2,    1,    4,    1,    1,
    1,    1,    1,    1,    1,    0,    2,    2,    1,    4,
    1,    1,    1,    3,    2,    1,    4,    6,    1,    3,
    3,    4,    5,    3,    1,    1,    1,    1,    3,    1,
    1,    1,    3,    0,    3,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    3,    6,    5,    2,
    5,    0,    2,    4,    0,    4,    5,    2,    1,    4,
    4,    8,    8,    1,    4,    4,    4,    1,    4,    3,
    1,    3,    3,    3,    3,    3,    3,    1,    3,    3,
    3,    1,    3,    3,    3,    3,    1,    1,    4,    1,
    3,    2,    2,    4,    3,    4,    4,    4,    4,    4,
    4,    4,    4,
};
final static short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,   61,    0,
   27,    0,    1,   64,    2,   62,    0,    0,   26,    0,
    0,    0,   39,    0,    0,    0,   29,   30,   31,   32,
   33,   34,   35,    0,    0,   63,    0,    0,    0,    0,
   64,    0,    0,    0,    0,    0,   69,   67,   68,   70,
   71,   72,   74,   75,   76,   73,    0,   38,    0,    0,
   22,    0,   60,    0,    0,    0,    7,    0,    8,    0,
   28,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  120,    0,    0,    0,
  117,    0,    0,    0,    0,    0,   80,    0,    0,    0,
    0,   65,    0,    0,   55,   56,   58,   57,    0,    0,
    0,    0,   43,   42,   41,    0,   21,    0,    0,    0,
    0,    5,    6,    0,    0,   66,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  123,  122,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   46,    0,    0,   40,    0,   59,    0,    0,    0,   18,
    0,    0,   96,   97,    0,   99,    0,    0,    0,    0,
    0,    0,    0,    0,  121,    0,    0,  125,    0,    0,
    0,  113,  114,  116,  115,    0,    0,    0,    0,    0,
    0,    0,    0,   86,    0,    0,    0,   89,    0,    0,
   95,    0,    0,   50,    0,   44,   45,    0,   51,   54,
   23,    0,    0,   14,    0,    0,    9,   17,    0,  126,
  127,  128,  129,  130,  131,  132,  133,  124,  119,    0,
   81,    0,    0,   87,   88,    0,    0,    0,    0,    0,
   52,    0,    0,    0,   12,    0,    0,   10,   83,    0,
    0,    0,    0,    0,   53,    0,   47,    0,   13,   16,
   90,   91,    0,    0,   48,   15,   92,   93,
};
final static short yydgoto[] = {                          2,
    6,    7,   66,   67,   68,  179,  233,  234,   69,   70,
   26,   60,   61,    8,   10,   11,   87,   18,   22,   23,
  112,  113,  170,  171,  114,  115,   62,   88,   15,   47,
   21,   48,   49,   50,   51,  251,   52,   53,  217,  218,
   54,   55,  128,   89,   90,   91,   56,  129,   57,
};
final static short yysindex[] = {                      -226,
 -252,    0, -277, -211, -209, -241, -197, -172,    0, -209,
    0, -193,    0,    0,    0,    0, -209, -153,    0,  352,
  -91, -209,    0, -170, -209,  -18,    0,    0,    0,    0,
    0,    0,    0, -181, -182,    0, -166, -160, -158,  113,
    0,  113,  113, -209, -106, -280,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -117,    0,   41, -209,
    0, -151,    0,  -66,  -61,  -18,    0, -103,    0,  -80,
    0, -246,  113,  113,  113,  -54,  -42,  -31,  -15,  -13,
   27,   28,   29,  113,  113,  113,    0, -162, -208,  -90,
    0,   51,  -35,  494, -155,  -77,    0,  113,  113,  113,
 -209,    0,  352, -209,    0,    0,    0,    0,   33, -209,
  -41,   38,    0,    0,    0,   39,    0, -209,   41,   42,
   42,    0,    0, -211, -211,    0,   32, -231,  380, -205,
  113,  113,  113,  113,  113,  113,  113,  113,    0,    0,
 -108,  113,  113, -209,  113,  113,  113,  113,  113,  113,
  113,    9,  113,  113,  113,  113,  113,  113,  113,    9,
  322,  113,  380,   31, -189,   56,   43, -138,   53,  -89,
    0,   -8,  352,    0, -209,    0,   44, -192,   49,    0,
   54,   55,    0,    0,  113,    0, -132, -111,  -88,  -81,
  -76,  -71,  -62,  -53,    0,  102,  -50,    0,  -90,  -90,
  -90,    0,    0,    0,    0,   84, -208, -208, -208, -208,
 -208, -208,  380,    0,   63,   64,  140,    0,  353,   70,
    0,  113, -206,    0,   75,    0,    0,   41,    0,    0,
    0, -209,  -12,    0,   -3,   53,    0,    0,  380,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    9,
    0,    9,    9,    0,    0,  113,  113,  113,  380,  352,
    0,   90,   73,    4,    0, -192,   53,    0,    0,   74,
   94,  505,  516,  380,    0,   41,    0,   53,    0,    0,
    0,    0,    9,    9,    0,    0,    0,    0,
};
final static short yyrindex[] = {                         0,
    0,    0,    0, -183,    0,    0,    0, -100,    0, -130,
    0,    0,    0,    0,    0,    0,    0, -228,    0,    0,
  101,  -52,    0,    0,    0,  149,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -278,    0,
    0,    0,    0,    0,    0, -268,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -67,
    0,    0,    0,    0,    0,  150,    0,    0,    0,    0,
    0, -263,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  134,  284,  164,
    0,    0,  101,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -19,    0,    0,    0,  104,
  109,    0,    0, -183, -183,    0,    0,    0,  -48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -263,    0,    0,    0,    0,    0,    0,    0, -263,
    0,    0, -262,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  194,  224,
  254,    0,    0,    0,    0,  114,  314,  344,  374,  404,
  434,  464, -244,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -37,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -263,
    0,  101,  101,    0,    0,    0,    0,    0, -242,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -233,    0,    0,    0,    0,    0,    0,
    0,    0, -263, -263,    0,    0,    0,    0,
};
final static short yygindex[] = {                         0,
  213,    0,    0,  369,    0,  321,    0,  178,  386,    0,
    0,    0,  393,    0,    0,  436,  -10,    0,    0,  433,
 -118,    0,    0,  295,    0, -167,  -95,   -5,    0,  461,
  428,  399,    0,    0,    0,    0,    0,    0,    0,  255,
    0,    0,  -16,  132,  187,  -59,    0,  -36, -149,
};
final static int YYTABLESIZE=816;
static short yytable[];
static { yytable();}
static void yytable(){
yytable = new short[]{                         12,
  177,  225,  206,   92,   12,   94,   95,   98,  168,   34,
  214,   24,    3,  127,  172,   46,   24,   94,    9,   63,
   98,   14,   85,   77,  139,  140,   37,   38,   39,   99,
    1,  100,   19,   19,  101,   98,    4,   40,   96,   19,
   41,   84,   42,   79,   43,   94,    5,   44,  111,  141,
   85,   77,   78,  116,   63,    9,   27,   28,  130,   29,
   30,  163,  164,   31,   32,   33,   46,  232,  268,   84,
   14,   79,    9,   13,  172,   24,   24,   24,   24,   45,
   78,  184,  235,  165,   24,  185,   17,   46,  202,  203,
  204,  205,  167,  145,  146,  166,  260,  147,   63,  280,
  269,   20,  270,  271,   63,  196,   25,  186,  111,  263,
  286,  185,  176,  116,  187,  188,  189,  190,  191,  192,
  193,  194,  213,  221,   59,  219,  197,  185,   25,   25,
   25,   25,   71,  287,  288,   72,  264,   25,  198,  153,
  154,  155,  156,  157,  158,   73,   46,  142,  239,  143,
  215,   74,  144,   75,   46,  216,   97,  285,  111,   36,
   36,   36,  229,  116,   63,  118,  119,   36,  161,  230,
  235,   35,   63,    9,  224,    9,   14,   36,  118,  226,
  240,   37,   38,   39,  185,  259,  153,  154,  155,  156,
  157,  158,   40,   20,   20,   41,  102,   42,  120,   43,
   20,  241,   44,  121,  195,  185,  215,   37,   37,   37,
  124,  216,  261,  148,  149,   37,  150,  111,  151,  272,
  273,  274,  116,  162,  242,  111,   63,   35,  185,    9,
  116,  243,   14,  125,   45,  185,  244,   37,   38,   39,
  185,  245,   64,   65,   46,  185,   46,   46,   40,  275,
  246,   41,  159,   42,  185,   43,  111,  131,   44,  247,
   63,  116,  249,  185,  101,  111,  185,  111,  101,  132,
  116,   35,  116,    9,  173,  100,   14,   46,   46,  100,
  133,   37,   38,   39,  207,  208,  209,  210,  211,  212,
   45,   49,   40,   49,   49,   41,  134,   42,  135,   43,
  265,  266,   44,   27,   28,    9,   29,   30,  118,  228,
   31,   32,   33,  118,  267,   27,   28,    9,   29,   30,
  118,  278,   31,   32,   33,  153,  154,  155,  156,  157,
  158,  199,  200,  201,   45,  152,  181,  182,  136,  137,
  138,  220,  169,  103,  183,  153,  154,  155,  156,  157,
  158,  174,  104,  178,  175,  103,  222,  231,  223,  105,
  106,  107,  108,  109,  104,  110,  236,  237,  238,  250,
  258,  105,  106,  107,  108,   27,   28,    9,   29,   30,
  252,  253,   31,   32,   33,  262,  277,  281,   76,   77,
   78,   79,   80,   81,   82,   83,  153,  154,  155,  156,
  157,  158,   27,   28,    9,   29,   30,  282,  254,   31,
   32,   33,  248,  276,   85,   84,    4,    3,  118,  118,
   85,   11,   11,  118,   86,  118,  118,   82,  118,  118,
  118,  118,  118,  118,  122,  118,  118,  118,  118,  118,
  118,  180,  118,  279,  118,   19,  118,  118,  112,  112,
  118,  123,  117,  112,   58,  112,  112,  118,  112,  112,
  112,  112,  112,  112,  227,  112,  112,   16,   93,  112,
  126,  255,    0,    0,  112,    0,  112,  112,  109,  109,
  112,    0,    0,  109,    0,  109,  109,  112,  109,  109,
  109,  109,  109,  109,    0,  109,  109,    0,    0,  109,
    0,    0,    0,    0,  109,    0,  109,  109,  110,  110,
  109,    0,    0,  110,    0,  110,  110,  109,  110,  110,
  110,  110,  110,  110,    0,  110,  110,    0,    0,  110,
    0,    0,    0,    0,  110,    0,  110,  110,  111,  111,
  110,    0,    0,  111,    0,  111,  111,  110,  111,  111,
  111,  111,  111,  111,    0,  111,  111,    0,    0,  111,
    0,    0,    0,    0,  111,    0,  111,  111,  108,  108,
  111,    0,    0,  108,    0,  108,  108,  111,  108,  108,
  108,  108,  108,  108,   27,   28,    9,   29,   30,    0,
    0,   31,   32,   33,  108,    0,  108,  108,  106,  106,
  108,    0,    0,  106,    0,  106,  106,  108,  106,  106,
  106,  106,  106,  106,   27,   28,    0,   29,   30,    0,
    0,   31,   32,   33,  106,    0,  106,  106,  107,  107,
  106,    0,    0,  107,    0,  107,  107,  106,  107,  107,
  107,  107,  107,  107,  256,  257,    0,  153,  154,  155,
  156,  157,  158,    0,  107,    0,  107,  107,  102,  102,
  107,    0,    0,  102,    0,  102,  102,  107,  102,  102,
  102,  102,  102,  102,  153,  154,  155,  156,  157,  158,
    0,    0,    0,    0,  102,    0,  102,  102,  103,  103,
  102,    0,    0,  103,    0,  103,  103,  102,  103,  103,
  103,  103,  103,  103,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  103,    0,  103,  103,  104,  104,
  103,    0,    0,  104,    0,  104,  104,  103,  104,  104,
  104,  104,  104,  104,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  104,    0,  104,  104,  105,  105,
  104,    0,    0,  105,    0,  105,  105,  104,  105,  105,
  105,  105,  105,  105,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  105,    0,  105,  105,    0,    0,
  105,    0,    0,  160,    0,    0,    0,  105,  153,  154,
  155,  156,  157,  158,  283,    0,    0,    0,    0,  153,
  154,  155,  156,  157,  158,  284,    0,    0,    0,    0,
  153,  154,  155,  156,  157,  158,
};
}
static short yycheck[];
static { yycheck(); }
static void yycheck() {
yycheck = new short[] {                          5,
  119,  169,  152,   40,   10,   42,   43,  286,  104,   20,
  160,   17,  265,   73,  110,   21,   22,  286,  265,   25,
  301,  268,  286,  286,   84,   85,  273,  274,  275,  310,
  257,  312,  261,  262,  315,  314,  314,  284,   44,  268,
  287,  286,  289,  286,  291,  314,  258,  294,   59,   86,
  314,  314,  286,   59,   60,  265,  263,  264,   75,  266,
  267,   98,   99,  270,  271,  272,   72,  260,  236,  314,
  268,  314,  265,  315,  170,  259,  260,  261,  262,  326,
  314,  313,  178,  100,  268,  317,  259,   93,  148,  149,
  150,  151,  103,  302,  303,  101,  303,  306,  104,  267,
  250,  295,  252,  253,  110,  142,  260,  313,  119,  228,
  278,  317,  118,  119,  131,  132,  133,  134,  135,  136,
  137,  138,  159,  313,  295,  162,  143,  317,  259,  260,
  261,  262,  314,  283,  284,  318,  232,  268,  144,  295,
  296,  297,  298,  299,  300,  312,  152,  310,  185,  312,
  161,  312,  315,  312,  160,  161,  263,  276,  169,  260,
  261,  262,  173,  169,  170,  317,  318,  268,  324,  175,
  266,  263,  178,  265,  313,  265,  268,  269,  317,  269,
  313,  273,  274,  275,  317,  222,  295,  296,  297,  298,
  299,  300,  284,  261,  262,  287,  314,  289,  265,  291,
  268,  313,  294,  265,  313,  317,  217,  260,  261,  262,
  314,  217,  223,  304,  305,  268,  307,  228,  309,  256,
  257,  258,  228,  301,  313,  236,  232,  263,  317,  265,
  236,  313,  268,  314,  326,  317,  313,  273,  274,  275,
  317,  313,  261,  262,  250,  317,  252,  253,  284,  260,
  313,  287,  288,  289,  317,  291,  267,  312,  294,  313,
  266,  267,  313,  317,  313,  276,  317,  278,  317,  312,
  276,  263,  278,  265,  316,  313,  268,  283,  284,  317,
  312,  273,  274,  275,  153,  154,  155,  156,  157,  158,
  326,  311,  284,  313,  314,  287,  312,  289,  312,  291,
  313,  314,  294,  263,  264,  265,  266,  267,  317,  318,
  270,  271,  272,  317,  318,  263,  264,  265,  266,  267,
  317,  318,  270,  271,  272,  295,  296,  297,  298,  299,
  300,  145,  146,  147,  326,  285,  124,  125,  312,  312,
  312,  311,  310,  303,  313,  295,  296,  297,  298,  299,
  300,  314,  312,  312,  316,  303,  301,  314,  316,  319,
  320,  321,  322,  323,  312,  325,  318,  314,  314,  286,
  301,  319,  320,  321,  322,  263,  264,  265,  266,  267,
  318,  318,  270,  271,  272,  311,  314,  314,  276,  277,
  278,  279,  280,  281,  282,  283,  295,  296,  297,  298,
  299,  300,  263,  264,  265,  266,  267,  314,  269,  270,
  271,  272,  311,  324,  314,  303,  268,  268,  285,  286,
  308,  318,  314,  290,  312,  292,  293,  314,  295,  296,
  297,  298,  299,  300,   66,  302,  303,  304,  305,  306,
  307,  121,  309,  266,  311,   10,  313,  314,  285,  286,
  317,   66,   60,  290,   22,  292,  293,  324,  295,  296,
  297,  298,  299,  300,  170,  302,  303,    7,   41,  306,
   72,  217,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,  302,  303,   -1,   -1,  306,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,  302,  303,   -1,   -1,  306,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,  302,  303,   -1,   -1,  306,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,  263,  264,  265,  266,  267,   -1,
   -1,  270,  271,  272,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,  263,  264,   -1,  266,  267,   -1,
   -1,  270,  271,  272,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,  292,  293,   -1,  295,  296,  297,
  298,  299,  300,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,  295,  296,  297,  298,  299,  300,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,  285,  286,
  317,   -1,   -1,  290,   -1,  292,  293,  324,  295,  296,
  297,  298,  299,  300,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  311,   -1,  313,  314,   -1,   -1,
  317,   -1,   -1,  290,   -1,   -1,   -1,  324,  295,  296,
  297,  298,  299,  300,  290,   -1,   -1,   -1,   -1,  295,
  296,  297,  298,  299,  300,  290,   -1,   -1,   -1,   -1,
  295,  296,  297,  298,  299,  300,
};
}
final static short YYFINAL=2;
final static short YYMAXTOKEN=327;
final static String yyname[] = {
"end-of-file",null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,"T_PROGRAM","T_CONST","T_TYPE","T_VAR","T_FUNCTION",
"T_PROCEDURE","T_INT","T_REAL","T_ID","T_CHAR","T_STRING","T_BEGIN","T_END",
"T_TRUE","T_FALSE","T_MAXINT","T_READ","T_WRITE","T_WRITELN","T_ABS","T_CHR",
"T_ODD","T_ORD","T_PRED","T_SQR","T_SQRT","T_SUCC","T_IF","T_THEN","T_ELSE",
"T_REPEAT","T_UNTIL","T_WHILE","T_DO","T_CASE","T_TO","T_DOWNTO","T_FOR",
"T_EQUAL","T_UNEQUAL","T_GE","T_GT","T_LE","T_LT","T_ASSIGN","T_PLUS","T_MINUS",
"T_MUL","T_DIV","T_OR","T_AND","T_NOT","T_MOD","T_LB","T_RB","T_LP","T_RP",
"T_SEMI","T_DOT","T_DOTDOT","T_COMMA","T_COLON","T_INTEGER_TYPE",
"T_BOOLEAN_TYPE","T_CHAR_TYPE","T_REAL_TYPE","T_ARRAY","T_OF","T_RECORD",
"T_GOTO","ERROR",
};
final static String yyrule[] = {
"$accept : program",
"program : T_PROGRAM T_ID T_SEMI routine T_DOT",
"routine : routine_head routine_body",
"routine_head : const_part type_part var_part routine_part",
"routine_part :",
"routine_part : routine_part function_decl",
"routine_part : routine_part procedure_decl",
"routine_part : function_decl",
"routine_part : procedure_decl",
"function_decl : function_head T_SEMI routine T_SEMI",
"function_head : T_FUNCTION T_ID parameters T_COLON simple_type_decl",
"parameters :",
"parameters : T_LP para_decl_list T_RP",
"para_decl_list : para_decl_list T_SEMI para_type_list",
"para_decl_list : para_type_list",
"para_type_list : T_VAR name_list T_COLON simple_type_decl",
"para_type_list : name_list T_COLON simple_type_decl",
"procedure_decl : procedure_head T_SEMI routine T_SEMI",
"procedure_head : T_PROCEDURE T_ID parameters",
"var_part :",
"var_part : T_VAR var_decl_list",
"var_decl_list : var_decl_list var_decl",
"var_decl_list : var_decl",
"var_decl : name_list T_COLON type_decl T_SEMI",
"const_part :",
"const_part : T_CONST const_expr_list",
"const_expr_list : const_expr_list const_expr",
"const_expr_list : const_expr",
"const_expr : ID T_EQUAL const_value T_SEMI",
"const_value : T_INT",
"const_value : T_REAL",
"const_value : T_CHAR",
"const_value : T_STRING",
"const_value : T_TRUE",
"const_value : T_FALSE",
"const_value : T_MAXINT",
"type_part :",
"type_part : T_TYPE type_decl_list",
"type_decl_list : type_decl_list type_definition",
"type_decl_list : type_definition",
"type_definition : ID T_EQUAL type_decl T_SEMI",
"type_decl : simple_type_decl",
"type_decl : array_type_decl",
"type_decl : record_type_decl",
"record_type_decl : T_RECORD field_decl_list T_END",
"field_decl_list : field_decl_list field_decl",
"field_decl_list : field_decl",
"field_decl : name_list T_COLON type_decl T_SEMI",
"array_type_decl : T_ARRAY T_LB simple_type_decl T_RB T_OF type_decl",
"simple_type_decl : ID",
"simple_type_decl : T_LP name_list T_RP",
"simple_type_decl : const_value T_DOTDOT const_value",
"simple_type_decl : T_MINUS const_value T_DOTDOT const_value",
"simple_type_decl : T_MINUS const_value T_DOTDOT T_MINUS const_value",
"simple_type_decl : ID T_DOTDOT ID",
"simple_type_decl : T_INTEGER_TYPE",
"simple_type_decl : T_BOOLEAN_TYPE",
"simple_type_decl : T_REAL_TYPE",
"simple_type_decl : T_CHAR_TYPE",
"name_list : name_list T_COMMA ID",
"name_list : ID",
"ID : T_ID",
"routine_body : compound_stmt",
"compound_stmt : T_BEGIN stmt_list T_END",
"stmt_list :",
"stmt_list : stmt_list stmt T_SEMI",
"stmt : T_INT T_COLON no_label_stmt",
"stmt : no_label_stmt",
"no_label_stmt : assign_stmt",
"no_label_stmt : compound_stmt",
"no_label_stmt : goto_stmt",
"no_label_stmt : if_stmt",
"no_label_stmt : repeat_stmt",
"no_label_stmt : while_stmt",
"no_label_stmt : case_stmt",
"no_label_stmt : for_stmt",
"no_label_stmt : proc_stmt",
"assign_stmt : ID T_ASSIGN expression",
"assign_stmt : ID T_LB expression T_RB T_ASSIGN expression",
"assign_stmt : ID T_DOT ID T_ASSIGN expression",
"goto_stmt : T_GOTO T_INT",
"if_stmt : T_IF expression T_THEN stmt else_clause",
"else_clause :",
"else_clause : T_ELSE stmt",
"repeat_stmt : T_REPEAT stmt_list T_UNTIL expression",
"repeat_stmt :",
"while_stmt : T_WHILE expression T_DO stmt",
"case_stmt : T_CASE expression T_OF case_expr_list T_END",
"case_expr_list : case_expr_list case_expr",
"case_expr_list : case_expr",
"case_expr : const_value T_COLON stmt T_SEMI",
"case_expr : ID T_COLON stmt T_SEMI",
"for_stmt : T_FOR ID T_ASSIGN expression T_TO expression T_DO stmt",
"for_stmt : T_FOR ID T_ASSIGN expression T_DOWNTO expression T_DO stmt",
"proc_stmt : ID",
"proc_stmt : ID T_LP args_list T_RP",
"proc_stmt : T_READ T_LP factor T_RP",
"proc_stmt : T_WRITE T_LP args_list T_RP",
"proc_stmt : T_WRITELN",
"proc_stmt : T_WRITELN T_LP args_list T_RP",
"args_list : args_list T_COMMA expression",
"args_list : expression",
"expression : expression T_GE expr",
"expression : expression T_GT expr",
"expression : expression T_LE expr",
"expression : expression T_LT expr",
"expression : expression T_EQUAL expr",
"expression : expression T_UNEQUAL expr",
"expression : expr",
"expr : expr T_PLUS term",
"expr : expr T_MINUS term",
"expr : expr T_OR term",
"expr : term",
"term : term T_MUL factor",
"term : term T_DIV factor",
"term : term T_MOD factor",
"term : term T_AND factor",
"term : factor",
"factor : ID",
"factor : ID T_LP args_list T_RP",
"factor : const_value",
"factor : T_LP expression T_RP",
"factor : T_NOT factor",
"factor : T_MINUS factor",
"factor : ID T_LB expression T_RB",
"factor : ID T_DOT ID",
"factor : T_ABS T_LP args_list T_RP",
"factor : T_CHR T_LP args_list T_RP",
"factor : T_ODD T_LP args_list T_RP",
"factor : T_ORD T_LP args_list T_RP",
"factor : T_PRED T_LP args_list T_RP",
"factor : T_SQR T_LP args_list T_RP",
"factor : T_SQRT T_LP args_list T_RP",
"factor : T_SUCC T_LP args_list T_RP",
};

//#line 624 "compiler.y"

    private scanner lex;
    private TreeNode savedTree;
    private char[] savedName;
    private int savedNum;
    private int yyline;

    private int yylex() {
        int retVal = -1;
        try {
            retVal = lex.yylex();
            yyline=lex.getLineNumber();
        } catch (IOException e) {
            System.err.println("IO Error:" + e);
        }
        return retVal;
    }

    /* error reporting */
    /* constructor taking in File Input */
    public Parser (Reader r) {
        lex = new scanner (r, this);
    }
    public TreeNode parse(){
        yyparse();
        return this.savedTree;
    }
    static boolean interactive;
    public static void main (String [] args) throws IOException {
      Parser yyparser;
      String filePath = args[0];
      yyparser = new Parser(new FileReader(filePath));
        System.err.println("YACC: Parsing...");
        TreeNode syntaxTree = yyparser.parse();
        System.out.println(syntaxTree);
        System.err.println("YACC: Parsed...");
        syntaxTree.printTree(syntaxTree);
        CodeGenerator.getCodeGenerator().generate(syntaxTree);
        System.err.println("code generation end");
    }

        /* error reporting */
    public void yyerror (String error) {
        System.err.println("Error : " + error + " at line " + lex.getLineNumber());
    }
//#line 691 "Parser.java"
//###############################################################
// method: yylexdebug : check lexer state
//###############################################################
void yylexdebug(int state,int ch)
{
String s=null;
  if (ch < 0) ch=0;
  if (ch <= YYMAXTOKEN) //check index bounds
     s = yyname[ch];    //now get it
  if (s==null)
    s = "illegal-symbol";
  debug("state "+state+", reading "+ch+" ("+s+")");
}





//The following are now global, to aid in error reporting
int yyn;       //next next thing to do
int yym;       //
int yystate;   //current parsing state from state table
String yys;    //current token string


//###############################################################
// method: yyparse : parse input and execute indicated items
//###############################################################
int yyparse()
{
boolean doaction;
  init_stacks();
  yynerrs = 0;
  yyerrflag = 0;
  yychar = -1;          //impossible char forces a read
  yystate=0;            //initial state
  state_push(yystate);  //save it
  val_push(yylval);     //save empty value
  while (true) //until parsing is done, either correctly, or w/error
    {
    doaction=true;
    if (yydebug) debug("loop"); 
    //#### NEXT ACTION (from reduction table)
    for (yyn=yydefred[yystate];yyn==0;yyn=yydefred[yystate])
      {
      if (yydebug) debug("yyn:"+yyn+"  state:"+yystate+"  yychar:"+yychar);
      if (yychar < 0)      //we want a char?
        {
        yychar = yylex();  //get next token
        if (yydebug) debug(" next yychar:"+yychar);
        //#### ERROR CHECK ####
        if (yychar < 0)    //it it didn't work/error
          {
          yychar = 0;      //change it to default string (no -1!)
          if (yydebug)
            yylexdebug(yystate,yychar);
          }
        }//yychar<0
      yyn = yysindex[yystate];  //get amount to shift by (shift index)
      if ((yyn != 0) && (yyn += yychar) >= 0 &&
          yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
        {
        if (yydebug)
          debug("state "+yystate+", shifting to state "+yytable[yyn]);
        //#### NEXT STATE ####
        yystate = yytable[yyn];//we are in a new state
        state_push(yystate);   //save it
        val_push(yylval);      //push our lval as the input for next rule
        yychar = -1;           //since we have 'eaten' a token, say we need another
        if (yyerrflag > 0)     //have we recovered an error?
           --yyerrflag;        //give ourselves credit
        doaction=false;        //but don't process yet
        break;   //quit the yyn=0 loop
        }

    yyn = yyrindex[yystate];  //reduce
    if ((yyn !=0 ) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
      {   //we reduced!
      if (yydebug) debug("reduce");
      yyn = yytable[yyn];
      doaction=true; //get ready to execute
      break;         //drop down to actions
      }
    else //ERROR RECOVERY
      {
      if (yyerrflag==0)
        {
        yyerror("syntax error");
        yynerrs++;
        }
      if (yyerrflag < 3) //low error count?
        {
        yyerrflag = 3;
        while (true)   //do until break
          {
          if (stateptr<0)   //check for under & overflow here
            {
            yyerror("stack underflow. aborting...");  //note lower case 's'
            return 1;
            }
          yyn = yysindex[state_peek(0)];
          if ((yyn != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
            if (yydebug)
              debug("state "+state_peek(0)+", error recovery shifting to state "+yytable[yyn]+" ");
            yystate = yytable[yyn];
            state_push(yystate);
            val_push(yylval);
            doaction=false;
            break;
            }
          else
            {
            if (yydebug)
              debug("error recovery discarding state "+state_peek(0)+" ");
            if (stateptr<0)   //check for under & overflow here
              {
              yyerror("Stack underflow. aborting...");  //capital 'S'
              return 1;
              }
            state_pop();
            val_pop();
            }
          }
        }
      else            //discard this token
        {
        if (yychar == 0)
          return 1; //yyabort
        if (yydebug)
          {
          yys = null;
          if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
          if (yys == null) yys = "illegal-symbol";
          debug("state "+yystate+", error recovery discards token "+yychar+" ("+yys+")");
          }
        yychar = -1;  //read another
        }
      }//end error recovery
    }//yyn=0 loop
    if (!doaction)   //any reason not to proceed?
      continue;      //skip action
    yym = yylen[yyn];          //get count of terminals on rhs
    if (yydebug)
      debug("state "+yystate+", reducing "+yym+" by rule "+yyn+" ("+yyrule[yyn]+")");
    if (yym>0)                 //if count of rhs not 'nil'
      yyval = val_peek(yym-1); //get current semantic value
    yyval = dup_yyval(yyval); //duplicate yyval if ParserVal is used as semantic value
    switch(yyn)
      {
//########## USER-SUPPLIED ACTIONS ##########
case 1:
//#line 32 "compiler.y"
{   yyval.node = val_peek(1).node;
                            yyval.node.setAttribute(val_peek(3).sval);
                            savedTree = yyval.node;
                        }
break;
case 2:
//#line 37 "compiler.y"
{
                            yyval.node =val_peek(1).node;
                            yyval.node.setSibling(val_peek(0).node);
                        }
break;
case 3:
//#line 42 "compiler.y"
{
                            yyval.node = new TreeNode(DeclarationKind.ROUTINEHEAD,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(1).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 4:
//#line 50 "compiler.y"
{   yyval.node= null;}
break;
case 5:
//#line 52 "compiler.y"
{   TreeNode t=val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 6:
//#line 63 "compiler.y"
{   TreeNode t=val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 7:
//#line 73 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 8:
//#line 74 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 9:
//#line 77 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.FUNCTION,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 10:
//#line 84 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.FUNCTIONHEAD,yyline);
                            yyval.node.setAttribute(val_peek(3).sval);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 11:
//#line 92 "compiler.y"
{yyval.node=null;}
break;
case 12:
//#line 94 "compiler.y"
{yyval.node=val_peek(1).node;}
break;
case 13:
//#line 97 "compiler.y"
{   TreeNode t=val_peek(2).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(2).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 14:
//#line 108 "compiler.y"
{   yyval.node=val_peek(0).node; }
break;
case 15:
//#line 111 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.VAR_PARA,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 16:
//#line 117 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.VAL_PARA,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 17:
//#line 124 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.PROCEDURE,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 18:
//#line 131 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.PROCEDUREHEAD,yyline);
                            yyval.node.setAttribute(val_peek(1).sval);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 19:
//#line 138 "compiler.y"
{   yyval.node = null;}
break;
case 20:
//#line 140 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 21:
//#line 143 "compiler.y"
{   TreeNode t = val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 22:
//#line 153 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 23:
//#line 156 "compiler.y"
{   yyval.node=new TreeNode(DeclarationKind.VAR,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 24:
//#line 162 "compiler.y"
{   yyval.node = null; }
break;
case 25:
//#line 164 "compiler.y"
{   yyval.node=val_peek(0).node; }
break;
case 26:
//#line 167 "compiler.y"
{
                            TreeNode t = val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 27:
//#line 180 "compiler.y"
{   yyval.node=val_peek(0).node; }
break;
case 28:
//#line 183 "compiler.y"
{
                            yyval.node=new TreeNode(DeclarationKind.CONST,yyline);
                            yyval.node.setAttribute(val_peek(3).node.getAttribute());
                            yyval.node.addChild(val_peek(1).node);
                            yyval.node.setExpType(val_peek(1).node.getExpType());
                        }
break;
case 29:
//#line 191 "compiler.y"
{
                            yyval.node =new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.INT);
                            yyval.node.setAttribute(val_peek(0).ival);
                        }
break;
case 30:
//#line 197 "compiler.y"
{
                            yyval.node = new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.REAL);
                            yyval.node.setAttribute(val_peek(0).dval);
                        }
break;
case 31:
//#line 203 "compiler.y"
{
                            yyval.node = new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.CHAR);
                            yyval.node.setAttribute(val_peek(0).sval.toCharArray());
                        }
break;
case 32:
//#line 209 "compiler.y"
{
                            yyval.node = new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.STRING);
                            yyval.node.setAttribute(val_peek(0).sval);
                        }
break;
case 33:
//#line 215 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.BOOL);
                            yyval.node.setAttribute(1);
                        }
break;
case 34:
//#line 221 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.BOOL);
                            yyval.node.setAttribute(0);
                        }
break;
case 35:
//#line 227 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.CONST,yyline);
                            yyval.node.setExpType(ExpressionType.INT);
                            yyval.node.setAttribute(2147483647);
                        }
break;
case 36:
//#line 234 "compiler.y"
{   yyval.node=null;}
break;
case 37:
//#line 236 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 38:
//#line 239 "compiler.y"
{
                            TreeNode t=val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                              yyval.node=val_peek(0).node;
                        }
break;
case 39:
//#line 251 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 40:
//#line 254 "compiler.y"
{   yyval.node=new TreeNode(DeclarationKind.TYPE,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 41:
//#line 259 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 42:
//#line 260 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 43:
//#line 261 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 44:
//#line 264 "compiler.y"
{   yyval.node=val_peek(1).node; }
break;
case 45:
//#line 267 "compiler.y"
{
                            TreeNode t=val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 46:
//#line 278 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 47:
//#line 281 "compiler.y"
{
                            yyval.node=new TreeNode(TypeKind.RECORD,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 48:
//#line 288 "compiler.y"
{
                            yyval.node=new TreeNode(TypeKind.ARRAY,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setExpType(ExpressionType.ARRAY);
                        }
break;
case 49:
//#line 296 "compiler.y"
{
                            yyval.node=new TreeNode(TypeKind.SIMPLE_ID,yyline);
                            yyval.node.setAttribute(val_peek(0).node.getAttribute());
                            /*free($1);*/
                        }
break;
case 50:
//#line 302 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_ENUM,yyline);
                            yyval.node.addChild(val_peek(1).node);
                            yyval.node.setExpType(ExpressionType.SIMPLE_ENUM);
                        }
break;
case 51:
//#line 307 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
break;
case 52:
//#line 313 "compiler.y"
{
                            yyval.node=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.getChildren().get(0).setAttribute(Integer.parseInt(String.valueOf(yyval.node.getChildren().get(0).getAttribute()))*(-1));
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
break;
case 53:
//#line 321 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.getChildren().get(0).setAttribute(Integer.parseInt(String.valueOf(yyval.node.getChildren().get(0).getAttribute()))*(-1));
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.getChildren().get(1).setAttribute(Integer.parseInt(String.valueOf(yyval.node.getChildren().get(1).getAttribute()))*(-1));
                            yyval.node.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
break;
case 54:
//#line 329 "compiler.y"
{
                            yyval.node=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
break;
case 55:
//#line 336 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            yyval.node.setExpType(ExpressionType.INT);
                        }
break;
case 56:
//#line 340 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            yyval.node.setExpType(ExpressionType.BOOL);
                        }
break;
case 57:
//#line 344 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            yyval.node.setExpType(ExpressionType.REAL);
                        }
break;
case 58:
//#line 348 "compiler.y"
{   yyval.node=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            yyval.node.setExpType(ExpressionType.CHAR);
                        }
break;
case 59:
//#line 353 "compiler.y"
{
                            TreeNode t=val_peek(2).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(2).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 60:
//#line 364 "compiler.y"
{   yyval.node=val_peek(0).node; }
break;
case 61:
//#line 367 "compiler.y"
{   yyval.node=new TreeNode(ExpressionKind.ID,yyline);
                            yyval.node.setAttribute(val_peek(0).sval);
                        }
break;
case 62:
//#line 370 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 63:
//#line 371 "compiler.y"
{yyval.node=val_peek(1).node;}
break;
case 64:
//#line 373 "compiler.y"
{yyval.node=null;}
break;
case 65:
//#line 375 "compiler.y"
{
                            TreeNode t=val_peek(2).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(1).node);
                                yyval.node=val_peek(2).node;
                            }
                            else
                                yyval.node=val_peek(1).node;
                        }
break;
case 66:
//#line 388 "compiler.y"
{
                            yyval.node=new TreeNode(StatementKind.LABEL,yyline);
                            yyval.node.setAttribute(val_peek(2).ival);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 67:
//#line 394 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 68:
//#line 396 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 69:
//#line 397 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 70:
//#line 398 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 71:
//#line 399 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 72:
//#line 400 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 73:
//#line 401 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 74:
//#line 402 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 75:
//#line 403 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 76:
//#line 404 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 77:
//#line 406 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.ASSIGN,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setAttribute(OperationKind.ID);
                        }
break;
case 78:
//#line 412 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.ASSIGN,yyline);
                            yyval.node.addChild(val_peek(5).node);
                            (yyval.node.getChildren().get(0)).addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setAttribute(OperationKind.ARRAY);
                        }
break;
case 79:
//#line 420 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.ASSIGN,yyline);
                            yyval.node.addChild(val_peek(4).node);
                            (yyval.node.getChildren().get(0)).addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setAttribute(OperationKind.RECORD);
                        }
break;
case 80:
//#line 428 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.GOTO,yyline);
                            yyval.node.setAttribute(val_peek(0).ival);
                        }
break;
case 81:
//#line 433 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.IF,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 82:
//#line 439 "compiler.y"
{yyval.node=null;}
break;
case 83:
//#line 440 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 84:
//#line 443 "compiler.y"
{
                            yyval.node=new TreeNode(StatementKind.REPEAT,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 86:
//#line 451 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.WHILE,yyline);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                        }
break;
case 87:
//#line 456 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.CASE,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 88:
//#line 461 "compiler.y"
{   TreeNode t=val_peek(1).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(1).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 89:
//#line 471 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 90:
//#line 473 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.CASE,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 91:
//#line 479 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.CASE,yyline);
                            yyval.node.addChild(val_peek(3).node);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 92:
//#line 485 "compiler.y"
{
                            yyval.node=new TreeNode(StatementKind.FOR,yyline);
                            yyval.node.addChild(val_peek(6).node);
                            yyval.node.addChild(val_peek(4).node);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setAttribute(OperationKind.TO);
                        }
break;
case 93:
//#line 494 "compiler.y"
{
                            yyval.node=new TreeNode(StatementKind.FOR,yyline);
                            yyval.node.addChild(val_peek(6).node);
                            yyval.node.addChild(val_peek(4).node);
                            yyval.node.addChild(val_peek(2).node);
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setAttribute(OperationKind.DOWNTO);
                        }
break;
case 94:
//#line 503 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.PROC_ID,yyline);
                            yyval.node.setAttribute(val_peek(0).node.getAttribute());
                        }
break;
case 95:
//#line 507 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.PROC_ID,yyline);
                            yyval.node.setAttribute(val_peek(3).node.getAttribute());
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 96:
//#line 512 "compiler.y"
{
                            yyval.node=new TreeNode(StatementKind.PROC_SYS,yyline);
                            yyval.node.setAttribute(OperationKind.READ);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 97:
//#line 518 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.PROC_SYS,yyline);
                            yyval.node.setAttribute(OperationKind.WRITE);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 98:
//#line 523 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.PROC_SYS,yyline);
                            yyval.node.setAttribute(OperationKind.WRITELN);
                        }
break;
case 99:
//#line 527 "compiler.y"
{   yyval.node=new TreeNode(StatementKind.PROC_SYS,yyline);
                            yyval.node.setAttribute(OperationKind.WRITELN);
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 100:
//#line 532 "compiler.y"
{   TreeNode t=val_peek(2).node;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling(val_peek(0).node);
                                yyval.node=val_peek(2).node;
                            }
                            else
                                yyval.node=val_peek(0).node;
                        }
break;
case 101:
//#line 542 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 102:
//#line 544 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.GE,yyline); }
break;
case 103:
//#line 545 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.GT,yyline); }
break;
case 104:
//#line 546 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.LE,yyline); }
break;
case 105:
//#line 547 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.LT,yyline); }
break;
case 106:
//#line 548 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.EQUAL,yyline); }
break;
case 107:
//#line 549 "compiler.y"
{  yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.UNEQUAL,yyline); }
break;
case 108:
//#line 550 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 109:
//#line 552 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.PLUS,yyline); }
break;
case 110:
//#line 553 "compiler.y"
{  yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.MINUS,yyline); }
break;
case 111:
//#line 554 "compiler.y"
{     yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.OR,yyline); }
break;
case 112:
//#line 555 "compiler.y"
{   yyval.node=val_peek(0).node;}
break;
case 113:
//#line 557 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.MUL,yyline); }
break;
case 114:
//#line 558 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.DIV,yyline); }
break;
case 115:
//#line 559 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.MOD,yyline); }
break;
case 116:
//#line 560 "compiler.y"
{   yyval.node=new TreeNode(val_peek(2).node,val_peek(0).node,OperationKind.AND,yyline); }
break;
case 117:
//#line 561 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 118:
//#line 564 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 119:
//#line 566 "compiler.y"
{
                            yyval.node=new TreeNode(ExpressionKind.FUNC_ID,yyline);
                            yyval.node.setAttribute(val_peek(3).node.getAttribute());
                            yyval.node.addChild(val_peek(1).node);
                        }
break;
case 120:
//#line 571 "compiler.y"
{yyval.node=val_peek(0).node;}
break;
case 121:
//#line 572 "compiler.y"
{yyval.node=val_peek(1).node;}
break;
case 122:
//#line 574 "compiler.y"
{
                           yyval.node=new TreeNode(val_peek(0).node,null,OperationKind.NOT,yyline);
                        }
break;
case 123:
//#line 578 "compiler.y"
{   yyval.node=new TreeNode(val_peek(0).node, null, OperationKind.MINUS, yyline);
                        }
break;
case 124:
//#line 581 "compiler.y"
{   yyval.node=val_peek(3).node;
                            yyval.node.addChild(val_peek(1).node);
                            yyval.node.setExpType(ExpressionType.ARRAY);
                        }
break;
case 125:
//#line 586 "compiler.y"
{   yyval.node=val_peek(2).node;
                            yyval.node.addChild(val_peek(0).node);
                            yyval.node.setExpType(ExpressionType.RECORD);
                        }
break;
case 126:
//#line 591 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.ABS, val_peek(1).node,yyline);
                        }
break;
case 127:
//#line 595 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.CHR, val_peek(1).node,yyline);
                        }
break;
case 128:
//#line 599 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.ODD, val_peek(1).node,yyline);
                        }
break;
case 129:
//#line 603 "compiler.y"
{

                            yyval.node=new TreeNode(OperationKind.ORD, val_peek(1).node,yyline);
                        }
break;
case 130:
//#line 608 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.PRED, val_peek(1).node,yyline);
                        }
break;
case 131:
//#line 612 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.SQR, val_peek(1).node,yyline);
                        }
break;
case 132:
//#line 616 "compiler.y"
{
                            yyval.node=new TreeNode(OperationKind.SQRT, val_peek(1).node,yyline);
                        }
break;
case 133:
//#line 620 "compiler.y"
{   yyval.node=new TreeNode(OperationKind.SUCC, val_peek(1).node,yyline);
                        }
break;
//#line 1697 "Parser.java"
//########## END OF USER-SUPPLIED ACTIONS ##########
    }//switch
    //#### Now let's reduce... ####
    if (yydebug) debug("reduce");
    state_drop(yym);             //we just reduced yylen states
    yystate = state_peek(0);     //get new state
    val_drop(yym);               //corresponding value drop
    yym = yylhs[yyn];            //select next TERMINAL(on lhs)
    if (yystate == 0 && yym == 0)//done? 'rest' state and at first TERMINAL
      {
      if (yydebug) debug("After reduction, shifting from state 0 to state "+YYFINAL+"");
      yystate = YYFINAL;         //explicitly say we're done
      state_push(YYFINAL);       //and save it
      val_push(yyval);           //also save the semantic value of parsing
      if (yychar < 0)            //we want another character?
        {
        yychar = yylex();        //get next character
        if (yychar<0) yychar=0;  //clean, if necessary
        if (yydebug)
          yylexdebug(yystate,yychar);
        }
      if (yychar == 0)          //Good exit (if lex returns 0 ;-)
         break;                 //quit the loop--all DONE
      }//if yystate
    else                        //else not done yet
      {                         //get next state and push, for next yydefred[]
      yyn = yygindex[yym];      //find out where to go
      if ((yyn != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn]; //get new state
      else
        yystate = yydgoto[yym]; //else go to new defred
      if (yydebug) debug("after reduction, shifting from state "+state_peek(0)+" to state "+yystate+"");
      state_push(yystate);     //going again, so push state & val...
      val_push(yyval);         //for next action
      }
    }//main loop
  return 0;//yyaccept!!
}
//## end of method parse() ######################################



//## run() --- for Thread #######################################
/**
 * A default run method, used for operating this parser
 * object in the background.  It is intended for extending Thread
 * or implementing Runnable.  Turn off with -Jnorun .
 */
public void run()
{
  yyparse();
}
//## end of method run() ########################################



//## Constructors ###############################################
/**
 * Default constructor.  Turn off with -Jnoconstruct .

 */
public Parser()
{
  //nothing to do
}


/**
 * Create a parser, setting the debug to true or false.
 * @param debugMe true for debugging, false for no debug.
 */
public Parser(boolean debugMe)
{
  yydebug=debugMe;
}
//###############################################################



}
//################### END OF CLASS ##############################
