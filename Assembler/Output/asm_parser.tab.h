/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ASM_PARSER_TAB_H_INCLUDED
# define YY_YY_ASM_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    SUB = 259,                     /* SUB  */
    OR = 260,                      /* OR  */
    AND = 261,                     /* AND  */
    NOT = 262,                     /* NOT  */
    XOR = 263,                     /* XOR  */
    CMP = 264,                     /* CMP  */
    BRANCH = 265,                  /* BRANCH  */
    JUMP = 266,                    /* JUMP  */
    JUMP_LINK = 267,               /* JUMP_LINK  */
    MOVE = 268,                    /* MOVE  */
    LOAD_DIRECT = 269,             /* LOAD_DIRECT  */
    LOAD_IMMEDIATE = 270,          /* LOAD_IMMEDIATE  */
    LOAD_INDEXED = 271,            /* LOAD_INDEXED  */
    STORE_DIRECT = 272,            /* STORE_DIRECT  */
    STORE_INDEXED = 273,           /* STORE_INDEXED  */
    PUSH = 274,                    /* PUSH  */
    POP = 275,                     /* POP  */
    RETI = 276,                    /* RETI  */
    HALT = 277,                    /* HALT  */
    NOP = 278,                     /* NOP  */
    NUMBER = 279,                  /* NUMBER  */
    REG = 280,                     /* REG  */
    IDENTIFIER = 281,              /* IDENTIFIER  */
    ENDFILE = 282,                 /* ENDFILE  */
    ERROR = 283,                   /* ERROR  */
    COMMA = 284,                   /* COMMA  */
    CARDINAL = 285,                /* CARDINAL  */
    COLON = 286,                   /* COLON  */
    DOLAR = 287,                   /* DOLAR  */
    BYTE = 288,                    /* BYTE  */
    WORD = 289,                    /* WORD  */
    ALLOC = 290,                   /* ALLOC  */
    ORG = 291,                     /* ORG  */
    EQU = 292                      /* EQU  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ASM_PARSER_TAB_H_INCLUDED  */
