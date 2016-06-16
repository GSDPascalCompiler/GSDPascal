/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

