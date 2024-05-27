/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 15 "Parser/Parser.y"

#include <stdint.h>
#include <errno.h>
#include "../main.h"
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

int yylex();
int yyerror(char* pStr);
const char* getTokenName(int tokenValue);
TreeNode_st* pTreeRoot;
static char* currentFunction;



#line 89 "Parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_IF = 3,                   /* TOKEN_IF  */
  YYSYMBOL_TOKEN_EOF = 4,                  /* TOKEN_EOF  */
  YYSYMBOL_TOKEN_ERROR = 5,                /* TOKEN_ERROR  */
  YYSYMBOL_TOKEN_ELSE = 6,                 /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_DO = 7,                   /* TOKEN_DO  */
  YYSYMBOL_TOKEN_WHILE = 8,                /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_FOR = 9,                  /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_SWITCH = 10,              /* TOKEN_SWITCH  */
  YYSYMBOL_TOKEN_CASE = 11,                /* TOKEN_CASE  */
  YYSYMBOL_TOKEN_DEFAULT = 12,             /* TOKEN_DEFAULT  */
  YYSYMBOL_TOKEN_RETURN = 13,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_BREAK = 14,               /* TOKEN_BREAK  */
  YYSYMBOL_TOKEN_INT = 15,                 /* TOKEN_INT  */
  YYSYMBOL_TOKEN_FLOAT = 16,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_DOUBLE = 17,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_CHAR = 18,                /* TOKEN_CHAR  */
  YYSYMBOL_TOKEN_VOID = 19,                /* TOKEN_VOID  */
  YYSYMBOL_TOKEN_STRUCT = 20,              /* TOKEN_STRUCT  */
  YYSYMBOL_TOKEN_TYPEDEF = 21,             /* TOKEN_TYPEDEF  */
  YYSYMBOL_TOKEN_CONTINUE = 22,            /* TOKEN_CONTINUE  */
  YYSYMBOL_TOKEN_EXTERN = 23,              /* TOKEN_EXTERN  */
  YYSYMBOL_TOKEN_GOTO = 24,                /* TOKEN_GOTO  */
  YYSYMBOL_TOKEN_LONG = 25,                /* TOKEN_LONG  */
  YYSYMBOL_TOKEN_ENUM = 26,                /* TOKEN_ENUM  */
  YYSYMBOL_TOKEN_SHORT = 27,               /* TOKEN_SHORT  */
  YYSYMBOL_TOKEN_SIZEOF = 28,              /* TOKEN_SIZEOF  */
  YYSYMBOL_TOKEN_STATIC = 29,              /* TOKEN_STATIC  */
  YYSYMBOL_TOKEN_SIGNED = 30,              /* TOKEN_SIGNED  */
  YYSYMBOL_TOKEN_UNION = 31,               /* TOKEN_UNION  */
  YYSYMBOL_TOKEN_UNSIGNED = 32,            /* TOKEN_UNSIGNED  */
  YYSYMBOL_TOKEN_VOLATILE = 33,            /* TOKEN_VOLATILE  */
  YYSYMBOL_TOKEN_ASSIGN = 34,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS = 35,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 36,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_OVER = 37,                /* TOKEN_OVER  */
  YYSYMBOL_TOKEN_PERCENT = 38,             /* TOKEN_PERCENT  */
  YYSYMBOL_TOKEN_LEFT_PARENTHESES = 39,    /* TOKEN_LEFT_PARENTHESES  */
  YYSYMBOL_TOKEN_RIGHT_PARENTHESES = 40,   /* TOKEN_RIGHT_PARENTHESES  */
  YYSYMBOL_TOKEN_LEFT_BRACE = 41,          /* TOKEN_LEFT_BRACE  */
  YYSYMBOL_TOKEN_RIGHT_BRACE = 42,         /* TOKEN_RIGHT_BRACE  */
  YYSYMBOL_TOKEN_LEFT_BRACKET = 43,        /* TOKEN_LEFT_BRACKET  */
  YYSYMBOL_TOKEN_RIGHT_BRACKET = 44,       /* TOKEN_RIGHT_BRACKET  */
  YYSYMBOL_TOKEN_TERNARY = 45,             /* TOKEN_TERNARY  */
  YYSYMBOL_TOKEN_SEMI = 46,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_COLON = 47,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_COMMA = 48,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_INCREMENT = 49,           /* TOKEN_INCREMENT  */
  YYSYMBOL_TOKEN_DECREMENT = 50,           /* TOKEN_DECREMENT  */
  YYSYMBOL_TOKEN_BITWISE_AND = 51,         /* TOKEN_BITWISE_AND  */
  YYSYMBOL_TOKEN_BITWISE_OR = 52,          /* TOKEN_BITWISE_OR  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 53,         /* TOKEN_LOGICAL_AND  */
  YYSYMBOL_TOKEN_BITWISE_NOT = 54,         /* TOKEN_BITWISE_NOT  */
  YYSYMBOL_TOKEN_BITWISE_XOR = 55,         /* TOKEN_BITWISE_XOR  */
  YYSYMBOL_TOKEN_LOGICAL_NOT = 56,         /* TOKEN_LOGICAL_NOT  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 57,          /* TOKEN_LOGICAL_OR  */
  YYSYMBOL_TOKEN_EQUAL = 58,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_NOT_EQUAL = 59,           /* TOKEN_NOT_EQUAL  */
  YYSYMBOL_TOKEN_LESS_THAN = 60,           /* TOKEN_LESS_THAN  */
  YYSYMBOL_TOKEN_GREATER_THAN = 61,        /* TOKEN_GREATER_THAN  */
  YYSYMBOL_TOKEN_LESS_THAN_OR_EQUAL = 62,  /* TOKEN_LESS_THAN_OR_EQUAL  */
  YYSYMBOL_TOKEN_GREATER_THAN_OR_EQUAL = 63, /* TOKEN_GREATER_THAN_OR_EQUAL  */
  YYSYMBOL_TOKEN_RIGHT_SHIFT = 64,         /* TOKEN_RIGHT_SHIFT  */
  YYSYMBOL_TOKEN_LEFT_SHIFT = 65,          /* TOKEN_LEFT_SHIFT  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 66,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 67,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_LEFT_SHIFT_ASSIGN = 68,   /* TOKEN_LEFT_SHIFT_ASSIGN  */
  YYSYMBOL_TOKEN_RIGHT_SHIFT_ASSIGN = 69,  /* TOKEN_RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_AND_ASSIGN = 70,  /* TOKEN_BITWISE_AND_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_OR_ASSIGN = 71,   /* TOKEN_BITWISE_OR_ASSIGN  */
  YYSYMBOL_TOKEN_BITWISE_XOR_ASSIGN = 72,  /* TOKEN_BITWISE_XOR_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 73,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 74,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULUS_ASSIGN = 75,      /* TOKEN_MODULUS_ASSIGN  */
  YYSYMBOL_TOKEN_ARROW = 76,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_CONSTANT = 77,            /* TOKEN_CONSTANT  */
  YYSYMBOL_TOKEN_ASTERISK = 78,            /* TOKEN_ASTERISK  */
  YYSYMBOL_TOKEN_ADDRESS_OF = 79,          /* TOKEN_ADDRESS_OF  */
  YYSYMBOL_TOKEN_DOT = 80,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_FNUM = 81,                /* TOKEN_FNUM  */
  YYSYMBOL_TOKEN_NUM = 82,                 /* TOKEN_NUM  */
  YYSYMBOL_TOKEN_STR = 83,                 /* TOKEN_STR  */
  YYSYMBOL_TOKEN_ID = 84,                  /* TOKEN_ID  */
  YYSYMBOL_TOKEN_CNUM = 85,                /* TOKEN_CNUM  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_R_PROGRAM = 87,                 /* R_PROGRAM  */
  YYSYMBOL_R_GLOBAL_STATEMENT = 88,        /* R_GLOBAL_STATEMENT  */
  YYSYMBOL_R_LOCAL_STATEMENT_LIST = 89,    /* R_LOCAL_STATEMENT_LIST  */
  YYSYMBOL_R_LOCAL_STATEMENT = 90,         /* R_LOCAL_STATEMENT  */
  YYSYMBOL_R_COMPOUND_STATEMENT = 91,      /* R_COMPOUND_STATEMENT  */
  YYSYMBOL_R_CONTINUE = 92,                /* R_CONTINUE  */
  YYSYMBOL_R_BREAK = 93,                   /* R_BREAK  */
  YYSYMBOL_R_GOTO = 94,                    /* R_GOTO  */
  YYSYMBOL_R_SWITCH = 95,                  /* R_SWITCH  */
  YYSYMBOL_R_SWITCH_BODY = 96,             /* R_SWITCH_BODY  */
  YYSYMBOL_R_CASE_LIST = 97,               /* R_CASE_LIST  */
  YYSYMBOL_R_CASE = 98,                    /* R_CASE  */
  YYSYMBOL_R_DEFAULT = 99,                 /* R_DEFAULT  */
  YYSYMBOL_R_IF_STATEMENT = 100,           /* R_IF_STATEMENT  */
  YYSYMBOL_R_RETURN = 101,                 /* R_RETURN  */
  YYSYMBOL_R_WHILE_LOOP = 102,             /* R_WHILE_LOOP  */
  YYSYMBOL_R_DO_WHILE_LOOP = 103,          /* R_DO_WHILE_LOOP  */
  YYSYMBOL_R_FOR_LOOP = 104,               /* R_FOR_LOOP  */
  YYSYMBOL_R_FOR_INIT_FIELD = 105,         /* R_FOR_INIT_FIELD  */
  YYSYMBOL_R_FOR_ASSIGNMENT_FIELD = 106,   /* R_FOR_ASSIGNMENT_FIELD  */
  YYSYMBOL_R_LABEL = 107,                  /* R_LABEL  */
  YYSYMBOL_R_FUNC_SIGNATURE = 108,         /* R_FUNC_SIGNATURE  */
  YYSYMBOL_R_FUNC_PROTOTYPE = 109,         /* R_FUNC_PROTOTYPE  */
  YYSYMBOL_R_FUNC_IMPLEMENT = 110,         /* R_FUNC_IMPLEMENT  */
  YYSYMBOL_R_FUNC_CALL = 111,              /* R_FUNC_CALL  */
  YYSYMBOL_R_EXP_LIST = 112,               /* R_EXP_LIST  */
  YYSYMBOL_R_ARG_LIST = 113,               /* R_ARG_LIST  */
  YYSYMBOL_R_ARG = 114,                    /* R_ARG  */
  YYSYMBOL_R_VAR_DECLARATION = 115,        /* R_VAR_DECLARATION  */
  YYSYMBOL_R_ARR_DECLARATION = 116,        /* R_ARR_DECLARATION  */
  YYSYMBOL_R_ARR_SIZE = 117,               /* R_ARR_SIZE  */
  YYSYMBOL_R_ID_LIST = 118,                /* R_ID_LIST  */
  YYSYMBOL_R_VAR_ASSIGNMENT = 119,         /* R_VAR_ASSIGNMENT  */
  YYSYMBOL_R_COMPOUND_VAR_ASSIGN = 120,    /* R_COMPOUND_VAR_ASSIGN  */
  YYSYMBOL_R_SIMPLE_VAR_ASSIGN = 121,      /* R_SIMPLE_VAR_ASSIGN  */
  YYSYMBOL_R_VAR_PREAMBLE = 122,           /* R_VAR_PREAMBLE  */
  YYSYMBOL_R_EXP = 123,                    /* R_EXP  */
  YYSYMBOL_R_TERM = 124,                   /* R_TERM  */
  YYSYMBOL_R_OPERAND = 125,                /* R_OPERAND  */
  YYSYMBOL_R_FACTOR = 126,                 /* R_FACTOR  */
  YYSYMBOL_R_ARRAY_INDEX = 127,            /* R_ARRAY_INDEX  */
  YYSYMBOL_R_POINTER_CONTENT = 128,        /* R_POINTER_CONTENT  */
  YYSYMBOL_R_INC_DEC = 129,                /* R_INC_DEC  */
  YYSYMBOL_R_PRE_INCREMENT = 130,          /* R_PRE_INCREMENT  */
  YYSYMBOL_R_POST_INCREMENT = 131,         /* R_POST_INCREMENT  */
  YYSYMBOL_R_PRE_DECREMENT = 132,          /* R_PRE_DECREMENT  */
  YYSYMBOL_R_POST_DECREMENT = 133,         /* R_POST_DECREMENT  */
  YYSYMBOL_R_ARITHMETIC_OPERATOR = 134,    /* R_ARITHMETIC_OPERATOR  */
  YYSYMBOL_R_PRIORITY_OPERATOR = 135,      /* R_PRIORITY_OPERATOR  */
  YYSYMBOL_R_CONDITION_OPERATOR = 136,     /* R_CONDITION_OPERATOR  */
  YYSYMBOL_R_LOGIC_OPERATOR = 137,         /* R_LOGIC_OPERATOR  */
  YYSYMBOL_R_BITWISE_OPERATOR = 138,       /* R_BITWISE_OPERATOR  */
  YYSYMBOL_R_COMPOUND_ASSIGN_OPERATOR = 139, /* R_COMPOUND_ASSIGN_OPERATOR  */
  YYSYMBOL_R_TYPE_CAST = 140,              /* R_TYPE_CAST  */
  YYSYMBOL_R_TYPE_ALL = 141,               /* R_TYPE_ALL  */
  YYSYMBOL_R_TYPE_PTR = 142,               /* R_TYPE_PTR  */
  YYSYMBOL_R_TYPE = 143,                   /* R_TYPE  */
  YYSYMBOL_R_VISIBILITY_QUALIFIER = 144,   /* R_VISIBILITY_QUALIFIER  */
  YYSYMBOL_R_MOD_QUALIFIER = 145,          /* R_MOD_QUALIFIER  */
  YYSYMBOL_R_SIGN_QUALIFIER = 146          /* R_SIGN_QUALIFIER  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1113

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  285

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   340


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   137,   156,   163,   168,   173,   181,   186,
     205,   212,   217,   222,   227,   232,   237,   242,   247,   252,
     257,   262,   267,   272,   277,   282,   290,   317,   329,   335,
     341,   350,   359,   378,   383,   391,   410,   418,   425,   436,
     447,   455,   467,   473,   486,   495,   503,   512,   540,   555,
     560,   565,   576,   588,   602,   609,   617,   627,   632,   652,
     660,   665,   684,   691,   702,   712,   722,   737,   758,   768,
     779,   788,   813,   843,   854,   865,   870,   875,   884,   895,
     909,   926,   934,   941,   948,   955,   961,   967,   973,   983,
     991,   999,  1007,  1015,  1022,  1030,  1039,  1048,  1056,  1063,
    1068,  1076,  1082,  1091,  1096,  1101,  1107,  1113,  1119,  1124,
    1130,  1136,  1142,  1148,  1155,  1161,  1168,  1178,  1187,  1192,
    1197,  1202,  1210,  1218,  1226,  1234,  1247,  1253,  1259,  1265,
    1273,  1279,  1285,  1293,  1299,  1305,  1311,  1317,  1323,  1331,
    1337,  1345,  1351,  1357,  1365,  1371,  1377,  1383,  1389,  1395,
    1401,  1407,  1413,  1419,  1432,  1441,  1446,  1454,  1465,  1471,
    1477,  1483,  1489,  1495,  1501,  1506,  1515,  1521,  1531,  1537,
    1545,  1551
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_IF",
  "TOKEN_EOF", "TOKEN_ERROR", "TOKEN_ELSE", "TOKEN_DO", "TOKEN_WHILE",
  "TOKEN_FOR", "TOKEN_SWITCH", "TOKEN_CASE", "TOKEN_DEFAULT",
  "TOKEN_RETURN", "TOKEN_BREAK", "TOKEN_INT", "TOKEN_FLOAT",
  "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_VOID", "TOKEN_STRUCT",
  "TOKEN_TYPEDEF", "TOKEN_CONTINUE", "TOKEN_EXTERN", "TOKEN_GOTO",
  "TOKEN_LONG", "TOKEN_ENUM", "TOKEN_SHORT", "TOKEN_SIZEOF",
  "TOKEN_STATIC", "TOKEN_SIGNED", "TOKEN_UNION", "TOKEN_UNSIGNED",
  "TOKEN_VOLATILE", "TOKEN_ASSIGN", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_OVER", "TOKEN_PERCENT", "TOKEN_LEFT_PARENTHESES",
  "TOKEN_RIGHT_PARENTHESES", "TOKEN_LEFT_BRACE", "TOKEN_RIGHT_BRACE",
  "TOKEN_LEFT_BRACKET", "TOKEN_RIGHT_BRACKET", "TOKEN_TERNARY",
  "TOKEN_SEMI", "TOKEN_COLON", "TOKEN_COMMA", "TOKEN_INCREMENT",
  "TOKEN_DECREMENT", "TOKEN_BITWISE_AND", "TOKEN_BITWISE_OR",
  "TOKEN_LOGICAL_AND", "TOKEN_BITWISE_NOT", "TOKEN_BITWISE_XOR",
  "TOKEN_LOGICAL_NOT", "TOKEN_LOGICAL_OR", "TOKEN_EQUAL",
  "TOKEN_NOT_EQUAL", "TOKEN_LESS_THAN", "TOKEN_GREATER_THAN",
  "TOKEN_LESS_THAN_OR_EQUAL", "TOKEN_GREATER_THAN_OR_EQUAL",
  "TOKEN_RIGHT_SHIFT", "TOKEN_LEFT_SHIFT", "TOKEN_PLUS_ASSIGN",
  "TOKEN_MINUS_ASSIGN", "TOKEN_LEFT_SHIFT_ASSIGN",
  "TOKEN_RIGHT_SHIFT_ASSIGN", "TOKEN_BITWISE_AND_ASSIGN",
  "TOKEN_BITWISE_OR_ASSIGN", "TOKEN_BITWISE_XOR_ASSIGN",
  "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULUS_ASSIGN",
  "TOKEN_ARROW", "TOKEN_CONSTANT", "TOKEN_ASTERISK", "TOKEN_ADDRESS_OF",
  "TOKEN_DOT", "TOKEN_FNUM", "TOKEN_NUM", "TOKEN_STR", "TOKEN_ID",
  "TOKEN_CNUM", "$accept", "R_PROGRAM", "R_GLOBAL_STATEMENT",
  "R_LOCAL_STATEMENT_LIST", "R_LOCAL_STATEMENT", "R_COMPOUND_STATEMENT",
  "R_CONTINUE", "R_BREAK", "R_GOTO", "R_SWITCH", "R_SWITCH_BODY",
  "R_CASE_LIST", "R_CASE", "R_DEFAULT", "R_IF_STATEMENT", "R_RETURN",
  "R_WHILE_LOOP", "R_DO_WHILE_LOOP", "R_FOR_LOOP", "R_FOR_INIT_FIELD",
  "R_FOR_ASSIGNMENT_FIELD", "R_LABEL", "R_FUNC_SIGNATURE",
  "R_FUNC_PROTOTYPE", "R_FUNC_IMPLEMENT", "R_FUNC_CALL", "R_EXP_LIST",
  "R_ARG_LIST", "R_ARG", "R_VAR_DECLARATION", "R_ARR_DECLARATION",
  "R_ARR_SIZE", "R_ID_LIST", "R_VAR_ASSIGNMENT", "R_COMPOUND_VAR_ASSIGN",
  "R_SIMPLE_VAR_ASSIGN", "R_VAR_PREAMBLE", "R_EXP", "R_TERM", "R_OPERAND",
  "R_FACTOR", "R_ARRAY_INDEX", "R_POINTER_CONTENT", "R_INC_DEC",
  "R_PRE_INCREMENT", "R_POST_INCREMENT", "R_PRE_DECREMENT",
  "R_POST_DECREMENT", "R_ARITHMETIC_OPERATOR", "R_PRIORITY_OPERATOR",
  "R_CONDITION_OPERATOR", "R_LOGIC_OPERATOR", "R_BITWISE_OPERATOR",
  "R_COMPOUND_ASSIGN_OPERATOR", "R_TYPE_CAST", "R_TYPE_ALL", "R_TYPE_PTR",
  "R_TYPE", "R_VISIBILITY_QUALIFIER", "R_MOD_QUALIFIER",
  "R_SIGN_QUALIFIER", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-215)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     340,  -215,  -215,  -215,  -215,  -215,  -215,    25,  -215,  -215,
    -215,  -215,  -215,  -215,    90,  -215,    31,  -215,  -215,  -215,
    -215,   -26,  -215,  -215,   -16,   404,   138,   109,  -215,  -215,
    -215,  -215,   311,  -215,  -215,    40,    13,  -215,  -215,  -215,
     138,   109,  -215,   109,  -215,    34,   600,    37,    50,    53,
     607,    47,    49,    17,  -215,    26,    27,    28,   525,   383,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,    56,  -215,  -215,    68,    70,    45,    30,    84,
      75,  -215,  -215,  -215,  -215,   615,   404,    48,    85,  -215,
      51,  -215,   109,  -215,  -215,   615,   125,   615,    57,   615,
     665,   133,  -215,    58,   673,   408,  -215,  -215,  -215,    -4,
    -215,  -215,   717,   -22,  -215,  -215,  -215,  -215,  -215,   408,
    -215,  -215,    94,  -215,  -215,  -215,   615,   615,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,   615,  -215,  -215,  -215,  -215,  -215,   -13,   615,   615,
    -215,   675,   -11,  -215,    59,   138,   109,   100,  -215,   111,
    -215,  -215,   748,   107,   779,   113,   115,   810,  -215,  -215,
    1048,   841,   119,   121,  -215,     4,   -22,   615,     5,  -215,
    -215,  -215,   615,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   673,   673,   673,
     673,  -215,  -215,  -215,   673,  -215,  -215,     3,   675,   872,
     675,   903,   934,  -215,   404,  -215,    78,   109,    82,  -215,
     600,   615,   455,   615,   615,   130,  -215,  -215,  -215,  -215,
     965,   -22,   -22,   -22,   -22,  -215,  -215,   615,  -215,  -215,
    -215,  -215,  -215,    89,  -215,   528,   996,  -215,  -215,   675,
    1027,    76,   615,   675,  -215,   600,   128,   -37,   -54,   134,
     135,    76,  -215,  -215,   675,   600,  -215,   449,   140,  -215,
    -215,  -215,   139,   146,   600,  -215,  -215,  -215,   600,   600,
     600,   600,  -215,   600,   600
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   160,   162,   163,   158,   165,   167,   161,   159,   166,
     170,   171,   169,   168,     0,     4,     0,     6,     7,     5,
      68,     0,    88,   156,   155,     0,     0,     0,   164,     1,
       2,     3,     0,    54,    55,    74,     0,    73,   157,    85,
       0,     0,    86,     0,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
      10,    20,    15,    14,    12,    13,    11,    21,    18,    16,
      19,    17,     0,    22,    23,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,     0,    60,     0,     0,    67,
       0,    82,     0,    83,    84,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,   110,   106,   112,   107,
     111,   115,     0,    96,    98,   102,   104,   108,    99,     0,
      29,    28,     0,   122,   124,   117,    57,     0,    52,   123,
     125,   144,   145,   147,   148,   149,   150,   151,   152,   153,
     146,     0,    26,     9,    24,    76,    75,    74,     0,     0,
      25,    80,     0,    62,     0,     0,     0,     0,    69,    71,
      72,    81,     0,     0,     0,     0,     0,     0,   109,   105,
      89,     0,     0,   114,   113,     0,    93,     0,   107,   100,
     126,   127,     0,    43,   141,   142,   139,   143,   140,   137,
     138,   136,   133,   134,   135,   128,   129,     0,     0,     0,
       0,   131,   132,   130,     0,   101,    30,     0,    59,     0,
      79,     0,     0,    53,     0,    66,     0,     0,     0,    70,
       8,     0,     0,     0,     0,     0,   103,   154,   109,   105,
       0,    90,    91,    94,    92,    97,    56,     0,   116,    77,
      78,    61,    65,     0,    64,    40,     0,    45,    44,    48,
       0,     0,     0,    58,    63,     8,     0,     0,     0,     0,
       0,    33,    36,    34,    95,    41,    46,     0,     0,    50,
      49,    51,     0,     0,     8,    31,    35,    32,     0,     8,
       8,    39,    47,    37,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,   161,  -214,    32,   169,  -215,  -215,  -215,  -215,
    -215,  -215,   -67,   -66,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,   -10,  -215,  -215,   -12,    18,
    -215,  -215,  -215,  -215,   -59,   -20,    19,   -45,  -100,    -1,
     -85,   -32,    21,   -21,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,   -17,  -215,  -215,  -215,   -18,
     -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    14,    15,    59,    60,    61,    62,    63,    64,    65,
     260,   261,   262,   263,    66,    67,    68,    69,    70,   166,
     268,    71,    16,    17,    18,   111,   207,   152,   153,    73,
      20,    88,    36,    74,    75,    76,    77,   171,   113,   114,
     115,   116,   117,   118,    81,    82,    83,    84,   197,   204,
     198,   199,   200,   141,   119,    22,    23,    24,    25,    26,
      27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    37,    41,    43,   176,   112,   245,    40,    39,    42,
      44,    80,    55,    56,    78,   201,   202,    92,    19,    21,
     179,    85,    72,    91,    93,    80,    94,    78,   272,   213,
      87,   273,    19,    21,   205,   126,    72,   214,    80,   127,
     151,   265,    28,   236,   126,   129,   130,   267,   127,    72,
     162,   237,   164,    79,   167,   170,   203,    37,    35,    89,
     281,    90,    38,   156,   148,   283,   284,    79,   155,   154,
     160,   174,    32,    95,    85,   161,    97,    33,    96,    86,
      79,   208,   209,    87,   172,   228,   229,   258,   259,    98,
      29,   143,    99,   120,    30,   121,   210,   231,   232,   233,
     234,   122,   144,   211,   212,     1,     2,     3,     4,     5,
     123,   124,   125,     6,   145,     7,   146,     8,   149,     9,
      10,   150,    11,    12,     1,     2,     3,     4,     5,   147,
     157,   158,   217,   163,     7,   159,     8,   230,   216,   218,
     206,   165,   173,   215,   219,    85,   221,   223,     1,     2,
       3,     4,     5,     1,     2,     3,     4,     5,     7,   227,
       8,   224,   242,     7,   127,     8,   244,    13,    10,   100,
      11,   251,   101,   254,   266,    31,   246,   275,   249,   250,
     278,   274,    55,    56,   103,    34,   279,   104,    78,   105,
      78,   156,   253,   280,   276,   277,   155,   154,   269,    80,
     243,    80,   241,   235,     0,     0,     0,   264,     0,     0,
      72,    57,    72,    78,   106,   107,   108,   109,   110,     0,
       0,     0,     0,    78,    80,     0,     0,     0,     0,     0,
       0,     0,     0,    78,    80,    72,   271,   270,     0,     0,
       0,    79,    78,    79,    80,    72,    78,    78,    78,    78,
       0,    78,    78,    80,   248,    72,     0,    80,    80,    80,
      80,     0,    80,    80,    72,     0,    79,     0,    72,    72,
      72,    72,     0,    72,    72,     0,    79,   143,     0,     0,
       0,     0,     0,     0,     0,     0,    79,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,   143,     0,    79,
      79,    79,    79,     0,    79,    79,     0,     0,     0,     0,
     282,     0,     0,   143,    45,   143,   143,     0,    46,    47,
      48,    49,     0,     0,    50,    51,     1,     2,     3,     4,
       5,     0,     0,    52,     6,    53,     7,     0,     8,     0,
       9,    10,     0,    11,    12,     0,     0,     0,     0,     0,
       0,     0,    32,    54,     0,     1,     2,     3,     4,     5,
      55,    56,     0,     6,     0,     7,     0,     8,     0,     9,
      10,     0,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    13,    57,
      46,    47,    48,    49,     0,    58,    50,    51,     1,     2,
       3,     4,     5,     0,     0,    52,     6,    53,     7,     0,
       8,     0,     9,    10,     0,    11,    12,    13,     0,     1,
       2,     3,     4,     5,    32,   142,     0,     0,     0,     7,
       0,     8,    55,    56,    10,     0,    11,    12,     0,     0,
       0,     0,     0,     0,   175,     0,     0,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,   103,
      13,    57,    46,    47,    48,    49,     0,    58,    50,    51,
       1,     2,     3,     4,     5,     0,     0,    52,     6,    53,
       7,    13,     8,    85,     9,    10,    57,    11,    12,   106,
     107,   108,   178,   110,     0,     0,    32,     0,   129,   130,
       0,   247,     0,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     0,     0,     0,     0,     0,
       0,    45,    13,    57,   255,    46,    47,    48,    49,    58,
       0,    50,    51,     1,     2,     3,     4,     5,     0,     0,
      52,     6,    53,     7,     0,     8,     0,     9,    10,    85,
      11,    12,     0,     0,   126,     0,     0,     0,   127,    32,
       0,     0,   128,     0,   129,   130,     0,    55,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,     0,    45,     0,    13,    57,    46,    47,    48,
      49,     0,    58,    50,    51,     1,     2,     3,     4,     5,
       0,     0,    52,     6,    53,     7,     0,     8,     0,     9,
      10,     0,    11,    12,     0,     0,     0,     0,     0,     0,
       0,    32,     0,   100,     0,     0,   101,     0,     0,    55,
      56,   100,     0,   102,   101,     0,    55,    56,   103,     0,
       0,   104,     0,   105,    55,    56,   103,     0,     0,   104,
       0,   105,     0,     0,     0,     0,     0,    13,    57,     0,
       0,     0,     0,     0,    58,    57,     0,     0,   106,   107,
     108,   109,   110,    57,     0,     0,   106,   107,   108,   109,
     110,   100,     0,     0,   101,     0,     0,     0,     0,   175,
     180,   181,   101,     0,    55,    56,   103,     0,     0,   104,
     182,   105,    55,    56,   103,     0,   184,   185,   186,   105,
     187,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,     0,     0,    57,     0,     0,   168,   169,   108,   109,
     110,    57,   180,   181,   106,   107,   108,   109,   110,     0,
       0,     0,   182,   183,     0,     0,     0,     0,   184,   185,
     186,     0,   187,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   180,   181,     0,     0,     0,   220,     0,
       0,     0,     0,   182,     0,     0,     0,     0,     0,   184,
     185,   186,     0,   187,     0,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   180,   181,     0,     0,     0,   222,
       0,     0,     0,     0,   182,     0,     0,     0,     0,     0,
     184,   185,   186,     0,   187,     0,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   180,   181,     0,     0,     0,
     225,     0,     0,     0,     0,   182,     0,     0,     0,     0,
       0,   184,   185,   186,     0,   187,     0,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   180,   181,     0,     0,
       0,   226,     0,     0,     0,     0,   182,     0,     0,     0,
       0,     0,   184,   185,   186,     0,   187,     0,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   180,   181,     0,
       0,     0,     0,     0,     0,     0,   238,   182,     0,     0,
       0,     0,     0,   184,   185,   186,     0,   187,     0,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   239,
       0,     0,     0,     0,   184,   185,   186,     0,   187,     0,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     240,     0,     0,     0,     0,   184,   185,   186,     0,   187,
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
     182,     0,   252,     0,     0,     0,   184,   185,   186,     0,
     187,     0,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   180,   181,     0,     0,     0,   256,     0,     0,     0,
       0,   182,     0,     0,     0,     0,     0,   184,   185,   186,
       0,   187,     0,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   257,     0,     0,     0,     0,   184,   185,
     186,     0,   187,     0,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   182,     0,     0,     0,     0,     0,   184,
     185,   186,     0,   187,     0,   188,   189,   190,   191,   192,
     193,   194,   195,   196
};

static const yytype_int16 yycheck[] =
{
      32,    21,    25,    26,   104,    50,   220,    25,    25,    26,
      27,    32,    49,    50,    46,    37,    38,    40,     0,     0,
     105,    34,    32,    40,    41,    46,    43,    59,    82,    40,
      43,    85,    14,    14,   119,    39,    46,    48,    59,    43,
      85,   255,    17,    40,    39,    49,    50,    84,    43,    59,
      95,    48,    97,    32,    99,   100,    78,    77,    84,    46,
     274,    48,    78,    86,    34,   279,   280,    46,    86,    86,
      90,   103,    41,    39,    34,    92,    39,    46,    46,    39,
      59,   126,   127,    43,   101,    81,    82,    11,    12,    39,
       0,    59,    39,    46,     4,    46,   141,   197,   198,   199,
     200,    84,    46,   148,   149,    15,    16,    17,    18,    19,
      84,    84,    84,    23,    46,    25,    46,    27,    34,    29,
      30,    46,    32,    33,    15,    16,    17,    18,    19,    84,
      82,    46,   155,     8,    25,    84,    27,   182,   155,   156,
      46,    84,    84,    84,    44,    34,    39,    34,    15,    16,
      17,    18,    19,    15,    16,    17,    18,    19,    25,    40,
      27,    46,    84,    25,    43,    27,    84,    77,    30,    36,
      32,    41,    39,    84,    46,    14,   221,    42,   223,   224,
      40,    47,    49,    50,    51,    16,    47,    54,   220,    56,
     222,   214,   237,    47,   261,   261,   214,   214,   257,   220,
     217,   222,   214,   204,    -1,    -1,    -1,   252,    -1,    -1,
     220,    78,   222,   245,    81,    82,    83,    84,    85,    -1,
      -1,    -1,    -1,   255,   245,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   265,   255,   245,   257,   257,    -1,    -1,
      -1,   220,   274,   222,   265,   255,   278,   279,   280,   281,
      -1,   283,   284,   274,   222,   265,    -1,   278,   279,   280,
     281,    -1,   283,   284,   274,    -1,   245,    -1,   278,   279,
     280,   281,    -1,   283,   284,    -1,   255,   245,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   274,    -1,   265,    -1,   278,
     279,   280,   281,    -1,   283,   284,    -1,    -1,    -1,    -1,
     278,    -1,    -1,   281,     3,   283,   284,    -1,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    24,    25,    -1,    27,    -1,
      29,    30,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    15,    16,    17,    18,    19,
      49,    50,    -1,    23,    -1,    25,    -1,    27,    -1,    29,
      30,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    77,    78,
       7,     8,     9,    10,    -1,    84,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    24,    25,    -1,
      27,    -1,    29,    30,    -1,    32,    33,    77,    -1,    15,
      16,    17,    18,    19,    41,    42,    -1,    -1,    -1,    25,
      -1,    27,    49,    50,    30,    -1,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    51,
      77,    78,     7,     8,     9,    10,    -1,    84,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    24,
      25,    77,    27,    34,    29,    30,    78,    32,    33,    81,
      82,    83,    84,    85,    -1,    -1,    41,    -1,    49,    50,
      -1,    46,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    77,    78,     6,     7,     8,     9,    10,    84,
      -1,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    24,    25,    -1,    27,    -1,    29,    30,    34,
      32,    33,    -1,    -1,    39,    -1,    -1,    -1,    43,    41,
      -1,    -1,    47,    -1,    49,    50,    -1,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,     3,    -1,    77,    78,     7,     8,     9,
      10,    -1,    84,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    24,    25,    -1,    27,    -1,    29,
      30,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    36,    -1,    -1,    39,    -1,    -1,    49,
      50,    36,    -1,    46,    39,    -1,    49,    50,    51,    -1,
      -1,    54,    -1,    56,    49,    50,    51,    -1,    -1,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,
      -1,    -1,    -1,    -1,    84,    78,    -1,    -1,    81,    82,
      83,    84,    85,    78,    -1,    -1,    81,    82,    83,    84,
      85,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    36,
      35,    36,    39,    -1,    49,    50,    51,    -1,    -1,    54,
      45,    56,    49,    50,    51,    -1,    51,    52,    53,    56,
      55,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    -1,    -1,    78,    -1,    -1,    81,    82,    83,    84,
      85,    78,    35,    36,    81,    82,    83,    84,    85,    -1,
      -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    -1,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    35,    36,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    -1,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    35,    36,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    53,    -1,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    -1,    -1,    51,    52,    53,    -1,
      55,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      -1,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    51,    52,
      53,    -1,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    45,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    16,    17,    18,    19,    23,    25,    27,    29,
      30,    32,    33,    77,    87,    88,   108,   109,   110,   115,
     116,   122,   141,   142,   143,   144,   145,   146,    17,     0,
       4,    88,    41,    46,    91,    84,   118,   121,    78,   141,
     145,   146,   141,   146,   141,     3,     7,     8,     9,    10,
      13,    14,    22,    24,    42,    49,    50,    78,    84,    89,
      90,    91,    92,    93,    94,    95,   100,   101,   102,   103,
     104,   107,   111,   115,   119,   120,   121,   122,   127,   128,
     129,   130,   131,   132,   133,    34,    39,    43,   117,    46,
      48,   141,   146,   141,   141,    39,    90,    39,    39,    39,
      36,    39,    46,    51,    54,    56,    81,    82,    83,    84,
      85,   111,   123,   124,   125,   126,   127,   128,   129,   140,
      46,    46,    84,    84,    84,    84,    39,    43,    47,    49,
      50,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,   139,    42,    90,    46,    46,    46,    84,    34,    34,
      46,   123,   113,   114,   141,   145,   146,    82,    46,    84,
     121,   141,   123,     8,   123,    84,   105,   123,    81,    82,
     123,   123,   141,    84,   127,    36,   124,    39,    84,   126,
      35,    36,    45,    46,    51,    52,    53,    55,    57,    58,
      59,    60,    61,    62,    63,    64,    65,   134,   136,   137,
     138,    37,    38,    78,   135,   126,    46,   112,   123,   123,
     123,   123,   123,    40,    48,    84,   141,   146,   141,    44,
      40,    39,    40,    34,    46,    40,    40,    40,    81,    82,
     123,   124,   124,   124,   124,   125,    40,    48,    44,    46,
      46,   114,    84,   141,    84,    89,   123,    46,    90,   123,
     123,    41,    47,   123,    84,     6,    40,    46,    11,    12,
      96,    97,    98,    99,   123,    89,    46,    84,   106,   120,
     121,   129,    82,    85,    47,    42,    98,    99,    40,    47,
      47,    89,    90,    89,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    91,    92,    93,
      94,    95,    96,    96,    96,    97,    97,    98,    98,    99,
     100,   100,   101,   101,   102,   102,   103,   104,   105,   106,
     106,   106,   107,   108,   109,   110,   111,   112,   112,   112,
     113,   113,   113,   114,   114,   114,   114,   115,   115,   116,
     117,   118,   118,   118,   118,   119,   119,   119,   119,   120,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   128,   129,   129,
     129,   129,   130,   131,   132,   133,   134,   134,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   137,
     137,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   141,   141,   142,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   144,   145,   145,
     146,   146
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     2,     2,     2,
       3,     7,     2,     1,     1,     2,     1,     4,     4,     3,
       5,     7,     2,     3,     5,     5,     7,     9,     3,     1,
       1,     1,     2,     5,     2,     2,     4,     0,     3,     1,
       0,     3,     1,     4,     3,     3,     2,     3,     1,     4,
       3,     3,     3,     1,     1,     2,     2,     4,     4,     3,
       3,     4,     3,     3,     3,     2,     2,     2,     1,     2,
       3,     3,     3,     2,     3,     5,     1,     3,     1,     1,
       2,     2,     1,     3,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     2,     2,     1,     4,     2,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* R_PROGRAM: R_PROGRAM TOKEN_EOF  */
#line 132 "Parser/Parser.y"
                            {
                                pTreeRoot = yyvsp[-1].treeNode;
                                LOG_DEBUG("Reached end of file!\n");
                                return 0;
                            }
#line 1630 "Parser.tab.c"
    break;

  case 3: /* R_PROGRAM: R_PROGRAM R_GLOBAL_STATEMENT  */
#line 138 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                                pTreeRoot = yyval.treeNode;
                            }
#line 1653 "Parser.tab.c"
    break;

  case 4: /* R_PROGRAM: R_GLOBAL_STATEMENT  */
#line 157 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1661 "Parser.tab.c"
    break;

  case 5: /* R_GLOBAL_STATEMENT: R_VAR_DECLARATION  */
#line 164 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1669 "Parser.tab.c"
    break;

  case 6: /* R_GLOBAL_STATEMENT: R_FUNC_PROTOTYPE  */
#line 169 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1677 "Parser.tab.c"
    break;

  case 7: /* R_GLOBAL_STATEMENT: R_FUNC_IMPLEMENT  */
#line 174 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1685 "Parser.tab.c"
    break;

  case 8: /* R_LOCAL_STATEMENT_LIST: %empty  */
#line 182 "Parser/Parser.y"
                            {
                                yyval.treeNode = NULL;
                            }
#line 1693 "Parser.tab.c"
    break;

  case 9: /* R_LOCAL_STATEMENT_LIST: R_LOCAL_STATEMENT_LIST R_LOCAL_STATEMENT  */
#line 187 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                            }
#line 1715 "Parser.tab.c"
    break;

  case 10: /* R_LOCAL_STATEMENT_LIST: R_LOCAL_STATEMENT  */
#line 206 "Parser/Parser.y"
                            { 
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1723 "Parser.tab.c"
    break;

  case 11: /* R_LOCAL_STATEMENT: R_IF_STATEMENT  */
#line 213 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1731 "Parser.tab.c"
    break;

  case 12: /* R_LOCAL_STATEMENT: R_GOTO  */
#line 218 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1739 "Parser.tab.c"
    break;

  case 13: /* R_LOCAL_STATEMENT: R_SWITCH  */
#line 223 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1747 "Parser.tab.c"
    break;

  case 14: /* R_LOCAL_STATEMENT: R_BREAK  */
#line 228 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1755 "Parser.tab.c"
    break;

  case 15: /* R_LOCAL_STATEMENT: R_CONTINUE  */
#line 233 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1763 "Parser.tab.c"
    break;

  case 16: /* R_LOCAL_STATEMENT: R_DO_WHILE_LOOP  */
#line 238 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1771 "Parser.tab.c"
    break;

  case 17: /* R_LOCAL_STATEMENT: R_LABEL  */
#line 243 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1779 "Parser.tab.c"
    break;

  case 18: /* R_LOCAL_STATEMENT: R_WHILE_LOOP  */
#line 248 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1787 "Parser.tab.c"
    break;

  case 19: /* R_LOCAL_STATEMENT: R_FOR_LOOP  */
#line 253 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1795 "Parser.tab.c"
    break;

  case 20: /* R_LOCAL_STATEMENT: R_COMPOUND_STATEMENT  */
#line 258 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1803 "Parser.tab.c"
    break;

  case 21: /* R_LOCAL_STATEMENT: R_RETURN  */
#line 263 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1811 "Parser.tab.c"
    break;

  case 22: /* R_LOCAL_STATEMENT: R_VAR_DECLARATION  */
#line 268 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1819 "Parser.tab.c"
    break;

  case 23: /* R_LOCAL_STATEMENT: R_VAR_ASSIGNMENT  */
#line 273 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 1827 "Parser.tab.c"
    break;

  case 24: /* R_LOCAL_STATEMENT: R_FUNC_CALL TOKEN_SEMI  */
#line 278 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 1835 "Parser.tab.c"
    break;

  case 25: /* R_LOCAL_STATEMENT: R_INC_DEC TOKEN_SEMI  */
#line 283 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 1843 "Parser.tab.c"
    break;

  case 26: /* R_COMPOUND_STATEMENT: TOKEN_LEFT_BRACE R_LOCAL_STATEMENT_LIST TOKEN_RIGHT_BRACE  */
#line 291 "Parser/Parser.y"
                            {
                                TreeNode_st* pNode = yyvsp[-1].treeNode;
                                TreeNode_st* pEnd;
                                TreeNode_st* pStart;
                                TreeNode_st* pNull;

                                if (pNode != NULL)
                                { 
                                    NodeCreate(&pEnd, NODE_END_SCOPE);
                                    NodeCreate(&pStart, NODE_START_SCOPE);

                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = pEnd;
                                    yyval.treeNode = pStart;
                                    pStart->pSibling = yyvsp[-1].treeNode; 
                                }
                                else
                                {
                                    NodeCreate(&pNull, NODE_NULL);
                                    yyval.treeNode = pNull;
                                }
                            }
#line 1873 "Parser.tab.c"
    break;

  case 27: /* R_COMPOUND_STATEMENT: TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE  */
#line 318 "Parser/Parser.y"
                            {
                                yyval.treeNode = NULL;
                            }
#line 1881 "Parser.tab.c"
    break;

  case 28: /* R_CONTINUE: TOKEN_CONTINUE TOKEN_SEMI  */
#line 330 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_CONTINUE);
                }
#line 1889 "Parser.tab.c"
    break;

  case 29: /* R_BREAK: TOKEN_BREAK TOKEN_SEMI  */
#line 336 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_BREAK);
                }
#line 1897 "Parser.tab.c"
    break;

  case 30: /* R_GOTO: TOKEN_GOTO TOKEN_ID TOKEN_SEMI  */
#line 342 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_GOTO);
                    yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                }
#line 1906 "Parser.tab.c"
    break;

  case 31: /* R_SWITCH: TOKEN_SWITCH TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_LEFT_BRACE R_SWITCH_BODY TOKEN_RIGHT_BRACE  */
#line 351 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_SWITCH);
                    NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);
                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                }
#line 1916 "Parser.tab.c"
    break;

  case 32: /* R_SWITCH_BODY: R_CASE_LIST R_DEFAULT  */
#line 360 "Parser/Parser.y"
                    {
                        TreeNode_st* pNode = yyvsp[-1].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = yyvsp[0].treeNode;
                            yyval.treeNode = yyvsp[-1].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = yyvsp[0].treeNode;
                        }
                    }
#line 1938 "Parser.tab.c"
    break;

  case 33: /* R_SWITCH_BODY: R_CASE_LIST  */
#line 379 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1946 "Parser.tab.c"
    break;

  case 34: /* R_SWITCH_BODY: R_DEFAULT  */
#line 384 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1954 "Parser.tab.c"
    break;

  case 35: /* R_CASE_LIST: R_CASE_LIST R_CASE  */
#line 392 "Parser/Parser.y"
                    {
                        TreeNode_st* pNode = yyvsp[-1].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = yyvsp[0].treeNode;
                            yyval.treeNode = yyvsp[-1].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = yyvsp[0].treeNode;
                        }
                    }
#line 1976 "Parser.tab.c"
    break;

  case 36: /* R_CASE_LIST: R_CASE  */
#line 411 "Parser/Parser.y"
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
#line 1984 "Parser.tab.c"
    break;

  case 37: /* R_CASE: TOKEN_CASE TOKEN_NUM TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 419 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_CASE);
                        yyval.treeNode->nodeData.dVal = yyvsp[-2].nodeData.dVal;

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 1995 "Parser.tab.c"
    break;

  case 38: /* R_CASE: TOKEN_CASE TOKEN_CNUM TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 426 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_CASE);
                        yyval.treeNode->nodeData.dVal = yyvsp[-2].nodeData.dVal;

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 2006 "Parser.tab.c"
    break;

  case 39: /* R_DEFAULT: TOKEN_DEFAULT TOKEN_COLON R_LOCAL_STATEMENT_LIST  */
#line 437 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_DEFAULT);

                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                    }
#line 2016 "Parser.tab.c"
    break;

  case 40: /* R_IF_STATEMENT: TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT_LIST  */
#line 448 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_IF);

                        NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);                      // Condition:
                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);                      // if true
                    }
#line 2027 "Parser.tab.c"
    break;

  case 41: /* R_IF_STATEMENT: TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT_LIST TOKEN_ELSE R_LOCAL_STATEMENT_LIST  */
#line 456 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_IF);

                        NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);                      // Condition:
                        NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);                      // if true
                        NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);                      // else 
                    }
#line 2039 "Parser.tab.c"
    break;

  case 42: /* R_RETURN: TOKEN_RETURN TOKEN_SEMI  */
#line 468 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_RETURN);
                        yyval.treeNode->nodeData.sVal = currentFunction;
                    }
#line 2048 "Parser.tab.c"
    break;

  case 43: /* R_RETURN: TOKEN_RETURN R_EXP TOKEN_SEMI  */
#line 474 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_RETURN);
                        NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        yyval.treeNode->nodeData.sVal = currentFunction;
                    }
#line 2058 "Parser.tab.c"
    break;

  case 44: /* R_WHILE_LOOP: TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT  */
#line 487 "Parser/Parser.y"
                        {

                            NodeCreate(&(yyval.treeNode), NODE_WHILE);
                        
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);      // if true
                        }
#line 2070 "Parser.tab.c"
    break;

  case 45: /* R_WHILE_LOOP: TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI  */
#line 496 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_WHILE);
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                        }
#line 2079 "Parser.tab.c"
    break;

  case 46: /* R_DO_WHILE_LOOP: TOKEN_DO R_LOCAL_STATEMENT TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI  */
#line 504 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_DO_WHILE);
                        
                            NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode);      // Condition
                            NodeAddChild(yyval.treeNode, yyvsp[-5].treeNode);      // if true
                        }
#line 2090 "Parser.tab.c"
    break;

  case 47: /* R_FOR_LOOP: TOKEN_FOR TOKEN_LEFT_PARENTHESES R_FOR_INIT_FIELD TOKEN_SEMI R_EXP TOKEN_SEMI R_FOR_ASSIGNMENT_FIELD TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT  */
#line 513 "Parser/Parser.y"
                        {
                            TreeNode_st* pNode = yyvsp[0].treeNode;
                            TreeNode_st* pNodeWhile;

                            if (pNode != NULL)
                            { 
                                while (pNode->pSibling != NULL)
                                {
                                    pNode = pNode->pSibling;    
                                }                                        
                                pNode->pSibling = yyvsp[-2].treeNode;
                            }
                            else
                            {
                                yyval.treeNode = yyvsp[-2].treeNode;
                            }
                            
                            NodeCreate(&pNodeWhile, NODE_WHILE);
                        
                            NodeAddChild(pNodeWhile, yyvsp[-4].treeNode);      // Condition
                            NodeAddChild(pNodeWhile, yyvsp[0].treeNode);      // if true
                            
                            yyvsp[-6].treeNode->pSibling = pNodeWhile;
                            yyval.treeNode = yyvsp[-6].treeNode;
                        }
#line 2120 "Parser.tab.c"
    break;

  case 48: /* R_FOR_INIT_FIELD: TOKEN_ID TOKEN_ASSIGN R_EXP  */
#line 541 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild(yyval.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                        }
#line 2136 "Parser.tab.c"
    break;

  case 49: /* R_FOR_ASSIGNMENT_FIELD: R_SIMPLE_VAR_ASSIGN  */
#line 556 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2144 "Parser.tab.c"
    break;

  case 50: /* R_FOR_ASSIGNMENT_FIELD: R_COMPOUND_VAR_ASSIGN  */
#line 561 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2152 "Parser.tab.c"
    break;

  case 51: /* R_FOR_ASSIGNMENT_FIELD: R_INC_DEC  */
#line 566 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2160 "Parser.tab.c"
    break;

  case 52: /* R_LABEL: TOKEN_ID TOKEN_COLON  */
#line 577 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_LABEL);
                                yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                            }
#line 2169 "Parser.tab.c"
    break;

  case 53: /* R_FUNC_SIGNATURE: R_VAR_PREAMBLE TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES  */
#line 589 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_FUNCTION);
                                yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode);
                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);

                                currentFunction = yyvsp[-3].nodeData.sVal;
                            }
#line 2183 "Parser.tab.c"
    break;

  case 54: /* R_FUNC_PROTOTYPE: R_FUNC_SIGNATURE TOKEN_SEMI  */
#line 603 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                            }
#line 2191 "Parser.tab.c"
    break;

  case 55: /* R_FUNC_IMPLEMENT: R_FUNC_SIGNATURE R_COMPOUND_STATEMENT  */
#line 610 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[-1].treeNode;
                                NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                            }
#line 2200 "Parser.tab.c"
    break;

  case 56: /* R_FUNC_CALL: TOKEN_ID TOKEN_LEFT_PARENTHESES R_EXP_LIST TOKEN_RIGHT_PARENTHESES  */
#line 618 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_FUNCTION_CALL);
                                yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2211 "Parser.tab.c"
    break;

  case 57: /* R_EXP_LIST: %empty  */
#line 628 "Parser/Parser.y"
                {
                    yyval.treeNode = NULL;
                }
#line 2219 "Parser.tab.c"
    break;

  case 58: /* R_EXP_LIST: R_EXP_LIST TOKEN_COMMA R_EXP  */
#line 633 "Parser/Parser.y"
                {
                    TreeNode_st* pNode = yyvsp[-2].treeNode;

                    if (pNode != NULL)
                    { 
                        while (pNode->pSibling != NULL)
                        {
                            pNode = pNode->pSibling;    
                        }                                        
                        pNode->pSibling = yyvsp[0].treeNode;
                        yyval.treeNode = yyvsp[-2].treeNode; 
                    }
                    else
                    {
                        yyval.treeNode = yyvsp[0].treeNode;
                    }
                    pTreeRoot = yyval.treeNode;
                }
#line 2242 "Parser.tab.c"
    break;

  case 59: /* R_EXP_LIST: R_EXP  */
#line 653 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2250 "Parser.tab.c"
    break;

  case 60: /* R_ARG_LIST: %empty  */
#line 661 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_NULL);
                            }
#line 2258 "Parser.tab.c"
    break;

  case 61: /* R_ARG_LIST: R_ARG_LIST TOKEN_COMMA R_ARG  */
#line 666 "Parser/Parser.y"
                            {
                                TreeNode_st *pNode = yyvsp[-2].treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = yyvsp[0].treeNode;
                                    yyval.treeNode = yyvsp[-2].treeNode; 
                                }
                                else
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
                            }
#line 2280 "Parser.tab.c"
    break;

  case 62: /* R_ARG_LIST: R_ARG  */
#line 685 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2288 "Parser.tab.c"
    break;

  case 63: /* R_ARG: R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 692 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-2].treeNode->pSibling = yyvsp[-3].treeNode;
                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2302 "Parser.tab.c"
    break;

  case 64: /* R_ARG: R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 703 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2315 "Parser.tab.c"
    break;

  case 65: /* R_ARG: R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID  */
#line 713 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                yyvsp[-1].treeNode->pSibling = yyvsp[-2].treeNode;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2328 "Parser.tab.c"
    break;

  case 66: /* R_ARG: R_TYPE_ALL TOKEN_ID  */
#line 723 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_PARAMETER);
                                yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 2339 "Parser.tab.c"
    break;

  case 67: /* R_VAR_DECLARATION: R_VAR_PREAMBLE R_ID_LIST TOKEN_SEMI  */
#line 738 "Parser/Parser.y"
                            {   
                                TreeNode_st* pNode =  yyvsp[-1].treeNode;

                                TreeNode_st nodePreambleCopy;
                                memcpy(&nodePreambleCopy, yyvsp[-2].treeNode, sizeof(TreeNode_st));
                                free(yyvsp[-2].treeNode);

                                do
                                {
                                    if(pNode->nodeType == NODE_VAR_DECLARATION)
                                    {
                                        NodeAddChildCopy(pNode, &nodePreambleCopy);
                                    }

                                    pNode = pNode->pSibling;    
                                }while (pNode != NULL); 

                                yyval.treeNode = yyvsp[-1].treeNode; 
                            }
#line 2363 "Parser.tab.c"
    break;

  case 68: /* R_VAR_DECLARATION: R_ARR_DECLARATION  */
#line 759 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode; 
                            }
#line 2371 "Parser.tab.c"
    break;

  case 69: /* R_ARR_DECLARATION: R_VAR_PREAMBLE TOKEN_ID R_ARR_SIZE TOKEN_SEMI  */
#line 769 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_ARRAY_DECLARATION);
                            yyval.treeNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;
                            
                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2383 "Parser.tab.c"
    break;

  case 70: /* R_ARR_SIZE: TOKEN_LEFT_BRACKET TOKEN_NUM TOKEN_RIGHT_BRACKET  */
#line 780 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                            yyval.treeNode->nodeData.dVal = yyvsp[-1].nodeData.dVal;
                        }
#line 2392 "Parser.tab.c"
    break;

  case 71: /* R_ID_LIST: R_ID_LIST TOKEN_COMMA TOKEN_ID  */
#line 789 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode; 
                          
                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = yyvsp[0].nodeData.sVal;

                        pNode = yyvsp[-2].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            yyval.treeNode = yyvsp[-2].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = pNewNode;
                        }
                    }
#line 2420 "Parser.tab.c"
    break;

  case 72: /* R_ID_LIST: R_ID_LIST TOKEN_COMMA R_SIMPLE_VAR_ASSIGN  */
#line 814 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode;
                        pNode = yyvsp[0].treeNode->pChilds;   //Var indentifier - first child


                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = pNode->nodeData.sVal;


                        pNode = yyvsp[-2].treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            yyval.treeNode = yyvsp[-2].treeNode; 
                        }
                        else
                        {
                            yyval.treeNode = pNewNode;
                        }

                        pNewNode->pSibling = yyvsp[0].treeNode;
                    }
#line 2453 "Parser.tab.c"
    break;

  case 73: /* R_ID_LIST: R_SIMPLE_VAR_ASSIGN  */
#line 844 "Parser/Parser.y"
                    {
                        TreeNode_st *pNode;
                        pNode = yyvsp[0].treeNode->pChilds;   //Var indentifier - first child

                        NodeCreate(&(yyval.treeNode), NODE_VAR_DECLARATION);
                        yyval.treeNode->nodeData.sVal = pNode->nodeData.sVal;

                        yyval.treeNode->pSibling = yyvsp[0].treeNode;
                    }
#line 2467 "Parser.tab.c"
    break;

  case 74: /* R_ID_LIST: TOKEN_ID  */
#line 855 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_VAR_DECLARATION);
                        yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                    }
#line 2476 "Parser.tab.c"
    break;

  case 75: /* R_VAR_ASSIGNMENT: R_SIMPLE_VAR_ASSIGN TOKEN_SEMI  */
#line 866 "Parser/Parser.y"
                        {                                                               //var &= 4;
                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2484 "Parser.tab.c"
    break;

  case 76: /* R_VAR_ASSIGNMENT: R_COMPOUND_VAR_ASSIGN TOKEN_SEMI  */
#line 871 "Parser/Parser.y"
                        {
                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2492 "Parser.tab.c"
    break;

  case 77: /* R_VAR_ASSIGNMENT: R_ARRAY_INDEX TOKEN_ASSIGN R_EXP TOKEN_SEMI  */
#line 876 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2504 "Parser.tab.c"
    break;

  case 78: /* R_VAR_ASSIGNMENT: R_POINTER_CONTENT TOKEN_ASSIGN R_EXP TOKEN_SEMI  */
#line 885 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild(yyval.treeNode, yyvsp[-3].treeNode);
                            NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                        }
#line 2516 "Parser.tab.c"
    break;

  case 79: /* R_COMPOUND_VAR_ASSIGN: TOKEN_ID R_COMPOUND_ASSIGN_OPERATOR R_EXP  */
#line 896 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeAddNewChild(yyvsp[-1].treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode);

                            yyval.treeNode = yyvsp[-1].treeNode;
                        }
#line 2531 "Parser.tab.c"
    break;

  case 80: /* R_SIMPLE_VAR_ASSIGN: TOKEN_ID TOKEN_ASSIGN R_EXP  */
#line 910 "Parser/Parser.y"
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                            yyval.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild(yyval.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = yyvsp[-2].nodeData.sVal;

                            NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                        }
#line 2547 "Parser.tab.c"
    break;

  case 81: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 927 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-3].treeNode;
                                yyvsp[-3].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2558 "Parser.tab.c"
    break;

  case 82: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL  */
#line 935 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2568 "Parser.tab.c"
    break;

  case 83: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 942 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2578 "Parser.tab.c"
    break;

  case 84: /* R_VAR_PREAMBLE: R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 949 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-2].treeNode;
                                yyvsp[-2].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2588 "Parser.tab.c"
    break;

  case 85: /* R_VAR_PREAMBLE: R_VISIBILITY_QUALIFIER R_TYPE_ALL  */
#line 956 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2597 "Parser.tab.c"
    break;

  case 86: /* R_VAR_PREAMBLE: R_MOD_QUALIFIER R_TYPE_ALL  */
#line 962 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2606 "Parser.tab.c"
    break;

  case 87: /* R_VAR_PREAMBLE: R_SIGN_QUALIFIER R_TYPE_ALL  */
#line 968 "Parser/Parser.y"
                            {
                                yyvsp[0].treeNode->pSibling = yyvsp[-1].treeNode;
                                yyval.treeNode = yyvsp[0].treeNode;
                            }
#line 2615 "Parser.tab.c"
    break;

  case 88: /* R_VAR_PREAMBLE: R_TYPE_ALL  */
#line 974 "Parser/Parser.y"
                            {
                                yyval.treeNode = yyvsp[0].treeNode; 
                            }
#line 2623 "Parser.tab.c"
    break;

  case 89: /* R_EXP: TOKEN_MINUS R_EXP  */
#line 984 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_MINUS;

                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);  
                }
#line 2634 "Parser.tab.c"
    break;

  case 90: /* R_EXP: R_EXP R_ARITHMETIC_OPERATOR R_TERM  */
#line 992 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2645 "Parser.tab.c"
    break;

  case 91: /* R_EXP: R_EXP R_CONDITION_OPERATOR R_TERM  */
#line 1000 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2656 "Parser.tab.c"
    break;

  case 92: /* R_EXP: R_EXP R_BITWISE_OPERATOR R_TERM  */
#line 1008 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode; 
                }
#line 2667 "Parser.tab.c"
    break;

  case 93: /* R_EXP: TOKEN_BITWISE_NOT R_TERM  */
#line 1016 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_BITWISE_NOT;
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode); 
                }
#line 2677 "Parser.tab.c"
    break;

  case 94: /* R_EXP: R_EXP R_LOGIC_OPERATOR R_TERM  */
#line 1023 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 

                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2688 "Parser.tab.c"
    break;

  case 95: /* R_EXP: R_EXP TOKEN_TERNARY R_EXP TOKEN_COLON R_EXP  */
#line 1031 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_TERNARY);

                    NodeAddChild(yyval.treeNode, yyvsp[-4].treeNode); 
                    NodeAddChild(yyval.treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);   
                }
#line 2700 "Parser.tab.c"
    break;

  case 96: /* R_EXP: R_TERM  */
#line 1040 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2708 "Parser.tab.c"
    break;

  case 97: /* R_TERM: R_TERM R_PRIORITY_OPERATOR R_OPERAND  */
#line 1049 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[-2].treeNode); 
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode); 
                    
                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2719 "Parser.tab.c"
    break;

  case 98: /* R_TERM: R_OPERAND  */
#line 1057 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2727 "Parser.tab.c"
    break;

  case 99: /* R_OPERAND: R_INC_DEC  */
#line 1064 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2735 "Parser.tab.c"
    break;

  case 100: /* R_OPERAND: TOKEN_LOGICAL_NOT R_FACTOR  */
#line 1069 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                    yyval.treeNode->nodeData.dVal = OP_LOGICAL_NOT;

                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);
                }
#line 2746 "Parser.tab.c"
    break;

  case 101: /* R_OPERAND: R_TYPE_CAST R_FACTOR  */
#line 1077 "Parser/Parser.y"
                {
                    NodeAddChild(yyvsp[-1].treeNode, yyvsp[0].treeNode);
                    yyval.treeNode = yyvsp[-1].treeNode;
                }
#line 2755 "Parser.tab.c"
    break;

  case 102: /* R_OPERAND: R_FACTOR  */
#line 1083 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode; 
                }
#line 2763 "Parser.tab.c"
    break;

  case 103: /* R_FACTOR: TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES  */
#line 1092 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[-1].treeNode;
                }
#line 2771 "Parser.tab.c"
    break;

  case 104: /* R_FACTOR: R_ARRAY_INDEX  */
#line 1097 "Parser/Parser.y"
                {
                    yyval.treeNode =  yyvsp[0].treeNode;
                }
#line 2779 "Parser.tab.c"
    break;

  case 105: /* R_FACTOR: TOKEN_MINUS TOKEN_NUM  */
#line 1102 "Parser/Parser.y"
                {   
                    NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                    yyval.treeNode->nodeData.dVal = -yyvsp[0].nodeData.dVal;
                }
#line 2788 "Parser.tab.c"
    break;

  case 106: /* R_FACTOR: TOKEN_NUM  */
#line 1108 "Parser/Parser.y"
                {   
                    NodeCreate(&(yyval.treeNode), NODE_INTEGER);
                    yyval.treeNode->nodeData.dVal = yyvsp[0].nodeData.dVal;
                }
#line 2797 "Parser.tab.c"
    break;

  case 107: /* R_FACTOR: TOKEN_ID  */
#line 1114 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_IDENTIFIER);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2806 "Parser.tab.c"
    break;

  case 108: /* R_FACTOR: R_POINTER_CONTENT  */
#line 1120 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2814 "Parser.tab.c"
    break;

  case 109: /* R_FACTOR: TOKEN_MINUS TOKEN_FNUM  */
#line 1125 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_FLOAT);
                    yyval.treeNode->nodeData.fVal = -yyvsp[0].nodeData.fVal;
                }
#line 2823 "Parser.tab.c"
    break;

  case 110: /* R_FACTOR: TOKEN_FNUM  */
#line 1131 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_FLOAT);
                    yyval.treeNode->nodeData.fVal = yyvsp[0].nodeData.fVal;
                }
#line 2832 "Parser.tab.c"
    break;

  case 111: /* R_FACTOR: TOKEN_CNUM  */
#line 1137 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_CHAR);
                    yyval.treeNode->nodeData.dVal = yyvsp[0].nodeData.dVal;
                }
#line 2841 "Parser.tab.c"
    break;

  case 112: /* R_FACTOR: TOKEN_STR  */
#line 1143 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_STRING);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2850 "Parser.tab.c"
    break;

  case 113: /* R_FACTOR: TOKEN_BITWISE_AND R_ARRAY_INDEX  */
#line 1149 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_REFERENCE);
                    NodeAddChild(yyval.treeNode, yyvsp[0].treeNode);  
                }
#line 2859 "Parser.tab.c"
    break;

  case 114: /* R_FACTOR: TOKEN_BITWISE_AND TOKEN_ID  */
#line 1156 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_REFERENCE);
                    yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                }
#line 2868 "Parser.tab.c"
    break;

  case 115: /* R_FACTOR: R_FUNC_CALL  */
#line 1162 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2876 "Parser.tab.c"
    break;

  case 116: /* R_ARRAY_INDEX: TOKEN_ID TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET  */
#line 1169 "Parser/Parser.y"
                {
                    NodeCreate(&(yyval.treeNode), NODE_ARRAY_INDEX);
                    yyval.treeNode->nodeData.sVal = yyvsp[-3].nodeData.sVal;

                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);  
                }
#line 2887 "Parser.tab.c"
    break;

  case 117: /* R_POINTER_CONTENT: TOKEN_ASTERISK TOKEN_ID  */
#line 1179 "Parser/Parser.y"
                    {
                        NodeCreate(&(yyval.treeNode), NODE_POINTER_CONTENT);
                        yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                    }
#line 2896 "Parser.tab.c"
    break;

  case 118: /* R_INC_DEC: R_PRE_INCREMENT  */
#line 1188 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2904 "Parser.tab.c"
    break;

  case 119: /* R_INC_DEC: R_POST_INCREMENT  */
#line 1193 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2912 "Parser.tab.c"
    break;

  case 120: /* R_INC_DEC: R_PRE_DECREMENT  */
#line 1198 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2920 "Parser.tab.c"
    break;

  case 121: /* R_INC_DEC: R_POST_DECREMENT  */
#line 1203 "Parser/Parser.y"
                {
                    yyval.treeNode = yyvsp[0].treeNode;
                }
#line 2928 "Parser.tab.c"
    break;

  case 122: /* R_PRE_INCREMENT: TOKEN_INCREMENT TOKEN_ID  */
#line 1211 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_PRE_INC);
                            yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal;
                        }
#line 2937 "Parser.tab.c"
    break;

  case 123: /* R_POST_INCREMENT: TOKEN_ID TOKEN_INCREMENT  */
#line 1219 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_POST_INC);
                            yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal; 
                        }
#line 2946 "Parser.tab.c"
    break;

  case 124: /* R_PRE_DECREMENT: TOKEN_DECREMENT TOKEN_ID  */
#line 1227 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_PRE_DEC);
                            yyval.treeNode->nodeData.sVal = yyvsp[0].nodeData.sVal; 
                        }
#line 2955 "Parser.tab.c"
    break;

  case 125: /* R_POST_DECREMENT: TOKEN_ID TOKEN_DECREMENT  */
#line 1235 "Parser/Parser.y"
                        {
                            NodeCreate(&(yyval.treeNode), NODE_POST_DEC);
                            yyval.treeNode->nodeData.sVal = yyvsp[-1].nodeData.sVal;
                        }
#line 2964 "Parser.tab.c"
    break;

  case 126: /* R_ARITHMETIC_OPERATOR: TOKEN_PLUS  */
#line 1248 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_PLUS;
                            }
#line 2973 "Parser.tab.c"
    break;

  case 127: /* R_ARITHMETIC_OPERATOR: TOKEN_MINUS  */
#line 1254 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MINUS;
                            }
#line 2982 "Parser.tab.c"
    break;

  case 128: /* R_ARITHMETIC_OPERATOR: TOKEN_RIGHT_SHIFT  */
#line 1260 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_RIGHT_SHIFT;
                            }
#line 2991 "Parser.tab.c"
    break;

  case 129: /* R_ARITHMETIC_OPERATOR: TOKEN_LEFT_SHIFT  */
#line 1266 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LEFT_SHIFT;
                            }
#line 3000 "Parser.tab.c"
    break;

  case 130: /* R_PRIORITY_OPERATOR: TOKEN_ASTERISK  */
#line 1274 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MULTIPLY;
                            }
#line 3009 "Parser.tab.c"
    break;

  case 131: /* R_PRIORITY_OPERATOR: TOKEN_OVER  */
#line 1280 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_DIVIDE;
                            }
#line 3018 "Parser.tab.c"
    break;

  case 132: /* R_PRIORITY_OPERATOR: TOKEN_PERCENT  */
#line 1286 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_REMAIN;
                            }
#line 3027 "Parser.tab.c"
    break;

  case 133: /* R_CONDITION_OPERATOR: TOKEN_GREATER_THAN  */
#line 1294 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_GREATER_THAN;
                            }
#line 3036 "Parser.tab.c"
    break;

  case 134: /* R_CONDITION_OPERATOR: TOKEN_LESS_THAN_OR_EQUAL  */
#line 1300 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LESS_THAN_OR_EQUAL;
                            }
#line 3045 "Parser.tab.c"
    break;

  case 135: /* R_CONDITION_OPERATOR: TOKEN_GREATER_THAN_OR_EQUAL  */
#line 1306 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_GREATER_THAN_OR_EQUAL;
                            }
#line 3054 "Parser.tab.c"
    break;

  case 136: /* R_CONDITION_OPERATOR: TOKEN_LESS_THAN  */
#line 1312 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LESS_THAN;
                            }
#line 3063 "Parser.tab.c"
    break;

  case 137: /* R_CONDITION_OPERATOR: TOKEN_EQUAL  */
#line 1318 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_EQUAL;
                            }
#line 3072 "Parser.tab.c"
    break;

  case 138: /* R_CONDITION_OPERATOR: TOKEN_NOT_EQUAL  */
#line 1324 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_NOT_EQUAL;
                            }
#line 3081 "Parser.tab.c"
    break;

  case 139: /* R_LOGIC_OPERATOR: TOKEN_LOGICAL_AND  */
#line 1332 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LOGICAL_AND;
                            }
#line 3090 "Parser.tab.c"
    break;

  case 140: /* R_LOGIC_OPERATOR: TOKEN_LOGICAL_OR  */
#line 1338 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LOGICAL_OR;
                            }
#line 3099 "Parser.tab.c"
    break;

  case 141: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_AND  */
#line 1346 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_AND;
                            }
#line 3108 "Parser.tab.c"
    break;

  case 142: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_OR  */
#line 1352 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_OR;
                            }
#line 3117 "Parser.tab.c"
    break;

  case 143: /* R_BITWISE_OPERATOR: TOKEN_BITWISE_XOR  */
#line 1358 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_XOR;
                            }
#line 3126 "Parser.tab.c"
    break;

  case 144: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_PLUS_ASSIGN  */
#line 1366 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_PLUS_ASSIGN;
                            }
#line 3135 "Parser.tab.c"
    break;

  case 145: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MINUS_ASSIGN  */
#line 1372 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MINUS_ASSIGN;
                            }
#line 3144 "Parser.tab.c"
    break;

  case 146: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MODULUS_ASSIGN  */
#line 1378 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MODULUS_ASSIGN;
                            }
#line 3153 "Parser.tab.c"
    break;

  case 147: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_LEFT_SHIFT_ASSIGN  */
#line 1384 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_LEFT_SHIFT_ASSIGN;
                            }
#line 3162 "Parser.tab.c"
    break;

  case 148: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_RIGHT_SHIFT_ASSIGN  */
#line 1390 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_RIGHT_SHIFT_ASSIGN;
                            }
#line 3171 "Parser.tab.c"
    break;

  case 149: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_AND_ASSIGN  */
#line 1396 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_AND_ASSIGN;
                            }
#line 3180 "Parser.tab.c"
    break;

  case 150: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_OR_ASSIGN  */
#line 1402 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_OR_ASSIGN;
                            }
#line 3189 "Parser.tab.c"
    break;

  case 151: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_BITWISE_XOR_ASSIGN  */
#line 1408 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_BITWISE_XOR_ASSIGN;
                            }
#line 3198 "Parser.tab.c"
    break;

  case 152: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_MULTIPLY_ASSIGN  */
#line 1414 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_MULTIPLY_ASSIGN;
                            }
#line 3207 "Parser.tab.c"
    break;

  case 153: /* R_COMPOUND_ASSIGN_OPERATOR: TOKEN_DIVIDE_ASSIGN  */
#line 1420 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_OPERATOR);
                                yyval.treeNode->nodeData.dVal = OP_DIVIDE_ASSIGN;
                            }
#line 3216 "Parser.tab.c"
    break;

  case 154: /* R_TYPE_CAST: TOKEN_LEFT_PARENTHESES R_TYPE_ALL TOKEN_RIGHT_PARENTHESES  */
#line 1433 "Parser/Parser.y"
                            {
                                NodeCreate(&(yyval.treeNode), NODE_TYPE_CAST);
                                NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);
                            }
#line 3225 "Parser.tab.c"
    break;

  case 155: /* R_TYPE_ALL: R_TYPE  */
#line 1442 "Parser/Parser.y"
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;  
                                }
#line 3233 "Parser.tab.c"
    break;

  case 156: /* R_TYPE_ALL: R_TYPE_PTR  */
#line 1447 "Parser/Parser.y"
                                {
                                    yyval.treeNode = yyvsp[0].treeNode;
                                }
#line 3241 "Parser.tab.c"
    break;

  case 157: /* R_TYPE_PTR: R_TYPE TOKEN_ASTERISK  */
#line 1455 "Parser/Parser.y"
                                {  
                                    NodeCreate(&(yyval.treeNode), NODE_POINTER);

                                    NodeAddChild(yyval.treeNode, yyvsp[-1].treeNode);                                
                                }
#line 3251 "Parser.tab.c"
    break;

  case 158: /* R_TYPE: TOKEN_CHAR  */
#line 1466 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_CHAR;
                                }
#line 3260 "Parser.tab.c"
    break;

  case 159: /* R_TYPE: TOKEN_SHORT  */
#line 1472 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_SHORT;
                                }
#line 3269 "Parser.tab.c"
    break;

  case 160: /* R_TYPE: TOKEN_INT  */
#line 1478 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_INT;
                                }
#line 3278 "Parser.tab.c"
    break;

  case 161: /* R_TYPE: TOKEN_LONG  */
#line 1484 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_LONG;
                                }
#line 3287 "Parser.tab.c"
    break;

  case 162: /* R_TYPE: TOKEN_FLOAT  */
#line 1490 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_FLOAT;
                                }
#line 3296 "Parser.tab.c"
    break;

  case 163: /* R_TYPE: TOKEN_DOUBLE  */
#line 1496 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_DOUBLE;
                                }
#line 3305 "Parser.tab.c"
    break;

  case 164: /* R_TYPE: TOKEN_LONG TOKEN_DOUBLE  */
#line 1502 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_LONG_DOUBLE;
                                }
#line 3314 "Parser.tab.c"
    break;

  case 165: /* R_TYPE: TOKEN_VOID  */
#line 1507 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_TYPE);
                                    yyval.treeNode->nodeData.dVal = TYPE_VOID;
                                }
#line 3323 "Parser.tab.c"
    break;

  case 166: /* R_VISIBILITY_QUALIFIER: TOKEN_STATIC  */
#line 1516 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_VISIBILITY);
                                    yyval.treeNode->nodeData.dVal = (long int) VIS_STATIC;    
                                }
#line 3332 "Parser.tab.c"
    break;

  case 167: /* R_VISIBILITY_QUALIFIER: TOKEN_EXTERN  */
#line 1522 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_VISIBILITY);
                                    yyval.treeNode->nodeData.dVal = (long int) VIS_EXTERN;     
                                }
#line 3341 "Parser.tab.c"
    break;

  case 168: /* R_MOD_QUALIFIER: TOKEN_CONSTANT  */
#line 1532 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_MODIFIER);
                                    yyval.treeNode->nodeData.dVal = (long int) MOD_CONST;
                                }
#line 3350 "Parser.tab.c"
    break;

  case 169: /* R_MOD_QUALIFIER: TOKEN_VOLATILE  */
#line 1538 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_MODIFIER);
                                    yyval.treeNode->nodeData.dVal = (long int) MOD_VOLATILE; 
                                }
#line 3359 "Parser.tab.c"
    break;

  case 170: /* R_SIGN_QUALIFIER: TOKEN_SIGNED  */
#line 1546 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_SIGN);
                                    yyval.treeNode->nodeData.dVal = (long int) SIGN_SIGNED; 
                                }
#line 3368 "Parser.tab.c"
    break;

  case 171: /* R_SIGN_QUALIFIER: TOKEN_UNSIGNED  */
#line 1552 "Parser/Parser.y"
                                {
                                    NodeCreate(&(yyval.treeNode), NODE_SIGN);
                                    yyval.treeNode->nodeData.dVal = (long int) SIGN_UNSIGNED;
                                }
#line 3377 "Parser.tab.c"
    break;


#line 3381 "Parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1557 "Parser/Parser.y"



//--------------------------------------------------------------------------------------------------------------------//
// Code
//--------------------------------------------------------------------------------------------------------------------//
int executeParser(TreeNode_st** ppTreeRoot)
{
    int ret;

    if (!ppTreeRoot)
        return -EINVAL;
    
    ret = initLexer();
    if (ret < 0)
    {
        LOG_ERROR("Failed to get source file!\n");
        return ret; 
    }

    LOG_WARNING("\n--------------Parser Start--------------\n");

    ret = yyparse();

    *ppTreeRoot = pTreeRoot;

    return ret;
}


int yyerror(char* pStr)
{
    if (!pStr)
        return -EINVAL;

    LOG_ERROR("Error at line: %lu | Error was: %s\n", getLineNumber(), pStr);

    return 0;
}


const char* getTokenName(int tokenValue) 
{
    return yysymbol_name(YYTRANSLATE(tokenValue));
}
