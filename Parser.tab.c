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
#line 1 "Parser.y"


#define YYPARSER 
#include "globals.h"
#include "useful.h"
#include "scanner.h"
#include "parser.h"

int yylex();

#define YYSTYPE TreeNode *
static char * savedName;
static int savedLineNo; 
static TreeNode * savedTree;


#line 88 "Parser.tab.c"

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
  YYSYMBOL_ENDFILE = 3,                    /* ENDFILE  */
  YYSYMBOL_ERROR = 4,                      /* ERROR  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSEIF = 6,                     /* ELSEIF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_DO = 8,                         /* DO  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_SWITCH = 11,                    /* SWITCH  */
  YYSYMBOL_CASE = 12,                      /* CASE  */
  YYSYMBOL_DEFAULT = 13,                   /* DEFAULT  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_INT = 16,                       /* INT  */
  YYSYMBOL_FLOAT = 17,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 18,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 19,                      /* CHAR  */
  YYSYMBOL_VOID = 20,                      /* VOID  */
  YYSYMBOL_STRUCT = 21,                    /* STRUCT  */
  YYSYMBOL_TYPEDEF = 22,                   /* TYPEDEF  */
  YYSYMBOL_CONTINUE = 23,                  /* CONTINUE  */
  YYSYMBOL_EXTERN = 24,                    /* EXTERN  */
  YYSYMBOL_GOTO = 25,                      /* GOTO  */
  YYSYMBOL_LONG = 26,                      /* LONG  */
  YYSYMBOL_ENUM = 27,                      /* ENUM  */
  YYSYMBOL_REGISTER = 28,                  /* REGISTER  */
  YYSYMBOL_SHORT = 29,                     /* SHORT  */
  YYSYMBOL_SIZEOF = 30,                    /* SIZEOF  */
  YYSYMBOL_STATIC = 31,                    /* STATIC  */
  YYSYMBOL_SIGNED = 32,                    /* SIGNED  */
  YYSYMBOL_UNION = 33,                     /* UNION  */
  YYSYMBOL_UNSIGNED = 34,                  /* UNSIGNED  */
  YYSYMBOL_VOLATILE = 35,                  /* VOLATILE  */
  YYSYMBOL_NUM = 36,                       /* NUM  */
  YYSYMBOL_ID = 37,                        /* ID  */
  YYSYMBOL_FNUM = 38,                      /* FNUM  */
  YYSYMBOL_ASSIGN = 39,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 40,                      /* PLUS  */
  YYSYMBOL_MINUS = 41,                     /* MINUS  */
  YYSYMBOL_TIMES = 42,                     /* TIMES  */
  YYSYMBOL_OVER = 43,                      /* OVER  */
  YYSYMBOL_PERCENT = 44,                   /* PERCENT  */
  YYSYMBOL_LPAREN = 45,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 46,                    /* RPAREN  */
  YYSYMBOL_LEFT_BRACE = 47,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 48,               /* RIGHT_BRACE  */
  YYSYMBOL_LEFT_BRACKET = 49,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 50,             /* RIGHT_BRACKET  */
  YYSYMBOL_TERNARY = 51,                   /* TERNARY  */
  YYSYMBOL_SEMI = 52,                      /* SEMI  */
  YYSYMBOL_COLON = 53,                     /* COLON  */
  YYSYMBOL_COMMA = 54,                     /* COMMA  */
  YYSYMBOL_INCREMENT = 55,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 56,                 /* DECREMENT  */
  YYSYMBOL_BITWISE_AND = 57,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 58,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_NOT = 59,               /* BITWISE_NOT  */
  YYSYMBOL_BITWISE_XOR = 60,               /* BITWISE_XOR  */
  YYSYMBOL_LOGICAL_NOT = 61,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 62,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 63,                /* LOGICAL_OR  */
  YYSYMBOL_EQUAL = 64,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 65,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 66,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 67,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN_OR_EQUAL = 68,        /* LESS_THAN_OR_EQUAL  */
  YYSYMBOL_GREATER_THAN_OR_EQUAL = 69,     /* GREATER_THAN_OR_EQUAL  */
  YYSYMBOL_RIGHT_SHIFT = 70,               /* RIGHT_SHIFT  */
  YYSYMBOL_LEFT_SHIFT = 71,                /* LEFT_SHIFT  */
  YYSYMBOL_PLUS_ASSIGN = 72,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 73,              /* MINUS_ASSIGN  */
  YYSYMBOL_LEFT_SHIFT_ASSIGN = 74,         /* LEFT_SHIFT_ASSIGN  */
  YYSYMBOL_RIGHT_SHIFT_ASSIGN = 75,        /* RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_BITWISE_AND_ASSIGN = 76,        /* BITWISE_AND_ASSIGN  */
  YYSYMBOL_BITWISE_OR_ASSIGN = 77,         /* BITWISE_OR_ASSIGN  */
  YYSYMBOL_BITWISE_XOR_ASSIGN = 78,        /* BITWISE_XOR_ASSIGN  */
  YYSYMBOL_MULTIPLY_ASSIGN = 79,           /* MULTIPLY_ASSIGN  */
  YYSYMBOL_DIVIDE_ASSIGN = 80,             /* DIVIDE_ASSIGN  */
  YYSYMBOL_MODULUS_ASSIGN = 81,            /* MODULUS_ASSIGN  */
  YYSYMBOL_CARDINAL = 82,                  /* CARDINAL  */
  YYSYMBOL_ARROW = 83,                     /* ARROW  */
  YYSYMBOL_DEFINE = 84,                    /* DEFINE  */
  YYSYMBOL_CONSTANT = 85,                  /* CONSTANT  */
  YYSYMBOL_POINTER = 86,                   /* POINTER  */
  YYSYMBOL_ADDRESS_OF = 87,                /* ADDRESS_OF  */
  YYSYMBOL_OTHER = 88,                     /* OTHER  */
  YYSYMBOL_DOT = 89,                       /* DOT  */
  YYSYMBOL_QUOTE = 90,                     /* QUOTE  */
  YYSYMBOL_YYACCEPT = 91,                  /* $accept  */
  YYSYMBOL_Final = 92,                     /* Final  */
  YYSYMBOL_prog = 93,                      /* prog  */
  YYSYMBOL_global_stmt = 94,               /* global_stmt  */
  YYSYMBOL_stmts = 95,                     /* stmts  */
  YYSYMBOL_stmt = 96,                      /* stmt  */
  YYSYMBOL_assignment_stmt = 97,           /* assignment_stmt  */
  YYSYMBOL_declaration_stmt = 98,          /* declaration_stmt  */
  YYSYMBOL_variable_declaration = 99,      /* variable_declaration  */
  YYSYMBOL_array_declaration = 100,        /* array_declaration  */
  YYSYMBOL_func_declaration = 101,         /* func_declaration  */
  YYSYMBOL_func_parameters_declaration = 102, /* func_parameters_declaration  */
  YYSYMBOL_struct_declaration = 103,       /* struct_declaration  */
  YYSYMBOL_union_declaration = 104,        /* union_declaration  */
  YYSYMBOL_data_struct_stmts = 105,        /* data_struct_stmts  */
  YYSYMBOL_enum_declaration = 106,         /* enum_declaration  */
  YYSYMBOL_enum_parameters = 107,          /* enum_parameters  */
  YYSYMBOL_typeDef_declaration = 108,      /* typeDef_declaration  */
  YYSYMBOL_instantiation_stmt = 109,       /* instantiation_stmt  */
  YYSYMBOL_struct_inst = 110,              /* struct_inst  */
  YYSYMBOL_union_inst = 111,               /* union_inst  */
  YYSYMBOL_func_inst = 112,                /* func_inst  */
  YYSYMBOL_func_inst_parameters = 113,     /* func_inst_parameters  */
  YYSYMBOL_expr = 114,                     /* expr  */
  YYSYMBOL_term = 115,                     /* term  */
  YYSYMBOL_operand = 116,                  /* operand  */
  YYSYMBOL_factor = 117,                   /* factor  */
  YYSYMBOL_op = 118,                       /* op  */
  YYSYMBOL_prio_op = 119,                  /* prio_op  */
  YYSYMBOL_unary_op = 120,                 /* unary_op  */
  YYSYMBOL_comp_op = 121,                  /* comp_op  */
  YYSYMBOL_logical_op = 122,               /* logical_op  */
  YYSYMBOL_bitwise_op = 123,               /* bitwise_op  */
  YYSYMBOL_assign_op = 124,                /* assign_op  */
  YYSYMBOL_compound_stmt = 125,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 126,                  /* if_stmt  */
  YYSYMBOL_elseif_stmt = 127,              /* elseif_stmt  */
  YYSYMBOL_else_stmt = 128,                /* else_stmt  */
  YYSYMBOL_do_while_stmt = 129,            /* do_while_stmt  */
  YYSYMBOL_while_stmt = 130,               /* while_stmt  */
  YYSYMBOL_for_stmt = 131,                 /* for_stmt  */
  YYSYMBOL_condition = 132,                /* condition  */
  YYSYMBOL_switch_case = 133,              /* switch_case  */
  YYSYMBOL_case_list = 134,                /* case_list  */
  YYSYMBOL_case = 135,                     /* case  */
  YYSYMBOL_case_default = 136,             /* case_default  */
  YYSYMBOL_return_stmt = 137,              /* return_stmt  */
  YYSYMBOL_goto_stmt = 138,                /* goto_stmt  */
  YYSYMBOL_size_of_stmt = 139,             /* size_of_stmt  */
  YYSYMBOL_label = 140,                    /* label  */
  YYSYMBOL_endfile = 141,                  /* endfile  */
  YYSYMBOL_type = 142,                     /* type  */
  YYSYMBOL_special_type = 143,             /* special_type  */
  YYSYMBOL_prefixes = 144,                 /* prefixes  */
  YYSYMBOL_prefix = 145,                   /* prefix  */
  YYSYMBOL_type_cast = 146                 /* type_cast  */
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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  335

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   345


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
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    48,    48,    51,    52,    64,    72,    73,    74,    78,
      79,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   103,   104,   105,   106,   107,
     113,   114,   115,   116,   117,   118,   122,   123,   127,   128,
     132,   140,   143,   144,   145,   146,   150,   153,   156,   157,
     158,   159,   160,   163,   166,   167,   168,   172,   173,   174,
     175,   176,   177,   178,   184,   185,   186,   189,   195,   198,
     201,   202,   203,   204,   210,   211,   212,   213,   214,   217,
     218,   221,   222,   223,   224,   225,   228,   229,   234,   239,
     244,   245,   251,   252,   253,   254,   257,   258,   259,   262,
     263,   266,   267,   268,   269,   270,   271,   274,   275,   278,
     279,   280,   281,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   300,   305,   309,   315,   322,   329,
     336,   343,   349,   358,   366,   374,   380,   388,   389,   393,
     394,   398,   399,   400,   401,   404,   405,   408,   411,   415,
     419,   421,   422,   423,   426,   428,   434,   435,   436,   437,
     438,   441,   442,   443,   444,   448,   449,   450,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   465
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ENDFILE", "ERROR",
  "IF", "ELSEIF", "ELSE", "DO", "WHILE", "FOR", "SWITCH", "CASE",
  "DEFAULT", "RETURN", "BREAK", "INT", "FLOAT", "DOUBLE", "CHAR", "VOID",
  "STRUCT", "TYPEDEF", "CONTINUE", "EXTERN", "GOTO", "LONG", "ENUM",
  "REGISTER", "SHORT", "SIZEOF", "STATIC", "SIGNED", "UNION", "UNSIGNED",
  "VOLATILE", "NUM", "ID", "FNUM", "ASSIGN", "PLUS", "MINUS", "TIMES",
  "OVER", "PERCENT", "LPAREN", "RPAREN", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_BRACKET", "RIGHT_BRACKET", "TERNARY", "SEMI", "COLON", "COMMA",
  "INCREMENT", "DECREMENT", "BITWISE_AND", "BITWISE_OR", "BITWISE_NOT",
  "BITWISE_XOR", "LOGICAL_NOT", "LOGICAL_AND", "LOGICAL_OR", "EQUAL",
  "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_THAN_OR_EQUAL",
  "GREATER_THAN_OR_EQUAL", "RIGHT_SHIFT", "LEFT_SHIFT", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "LEFT_SHIFT_ASSIGN", "RIGHT_SHIFT_ASSIGN",
  "BITWISE_AND_ASSIGN", "BITWISE_OR_ASSIGN", "BITWISE_XOR_ASSIGN",
  "MULTIPLY_ASSIGN", "DIVIDE_ASSIGN", "MODULUS_ASSIGN", "CARDINAL",
  "ARROW", "DEFINE", "CONSTANT", "POINTER", "ADDRESS_OF", "OTHER", "DOT",
  "QUOTE", "$accept", "Final", "prog", "global_stmt", "stmts", "stmt",
  "assignment_stmt", "declaration_stmt", "variable_declaration",
  "array_declaration", "func_declaration", "func_parameters_declaration",
  "struct_declaration", "union_declaration", "data_struct_stmts",
  "enum_declaration", "enum_parameters", "typeDef_declaration",
  "instantiation_stmt", "struct_inst", "union_inst", "func_inst",
  "func_inst_parameters", "expr", "term", "operand", "factor", "op",
  "prio_op", "unary_op", "comp_op", "logical_op", "bitwise_op",
  "assign_op", "compound_stmt", "if_stmt", "elseif_stmt", "else_stmt",
  "do_while_stmt", "while_stmt", "for_stmt", "condition", "switch_case",
  "case_list", "case", "case_default", "return_stmt", "goto_stmt",
  "size_of_stmt", "label", "endfile", "type", "special_type", "prefixes",
  "prefix", "type_cast", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-198)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     838,   -31,  1164,  -198,  -198,   -24,  -198,  -198,  -198,  -198,
       4,  -198,  -198,    28,  -198,    44,   333,  -198,     3,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,    66,  -198,  -198,  -198,
     822,  -198,    -9,  -198,  -198,  -198,  -198,  -198,    15,    39,
      48,    54,    82,    90,    92,    84,    53,  1157,  -198,  -198,
    -198,  -198,  -198,  -198,    95,  -198,  -198,   951,    87,   951,
     103,   100,   951,  -198,  -198,  -198,  -198,   103,  -198,   951,
    -198,    97,  -198,    28,  -198,  1013,  -198,  -198,   124,  -198,
     -34,  1321,   113,  -198,    46,   124,  -198,   124,  1095,   122,
     129,   116,   121,   855,   884,  -198,   -22,   915,    -8,   933,
     277,  1163,   131,   574,  -198,  -198,   574,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,   574,   574,   574,   574,  -198,  -198,  -198,
     574,  -198,  -198,  -198,  -198,    25,   574,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,   574,  -198,  -198,
    -198,   123,   128,   144,   145,   146,   147,  -198,  -198,  -198,
    -198,  -198,  -198,   150,   157,   154,  -198,  -198,  1321,   113,
     113,   113,   113,  -198,  -198,  -198,   -29,   822,  1195,  1321,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   159,    -4,
     117,   156,   267,  -198,   415,  -198,  -198,  -198,   267,   160,
     161,   660,   165,   167,   168,   574,   152,   162,   179,  1037,
    -198,   464,  -198,   166,   169,   171,   182,  -198,  -198,   174,
    -198,  -198,  -198,   180,  -198,  -198,   822,   574,   979,   703,
     979,   967,  1009,  1321,  -198,  -198,   185,   574,  -198,  -198,
     372,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   197,
    1227,  1052,  -198,  1321,   134,   193,   196,   198,   190,   191,
      63,  1242,  -198,  1274,   574,  1321,   819,  -198,    52,   513,
    1105,   562,   979,   979,   199,   201,   267,  1306,  -198,   366,
    1043,  -198,   660,   204,   206,   238,   238,   574,  -198,   214,
     660,   255,  -198,  1163,   216,   979,   979,   227,     2,  -198,
      10,  1321,   979,   660,   220,  -198,   222,   224,   213,   219,
    -198,  -198,   225,  -198,   228,   234,   979,   660,   660,   660,
     660,  -198,  -198,   660,   235,   660,   660,   746,   789,   617,
     660,   152,   152,  -198,   660
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     165,     0,     0,   168,   169,     0,   175,   170,   171,   172,
       0,   173,   174,     0,   176,     0,   165,     5,     0,    30,
      31,     6,    32,    34,    33,    35,     0,    64,    65,    66,
       0,   167,     0,   156,   157,   158,   159,   160,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     1,   155,
       4,     3,     7,     8,     0,   166,    67,    48,     0,    48,
      54,     0,    48,    61,    59,    57,    63,    54,    68,    48,
      73,     0,    87,    88,    89,     0,    99,   100,     0,    90,
       0,    72,    78,    80,    85,     0,    91,     0,    36,     0,
       0,     0,     0,   165,   165,    56,     0,   165,     0,   165,
       0,     0,     0,     0,    84,    69,     0,    92,    93,   109,
     111,   110,   112,   107,   108,   105,   106,   104,   101,   102,
     103,    94,    95,     0,     0,     0,     0,    96,    97,    98,
       0,    82,    81,    83,   113,   165,     0,   114,   115,   117,
     118,   119,   120,   121,   122,   123,   116,     0,    51,    52,
      46,     0,     0,     0,     0,     0,     0,    53,    47,   161,
     162,   163,   164,     0,     0,     0,    86,   177,    71,    74,
      75,    77,    76,    79,    45,    44,     0,     0,     0,    37,
      49,    50,    62,    58,    55,    60,   151,   152,     0,     0,
     165,     0,    38,   153,   165,    41,    40,    43,    36,     0,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   165,    10,     0,     0,     0,     0,    22,    13,     0,
      15,    14,    16,     0,    11,    12,     0,     0,     0,   165,
       0,   165,     0,   149,    24,    23,     0,     0,   154,    27,
       0,   124,     9,    20,    19,    21,    26,    17,    18,     0,
       0,    88,   140,   139,     0,     0,     0,     0,     0,     0,
      88,     0,   150,     0,     0,    25,    36,    39,    88,   165,
       0,   165,     0,     0,     0,     0,     0,     0,   129,   126,
       0,   136,   135,     0,     0,     0,     0,     0,    28,     0,
     165,   127,   128,     0,     0,     0,     0,     0,     0,   146,
       0,    29,     0,   133,     0,   134,     0,     0,     0,     0,
     141,   145,     0,   143,     0,     0,     0,   165,   165,   165,
     165,   142,   144,   165,     0,   138,   137,   165,   165,   131,
     165,   147,   148,   132,   130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,  -198,   268,  -197,  -190,     5,   158,  -125,  -198,
      31,  -198,   281,   284,   -32,   285,   221,  -198,     8,  -198,
    -198,     0,  -198,   -40,   -56,   172,   -76,  -198,  -198,   -42,
    -198,  -198,  -198,  -173,   102,  -198,  -198,   -37,  -198,  -198,
    -198,    36,  -198,    19,  -184,   -11,  -198,  -198,  -198,  -198,
    -198,    -1,  -198,    18,   -27,  -198
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    15,    16,    17,   211,   212,   213,   214,    19,    20,
      92,   176,    22,    23,    93,    24,    96,    25,   215,    27,
      28,    79,    80,   253,    82,    83,    84,   123,   130,   216,
     124,   125,   126,   147,   217,   218,   291,   292,   219,   220,
     221,   257,   222,   298,   299,   312,   223,   224,    86,   225,
      51,   102,   165,   226,    31,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    44,   104,    55,   229,    85,    32,    81,    26,   132,
     175,   133,   105,    45,   297,   309,    29,   189,    30,   199,
     106,   242,   297,   309,    26,   190,   154,    94,    56,    54,
      97,    21,   155,    85,    30,   101,   240,    99,    57,   242,
     157,    46,   131,   194,    48,   174,   155,    21,   195,     3,
     310,     4,    58,     6,     7,    52,     8,     9,   313,    11,
      12,    85,    59,   101,    85,   197,   168,   169,   170,   171,
     172,   -42,   279,    47,   282,    30,    45,    30,   240,   -42,
      30,    85,    85,    85,    85,    61,    60,    30,    85,   242,
      68,    63,   242,   303,    85,    62,   178,    47,   -26,   164,
      69,    76,    77,   287,   -26,    85,   258,   179,    47,   274,
      14,    30,    30,   242,   311,    30,   311,    30,    53,    64,
     325,   326,   327,   328,   152,   152,   329,    65,   152,    66,
     152,    67,    88,   334,    57,   242,   242,   242,   242,   242,
      95,     3,   100,     4,   242,     6,     7,    69,     8,     9,
      55,    11,    12,   177,    71,   127,   128,   129,    18,    58,
      72,    73,    74,    85,    71,   233,    61,   239,   148,   103,
      72,   268,    74,   149,    18,   180,   191,   167,   132,   103,
     181,   182,   183,   184,   185,    85,   254,   250,   254,   254,
      85,   188,   261,   198,    29,    85,   186,   263,    85,    55,
     265,    29,    14,   187,   234,   193,   228,   227,   177,   239,
     230,    29,   231,   232,   235,    91,   236,    91,   243,   246,
      91,   244,    85,   245,   277,   249,   247,    91,   254,    29,
     254,   254,   248,   252,   266,   252,   252,   262,   254,   269,
     293,   270,   272,   273,   271,    85,   285,   301,   286,   177,
     297,   151,   151,   254,   254,   151,   295,   151,   296,   302,
     254,   304,   305,   308,   255,   316,   319,   259,   317,    29,
     318,    29,   320,   321,   254,   252,   322,   252,   252,    29,
     323,   330,    29,    41,    50,   252,    42,    43,    98,   314,
      29,   196,   333,    33,    34,    35,    36,    37,   159,   160,
     252,   252,   173,    29,   161,   300,   134,   252,   283,   284,
     162,     0,     0,     0,   163,     0,   294,    29,    29,    29,
      29,   252,     0,    29,     0,    29,    29,    29,    29,    29,
      29,   306,   307,    -2,    29,     0,    49,     0,   315,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,   324,     0,     1,     2,     0,     3,     0,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,     0,
      13,   200,   289,   290,   201,   202,   203,   204,     0,     0,
     205,   206,     0,     0,     0,     0,     0,     1,     2,   207,
       3,   208,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    71,   209,     0,     0,     0,     0,    72,    73,
      74,     0,     0,   194,     0,     0,     0,    75,    14,   264,
     200,    76,    77,   201,   202,   203,   204,    76,    77,   205,
     206,     0,     0,    78,     0,     0,     1,     2,   207,     3,
     208,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    14,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   194,   210,     0,     0,     0,     0,     0,   200,
      76,    77,   201,   202,   203,   204,     0,     0,   205,   206,
       0,     0,     0,     0,     0,     1,     2,   207,     3,   208,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      14,   209,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   194,   241,     0,     0,     0,     0,     0,   200,    76,
      77,   201,   202,   203,   204,     0,     0,   205,   206,     0,
       0,     0,     0,     0,     1,     2,   207,     3,   208,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    14,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     194,     0,     0,     0,     0,   278,     0,   200,    76,    77,
     201,   202,   203,   204,     0,     0,   205,   206,     0,     0,
       0,     0,     0,     1,     2,   207,     3,   208,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    14,   209,
       0,     0,     0,     0,    71,     0,     0,     0,     0,   194,
      72,    73,    74,     0,   281,     0,     0,    76,    77,    75,
       0,     0,   200,     0,   290,   201,   202,   203,   204,    76,
      77,   205,   206,     0,     0,    78,     0,     0,     1,     2,
     207,     3,   208,     4,     5,     6,     7,    14,     8,     9,
      10,    11,    12,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   194,   200,     0,     0,   201,   202,
     203,   204,    76,    77,   205,   206,     0,     0,     0,     0,
       0,     1,     2,   207,     3,   208,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,     0,   209,     0,     0,
       0,     0,    14,     0,     0,     0,     0,   194,   200,     0,
       0,   201,   256,   203,   204,    76,    77,   205,   206,     0,
       0,     0,     0,     0,     1,     2,   207,     3,   208,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,     0,
     209,     0,     0,     0,     0,    14,     0,     0,     0,     0,
     194,   200,     0,     0,   201,   202,   203,   204,    76,    77,
     205,   331,     0,     0,     0,     0,     0,     1,     2,   207,
       3,   208,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,     0,   209,     0,     0,     0,     0,    14,     0,
       0,     0,     0,   194,   200,     0,     0,   201,   202,   203,
     204,    76,    77,   205,   332,     0,     0,     0,     0,     0,
       1,     2,   207,     3,   208,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,   209,     0,     0,     0,
       0,    14,     0,     0,     0,     0,   194,     0,    33,    34,
      35,    36,    37,     0,    76,    77,     3,     0,     4,     0,
       6,     7,     0,     8,     9,     0,    11,    12,   134,     1,
       2,     0,     3,     0,     4,     5,     6,     7,   136,     8,
       9,    10,    11,    12,    14,    13,    89,     2,     0,     3,
       0,     4,     5,     6,     7,     0,     8,     9,    90,    11,
      12,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,     0,   150,     0,    89,     2,    14,     3,     0,
       4,     5,     6,     7,     0,     8,     9,    90,    11,    12,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,    89,     2,     0,     3,
      14,     4,     5,     6,     7,     0,     8,     9,    90,    11,
      12,     0,     0,     0,    89,     2,     0,     3,     0,     4,
       5,     6,     7,   156,     8,     9,    90,    11,    12,    14,
       0,     0,    89,     2,     0,     3,     0,     4,     5,     6,
       7,   158,     8,     9,    90,    11,    12,     0,     0,     0,
       0,     3,     0,     4,     0,     6,     7,    71,     8,     9,
      14,    11,    12,    72,   251,    74,     0,     0,     0,    71,
       0,     0,    75,     0,     0,    72,   251,    74,    14,     0,
       0,     0,    76,    77,    75,     0,     0,     0,    78,    33,
      34,    35,    36,    37,    76,    77,    14,     0,     0,    71,
      78,     0,     0,    71,     0,    72,   260,    74,     0,    72,
      73,    74,    14,     0,    75,     0,     0,     0,    75,    33,
      34,    35,    36,    37,    76,    77,     0,     0,    76,    77,
      78,     0,     0,    71,    78,     0,   134,     0,     0,    72,
     251,    74,    47,     0,     0,     0,   237,     0,    75,     0,
     238,   134,    76,    77,     0,     0,     0,    47,    76,    77,
       0,   237,     0,     0,    78,     0,     0,    76,    77,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,     0,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   134,    71,     0,     0,     0,     0,
     135,    72,   251,    74,   136,     0,     0,     0,     0,     0,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,    77,     0,     0,     0,     0,    78,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,    70,     0,     0,
      33,    34,    35,    36,    37,    38,     0,    71,     0,     0,
       0,    39,     0,    72,    73,    74,     0,    40,     0,     0,
       0,     0,    75,   107,   108,     0,     0,     0,     0,   166,
       0,     0,    76,    77,     0,     0,     0,     0,    78,     0,
     109,   110,   111,   112,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,   192,     0,     0,     0,     0,
       0,     0,   109,   110,   111,   112,     0,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   107,   108,     0,
       0,     0,     0,     0,     0,   267,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   275,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   109,
     110,   111,   112,     0,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,     0,     0,     0,
       0,   109,   110,   111,   112,     0,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   107,   108,     0,     0,
       0,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,     0,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   109,   110,
     111,   112,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122
};

static const yytype_int16 yycheck[] =
{
       0,     2,    78,    30,   201,    47,    37,    47,     0,    85,
     135,    87,    46,    37,    12,    13,    16,    46,     0,   192,
      54,   211,    12,    13,    16,    54,    48,    59,    37,    30,
      62,     0,    54,    75,    16,    75,   209,    69,    47,   229,
      48,    37,    84,    47,     0,    20,    54,    16,    52,    24,
      48,    26,    37,    28,    29,    52,    31,    32,    48,    34,
      35,   103,    47,   103,   106,   190,   106,   123,   124,   125,
     126,    46,   269,    45,   271,    57,    37,    59,   251,    54,
      62,   123,   124,   125,   126,    37,    47,    69,   130,   279,
      37,    37,   282,   290,   136,    47,   136,    45,    46,   100,
      47,    55,    56,   276,    52,   147,   231,   147,    45,    46,
      85,    93,    94,   303,   298,    97,   300,    99,    52,    37,
     317,   318,   319,   320,    93,    94,   323,    37,    97,    37,
      99,    47,    37,   330,    47,   325,   326,   327,   328,   329,
      37,    24,    45,    26,   334,    28,    29,    47,    31,    32,
     177,    34,    35,   135,    30,    42,    43,    44,     0,    37,
      36,    37,    38,   205,    30,   205,    37,   209,    52,    45,
      36,    37,    38,    52,    16,    52,   177,    46,   254,    45,
      52,    37,    37,    37,    37,   227,   228,   227,   230,   231,
     232,    37,   232,    37,   194,   237,    46,   237,   240,   226,
     240,   201,    85,    46,    52,    46,    45,    47,   190,   251,
      45,   211,    45,    45,    52,    57,    37,    59,    52,    37,
      62,    52,   264,    52,   264,   226,    52,    69,   270,   229,
     272,   273,    52,   228,    37,   230,   231,    52,   280,    46,
     280,    45,    52,    52,    46,   287,    47,   287,    47,   231,
      12,    93,    94,   295,   296,    97,    52,    99,    52,    45,
     302,     6,    46,    36,   228,    45,    53,   231,    46,   269,
      46,   271,    53,    48,   316,   270,    48,   272,   273,   279,
      46,    46,   282,     2,    16,   280,     2,     2,    67,   300,
     290,   189,   329,    16,    17,    18,    19,    20,    21,    22,
     295,   296,   130,   303,    27,   286,    39,   302,   272,   273,
      33,    -1,    -1,    -1,    37,    -1,   280,   317,   318,   319,
     320,   316,    -1,   323,    -1,   325,   326,   327,   328,   329,
     330,   295,   296,     0,   334,    -1,     3,    -1,   302,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,   316,    -1,    21,    22,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    -1,
      37,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    30,    37,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    47,    -1,    -1,    -1,    45,    85,    47,
       5,    55,    56,     8,     9,    10,    11,    55,    56,    14,
      15,    -1,    -1,    61,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    85,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,     5,
      55,    56,     8,     9,    10,    11,    -1,    -1,    14,    15,
      -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      85,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,     5,    55,
      56,     8,     9,    10,    11,    -1,    -1,    14,    15,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    85,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    52,    -1,     5,    55,    56,
       8,     9,    10,    11,    -1,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    85,    37,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    47,
      36,    37,    38,    -1,    52,    -1,    -1,    55,    56,    45,
      -1,    -1,     5,    -1,     7,     8,     9,    10,    11,    55,
      56,    14,    15,    -1,    -1,    61,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    85,    31,    32,
      33,    34,    35,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,     5,    -1,    -1,     8,     9,
      10,    11,    55,    56,    14,    15,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    -1,    37,    -1,    -1,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    47,     5,    -1,
      -1,     8,     9,    10,    11,    55,    56,    14,    15,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    -1,
      37,    -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      47,     5,    -1,    -1,     8,     9,    10,    11,    55,    56,
      14,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    -1,    37,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    47,     5,    -1,    -1,     8,     9,    10,
      11,    55,    56,    14,    15,    -1,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    -1,    37,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    47,    -1,    16,    17,
      18,    19,    20,    -1,    55,    56,    24,    -1,    26,    -1,
      28,    29,    -1,    31,    32,    -1,    34,    35,    39,    21,
      22,    -1,    24,    -1,    26,    27,    28,    29,    49,    31,
      32,    33,    34,    35,    85,    37,    21,    22,    -1,    24,
      -1,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    48,    -1,    21,    22,    85,    24,    -1,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    21,    22,    -1,    24,
      85,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    21,    22,    -1,    24,    -1,    26,
      27,    28,    29,    48,    31,    32,    33,    34,    35,    85,
      -1,    -1,    21,    22,    -1,    24,    -1,    26,    27,    28,
      29,    48,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    24,    -1,    26,    -1,    28,    29,    30,    31,    32,
      85,    34,    35,    36,    37,    38,    -1,    -1,    -1,    30,
      -1,    -1,    45,    -1,    -1,    36,    37,    38,    85,    -1,
      -1,    -1,    55,    56,    45,    -1,    -1,    -1,    61,    16,
      17,    18,    19,    20,    55,    56,    85,    -1,    -1,    30,
      61,    -1,    -1,    30,    -1,    36,    37,    38,    -1,    36,
      37,    38,    85,    -1,    45,    -1,    -1,    -1,    45,    16,
      17,    18,    19,    20,    55,    56,    -1,    -1,    55,    56,
      61,    -1,    -1,    30,    61,    -1,    39,    -1,    -1,    36,
      37,    38,    45,    -1,    -1,    -1,    49,    -1,    45,    -1,
      53,    39,    55,    56,    -1,    -1,    -1,    45,    55,    56,
      -1,    49,    -1,    -1,    61,    -1,    -1,    55,    56,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    39,    30,    -1,    -1,    -1,    -1,
      45,    36,    37,    38,    49,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    61,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    20,    -1,    -1,
      16,    17,    18,    19,    20,    21,    -1,    30,    -1,    -1,
      -1,    27,    -1,    36,    37,    38,    -1,    33,    -1,    -1,
      -1,    -1,    45,    40,    41,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    61,    -1,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    57,    58,    59,    60,    46,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    57,    58,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    57,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    22,    24,    26,    27,    28,    29,    31,    32,
      33,    34,    35,    37,    85,    92,    93,    94,    98,    99,
     100,   101,   103,   104,   106,   108,   109,   110,   111,   112,
     144,   145,    37,    16,    17,    18,    19,    20,    21,    27,
      33,   103,   104,   106,   142,    37,    37,    45,     0,     3,
      94,   141,    52,    52,   142,   145,    37,    47,    37,    47,
      47,    37,    47,    37,    37,    37,    37,    47,    37,    47,
      20,    30,    36,    37,    38,    45,    55,    56,    61,   112,
     113,   114,   115,   116,   117,   120,   139,   146,    37,    21,
      33,    98,   101,   105,   105,    37,   107,   105,   107,   105,
      45,   114,   142,    45,   117,    46,    54,    40,    41,    57,
      58,    59,    60,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,   118,   121,   122,   123,    42,    43,    44,
     119,   120,   117,   117,    39,    45,    49,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,   124,    52,    52,
      48,    98,   101,    48,    48,    54,    48,    48,    48,    21,
      22,    27,    33,    37,   142,   143,    46,    46,   114,   115,
     115,   115,   115,   116,    20,    99,   102,   144,   114,   114,
      52,    52,    37,    37,    37,    37,    46,    46,    37,    46,
      54,   142,    50,    46,    47,    52,   125,    99,    37,   124,
       5,     8,     9,    10,    11,    14,    15,    23,    25,    37,
      48,    95,    96,    97,    98,   109,   120,   125,   126,   129,
     130,   131,   133,   137,   138,   140,   144,    47,    45,    95,
      45,    45,    45,   114,    52,    52,    37,    49,    53,   120,
     124,    48,    96,    52,    52,    52,    37,    52,    52,   142,
     114,    37,    97,   114,   120,   132,     9,   132,    99,   132,
      37,   114,    52,   114,    47,   114,    37,    48,    37,    46,
      45,    46,    52,    52,    46,    46,    50,   114,    52,    95,
      45,    52,    95,   132,   132,    47,    47,   124,    48,     6,
       7,   127,   128,   114,   132,    52,    52,    12,   134,   135,
     134,   114,    45,    95,     6,    46,   132,   132,    36,    13,
      48,   135,   136,    48,   136,   132,    45,    46,    46,    53,
      53,    48,    48,    46,   132,    95,    95,    95,    95,    95,
      46,    15,    15,   128,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    93,    93,    94,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   104,   105,   105,
     105,   105,   105,   106,   107,   107,   107,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   110,   111,   112,
     113,   113,   113,   113,   114,   114,   114,   114,   114,   115,
     115,   116,   116,   116,   116,   116,   117,   117,   117,   117,
     117,   117,   118,   118,   118,   118,   119,   119,   119,   120,
     120,   121,   121,   121,   121,   121,   121,   122,   122,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   125,   125,   126,   126,   126,   126,
     127,   127,   127,   128,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   133,   134,   134,   135,   136,   137,
     138,   139,   139,   139,   140,   141,   142,   142,   142,   142,
     142,   143,   143,   143,   143,   144,   144,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   146
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     1,     2,     2,     3,     2,     2,     5,     6,
       1,     1,     1,     1,     1,     1,     3,     5,     6,    10,
       7,     7,     0,     3,     1,     1,     5,     5,     0,     3,
       3,     2,     2,     5,     0,     3,     1,     3,     6,     3,
       6,     3,     6,     3,     1,     1,     1,     3,     3,     4,
       0,     3,     1,     1,     3,     3,     3,     3,     1,     3,
       1,     2,     2,     2,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     5,     6,     6,     5,
       6,     5,     6,     2,     7,     5,     5,     9,     9,     1,
       1,     7,     8,     7,     8,     2,     1,     5,     4,     2,
       3,     4,     4,     5,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3
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
  case 2: /* Final: prog  */
#line 48 "Parser.y"
             {savedTree = yyvsp[0];}
#line 1681 "Parser.tab.c"
    break;

  case 4: /* prog: prog global_stmt  */
#line 53 "Parser.y"
        {            
          YYSTYPE t = yyvsp[-1];
          if (t != NULL)
          { 
            while (t->sibling != NULL)
               t = t->sibling;
            t->sibling = yyvsp[0];
            yyval = yyvsp[-1]; 
          }
            else yyval = yyvsp[0];
        }
#line 1697 "Parser.tab.c"
    break;

  case 5: /* prog: global_stmt  */
#line 64 "Parser.y"
                        { yyval = yyvsp[0]; }
#line 1703 "Parser.tab.c"
    break;

  case 6: /* global_stmt: func_declaration  */
#line 72 "Parser.y"
                                        { yyval = yyvsp[0]; }
#line 1709 "Parser.tab.c"
    break;

  case 7: /* global_stmt: declaration_stmt SEMI  */
#line 73 "Parser.y"
                                        { yyval = yyvsp[-1]; }
#line 1715 "Parser.tab.c"
    break;

  case 8: /* global_stmt: instantiation_stmt SEMI  */
#line 74 "Parser.y"
                                        { yyval = yyvsp[-1]; }
#line 1721 "Parser.tab.c"
    break;

  case 9: /* stmts: stmts stmt  */
#line 78 "Parser.y"
                   {yyval = yyvsp[-1]; }
#line 1727 "Parser.tab.c"
    break;

  case 10: /* stmts: stmt  */
#line 79 "Parser.y"
                   {yyval = yyvsp[0]; }
#line 1733 "Parser.tab.c"
    break;

  case 11: /* stmt: goto_stmt  */
#line 84 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1739 "Parser.tab.c"
    break;

  case 12: /* stmt: label  */
#line 85 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1745 "Parser.tab.c"
    break;

  case 13: /* stmt: if_stmt  */
#line 86 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1751 "Parser.tab.c"
    break;

  case 14: /* stmt: for_stmt  */
#line 87 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1757 "Parser.tab.c"
    break;

  case 15: /* stmt: while_stmt  */
#line 88 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1763 "Parser.tab.c"
    break;

  case 16: /* stmt: switch_case  */
#line 89 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1769 "Parser.tab.c"
    break;

  case 17: /* stmt: do_while_stmt SEMI  */
#line 90 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1775 "Parser.tab.c"
    break;

  case 18: /* stmt: return_stmt SEMI  */
#line 91 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1781 "Parser.tab.c"
    break;

  case 19: /* stmt: declaration_stmt SEMI  */
#line 92 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1787 "Parser.tab.c"
    break;

  case 20: /* stmt: assignment_stmt SEMI  */
#line 93 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1793 "Parser.tab.c"
    break;

  case 21: /* stmt: instantiation_stmt SEMI  */
#line 94 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1799 "Parser.tab.c"
    break;

  case 22: /* stmt: compound_stmt  */
#line 95 "Parser.y"
                                { yyval = yyvsp[0]; }
#line 1805 "Parser.tab.c"
    break;

  case 23: /* stmt: CONTINUE SEMI  */
#line 96 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1811 "Parser.tab.c"
    break;

  case 24: /* stmt: BREAK SEMI  */
#line 97 "Parser.y"
                                { yyval = yyvsp[-1]; }
#line 1817 "Parser.tab.c"
    break;

  case 40: /* func_declaration: prefixes type ID LPAREN func_parameters_declaration RPAREN compound_stmt  */
#line 133 "Parser.y"
                   {
                        yyval = newStmtNode(FuncDeclarationK);
                        yyval->child[0]=yyvsp[-6];    //prefixes
                        yyval->child[1]=yyvsp[-5];    //type
                        yyval->child[2]=yyvsp[-2];    //func_parameters_declaration
                        yyval->child[3]=yyvsp[0];    //compound_stmt
                    }
#line 1829 "Parser.tab.c"
    break;

  case 124: /* compound_stmt: LEFT_BRACE stmts RIGHT_BRACE  */
#line 301 "Parser.y"
                {
                yyval = newStmtNode(COMPOUNDK);
                yyval->child[0]=yyvsp[-1];    //condition
                }
#line 1838 "Parser.tab.c"
    break;

  case 125: /* compound_stmt: LEFT_BRACE RIGHT_BRACE  */
#line 305 "Parser.y"
                                        {yyval = NULL;}
#line 1844 "Parser.tab.c"
    break;

  case 126: /* if_stmt: IF LPAREN condition RPAREN stmts  */
#line 310 "Parser.y"
            {
                yyval = newStmtNode(IfK);
                yyval->child[0]=yyvsp[-2];    //condition
                yyval->child[1]=yyvsp[0];    //stmt
            }
#line 1854 "Parser.tab.c"
    break;

  case 127: /* if_stmt: IF LPAREN condition RPAREN stmts elseif_stmt  */
#line 316 "Parser.y"
            {
                yyval = newStmtNode(IfK);
                yyval->child[0]=yyvsp[-3];    //condition
                yyval->child[1]=yyvsp[-1];    //stmt
                yyval->child[2]=yyvsp[0];    //elseif_stmt
            }
#line 1865 "Parser.tab.c"
    break;

  case 128: /* if_stmt: IF LPAREN condition RPAREN stmts else_stmt  */
#line 323 "Parser.y"
            {
                yyval = newStmtNode(IfK);
                yyval->child[0]=yyvsp[-3];    //condition
                yyval->child[1]=yyvsp[-1];    //stmt
                yyval->child[2]=yyvsp[0];    //else_stmt
            }
#line 1876 "Parser.tab.c"
    break;

  case 129: /* if_stmt: IF LPAREN condition RPAREN SEMI  */
#line 330 "Parser.y"
            {
                yyval = newStmtNode(IfK);    
                yyval->child[0]=yyvsp[-2];    //condition
            }
#line 1885 "Parser.tab.c"
    break;

  case 130: /* elseif_stmt: elseif_stmt ELSEIF LPAREN condition RPAREN stmts  */
#line 337 "Parser.y"
            {
               // $$ = newStmtNode();
                yyval->child[0]=yyvsp[-5];    //elseif_stmt
                yyval->child[1]=yyvsp[-2];    //condition
                yyval->child[2]=yyvsp[0];    //stmt
            }
#line 1896 "Parser.tab.c"
    break;

  case 131: /* elseif_stmt: ELSEIF LPAREN condition RPAREN stmts  */
#line 344 "Parser.y"
            {
              //  $$ = newStmtNode();
                yyval->child[0]=yyvsp[-2];    //condition
                yyval->child[1]=yyvsp[0];    //stmt
            }
#line 1906 "Parser.tab.c"
    break;

  case 132: /* elseif_stmt: ELSEIF LPAREN condition RPAREN stmts else_stmt  */
#line 350 "Parser.y"
            {
                //$$ = newStmtNode();
                yyval->child[0]=yyvsp[-3];    //condition
                yyval->child[1]=yyvsp[-1];    //stmt
                yyval->child[2]=yyvsp[0];    //else_stmt
            }
#line 1917 "Parser.tab.c"
    break;

  case 133: /* else_stmt: ELSE stmts  */
#line 359 "Parser.y"
            {
                //$$ = newStmtNode();
                yyval->child[0]=yyvsp[0];    //stmt
            }
#line 1926 "Parser.tab.c"
    break;

  case 134: /* do_while_stmt: DO stmts WHILE LPAREN LPAREN condition RPAREN  */
#line 367 "Parser.y"
                {
                yyval = newStmtNode(DowhileK);
                yyval->child[0]=yyvsp[-5];    //stmt
                yyval->child[1]=yyvsp[-1];    //condition
                }
#line 1936 "Parser.tab.c"
    break;

  case 135: /* while_stmt: WHILE LPAREN condition RPAREN stmts  */
#line 375 "Parser.y"
            {
                yyval = newStmtNode(DowhileK);
                yyval->child[0]=yyvsp[-2];    //condition
                yyval->child[1]=yyvsp[0];    //compound_stmt
            }
#line 1946 "Parser.tab.c"
    break;

  case 136: /* while_stmt: WHILE LPAREN condition RPAREN SEMI  */
#line 381 "Parser.y"
            {
                yyval = newStmtNode(DowhileK);
                yyval->child[0]=yyvsp[-2];    //condition
            }
#line 1955 "Parser.tab.c"
    break;

  case 155: /* endfile: ENDFILE  */
#line 428 "Parser.y"
                                { printf("\nEnd of file\n");   printf("Numero de Linhas: %d\n", linenum);     return 0;}
#line 1961 "Parser.tab.c"
    break;


#line 1965 "Parser.tab.c"

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

#line 467 "Parser.y"


/*
*   Parser Functions
*/

// Error Handling Function:
// Returns line where syntax error was found
int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	//return 1;   
}

// Parse Function
TreeNode * parse(void){
	File_Init();
	yyparse();
    return savedTree;
}
