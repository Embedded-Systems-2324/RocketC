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
    STRINGliteral = 296,           /* STRINGliteral  */
    ASSIGN = 297,                  /* ASSIGN  */
    PLUS = 298,                    /* PLUS  */
    MINUS = 299,                   /* MINUS  */
    TIMES = 300,                   /* TIMES  */
    OVER = 301,                    /* OVER  */
    PERCENT = 302,                 /* PERCENT  */
    LPAREN = 303,                  /* LPAREN  */
    RPAREN = 304,                  /* RPAREN  */
    LEFT_BRACE = 305,              /* LEFT_BRACE  */
    RIGHT_BRACE = 306,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 307,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 308,           /* RIGHT_BRACKET  */
    TERNARY = 309,                 /* TERNARY  */
    SEMI = 310,                    /* SEMI  */
    COLON = 311,                   /* COLON  */
    COMMA = 312,                   /* COMMA  */
    INCREMENT = 313,               /* INCREMENT  */
    DECREMENT = 314,               /* DECREMENT  */
    BITWISE_AND = 315,             /* BITWISE_AND  */
    BITWISE_OR = 316,              /* BITWISE_OR  */
    BITWISE_NOT = 317,             /* BITWISE_NOT  */
    BITWISE_XOR = 318,             /* BITWISE_XOR  */
    LOGICAL_NOT = 319,             /* LOGICAL_NOT  */
    LOGICAL_AND = 320,             /* LOGICAL_AND  */
    LOGICAL_OR = 321,              /* LOGICAL_OR  */
    EQUAL = 322,                   /* EQUAL  */
    NOT_EQUAL = 323,               /* NOT_EQUAL  */
    LESS_THAN = 324,               /* LESS_THAN  */
    GREATER_THAN = 325,            /* GREATER_THAN  */
    LESS_THAN_OR_EQUAL = 326,      /* LESS_THAN_OR_EQUAL  */
    GREATER_THAN_OR_EQUAL = 327,   /* GREATER_THAN_OR_EQUAL  */
    RIGHT_SHIFT = 328,             /* RIGHT_SHIFT  */
    LEFT_SHIFT = 329,              /* LEFT_SHIFT  */
    PLUS_ASSIGN = 330,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 331,            /* MINUS_ASSIGN  */
    MODULO = 332,                  /* MODULO  */
    LEFT_SHIFT_ASSIGN = 333,       /* LEFT_SHIFT_ASSIGN  */
    RIGHT_SHIFT_ASSIGN = 334,      /* RIGHT_SHIFT_ASSIGN  */
    BITWISE_AND_ASSIGN = 335,      /* BITWISE_AND_ASSIGN  */
    BITWISE_OR_ASSIGN = 336,       /* BITWISE_OR_ASSIGN  */
    BITWISE_XOR_ASSIGN = 337,      /* BITWISE_XOR_ASSIGN  */
    MULTIPLY_ASSIGN = 338,         /* MULTIPLY_ASSIGN  */
    DIVIDE_ASSIGN = 339,           /* DIVIDE_ASSIGN  */
    MODULUS_ASSIGN = 340,          /* MODULUS_ASSIGN  */
    PREPROCESSOR = 341,            /* PREPROCESSOR  */
    ARROW = 342,                   /* ARROW  */
    DEFINE = 343,                  /* DEFINE  */
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
#line 39 "Parser.y"

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
