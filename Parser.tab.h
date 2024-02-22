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
    EOL = 260,                     /* EOL  */
    IF = 261,                      /* IF  */
    ELSEIF = 262,                  /* ELSEIF  */
    ELSE = 263,                    /* ELSE  */
    DO = 264,                      /* DO  */
    WHILE = 265,                   /* WHILE  */
    FOR = 266,                     /* FOR  */
    SWITCH = 267,                  /* SWITCH  */
    CASE = 268,                    /* CASE  */
    DEFAULT = 269,                 /* DEFAULT  */
    RETURN = 270,                  /* RETURN  */
    BREAK = 271,                   /* BREAK  */
    INT = 272,                     /* INT  */
    FLOAT = 273,                   /* FLOAT  */
    DOUBLE = 274,                  /* DOUBLE  */
    CHAR = 275,                    /* CHAR  */
    VOID = 276,                    /* VOID  */
    STRUCT = 277,                  /* STRUCT  */
    TYPEDEF = 278,                 /* TYPEDEF  */
    AUTO = 279,                    /* AUTO  */
    CONTINUE = 280,                /* CONTINUE  */
    EXTERN = 281,                  /* EXTERN  */
    GOTO = 282,                    /* GOTO  */
    LONG = 283,                    /* LONG  */
    ENUM = 284,                    /* ENUM  */
    REGISTER = 285,                /* REGISTER  */
    SHORT = 286,                   /* SHORT  */
    SIZEOF = 287,                  /* SIZEOF  */
    STATIC = 288,                  /* STATIC  */
    SIGNED = 289,                  /* SIGNED  */
    UNION = 290,                   /* UNION  */
    UNSIGNED = 291,                /* UNSIGNED  */
    VOLATILE = 292,                /* VOLATILE  */
    NUM = 293,                     /* NUM  */
    ID = 294,                      /* ID  */
    FNUM = 295,                    /* FNUM  */
    ASSIGN = 296,                  /* ASSIGN  */
    PLUS = 297,                    /* PLUS  */
    MINUS = 298,                   /* MINUS  */
    TIMES = 299,                   /* TIMES  */
    OVER = 300,                    /* OVER  */
    PERCENT = 301,                 /* PERCENT  */
    LPAREN = 302,                  /* LPAREN  */
    RPAREN = 303,                  /* RPAREN  */
    LEFT_BRACE = 304,              /* LEFT_BRACE  */
    RIGHT_BRACE = 305,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 306,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 307,           /* RIGHT_BRACKET  */
    TERNARY = 308,                 /* TERNARY  */
    SEMI = 309,                    /* SEMI  */
    COLON = 310,                   /* COLON  */
    COMMA = 311,                   /* COMMA  */
    INCREMENT = 312,               /* INCREMENT  */
    DECREMENT = 313,               /* DECREMENT  */
    BITWISE_AND = 314,             /* BITWISE_AND  */
    BITWISE_OR = 315,              /* BITWISE_OR  */
    BITWISE_NOT = 316,             /* BITWISE_NOT  */
    BITWISE_XOR = 317,             /* BITWISE_XOR  */
    LOGICAL_NOT = 318,             /* LOGICAL_NOT  */
    LOGICAL_AND = 319,             /* LOGICAL_AND  */
    LOGICAL_OR = 320,              /* LOGICAL_OR  */
    EQUAL = 321,                   /* EQUAL  */
    NOT_EQUAL = 322,               /* NOT_EQUAL  */
    LESS_THAN = 323,               /* LESS_THAN  */
    GREATER_THAN = 324,            /* GREATER_THAN  */
    LESS_THAN_OR_EQUAL = 325,      /* LESS_THAN_OR_EQUAL  */
    GREATER_THAN_OR_EQUAL = 326,   /* GREATER_THAN_OR_EQUAL  */
    RIGHT_SHIFT = 327,             /* RIGHT_SHIFT  */
    LEFT_SHIFT = 328,              /* LEFT_SHIFT  */
    PLUS_ASSIGN = 329,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 330,            /* MINUS_ASSIGN  */
    MODULO = 331,                  /* MODULO  */
    LEFT_SHIFT_ASSIGN = 332,       /* LEFT_SHIFT_ASSIGN  */
    RIGHT_SHIFT_ASSIGN = 333,      /* RIGHT_SHIFT_ASSIGN  */
    BITWISE_AND_ASSIGN = 334,      /* BITWISE_AND_ASSIGN  */
    BITWISE_OR_ASSIGN = 335,       /* BITWISE_OR_ASSIGN  */
    BITWISE_XOR_ASSIGN = 336,      /* BITWISE_XOR_ASSIGN  */
    MULTIPLY_ASSIGN = 337,         /* MULTIPLY_ASSIGN  */
    DIVIDE_ASSIGN = 338,           /* DIVIDE_ASSIGN  */
    MODULUS_ASSIGN = 339,          /* MODULUS_ASSIGN  */
    PREPROCESSOR = 340,            /* PREPROCESSOR  */
    ARROW = 341,                   /* ARROW  */
    DEFINE = 342,                  /* DEFINE  */
    EXIT = 343,                    /* EXIT  */
    CONSTANT = 344,                /* CONSTANT  */
    POINTER = 345,                 /* POINTER  */
    ADDRESS_OF = 346,              /* ADDRESS_OF  */
    OTHER = 347                    /* OTHER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "Parser.y"

	char identifier[20];
	int intval;              // For integer literals
    double floatval;         // For floating-point literals
    char *strval;            // For string literals or identifiers
    char charval;            // For single character tokens

#line 164 "Parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
