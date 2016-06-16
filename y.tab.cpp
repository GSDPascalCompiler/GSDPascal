/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     READ = 258,
     TYPE = 259,
     LP = 260,
     RP = 261,
     LB = 262,
     RB = 263,
     PLUS = 264,
     MINUS = 265,
     MUL = 266,
     DIV = 267,
     MOD = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     ASSIGN = 272,
     GE = 273,
     GT = 274,
     LE = 275,
     LT = 276,
     EQUAL = 277,
     UNEQUAL = 278,
     INTEGER = 279,
     REAL = 280,
     CHAR = 281,
     STRING = 282,
     CONST = 283,
     ARRAY = 284,
     SYS_CON = 285,
     SYS_TYPE = 286,
     SYS_PROC = 287,
     SYS_FUNCT = 288,
     PROGRAM = 289,
     FUNCTION = 290,
     PROCEDURE = 291,
     RECORD = 292,
     ID = 293,
     VAR = 294,
     DOT = 295,
     SEMI = 296,
     COLON = 297,
     COMMA = 298,
     OF = 299,
     BEG = 300,
     END = 301,
     TO = 302,
     DOWNTO = 303,
     IF = 304,
     THEN = 305,
     ELSE = 306,
     REPEAT = 307,
     UNTIL = 308,
     WHILE = 309,
     DO = 310,
     FOR = 311,
     GOTO = 312,
     CASE = 313
   };
#endif
/* Tokens.  */
#define READ 258
#define TYPE 259
#define LP 260
#define RP 261
#define LB 262
#define RB 263
#define PLUS 264
#define MINUS 265
#define MUL 266
#define DIV 267
#define MOD 268
#define AND 269
#define OR 270
#define NOT 271
#define ASSIGN 272
#define GE 273
#define GT 274
#define LE 275
#define LT 276
#define EQUAL 277
#define UNEQUAL 278
#define INTEGER 279
#define REAL 280
#define CHAR 281
#define STRING 282
#define CONST 283
#define ARRAY 284
#define SYS_CON 285
#define SYS_TYPE 286
#define SYS_PROC 287
#define SYS_FUNCT 288
#define PROGRAM 289
#define FUNCTION 290
#define PROCEDURE 291
#define RECORD 292
#define ID 293
#define VAR 294
#define DOT 295
#define SEMI 296
#define COLON 297
#define COMMA 298
#define OF 299
#define BEG 300
#define END 301
#define TO 302
#define DOWNTO 303
#define IF 304
#define THEN 305
#define ELSE 306
#define REPEAT 307
#define UNTIL 308
#define WHILE 309
#define DO 310
#define FOR 311
#define GOTO 312
#define CASE 313




/* Copy the first part of user declarations.  */
#line 1 "compiler.y"

#include "global.h"
#include "parsetree.h"
#include <stdio.h>
#include "util.h"

extern int yylex();
int yyerror(const char *s){
	printf("%s\n", s);
	return 0;
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 235 "compiler.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNRULES -- Number of states.  */
#define YYNSTATES  265

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    24,    27,
      28,    31,    33,    38,    40,    42,    44,    46,    48,    51,
      52,    55,    57,    62,    64,    66,    68,    70,    72,    76,
      81,    87,    94,    99,   106,   110,   113,   115,   120,   124,
     126,   128,   131,   132,   135,   137,   142,   145,   148,   150,
     152,   153,   158,   164,   169,   173,   177,   178,   182,   184,
     188,   192,   195,   197,   199,   203,   207,   208,   212,   214,
     216,   218,   220,   222,   224,   226,   228,   230,   232,   236,
     243,   249,   251,   256,   258,   263,   268,   274,   277,   278,
     283,   288,   297,   299,   301,   307,   310,   312,   317,   322,
     325,   329,   331,   335,   339,   343,   347,   351,   355,   357,
     361,   365,   369,   371,   375,   379,   383,   387,   389,   391,
     396,   398,   402,   405,   408,   413,   414,   420,   424,   426,
     428,   429,   433
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      60,     0,    -1,    61,    62,    40,    -1,    34,    38,    41,
      -1,    64,    94,    -1,    64,    94,    -1,    65,    66,    70,
      81,    84,    -1,    -1,    28,    67,    -1,    -1,    67,    68,
      -1,    68,    -1,    38,    22,    69,    41,    -1,    24,    -1,
      25,    -1,    26,    -1,    27,    -1,    30,    -1,     4,    71,
      -1,    -1,    71,    72,    -1,    72,    -1,    38,    22,    73,
      41,    -1,    74,    -1,    75,    -1,    76,    -1,    31,    -1,
      38,    -1,     5,    79,     6,    -1,    69,    40,    40,    69,
      -1,    10,    69,    40,    40,    69,    -1,    10,    69,    40,
      40,    10,    69,    -1,    38,    40,    40,    38,    -1,    29,
       7,    74,     8,    44,    73,    -1,    37,    77,    46,    -1,
      77,    78,    -1,    78,    -1,    79,    42,    73,    41,    -1,
      79,    43,    80,    -1,    80,    -1,    38,    -1,    39,    82,
      -1,    -1,    82,    83,    -1,    83,    -1,    79,    42,    73,
      41,    -1,    84,    85,    -1,    84,    87,    -1,    85,    -1,
      87,    -1,    -1,    86,    41,    63,    41,    -1,    35,    38,
      89,    42,    74,    -1,    88,    41,    63,    41,    -1,    36,
      38,    89,    -1,     5,    90,     6,    -1,    -1,    90,    41,
      91,    -1,    91,    -1,    92,    42,    74,    -1,    93,    42,
      74,    -1,    39,    79,    -1,    79,    -1,    95,    -1,    45,
      96,    46,    -1,    96,    97,    41,    -1,    -1,    24,    42,
      98,    -1,    98,    -1,    99,    -1,   100,    -1,    95,    -1,
     101,    -1,   103,    -1,   104,    -1,   105,    -1,   107,    -1,
     110,    -1,    38,    17,   112,    -1,    38,     7,   112,     8,
      17,   112,    -1,    38,    40,    38,    17,   112,    -1,    38,
      -1,    38,     5,   117,     6,    -1,    32,    -1,    32,     5,
     111,     6,    -1,     3,     5,   115,     6,    -1,    49,   112,
      50,    97,   102,    -1,    51,    97,    -1,    -1,    52,    96,
      53,   112,    -1,    54,   112,    55,    97,    -1,    56,    38,
      17,   112,   106,   112,    55,    97,    -1,    47,    -1,    48,
      -1,    58,   112,    44,   108,    46,    -1,   108,   109,    -1,
     109,    -1,    69,    42,    97,    41,    -1,    38,    42,    97,
      41,    -1,    57,    24,    -1,   111,    43,   112,    -1,   112,
      -1,   112,    18,   113,    -1,   112,    19,   113,    -1,   112,
      20,   113,    -1,   112,    21,   113,    -1,   112,    22,   113,
      -1,   112,    23,   113,    -1,   113,    -1,   113,     9,   114,
      -1,   113,    10,   114,    -1,   113,    15,   114,    -1,   114,
      -1,   114,    11,   115,    -1,   114,    12,   115,    -1,   114,
      13,   115,    -1,   114,    14,   115,    -1,   115,    -1,    33,
      -1,    33,     5,   118,     6,    -1,    69,    -1,     5,   112,
       6,    -1,    16,   115,    -1,    10,   115,    -1,    38,     7,
     112,     8,    -1,    -1,    38,     5,   117,     6,   116,    -1,
      38,    40,    38,    -1,    38,    -1,   118,    -1,    -1,   118,
      43,   112,    -1,   112,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    32,    32,    40,    46,    52,    77,    84,    89,    94,
      99,   103,   109,   115,   119,   123,   127,   131,   137,   142,
     147,   151,   157,   163,   167,   172,   179,   183,   187,   191,
     195,   199,   203,   209,   215,   221,   225,   231,   237,   241,
     247,   253,   258,   263,   267,   273,   297,   301,   305,   309,
     314,   319,   325,   331,   337,   343,   348,   353,   357,   363,
     367,   373,   379,   396,   402,   408,   413,   418,   422,   428,
     432,   436,   440,   444,   448,   452,   456,   460,   466,   470,
     474,   480,   484,   488,   492,   496,   502,   508,   512,   515,
     521,   527,   533,   537,   543,   549,   553,   559,   563,   569,
     575,   579,   585,   589,   593,   597,   601,   605,   609,   615,
     619,   623,   627,   633,   637,   641,   645,   649,   655,   659,
     663,   667,   671,   675,   679,   683,   683,   687,   691,   697,
     702,   709,   713
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "READ", "TYPE", "LP", "RP", "LB", "RB",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "AND", "OR", "NOT", "ASSIGN", "GE",
  "GT", "LE", "LT", "EQUAL", "UNEQUAL", "INTEGER", "REAL", "CHAR",
  "STRING", "CONST", "ARRAY", "SYS_CON", "SYS_TYPE", "SYS_PROC",
  "SYS_FUNCT", "PROGRAM", "FUNCTION", "PROCEDURE", "RECORD", "ID", "VAR",
  "DOT", "SEMI", "COLON", "COMMA", "OF", "BEG", "END", "TO", "DOWNTO",
  "IF", "THEN", "ELSE", "REPEAT", "UNTIL", "WHILE", "DO", "FOR", "GOTO",
  "CASE", "$accept", "program", "program_head", "routine", "sub_routine",
  "routine_head", "label_part", "const_part", "const_expr_list",
  "const_expr", "const_value", "type_part", "type_decl_list",
  "type_definition", "type_decl", "simple_type_decl", "array_type_decl",
  "record_type_decl", "field_decl_list", "field_decl", "name_list", "name",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression_list", "expression", "expr",
  "term", "factor", "@1", "args", "args_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    62,    63,    64,    65,    66,    66,
      67,    67,    68,    69,    69,    69,    69,    69,    70,    70,
      71,    71,    72,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    75,    76,    77,    77,    78,    79,    79,
      80,    81,    81,    82,    82,    83,    84,    84,    84,    84,
      84,    85,    86,    87,    88,    89,    89,    90,    90,    91,
      91,    92,    93,    94,    95,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   102,   102,   103,
     104,   105,   106,   106,   107,   108,   108,   109,   109,   110,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   113,
     113,   113,   113,   114,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   116,   115,   115,   115,   117,
     117,   118,   118
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     1,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     1,     3,     4,
       5,     6,     4,     6,     3,     2,     1,     4,     3,     1,
       1,     2,     0,     2,     1,     4,     2,     2,     1,     1,
       0,     4,     5,     4,     3,     3,     0,     3,     1,     3,
       3,     2,     1,     1,     3,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     6,
       5,     1,     4,     1,     4,     4,     5,     2,     0,     4,
       4,     8,     1,     1,     5,     2,     1,     4,     4,     2,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     3,     3,     1,     1,     4,
       1,     3,     2,     2,     4,     0,     5,     3,     1,     1,
       0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    66,     4,    63,     0,    19,     0,     0,     8,    11,
       0,    42,     0,     0,    83,    81,    64,     0,    66,     0,
       0,     0,     0,    71,     0,    68,    69,    70,    72,    73,
      74,    75,    76,    77,     0,    10,     0,    18,    21,     0,
      50,     0,     0,     0,   130,     0,     0,     0,     0,     0,
       0,    13,    14,    15,    16,    17,   118,   128,   120,     0,
     108,   112,   117,     0,     0,     0,    99,     0,    65,     0,
       0,    20,    40,     0,    39,    41,    44,     0,     0,     6,
      48,     0,    49,     0,     0,    67,     0,   101,   132,     0,
     129,     0,    78,     0,     0,   123,   122,     0,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,    26,     0,    27,     0,     0,    23,    24,
      25,     0,     0,    43,    56,    56,    46,    47,     7,     7,
      85,    84,     0,    82,     0,     0,     0,   121,     0,     0,
       0,   127,   102,   103,   104,   105,   106,   107,    88,   109,
     110,   111,   113,   114,   115,   116,    89,    90,     0,     0,
       0,     0,    96,     0,     0,     0,     0,    36,     0,     0,
       0,    22,     0,    38,     0,     0,    54,     0,     0,     0,
     100,   131,     0,    80,   119,   125,   124,     0,    86,    92,
      93,     0,     0,     0,    94,    95,    28,     0,     0,    34,
      35,     0,     0,     0,    45,     0,    62,     0,    58,     0,
       0,     0,    51,     5,    53,    79,   126,    87,     0,     0,
       0,     0,     0,     0,    32,    29,    61,    55,     0,     0,
       0,    52,     0,    98,    97,     0,    30,     0,    37,    57,
      59,    60,    91,    31,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   197,   198,     8,    15,    18,    19,
      68,    21,    47,    48,   137,   138,   139,   140,   186,   187,
      83,    84,    50,    85,    86,    89,    90,    91,    92,    93,
     195,   227,   228,   229,   230,    12,    33,    16,    34,    35,
      36,    37,    38,   208,    39,    40,    41,   211,    42,   181,
     182,    43,    96,    98,    70,    71,    72,   236,    99,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
      -3,    -5,    40,  -179,    13,  -179,    16,    15,    30,  -179,
    -179,  -179,  -179,  -179,    25,    66,    70,    52,    25,  -179,
      43,    44,    81,    63,   102,    96,  -179,   213,  -179,   213,
      76,    93,   213,  -179,    79,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,   223,  -179,   103,    43,  -179,   101,
       3,   213,    10,   213,   213,   213,   213,   107,   213,   213,
     213,  -179,  -179,  -179,  -179,  -179,   129,    45,  -179,   245,
     134,   196,  -179,   108,     2,   130,  -179,   252,  -179,   110,
     190,  -179,  -179,    53,  -179,   101,  -179,   114,   116,     3,
    -179,   117,  -179,   127,   142,  -179,    -2,   259,   259,   149,
     126,   279,   259,   154,   270,  -179,  -179,   213,   213,   213,
     121,   213,   213,   213,   213,   213,   213,   118,   213,   213,
     213,   213,   213,   213,   213,   213,   118,   213,   287,  -179,
     101,   223,   166,  -179,   101,   138,   140,   145,  -179,  -179,
    -179,   190,   101,  -179,   184,   184,  -179,  -179,  -179,  -179,
    -179,  -179,   213,  -179,   213,   174,   213,  -179,     4,   187,
     286,  -179,   134,   134,   134,   134,   134,   134,   143,   196,
     196,   196,  -179,  -179,  -179,  -179,   259,  -179,   212,   156,
     157,   158,  -179,     8,   161,   231,   -20,  -179,    67,   162,
     163,  -179,   171,  -179,    91,   180,  -179,   183,    15,   185,
     259,   259,   213,   259,  -179,  -179,  -179,   118,  -179,  -179,
    -179,   213,   118,   118,  -179,  -179,  -179,   202,   217,  -179,
    -179,   190,   206,   223,  -179,   101,   209,    24,  -179,   203,
     241,   231,  -179,  -179,  -179,   259,  -179,  -179,    57,   243,
     244,    19,   210,   262,  -179,  -179,   209,  -179,    91,   231,
     231,  -179,   118,  -179,  -179,   223,  -179,   190,  -179,  -179,
    -179,  -179,  -179,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,   137,   307,  -179,  -179,  -179,   297,
     -44,  -179,  -179,   269,  -139,  -178,  -179,  -179,  -179,   141,
    -125,   182,  -179,  -179,   246,  -179,   237,  -179,   239,  -179,
     188,  -179,    82,  -179,  -179,   131,    -6,   304,  -114,   282,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
     155,  -179,  -179,   -21,   207,  -103,   -32,  -179,   227,   230
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      79,    13,   192,   168,   151,   183,    69,   218,    74,   188,
     204,    77,   177,    22,   216,   169,   170,   171,    82,    94,
     111,   112,   113,   114,   115,   116,   219,   105,   106,   255,
     247,     1,    97,     4,   101,   102,   136,   104,    87,    88,
       5,   152,    24,    61,    62,    63,    64,   154,    25,    65,
     108,   142,   109,   251,     9,    11,    10,   126,    14,    27,
      11,   188,    28,    17,    29,   248,    30,    31,    32,   226,
      20,   260,   261,    22,    44,   111,   112,   113,   114,   115,
     116,    46,   243,    49,   180,   110,    51,   184,   160,   172,
     173,   174,   175,   237,    23,   141,   142,   136,   239,   240,
     246,    54,    24,    55,   176,    52,   178,    53,    25,   221,
     142,    22,   252,    56,    75,    11,    26,    76,   264,    27,
      78,    22,    28,   226,    29,    80,    30,    31,    32,    82,
     225,   200,    23,   201,   107,   203,    57,   180,   262,    82,
      24,   136,    23,   118,   119,   103,    25,   127,   150,   120,
      24,   129,   144,    11,   145,   153,    25,    27,   148,   161,
      28,   125,    29,    11,    30,    31,    32,    27,   149,   154,
      28,   156,    29,   185,    30,    31,    32,   136,   189,   245,
     190,   235,    61,    62,    63,    64,   191,   136,    65,   194,
     238,   202,    13,   205,   207,   130,   179,   256,   212,   213,
     131,   217,   222,   223,   214,   136,   136,   121,   122,   123,
     124,   263,   224,   136,    61,    62,    63,    64,    58,   132,
      65,   133,   231,    59,   232,   242,   234,   134,   135,    60,
     111,   112,   113,   114,   115,   116,   130,    61,    62,    63,
      64,   131,   241,    65,   244,   249,    66,    61,    62,    63,
      64,    67,   142,    65,   257,    61,    62,    63,    64,   209,
     210,    65,   133,   111,   112,   113,   114,   115,   116,   135,
     111,   112,   113,   114,   115,   116,   157,   111,   112,   113,
     114,   115,   116,   250,   253,   254,   199,   155,   111,   112,
     113,   114,   115,   116,   206,   117,   128,   111,   112,   113,
     114,   115,   116,   258,   111,   112,   113,   114,   115,   116,
       7,    61,    62,    63,    64,    45,    81,    65,   162,   163,
     164,   165,   166,   167,   193,   179,   146,   220,   147,   233,
     259,   143,    73,   196,    95,   159,   215,   158
};

static const yytype_uint16 yycheck[] =
{
      44,     7,   141,   117,     6,   130,    27,   185,    29,   134,
       6,    32,   126,     3,     6,   118,   119,   120,    38,    51,
      18,    19,    20,    21,    22,    23,    46,    59,    60,    10,
       6,    34,    53,    38,    55,    56,    80,    58,    35,    36,
       0,    43,    32,    24,    25,    26,    27,    43,    38,    30,
       5,    43,     7,   231,    41,    45,    40,    55,    28,    49,
      45,   186,    52,    38,    54,    41,    56,    57,    58,   194,
       4,   249,   250,     3,    22,    18,    19,    20,    21,    22,
      23,    38,   221,    39,   128,    40,     5,   131,   109,   121,
     122,   123,   124,   207,    24,    42,    43,   141,   212,   213,
     225,     5,    32,     7,   125,    42,   127,     5,    38,    42,
      43,     3,    55,    17,    38,    45,    46,    24,   257,    49,
      41,     3,    52,   248,    54,    22,    56,    57,    58,    38,
      39,   152,    24,   154,     5,   156,    40,   181,   252,    38,
      32,   185,    24,     9,    10,    38,    38,    17,     6,    15,
      32,    41,    38,    45,    38,     6,    38,    49,    41,    38,
      52,    53,    54,    45,    56,    57,    58,    49,    41,    43,
      52,    17,    54,     7,    56,    57,    58,   221,    40,   223,
      40,   202,    24,    25,    26,    27,    41,   231,    30,     5,
     211,    17,   198,     6,    51,     5,    38,   241,    42,    42,
      10,    40,    40,    40,    46,   249,   250,    11,    12,    13,
      14,   255,    41,   257,    24,    25,    26,    27,     5,    29,
      30,    31,    42,    10,    41,     8,    41,    37,    38,    16,
      18,    19,    20,    21,    22,    23,     5,    24,    25,    26,
      27,    10,    40,    30,    38,    42,    33,    24,    25,    26,
      27,    38,    43,    30,    44,    24,    25,    26,    27,    47,
      48,    30,    31,    18,    19,    20,    21,    22,    23,    38,
      18,    19,    20,    21,    22,    23,     6,    18,    19,    20,
      21,    22,    23,    42,    41,    41,   149,     8,    18,    19,
      20,    21,    22,    23,     8,    50,    44,    18,    19,    20,
      21,    22,    23,    41,    18,    19,    20,    21,    22,    23,
       3,    24,    25,    26,    27,    18,    47,    30,   111,   112,
     113,   114,   115,   116,   142,    38,    89,   186,    89,   198,
     248,    85,    28,   145,    52,   108,   181,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    60,    61,    38,     0,    62,    64,    65,    41,
      40,    45,    94,    95,    28,    66,    96,    38,    67,    68,
       4,    70,     3,    24,    32,    38,    46,    49,    52,    54,
      56,    57,    58,    95,    97,    98,    99,   100,   101,   103,
     104,   105,   107,   110,    22,    68,    38,    71,    72,    39,
      81,     5,    42,     5,     5,     7,    17,    40,     5,    10,
      16,    24,    25,    26,    27,    30,    33,    38,    69,   112,
     113,   114,   115,    96,   112,    38,    24,   112,    41,    69,
      22,    72,    38,    79,    80,    82,    83,    35,    36,    84,
      85,    86,    87,    88,   115,    98,   111,   112,   112,   117,
     118,   112,   112,    38,   112,   115,   115,     5,     5,     7,
      40,    18,    19,    20,    21,    22,    23,    50,     9,    10,
      15,    11,    12,    13,    14,    53,    55,    17,    44,    41,
       5,    10,    29,    31,    37,    38,    69,    73,    74,    75,
      76,    42,    43,    83,    38,    38,    85,    87,    41,    41,
       6,     6,    43,     6,    43,     8,    17,     6,   118,   117,
     112,    38,   113,   113,   113,   113,   113,   113,    97,   114,
     114,   114,   115,   115,   115,   115,   112,    97,   112,    38,
      69,   108,   109,    79,    69,     7,    77,    78,    79,    40,
      40,    41,    73,    80,     5,    89,    89,    63,    64,    63,
     112,   112,    17,   112,     6,     6,     8,    51,   102,    47,
      48,   106,    42,    42,    46,   109,     6,    40,    74,    46,
      78,    42,    40,    40,    41,    39,    79,    90,    91,    92,
      93,    42,    41,    94,    41,   112,   116,    97,   112,    97,
      97,    40,     8,    73,    38,    69,    79,     6,    41,    42,
      42,    74,    55,    41,    41,    10,    69,    44,    41,    91,
      74,    74,    97,    69,    73
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 33 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])}, NODE_STMT, S_PROGRAM, E_NONE);
	printTreeNodes((yyval).data.treeNode, 0);
;}
    break;

  case 3:
#line 41 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_PROGRAM_HEAD, E_NONE);
;}
    break;

  case 4:
#line 47 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_ROUTINE, E_NONE);
;}
    break;

  case 5:
#line 53 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_ROUTINE, E_NONE);
;}
    break;

  case 6:
#line 78 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_ROUTINE_HEAD, E_NONE);
;}
    break;

  case 7:
#line 84 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_LABEL_PART_NULL, E_NONE);
;}
    break;

  case 8:
#line 90 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_CONST_PART, E_NONE);;
;}
    break;

  case 9:
#line 94 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_CONST_PART_NULL, E_NONE);
;}
    break;

  case 10:
#line 100 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
;}
    break;

  case 11:
#line 104 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_CONST_EXPR_LIST, E_NONE);
;}
    break;

  case 12:
#line 110 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_CONST_EXPR, E_NONE);
;}
    break;

  case 13:
#line 116 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_INT,E_NONE);
;}
    break;

  case 14:
#line 120 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_REAL,E_NONE);
;}
    break;

  case 15:
#line 124 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_CHAR,E_NONE);
;}
    break;

  case 16:
#line 128 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_STRING,E_NONE);
;}
    break;

  case 17:
#line 132 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_SYS_CON,E_NONE);
;}
    break;

  case 18:
#line 138 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_TYPE_PART, E_NONE);
;}
    break;

  case 19:
#line 142 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_TYPE_PART_NULL, E_NONE);
;}
    break;

  case 20:
#line 148 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
;}
    break;

  case 21:
#line 152 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_LIST, E_NONE);;
;}
    break;

  case 22:
#line 158 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_TYPE_DEFINITION, E_NONE);
;}
    break;

  case 23:
#line 164 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_SIMPLE, E_NONE);
;}
    break;

  case 24:
#line 168 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_ARRAY, E_NONE);

;}
    break;

  case 25:
#line 173 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_RECORD, E_NONE);

;}
    break;

  case 26:
#line 180 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_SYS,E_NONE);
;}
    break;

  case 27:
#line 184 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_ID,E_NONE);
;}
    break;

  case 28:
#line 188 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_NAME_LIST,E_NONE);
;}
    break;

  case 29:
#line 192 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_CDC, E_NONE);
;}
    break;

  case 30:
#line 196 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDC, E_NONE);
;}
    break;

  case 31:
#line 200 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (6)]), (yyvsp[(6) - (6)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDMC, E_NONE);
;}
    break;

  case 32:
#line 204 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_IDI, E_NONE);
;}
    break;

  case 33:
#line 210 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(3) - (6)]), (yyvsp[(6) - (6)])}, NODE_STMT, S_ARRAY_TYPE_DECL, E_NONE);
;}
    break;

  case 34:
#line 216 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_RECORD_TYPE_DECL, E_NONE);
;}
    break;

  case 35:
#line 222 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
;}
    break;

  case 36:
#line 226 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_FILED_DECL_LIST, E_NONE);
;}
    break;

  case 37:
#line 232 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_FILED_DECL, E_NONE);
;}
    break;

  case 38:
#line 238 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
;}
    break;

  case 39:
#line 242 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_NAME_LIST,E_NONE);
;}
    break;

  case 40:
#line 248 "compiler.y"
    {
(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_NAME,E_NONE);
;}
    break;

  case 41:
#line 254 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_VAR_PART, E_NONE);
;}
    break;

  case 42:
#line 258 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_VAR_PART_NULL, E_NONE);
;}
    break;

  case 43:
#line 264 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
;}
    break;

  case 44:
#line 268 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_VAR_DECL_LIST, E_NONE);
;}
    break;

  case 45:
#line 274 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_VAR_DECL, E_NONE);
;}
    break;

  case 46:
#line 298 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_ROUTINE_PART_FUNC_LIST, E_NONE);
;}
    break;

  case 47:
#line 302 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_ROUTINE_PART_PROC_LIST, E_NONE);
;}
    break;

  case 48:
#line 306 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_ROUTINE_PART_FUNC_DECL, E_NONE);
;}
    break;

  case 49:
#line 310 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_ROUTINE_PART_PROC_DECL, E_NONE);
;}
    break;

  case 50:
#line 314 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_ROUTINE_NULL, E_NONE);
;}
    break;

  case 51:
#line 320 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_FUNCTION_DECL, E_NONE);
;}
    break;

  case 52:
#line 326 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_FUNCTION_HEAD, E_NONE);
;}
    break;

  case 53:
#line 332 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_PROCEDURE_DECL, E_NONE);
;}
    break;

  case 54:
#line 338 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PROCEDURE_HEAD, E_NONE);
;}
    break;

  case 55:
#line 344 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_PARAMETERS, E_NONE);
;}
    break;

  case 56:
#line 348 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_PARAMETERS_NULL, E_NONE);
;}
    break;

  case 57:
#line 354 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))
;}
    break;

  case 58:
#line 358 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_PARA_DECL_LIST, E_NONE);
;}
    break;

  case 59:
#line 364 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PARA_TYPE_LIST_VAR, E_NONE);
;}
    break;

  case 60:
#line 368 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PARA_TYPE_LIST_VAL, E_NONE);
;}
    break;

  case 61:
#line 374 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_VAR_PARA_LIST, E_NONE);
				;}
    break;

  case 62:
#line 380 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_VAL_PARA_LIST, E_NONE);
				;}
    break;

  case 63:
#line 397 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ROUTINE_BODY,E_NONE);
				;}
    break;

  case 64:
#line 403 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (3)])},NODE_STMT,S_COMPOUND_STMT,E_NONE);
				;}
    break;

  case 65:
#line 409 "compiler.y"
    {
				(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
			;}
    break;

  case 66:
#line 413 "compiler.y"
    {
				(yyval)=newTreeNode({}, NODE_STMT, S_STMT_LIST, E_NONE);
			;}
    break;

  case 67:
#line 419 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_STMT,E_NONE);
			;}
    break;

  case 68:
#line 423 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_STMT_NON,E_NONE);
			;}
    break;

  case 69:
#line 429 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 70:
#line 433 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 71:
#line 437 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 72:
#line 441 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 73:
#line 445 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 74:
#line 449 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 75:
#line 453 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 76:
#line 457 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 77:
#line 461 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 78:
#line 467 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_ASSIGN,E_NONE);
				;}
    break;

  case 79:
#line 471 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(6) - (6)])},NODE_STMT,S_ASSIGN_ARRAY,E_NONE);
				;}
    break;

  case 80:
#line 475 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)])},NODE_STMT,S_ASSIGN_RECORD,E_NONE);
				;}
    break;

  case 81:
#line 481 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_PROC,E_NONE);
				;}
    break;

  case 82:
#line 485 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(3) - (4)])},NODE_STMT,S_PROC_FUNC,E_NONE);
				;}
    break;

  case 83:
#line 489 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_PROC_SYS,E_NONE);
				;}
    break;

  case 84:
#line 493 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_PROC_SYS_ARG,E_NONE);
				;}
    break;

  case 85:
#line 497 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(3) - (4)])},NODE_STMT,S_PROC_READ,E_NONE);
				;}
    break;

  case 86:
#line 503 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)]),(yyvsp[(5) - (5)])},NODE_STMT,S_IF,E_NONE);
				;}
    break;

  case 87:
#line 509 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_ELSE,E_NONE);
				;}
    break;

  case 89:
#line 516 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])},NODE_STMT,S_REPEAT,E_NONE);
				;}
    break;

  case 90:
#line 522 "compiler.y"
    {
						(yyval)=newTreeNode({(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])},NODE_STMT,S_WHILE,E_NONE);
				;}
    break;

  case 91:
#line 528 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(4) - (8)]),(yyvsp[(5) - (8)]),(yyvsp[(6) - (8)]),(yyvsp[(8) - (8)])},NODE_STMT,S_FOR,E_NONE);
				;}
    break;

  case 92:
#line 534 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_DIRECTION_TO,E_NONE);
				;}
    break;

  case 93:
#line 538 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_DIRECTION_DOWNTO,E_NONE);
				;}
    break;

  case 94:
#line 544 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)])},NODE_STMT,S_CASE,E_NONE);
				;}
    break;

  case 95:
#line 550 "compiler.y"
    {
					(yyval)=linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
				;}
    break;

  case 96:
#line 554 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CASE_EXPR_LIST,E_NONE);
				;}
    break;

  case 97:
#line 560 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_CASE_EXPR_CONST,E_NONE);
				;}
    break;

  case 98:
#line 564 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_CASE_EXPR_ID,E_NONE);
				;}
    break;

  case 99:
#line 570 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_GOTO,E_NONE);
				;}
    break;

  case 100:
#line 576 "compiler.y"
    {
					(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
				;}
    break;

  case 101:
#line 580 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_EXPRESSION_LIST,E_NONE);
				;}
    break;

  case 102:
#line 586 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_GE);
				;}
    break;

  case 103:
#line 590 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_GT);
				;}
    break;

  case 104:
#line 594 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_LE);
				;}
    break;

  case 105:
#line 598 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_LT);
				;}
    break;

  case 106:
#line 602 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_EQUAL);
				;}
    break;

  case 107:
#line 606 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_UNEQUAL);
				;}
    break;

  case 108:
#line 610 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				;}
    break;

  case 109:
#line 616 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_PLUS);
		;}
    break;

  case 110:
#line 620 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MINUS);
		;}
    break;

  case 111:
#line 624 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_OR);
		;}
    break;

  case 112:
#line 628 "compiler.y"
    {
			(yyval)=(yyvsp[(1) - (1)]);
		;}
    break;

  case 113:
#line 634 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MUL);
		;}
    break;

  case 114:
#line 638 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_DIV);
		;}
    break;

  case 115:
#line 642 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MOD);
		;}
    break;

  case 116:
#line 646 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_AND);
		;}
    break;

  case 117:
#line 650 "compiler.y"
    {
			(yyval)=(yyvsp[(1) - (1)]);
		;}
    break;

  case 118:
#line 656 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_FACTOR_SYS,E_NONE);
		;}
    break;

  case 119:
#line 660 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_FACTOR_SYS_ARG,E_NONE);
		;}
    break;

  case 120:
#line 664 "compiler.y"
    {
			(yyval)=(yyvsp[(1) - (1)]);
		;}
    break;

  case 121:
#line 668 "compiler.y"
    {
			(yyval)=(yyvsp[(2) - (3)]);
		;}
    break;

  case 122:
#line 672 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_FACTOR_NOT,E_NONE);
		;}
    break;

  case 123:
#line 676 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_FACTOR_MINUS,E_NONE);
		;}
    break;

  case 124:
#line 680 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_FACTOR_ARRAY,E_NONE);
		;}
    break;

  case 125:
#line 683 "compiler.y"
    {/*new added*/;}
    break;

  case 126:
#line 684 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)])},NODE_STMT,S_FACTOR_FUNC,E_NONE);
		;}
    break;

  case 127:
#line 688 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_FACTOR_RECORD,E_NONE);
		;}
    break;

  case 128:
#line 692 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_FACTOR_ID,E_NONE);
		;}
    break;

  case 129:
#line 698 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ARGS,E_NONE);
			;}
    break;

  case 130:
#line 702 "compiler.y"
    {
			
				(yyval)=newTreeNode({},NODE_STMT,S_ARGS_NULL,E_NONE);
			
			;}
    break;

  case 131:
#line 710 "compiler.y"
    {
				(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
			;}
    break;

  case 132:
#line 714 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ARGS_LIST,E_NONE);
			;}
    break;


/* Line 1267 of yacc.c.  */
#line 2605 "compiler.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 718 "compiler.y"

int main(){
	return yyparse();
}

