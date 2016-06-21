/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
