/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "compiler.y"

#include <stdio.h>
#include "global.h"
#include "parsetree.h"
#include "util.h"
#include <vector>

extern int yylex();
extern SymbolItem *procFunc;
int yyerror(const char *s){
	printf("%s\n", s);
	return 0;
}


/* Line 371 of yacc.c  */
#line 84 "y.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 208 "y.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   368

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNRULES -- Number of states.  */
#define YYNSTATES  267

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
      81,    87,    94,    99,   104,   109,   116,   120,   123,   125,
     130,   134,   136,   138,   141,   142,   145,   147,   152,   155,
     158,   160,   162,   163,   168,   174,   179,   183,   187,   188,
     192,   194,   198,   202,   205,   207,   209,   213,   217,   218,
     222,   224,   226,   228,   230,   232,   234,   236,   238,   240,
     242,   246,   253,   259,   261,   266,   268,   273,   278,   284,
     287,   288,   293,   298,   307,   309,   311,   317,   320,   322,
     327,   332,   335,   339,   341,   345,   349,   353,   357,   361,
     365,   367,   371,   375,   379,   381,   385,   389,   393,   397,
     399,   401,   406,   408,   412,   415,   418,   423,   424,   430,
     434,   436,   438,   439,   443
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
      40,    10,    69,    -1,    38,    40,    40,    38,    -1,    69,
      40,    40,    38,    -1,    38,    40,    40,    69,    -1,    29,
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
       0,    35,    35,    43,    51,    58,    83,    90,    95,   102,
     107,   111,   117,   126,   130,   134,   138,   142,   148,   155,
     160,   164,   170,   177,   182,   187,   194,   198,   202,   206,
     210,   214,   218,   222,   226,   232,   238,   244,   248,   254,
     260,   264,   270,   276,   283,   288,   292,   298,   324,   328,
     332,   336,   341,   346,   358,   367,   379,   389,   394,   399,
     403,   409,   415,   423,   429,   445,   451,   457,   462,   467,
     472,   478,   482,   486,   490,   494,   498,   502,   506,   510,
     516,   521,   526,   533,   538,   543,   547,   551,   557,   564,
     568,   571,   578,   585,   592,   596,   602,   609,   614,   621,
     626,   633,   640,   645,   652,   657,   662,   667,   672,   677,
     682,   688,   693,   698,   703,   709,   714,   719,   724,   729,
     735,   740,   745,   750,   754,   759,   764,   769,   769,   774,
     779,   786,   792,   797,   801
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "term", "factor", "$@1", "args", "args_list", YY_NULL
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
      74,    74,    74,    74,    74,    75,    76,    77,    77,    78,
      79,    79,    80,    81,    81,    82,    82,    83,    84,    84,
      84,    84,    84,    85,    86,    87,    88,    89,    89,    90,
      90,    91,    91,    92,    93,    94,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,    99,   100,   100,   100,   100,   100,   101,   102,
     102,   103,   104,   105,   106,   106,   107,   108,   108,   109,
     109,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   116,   115,   115,
     115,   117,   117,   118,   118
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     1,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     1,     3,     4,
       5,     6,     4,     4,     4,     6,     3,     2,     1,     4,
       3,     1,     1,     2,     0,     2,     1,     4,     2,     2,
       1,     1,     0,     4,     5,     4,     3,     3,     0,     3,
       1,     3,     3,     2,     1,     1,     3,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     5,     1,     4,     1,     4,     4,     5,     2,
       0,     4,     4,     8,     1,     1,     5,     2,     1,     4,
       4,     2,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     4,     1,     3,     2,     2,     4,     0,     5,     3,
       1,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    68,     4,    65,     0,    19,     0,     0,     8,    11,
       0,    44,     0,     0,    85,    83,    66,     0,    68,     0,
       0,     0,     0,    73,     0,    70,    71,    72,    74,    75,
      76,    77,    78,    79,     0,    10,     0,    18,    21,     0,
      52,     0,     0,     0,   132,     0,     0,     0,     0,     0,
       0,    13,    14,    15,    16,    17,   120,   130,   122,     0,
     110,   114,   119,     0,     0,     0,   101,     0,    67,     0,
       0,    20,    42,     0,    41,    43,    46,     0,     0,     6,
      50,     0,    51,     0,     0,    69,     0,   103,   134,     0,
     131,     0,    80,     0,     0,   125,   124,     0,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,    26,     0,    27,     0,     0,    23,    24,
      25,     0,     0,    45,    58,    58,    48,    49,     7,     7,
      87,    86,     0,    84,     0,     0,     0,   123,     0,     0,
       0,   129,   104,   105,   106,   107,   108,   109,    90,   111,
     112,   113,   115,   116,   117,   118,    91,    92,     0,     0,
       0,     0,    98,     0,     0,     0,     0,    38,     0,     0,
       0,    22,     0,    40,     0,     0,    56,     0,     0,     0,
     102,   133,     0,    82,   121,   127,   126,     0,    88,    94,
      95,     0,     0,     0,    96,    97,    28,     0,     0,    36,
      37,     0,     0,     0,    47,     0,    64,     0,    60,     0,
       0,     0,    53,     5,    55,    81,   128,    89,     0,     0,
       0,     0,     0,     0,    32,    34,    33,    29,    63,    57,
       0,     0,     0,    54,     0,   100,    99,     0,    30,     0,
      39,    59,    61,    62,    93,    31,    35
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
#define YYPACT_NINF -182
static const yytype_int16 yypact[] =
{
      -1,     0,    41,  -182,     5,  -182,     3,    13,    21,  -182,
    -182,  -182,  -182,  -182,    22,    52,    70,    43,    22,  -182,
      25,    33,    81,    54,   100,    78,  -182,   212,  -182,   212,
      69,    86,   212,  -182,    73,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,   222,  -182,    95,    25,  -182,    83,
      18,   212,    10,   212,   212,   212,   212,    85,   212,   212,
     212,  -182,  -182,  -182,  -182,  -182,   124,    96,  -182,   244,
      30,   172,  -182,   106,     2,   115,  -182,   151,  -182,    93,
     194,  -182,  -182,   -27,  -182,    83,  -182,   101,   104,    18,
    -182,   102,  -182,   105,   139,  -182,     1,   336,   336,   142,
     107,   297,   336,   132,   290,  -182,  -182,   212,   212,   212,
     114,   212,   212,   212,   212,   212,   212,   144,   212,   212,
     212,   212,   212,   212,   212,   212,   144,   212,   307,  -182,
      83,   222,   146,  -182,    83,   116,   117,   113,  -182,  -182,
    -182,   194,    83,  -182,   156,   156,  -182,  -182,  -182,  -182,
    -182,  -182,   212,  -182,   212,   148,   212,  -182,     4,   160,
     306,  -182,    30,    30,    30,    30,    30,    30,   129,   172,
     172,   172,  -182,  -182,  -182,  -182,   336,  -182,   251,   125,
     133,   254,  -182,     8,   154,   230,   -20,  -182,    38,   163,
     165,  -182,   147,  -182,    74,   149,  -182,   168,    13,   169,
     336,   336,   212,   336,  -182,  -182,  -182,   144,  -182,  -182,
    -182,   212,   144,   144,  -182,  -182,  -182,   166,   203,  -182,
    -182,   194,   314,   323,  -182,    83,   171,    11,  -182,   170,
     174,   230,  -182,  -182,  -182,   336,  -182,  -182,    56,   185,
     186,   277,   189,   188,  -182,  -182,  -182,  -182,   171,  -182,
      74,   230,   230,  -182,   144,  -182,  -182,   222,  -182,   194,
    -182,  -182,  -182,  -182,  -182,  -182,  -182
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,  -182,    92,   227,  -182,  -182,  -182,   216,
     -44,  -182,  -182,   196,  -139,  -181,  -182,  -182,  -182,    58,
    -125,   109,  -182,  -182,   173,  -182,   164,  -182,   187,  -182,
     130,  -182,     9,  -182,  -182,    79,    -6,   255,  -114,   233,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     108,  -182,  -182,   -21,   252,   -89,   -32,  -182,   178,   175
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      79,    13,   192,   168,   218,   183,    69,   151,    74,   188,
     204,    77,   177,    22,   216,   141,   142,   249,    82,    94,
     111,   112,   113,   114,   115,   116,   219,   105,   106,   169,
     170,   171,    97,     1,   101,   102,   136,   104,     4,   118,
     119,     5,    24,    10,   152,   120,     9,   154,    25,    14,
     253,   142,   250,    87,    88,    11,    20,   126,    11,    27,
      17,   188,    28,    46,    29,    44,    30,    31,    32,   226,
     262,   263,    49,    22,   111,   112,   113,   114,   115,   116,
     221,   142,   243,    54,   180,    55,    51,   184,   160,   172,
     173,   174,   175,   237,    23,    56,    52,   136,   239,   240,
     248,   108,    24,   109,   176,    53,   178,    75,    25,    22,
      76,   254,    82,   225,    78,    11,    26,    80,    57,    27,
     266,    82,    28,   103,    29,   226,    30,    31,    32,   107,
      23,   200,   127,   201,   129,   203,   110,   180,    24,   144,
     264,   136,   145,   148,    25,   150,   149,    22,   153,   156,
     154,    11,   161,   185,   191,    27,   189,   190,    28,   125,
      29,   194,    30,    31,    32,   202,   205,   212,    23,   111,
     112,   113,   114,   115,   116,   213,    24,   136,   245,   247,
     207,   235,    25,   121,   122,   123,   124,   136,   224,    11,
     238,   231,    13,    27,   217,   128,    28,   258,    29,   130,
      30,    31,    32,   222,   131,   223,   241,   136,   136,   232,
     234,   242,   251,   265,   142,   136,   252,    58,    61,    62,
      63,    64,    59,   132,    65,   133,   255,   256,    60,   260,
       7,   134,   135,   259,    45,   130,    61,    62,    63,    64,
     131,   199,    65,    81,   220,    66,    61,    62,    63,    64,
      67,   193,    65,   146,    61,    62,    63,    64,   143,   261,
      65,   133,   111,   112,   113,   114,   115,   116,   135,   111,
     112,   113,   114,   115,   116,   196,   147,   233,    61,    62,
      63,    64,   158,    73,    65,    95,   159,   257,     0,   215,
       0,     0,   179,     0,   117,     0,   157,     0,   209,   210,
     214,    61,    62,    63,    64,   155,     0,    65,   111,   112,
     113,   114,   115,   116,   206,   111,   112,   113,   114,   115,
     116,     0,     0,     0,   111,   112,   113,   114,   115,   116,
       0,    61,    62,    63,    64,     0,     0,    65,    61,    62,
      63,    64,     0,     0,    65,   179,     0,    61,    62,    63,
      64,     0,   244,    65,   111,   112,   113,   114,   115,   116,
       0,   246,     0,   162,   163,   164,   165,   166,   167
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-182)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      44,     7,   141,   117,   185,   130,    27,     6,    29,   134,
       6,    32,   126,     3,     6,    42,    43,     6,    38,    51,
      18,    19,    20,    21,    22,    23,    46,    59,    60,   118,
     119,   120,    53,    34,    55,    56,    80,    58,    38,     9,
      10,     0,    32,    40,    43,    15,    41,    43,    38,    28,
     231,    43,    41,    35,    36,    45,     4,    55,    45,    49,
      38,   186,    52,    38,    54,    22,    56,    57,    58,   194,
     251,   252,    39,     3,    18,    19,    20,    21,    22,    23,
      42,    43,   221,     5,   128,     7,     5,   131,   109,   121,
     122,   123,   124,   207,    24,    17,    42,   141,   212,   213,
     225,     5,    32,     7,   125,     5,   127,    38,    38,     3,
      24,    55,    38,    39,    41,    45,    46,    22,    40,    49,
     259,    38,    52,    38,    54,   250,    56,    57,    58,     5,
      24,   152,    17,   154,    41,   156,    40,   181,    32,    38,
     254,   185,    38,    41,    38,     6,    41,     3,     6,    17,
      43,    45,    38,     7,    41,    49,    40,    40,    52,    53,
      54,     5,    56,    57,    58,    17,     6,    42,    24,    18,
      19,    20,    21,    22,    23,    42,    32,   221,   222,   223,
      51,   202,    38,    11,    12,    13,    14,   231,    41,    45,
     211,    42,   198,    49,    40,    44,    52,   241,    54,     5,
      56,    57,    58,    40,    10,    40,    40,   251,   252,    41,
      41,     8,    42,   257,    43,   259,    42,     5,    24,    25,
      26,    27,    10,    29,    30,    31,    41,    41,    16,    41,
       3,    37,    38,    44,    18,     5,    24,    25,    26,    27,
      10,   149,    30,    47,   186,    33,    24,    25,    26,    27,
      38,   142,    30,    89,    24,    25,    26,    27,    85,   250,
      30,    31,    18,    19,    20,    21,    22,    23,    38,    18,
      19,    20,    21,    22,    23,   145,    89,   198,    24,    25,
      26,    27,   107,    28,    30,    52,   108,    10,    -1,   181,
      -1,    -1,    38,    -1,    50,    -1,     6,    -1,    47,    48,
      46,    24,    25,    26,    27,     8,    -1,    30,    18,    19,
      20,    21,    22,    23,     8,    18,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    18,    19,    20,    21,    22,    23,
      -1,    24,    25,    26,    27,    -1,    -1,    30,    24,    25,
      26,    27,    -1,    -1,    30,    38,    -1,    24,    25,    26,
      27,    -1,    38,    30,    18,    19,    20,    21,    22,    23,
      -1,    38,    -1,   111,   112,   113,   114,   115,   116
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
      97,    40,     8,    73,    38,    69,    38,    69,    79,     6,
      41,    42,    42,    74,    55,    41,    41,    10,    69,    44,
      41,    91,    74,    74,    97,    69,    73
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 36 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])}, NODE_STMT, S_PROGRAM, E_NONE);
	printTreeNodes((yyval).data.treeNode, 0);
}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 44 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_PROGRAM_HEAD, E_NONE);
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 52 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_ROUTINE, E_NONE);
	symtable.leaveScope();
}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 59 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])}, NODE_STMT, S_SUB_ROUTINE, E_NONE);
}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 84 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_ROUTINE_HEAD, E_NONE);
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 90 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_LABEL_PART_NULL, E_NONE);
}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 96 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_CONST_PART, E_NONE);;
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 102 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_CONST_PART_NULL, E_NONE);
}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 108 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 112 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_CONST_EXPR_LIST, E_NONE);
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 118 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_CONST_EXPR, E_NONE);
	if(computeAttrGrammar((yyval)) == false)
		showErrMsg();
	
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 127 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_INT,E_NONE);
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 131 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_REAL,E_NONE);
}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 135 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_CHAR,E_NONE);
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 139 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_STRING,E_NONE);
}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 143 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CONST_VALUE_SYS_CON,E_NONE);
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 149 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_TYPE_PART, E_NONE);
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 155 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_TYPE_PART_NULL, E_NONE);
}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 161 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 165 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_LIST, E_NONE);;
}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 171 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_TYPE_DEFINITION, E_NONE);
	computeAttrGrammar((yyval));
}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 178 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_SIMPLE, E_NONE);
}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 183 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_ARRAY, E_NONE);

}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 188 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_TYPE_DECL_RECORD, E_NONE);

}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 195 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_SYS,E_NONE);
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 199 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_ID,E_NONE);
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 203 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT,S_SIMPLE_TYPE_DECL_NAME_LIST,E_NONE);
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 207 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_CDC, E_NONE);
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 211 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDC, E_NONE);
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 215 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (6)]), (yyvsp[(6) - (6)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_MCDMC, E_NONE);
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 219 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_IDI, E_NONE);
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 223 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_CDI, E_NONE);
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 227 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])}, NODE_STMT, S_SIMPLE_TYPE_DECL_IDC, E_NONE);
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 233 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(3) - (6)]), (yyvsp[(6) - (6)])}, NODE_STMT, S_ARRAY_TYPE_DECL, E_NONE);
}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 239 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_RECORD_TYPE_DECL, E_NONE);
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 245 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 249 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_FILED_DECL_LIST, E_NONE);
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 255 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_FILED_DECL, E_NONE);
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 261 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 265 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_NAME_LIST,E_NONE);
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 271 "compiler.y"
    {
(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_NAME,E_NONE);
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 277 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_VAR_PART, E_NONE);
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 283 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_VAR_PART_NULL, E_NONE);
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 289 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 293 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_VAR_DECL_LIST, E_NONE);
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 299 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_VAR_DECL, E_NONE);
	computeAttrGrammar((yyval));
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 325 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 329 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 333 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_ROUTINE_PART_FUNC_LIST, E_NONE);
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 337 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_ROUTINE_PART_PROC_LIST, E_NONE);
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 341 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_ROUTINE_NULL, E_NONE);
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 347 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_FUNCTION_DECL, E_NONE);
	procFunc = new SymbolItem();
	memcpy(procFunc, symtable.getFromSymtable((yyvsp[(1) - (4)]).data.treeNode->leftChild->value.nodeId.id), sizeof(SymbolItem));
	symtable.leaveScope();
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 359 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])}, NODE_STMT, S_FUNCTION_HEAD, E_NONE);
	symtable.setFuncName((yyval).data.treeNode->leftChild->value.nodeId.id);
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 368 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])}, NODE_STMT, S_PROCEDURE_DECL, E_NONE);
	procFunc = new SymbolItem();
	memcpy(procFunc, symtable.getFromSymtable((yyvsp[(1) - (4)]).data.treeNode->leftChild->value.nodeId.id), sizeof(SymbolItem));
	symtable.leaveScope();
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 380 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PROCEDURE_HEAD, E_NONE);
	symtable.setFuncName((yyval).data.treeNode->leftChild->value.nodeId.id);
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
	showErrMsg();
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 390 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(2) - (3)])}, NODE_STMT, S_PARAMETERS, E_NONE);
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 394 "compiler.y"
    {
	(yyval) = newTreeNode({}, NODE_STMT, S_PARAMETERS_NULL, E_NONE);
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 400 "compiler.y"
    {
	(yyval) = linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 404 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_PARA_DECL_LIST, E_NONE);
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 410 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PARA_TYPE_LIST_VAR, E_NONE);
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 416 "compiler.y"
    {
	(yyval) = newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])}, NODE_STMT, S_PARA_TYPE_LIST_VAL, E_NONE);
	computeAttrGrammar((yyval));
	symtable.showCurrentTable();
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 424 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])}, NODE_STMT, S_VAR_PARA_LIST, E_NONE);
				}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 430 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_VAL_PARA_LIST, E_NONE);
				}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 446 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ROUTINE_BODY,E_NONE);
				}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 452 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (3)])},NODE_STMT,S_COMPOUND_STMT,E_NONE);
				}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 458 "compiler.y"
    {
				(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
			}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 462 "compiler.y"
    {
				(yyval)=newTreeNode({}, NODE_STMT, S_STMT_LIST, E_NONE);
			}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 468 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_STMT,E_NONE);
				
			}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 473 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_STMT_NON,E_NONE);
			}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 479 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 483 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 487 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 491 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 495 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 499 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 503 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 507 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 511 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 517 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_ASSIGN,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 522 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(6) - (6)])},NODE_STMT,S_ASSIGN_ARRAY,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 527 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)])},NODE_STMT,S_ASSIGN_RECORD,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 534 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_PROC,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 539 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])},NODE_STMT,S_PROC_FUNC,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 544 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_PROC_SYS,E_NONE);
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 548 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_PROC_SYS_ARG,E_NONE);
				}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 552 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(3) - (4)])},NODE_STMT,S_PROC_READ,E_NONE);
				}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 558 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)]),(yyvsp[(5) - (5)])},NODE_STMT,S_IF,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 565 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_ELSE,E_NONE);
				}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 572 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])},NODE_STMT,S_REPEAT,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 579 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])},NODE_STMT,S_WHILE,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 586 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (8)]), (yyvsp[(4) - (8)]),(yyvsp[(5) - (8)]),(yyvsp[(6) - (8)]),(yyvsp[(8) - (8)])},NODE_STMT,S_FOR,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 593 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_DIRECTION_TO,E_NONE);
				}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 597 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_DIRECTION_DOWNTO,E_NONE);
				}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 603 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (5)]),(yyvsp[(4) - (5)])},NODE_STMT,S_CASE,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 610 "compiler.y"
    {
					(yyval)=linkTreeNode((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
					computeAttrGrammar((yyval));
				}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 615 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_CASE_EXPR_LIST,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 622 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_CASE_EXPR_CONST,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 627 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_CASE_EXPR_ID,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 634 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_GOTO,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 641 "compiler.y"
    {
					(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
					computeAttrGrammar((yyval));
				}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 646 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_EXPRESSION_LIST,E_NONE);
					computeAttrGrammar((yyval));
				}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 653 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_GE);
					computeAttrGrammar((yyval));
				}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 658 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_GT);
					computeAttrGrammar((yyval));
				}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 663 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_LE);
					computeAttrGrammar((yyval));
				}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 668 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_LT);
					computeAttrGrammar((yyval));
				}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 673 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_EQUAL);
					computeAttrGrammar((yyval));
				}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 678 "compiler.y"
    {
					(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_UNEQUAL);
					computeAttrGrammar((yyval));
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 683 "compiler.y"
    {
					(yyval)=(yyvsp[(1) - (1)]);
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 689 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_PLUS);
			computeAttrGrammar((yyval));
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 694 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MINUS);
			computeAttrGrammar((yyval));
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 699 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_OR);
			computeAttrGrammar((yyval));
		}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 704 "compiler.y"
    {
			(yyval)=(yyvsp[(1) - (1)]);
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 710 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MUL);
			computeAttrGrammar((yyval));
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 715 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_DIV);
			computeAttrGrammar((yyval));
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 720 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_MOD);
			computeAttrGrammar((yyval));
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 725 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])},NODE_EXP,S_NONE,E_AND);
			computeAttrGrammar((yyval));
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 730 "compiler.y"
    {
			(yyval)=(yyvsp[(1) - (1)]);
		}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 736 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_FACTOR_SYS,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 741 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_FACTOR_SYS_ARG,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 746 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (1)])}, NODE_STMT, S_FACTOR_CONST, E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 751 "compiler.y"
    {
			(yyval)=(yyvsp[(2) - (3)]);
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 755 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_FACTOR_NOT,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 760 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(2) - (2)])},NODE_STMT,S_FACTOR_MINUS,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 765 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (4)]),(yyvsp[(3) - (4)])},NODE_STMT,S_FACTOR_ARRAY,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 769 "compiler.y"
    {/*new added*/}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 770 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)])},NODE_STMT,S_FACTOR_FUNC,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 775 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])},NODE_STMT,S_FACTOR_RECORD,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 780 "compiler.y"
    {
			(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_FACTOR_ID,E_NONE);
			computeAttrGrammar((yyval));
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 787 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ARGS,E_NONE);
				computeAttrGrammar((yyval));
			}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 792 "compiler.y"
    {
				(yyval)=newTreeNode({},NODE_STMT,S_ARGS_NULL,E_NONE);
			}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 798 "compiler.y"
    {
				(yyval)=linkTreeNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
			}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 802 "compiler.y"
    {
				(yyval)=newTreeNode({(yyvsp[(1) - (1)])},NODE_STMT,S_ARGS_LIST,E_NONE);
			}
    break;


/* Line 1792 of yacc.c  */
#line 2803 "y.tab.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 806 "compiler.y"

int main(){
	int ret = yyparse();
	showErrMsg();
	savedTable.showAllTable();
	return ret;
}
