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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    ENDFILE = 258,                 /* ENDFILE  */
    ERROR = 259,                   /* ERROR  */
    IF = 260,                      /* IF  */
    ELSEIF = 261,                  /* ELSEIF  */
    ELSE = 262,                    /* ELSE  */
    DO = 263,                      /* DO  */
    WHILE = 264,                   /* WHILE  */
    FOR = 265,                     /* FOR  */
    SWITCH = 266,                  /* SWITCH  */
    CASE = 267,                    /* CASE  */
    DEFAULT = 268,                 /* DEFAULT  */
    RETURN = 269,                  /* RETURN  */
    BREAK = 270,                   /* BREAK  */
    INT = 271,                     /* INT  */
    FLOAT = 272,                   /* FLOAT  */
    DOUBLE = 273,                  /* DOUBLE  */
    CHAR = 274,                    /* CHAR  */
    VOID = 275,                    /* VOID  */
    STRUCT = 276,                  /* STRUCT  */
    TYPEDEF = 277,                 /* TYPEDEF  */
    CONTINUE = 278,                /* CONTINUE  */
    EXTERN = 279,                  /* EXTERN  */
    GOTO = 280,                    /* GOTO  */
    LONG = 281,                    /* LONG  */
    ENUM = 282,                    /* ENUM  */
    REGISTER = 283,                /* REGISTER  */
    SHORT = 284,                   /* SHORT  */
    SIZEOF = 285,                  /* SIZEOF  */
    STATIC = 286,                  /* STATIC  */
    SIGNED = 287,                  /* SIGNED  */
    UNION = 288,                   /* UNION  */
    UNSIGNED = 289,                /* UNSIGNED  */
    VOLATILE = 290,                /* VOLATILE  */
    NUM = 291,                     /* NUM  */
    ID = 292,                      /* ID  */
    FNUM = 293,                    /* FNUM  */
    ASSIGN = 294,                  /* ASSIGN  */
    PLUS = 295,                    /* PLUS  */
    MINUS = 296,                   /* MINUS  */
    TIMES = 297,                   /* TIMES  */
    OVER = 298,                    /* OVER  */
    PERCENT = 299,                 /* PERCENT  */
    LPAREN = 300,                  /* LPAREN  */
    RPAREN = 301,                  /* RPAREN  */
    LEFT_BRACE = 302,              /* LEFT_BRACE  */
    RIGHT_BRACE = 303,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 304,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 305,           /* RIGHT_BRACKET  */
    TERNARY = 306,                 /* TERNARY  */
    SEMI = 307,                    /* SEMI  */
    COLON = 308,                   /* COLON  */
    COMMA = 309,                   /* COMMA  */
    INCREMENT = 310,               /* INCREMENT  */
    DECREMENT = 311,               /* DECREMENT  */
    BITWISE_AND = 312,             /* BITWISE_AND  */
    BITWISE_OR = 313,              /* BITWISE_OR  */
    BITWISE_NOT = 314,             /* BITWISE_NOT  */
    BITWISE_XOR = 315,             /* BITWISE_XOR  */
    LOGICAL_NOT = 316,             /* LOGICAL_NOT  */
    LOGICAL_AND = 317,             /* LOGICAL_AND  */
    LOGICAL_OR = 318,              /* LOGICAL_OR  */
    EQUAL = 319,                   /* EQUAL  */
    NOT_EQUAL = 320,               /* NOT_EQUAL  */
    LESS_THAN = 321,               /* LESS_THAN  */
    GREATER_THAN = 322,            /* GREATER_THAN  */
    LESS_THAN_OR_EQUAL = 323,      /* LESS_THAN_OR_EQUAL  */
    GREATER_THAN_OR_EQUAL = 324,   /* GREATER_THAN_OR_EQUAL  */
    RIGHT_SHIFT = 325,             /* RIGHT_SHIFT  */
    LEFT_SHIFT = 326,              /* LEFT_SHIFT  */
    PLUS_ASSIGN = 327,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 328,            /* MINUS_ASSIGN  */
    LEFT_SHIFT_ASSIGN = 329,       /* LEFT_SHIFT_ASSIGN  */
    RIGHT_SHIFT_ASSIGN = 330,      /* RIGHT_SHIFT_ASSIGN  */
    BITWISE_AND_ASSIGN = 331,      /* BITWISE_AND_ASSIGN  */
    BITWISE_OR_ASSIGN = 332,       /* BITWISE_OR_ASSIGN  */
    BITWISE_XOR_ASSIGN = 333,      /* BITWISE_XOR_ASSIGN  */
    MULTIPLY_ASSIGN = 334,         /* MULTIPLY_ASSIGN  */
    DIVIDE_ASSIGN = 335,           /* DIVIDE_ASSIGN  */
    MODULUS_ASSIGN = 336,          /* MODULUS_ASSIGN  */
    CARDINAL = 337,                /* CARDINAL  */
    ARROW = 338,                   /* ARROW  */
    DEFINE = 339,                  /* DEFINE  */
    CONSTANT = 340,                /* CONSTANT  */
    POINTER = 341,                 /* POINTER  */
    ADDRESS_OF = 342,              /* ADDRESS_OF  */
    OTHER = 343,                   /* OTHER  */
    DOT = 344,                     /* DOT  */
    QUOTE = 345                    /* QUOTE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "Parser.y"

    char identifier[20];
    int intval;              // Integer literals
    double floatval;         // Floating-point literals

#line 160 "Parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
