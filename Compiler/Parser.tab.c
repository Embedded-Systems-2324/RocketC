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

#include "globals.h"
#include "scanner.h"

int yylex();
int yyerror(char *s);

#line 79 "Parser.tab.c"

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
  YYSYMBOL_prog = 92,                      /* prog  */
  YYSYMBOL_global_stmt = 93,               /* global_stmt  */
  YYSYMBOL_stmts = 94,                     /* stmts  */
  YYSYMBOL_stmt = 95,                      /* stmt  */
  YYSYMBOL_assignment_stmt = 96,           /* assignment_stmt  */
  YYSYMBOL_declaration_stmt = 97,          /* declaration_stmt  */
  YYSYMBOL_variable_declaration = 98,      /* variable_declaration  */
  YYSYMBOL_array_declaration = 99,         /* array_declaration  */
  YYSYMBOL_func_declaration = 100,         /* func_declaration  */
  YYSYMBOL_func_parameters_declaration = 101, /* func_parameters_declaration  */
  YYSYMBOL_data_struct_stmts = 102,        /* data_struct_stmts  */
  YYSYMBOL_struct_declaration = 103,       /* struct_declaration  */
  YYSYMBOL_union_declaration = 104,        /* union_declaration  */
  YYSYMBOL_enum_declaration = 105,         /* enum_declaration  */
  YYSYMBOL_enum_parameters = 106,          /* enum_parameters  */
  YYSYMBOL_typeDef_declaration = 107,      /* typeDef_declaration  */
  YYSYMBOL_instantiation_stmt = 108,       /* instantiation_stmt  */
  YYSYMBOL_struct_inst = 109,              /* struct_inst  */
  YYSYMBOL_union_inst = 110,               /* union_inst  */
  YYSYMBOL_func_inst = 111,                /* func_inst  */
  YYSYMBOL_func_inst_parameters = 112,     /* func_inst_parameters  */
  YYSYMBOL_expr = 113,                     /* expr  */
  YYSYMBOL_term = 114,                     /* term  */
  YYSYMBOL_operand = 115,                  /* operand  */
  YYSYMBOL_factor = 116,                   /* factor  */
  YYSYMBOL_op = 117,                       /* op  */
  YYSYMBOL_prio_op = 118,                  /* prio_op  */
  YYSYMBOL_unary_op = 119,                 /* unary_op  */
  YYSYMBOL_comp_op = 120,                  /* comp_op  */
  YYSYMBOL_logical_op = 121,               /* logical_op  */
  YYSYMBOL_bitwise_op = 122,               /* bitwise_op  */
  YYSYMBOL_assign_op = 123,                /* assign_op  */
  YYSYMBOL_compound_stmt = 124,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 125,                  /* if_stmt  */
  YYSYMBOL_elseif_stmt = 126,              /* elseif_stmt  */
  YYSYMBOL_else_stmt = 127,                /* else_stmt  */
  YYSYMBOL_do_while_stmt = 128,            /* do_while_stmt  */
  YYSYMBOL_while_stmt = 129,               /* while_stmt  */
  YYSYMBOL_for_stmt = 130,                 /* for_stmt  */
  YYSYMBOL_condition = 131,                /* condition  */
  YYSYMBOL_return_stmt = 132,              /* return_stmt  */
  YYSYMBOL_goto_stmt = 133,                /* goto_stmt  */
  YYSYMBOL_label = 134,                    /* label  */
  YYSYMBOL_endfile = 135,                  /* endfile  */
  YYSYMBOL_type = 136,                     /* type  */
  YYSYMBOL_prefixes = 137,                 /* prefixes  */
  YYSYMBOL_prefix = 138,                   /* prefix  */
  YYSYMBOL_type_cast = 139                 /* type_cast  */
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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   988

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

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
       0,    51,    51,    52,    53,    61,    62,    63,    67,    68,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    90,    91,    92,    93,    94,   100,   101,   102,
     103,   104,   105,   109,   110,   114,   115,   119,   120,   123,
     124,   125,   126,   130,   131,   132,   133,   134,   137,   140,
     144,   147,   148,   149,   153,   154,   155,   156,   157,   158,
     159,   165,   166,   167,   170,   173,   176,   179,   180,   181,
     182,   188,   189,   190,   191,   192,   195,   196,   199,   200,
     201,   202,   203,   206,   207,   208,   209,   210,   216,   217,
     218,   219,   222,   223,   224,   227,   228,   231,   232,   233,
     234,   235,   236,   239,   240,   243,   244,   245,   246,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     265,   266,   270,   271,   272,   273,   274,   275,   276,   279,
     280,   281,   282,   283,   284,   287,   288,   292,   293,   296,
     297,   298,   302,   303,   304,   305,   309,   310,   333,   337,
     344,   346,   352,   353,   354,   355,   356,   366,   367,   368,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   383
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
  "QUOTE", "$accept", "prog", "global_stmt", "stmts", "stmt",
  "assignment_stmt", "declaration_stmt", "variable_declaration",
  "array_declaration", "func_declaration", "func_parameters_declaration",
  "data_struct_stmts", "struct_declaration", "union_declaration",
  "enum_declaration", "enum_parameters", "typeDef_declaration",
  "instantiation_stmt", "struct_inst", "union_inst", "func_inst",
  "func_inst_parameters", "expr", "term", "operand", "factor", "op",
  "prio_op", "unary_op", "comp_op", "logical_op", "bitwise_op",
  "assign_op", "compound_stmt", "if_stmt", "elseif_stmt", "else_stmt",
  "do_while_stmt", "while_stmt", "for_stmt", "condition", "return_stmt",
  "goto_stmt", "label", "endfile", "type", "prefixes", "prefix",
  "type_cast", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-240)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-40)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     486,    -6,   743,  -240,  -240,    16,  -240,  -240,  -240,  -240,
      31,  -240,  -240,    44,  -240,   208,  -240,    24,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,    42,  -240,  -240,  -240,   453,
    -240,   -20,  -240,  -240,  -240,  -240,  -240,   -14,   -12,     1,
      67,    69,    85,    87,    -1,    14,   768,  -240,  -240,  -240,
    -240,  -240,  -240,    90,  -240,  -240,   606,    66,   606,    91,
      86,   606,  -240,  -240,  -240,  -240,    91,  -240,   606,  -240,
    -240,    44,  -240,   668,  -240,  -240,    36,  -240,   -24,   917,
      76,  -240,    55,    36,    36,   676,    97,    99,    88,    94,
     508,   541,  -240,    47,   570,    54,   588,   774,    93,   160,
    -240,  -240,   160,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,   160,
     160,   160,   160,  -240,  -240,  -240,   160,  -240,  -240,  -240,
    -240,   470,   160,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,   160,  -240,  -240,  -240,    96,   101,   117,
     119,   120,   121,  -240,  -240,  -240,  -240,   917,    76,    76,
      76,    76,  -240,  -240,  -240,    12,   453,   806,   917,  -240,
    -240,  -240,  -240,  -240,  -240,    -3,     8,   123,   706,   336,
    -240,  -240,  -240,   706,   115,   118,   372,   130,   139,   160,
     136,   138,   154,   505,  -240,   408,  -240,   149,   151,   152,
     173,  -240,   161,  -240,  -240,   162,  -240,  -240,   453,   160,
     607,   203,   213,   607,   622,   917,  -240,  -240,   172,   160,
    -240,  -240,   634,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,   188,   838,   663,  -240,   917,    46,   180,   182,   186,
     187,   192,   194,  -240,   870,   160,   917,   719,  -240,    34,
     251,   193,   607,   300,   607,   607,   706,   902,  -240,    57,
      57,   607,   201,  -240,  -240,  -240,   196,   199,   160,  -240,
     204,   372,   246,  -240,   246,  -240,   209,  -240,   607,   607,
     917,   607,  -240,  -240,   212,  -240,   216,   217,   218,   607,
     372,   372,   372,   221,  -240,  -240,  -240,  -240,   247,   247,
     372,  -240,  -240,  -240,  -240
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     157,     0,     0,   160,   161,     0,   167,   162,   163,   164,
       0,   165,   166,     0,   168,   157,     4,     0,    27,    28,
       5,    29,    31,    30,    32,     0,    61,    62,    63,     0,
     159,     0,   152,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     1,   151,     3,
       2,     6,     7,     0,   158,    64,    43,     0,    43,    51,
       0,    43,    58,    56,    54,    60,    51,    65,    43,    70,
      84,    85,    86,     0,    95,    96,     0,    87,     0,    69,
      75,    77,    82,     0,     0,    33,     0,     0,     0,     0,
     157,   157,    53,     0,   157,     0,   157,     0,     0,     0,
      81,    66,     0,    88,    89,   105,   107,   106,   108,   103,
     104,   101,   102,   100,    97,    98,    99,    90,    91,     0,
       0,     0,     0,    92,    93,    94,     0,    79,    78,    80,
     109,   157,     0,   110,   111,   113,   114,   115,   116,   117,
     118,   119,   112,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,    50,    49,    83,   169,    68,    71,    72,
      74,    73,    76,    42,    41,     0,     0,     0,    34,    44,
      45,    59,    55,    52,    57,     0,   157,     0,    35,   157,
      38,    37,    40,    33,     0,     0,   157,     0,     0,     0,
       0,     0,     0,     0,   121,   157,     9,     0,     0,     0,
       0,    12,     0,    14,    13,     0,    10,    11,     0,     0,
       0,     0,     0,     0,   157,   148,    21,    20,     0,     0,
     150,    24,     0,   120,     8,    18,    17,    19,    23,    15,
      16,     0,     0,    85,   147,   146,     0,     0,     0,     0,
       0,     0,     0,   149,     0,     0,    22,    33,    36,    85,
     157,     0,     0,   157,     0,     0,     0,     0,   128,   125,
     122,     0,     0,   141,   140,   139,     0,     0,     0,    25,
       0,   157,   126,   127,   123,   124,     0,   137,     0,     0,
      26,     0,   135,   136,     0,   138,     0,     0,     0,     0,
     157,   157,   157,     0,   145,   144,   143,   142,   131,   133,
     157,   132,   134,   129,   130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -240,  -240,   243,  -240,   -98,  -175,     9,  -129,  -240,    41,
    -240,   -42,   266,   267,   268,   215,  -240,     3,  -240,  -240,
       0,  -240,   -45,    50,   163,   -71,  -240,  -240,   -72,  -240,
    -240,  -240,  -164,  -141,  -240,    27,  -239,  -240,  -240,  -240,
     197,  -240,  -240,  -240,  -240,   -23,  -124,   -21,  -240
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    15,    16,   195,   196,   234,   198,    18,    19,    89,
     165,    90,    21,    22,    23,    93,    24,   199,    26,    27,
      77,    78,   235,    80,    81,    82,   119,   126,    83,   120,
     121,   122,   143,   181,   201,   272,   273,   202,   203,   204,
     237,   205,   206,   207,    50,    43,    29,    30,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    79,   164,    25,   197,   100,    53,   166,    54,    17,
     127,   197,   128,   129,   184,    28,    91,    55,    25,    94,
     197,   275,   101,    57,    17,    44,    96,    56,    97,   222,
     102,    31,     3,    58,     4,    59,     6,     7,    60,     8,
       9,    20,    11,    12,   179,   212,    66,   182,    61,   180,
      98,    67,   166,    44,    97,   208,    20,   157,   175,   301,
     302,    68,   208,   270,   271,    88,   176,    88,    45,   222,
      88,   208,    70,    71,    72,   197,    51,    88,   197,    46,
     -23,    99,    70,   249,    72,   241,   -23,   167,   211,    46,
     166,    99,   268,    14,    52,   150,   197,   224,   168,   147,
     147,   151,   153,   147,    62,   147,    63,   200,   151,   260,
      74,    75,   265,    56,   200,   197,   197,   197,   123,   124,
     125,   221,    64,   200,    65,   197,   208,    85,    92,   208,
     283,   148,   148,    68,    57,   148,    60,   148,   236,   156,
     144,   236,   236,   177,   215,    54,   145,   208,   169,   295,
     297,   299,   259,   170,   171,   264,   172,   173,   174,   304,
     183,   221,   209,   210,   232,   128,   208,   208,   208,   158,
     159,   160,   161,   282,   244,   213,   208,   246,   200,    28,
     236,   200,   236,   236,   214,   231,    28,    54,   216,   236,
     217,   218,   294,   296,   298,    28,    70,    71,    72,   200,
     257,   225,   303,   226,   227,    73,   236,   236,    47,   236,
     228,    48,   238,   229,   230,    74,    75,   236,   200,   200,
     200,    76,   239,   280,   243,   247,   250,   251,   200,     1,
       2,   252,     3,   253,     4,     5,     6,     7,   261,     8,
       9,    10,    11,    12,   254,    13,   255,   277,   278,   281,
      28,   279,   284,    28,   271,   285,   185,   289,    49,   186,
     187,   188,   290,   291,   292,   189,   190,   300,    40,    41,
      42,    28,     1,     2,   191,     3,   192,     4,     5,     6,
       7,    95,     8,     9,    10,    11,    12,   274,   193,   162,
      28,    28,    28,    14,     0,     0,     0,     0,   179,     0,
      28,     0,     0,   258,     0,   185,    74,    75,   186,   187,
     188,     0,     0,     0,   189,   190,     0,     0,     0,     0,
       0,     1,     2,   191,     3,   192,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    14,   193,     0,     0,
       0,   185,     0,     0,   186,   187,   188,   179,     0,     0,
     189,   190,   263,     0,     0,    74,    75,     1,     2,   191,
       3,   192,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,     0,   193,     0,     0,     0,   185,     0,     0,
     186,   187,   188,     0,   194,    14,   189,   190,     0,     0,
       0,    74,    75,     1,     2,   191,     3,   192,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,     0,   193,
     240,   242,     0,   185,     0,     0,   186,   187,   188,   179,
       0,    14,   189,   190,     0,     0,     0,    74,    75,     1,
       2,   191,     3,   192,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,     0,   193,     0,     0,     0,   262,
       0,   266,   267,     0,     0,     0,   223,    14,   276,     0,
       0,     0,     0,    74,    75,     0,     0,     0,     0,    32,
      33,    34,    35,    36,     0,   286,   287,     3,   288,     4,
       0,     6,     7,     0,     8,     9,   293,    11,    12,     0,
     163,     0,     0,    14,     3,     0,     4,     0,     6,     7,
       0,     8,     9,     0,    11,    12,     0,     1,     2,     0,
       3,     0,     4,     5,     6,     7,   -39,     8,     9,    10,
      11,    12,     0,    13,   -39,     0,     0,     0,     0,    86,
       2,     0,     3,     0,     4,     5,     6,     7,    14,     8,
       9,    87,    11,    12,   130,     0,     0,     0,     0,     0,
      46,     0,     0,     0,   219,    14,   146,     0,   220,     0,
      74,    75,    86,     2,     0,     3,     0,     4,     5,     6,
       7,    14,     8,     9,    87,    11,    12,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,     0,   149,
       0,    86,     2,    14,     3,     0,     4,     5,     6,     7,
       0,     8,     9,    87,    11,    12,     0,     0,     0,    86,
       2,     0,     3,     0,     4,     5,     6,     7,   152,     8,
       9,    87,    11,    12,     0,     0,    14,    86,     2,     0,
       3,     0,     4,     5,     6,     7,   154,     8,     9,    87,
      11,    12,     0,    70,   233,    72,     3,     0,     4,     0,
       6,     7,    73,     8,     9,    14,    11,    12,    70,   233,
      72,     0,    74,    75,     0,     0,     0,    73,    76,     0,
      70,    71,    72,    14,     0,     0,     0,    74,    75,    73,
       0,   245,     0,    76,    32,    33,    34,    35,    36,    74,
      75,    14,     0,     0,     0,    76,     0,     0,     0,     0,
       0,     0,   130,     0,    70,    71,    72,    14,    46,     0,
       0,     0,   219,    73,     0,   130,     0,     0,    74,    75,
       0,   131,     0,    74,    75,   132,     0,     0,     0,    76,
       0,     0,     0,     0,     0,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   130,     0,     0,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   130,    32,
      33,    34,    35,    36,    37,     0,     0,     0,   132,     0,
      38,     0,     0,     0,     0,     0,    39,     0,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    69,     0,
       0,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,     0,     0,     0,    70,    71,    72,     0,     0,     0,
       0,     0,     0,    73,   103,   104,     0,     0,     0,     0,
     155,     0,     0,    74,    75,     0,     0,     0,     0,    76,
       0,   105,   106,   107,   108,     0,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,   178,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,     0,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   103,   104,
       0,     0,     0,     0,     0,     0,   248,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,     0,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
     256,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   103,   104,     0,     0,     0,     0,     0,     0,
     269,     0,     0,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,     0,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   105,   106,   107,   108,     0,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118
};

static const yytype_int16 yycheck[] =
{
       0,    46,   131,     0,   179,    76,    29,   131,    29,     0,
      82,   186,    83,    84,   178,    15,    58,    37,    15,    61,
     195,   260,    46,    37,    15,    37,    68,    47,    73,   193,
      54,    37,    24,    47,    26,    47,    28,    29,    37,    31,
      32,     0,    34,    35,    47,   186,    47,   176,    47,    52,
      73,    37,   176,    37,    99,   179,    15,   102,    46,   298,
     299,    47,   186,     6,     7,    56,    54,    58,    37,   233,
      61,   195,    36,    37,    38,   250,    52,    68,   253,    45,
      46,    45,    36,    37,    38,   214,    52,   132,   186,    45,
     214,    45,   256,    85,    52,    48,   271,   195,   143,    90,
      91,    54,    48,    94,    37,    96,    37,   179,    54,   250,
      55,    56,   253,    47,   186,   290,   291,   292,    42,    43,
      44,   193,    37,   195,    37,   300,   250,    37,    37,   253,
     271,    90,    91,    47,    37,    94,    37,    96,   210,    46,
      52,   213,   214,   166,   189,   166,    52,   271,    52,   290,
     291,   292,   250,    52,    37,   253,    37,    37,    37,   300,
      37,   233,    47,    45,   209,   236,   290,   291,   292,   119,
     120,   121,   122,   271,   219,    45,   300,   222,   250,   179,
     252,   253,   254,   255,    45,   208,   186,   208,    52,   261,
      52,    37,   290,   291,   292,   195,    36,    37,    38,   271,
     245,    52,   300,    52,    52,    45,   278,   279,     0,   281,
      37,     3,     9,    52,    52,    55,    56,   289,   290,   291,
     292,    61,     9,   268,    52,    37,    46,    45,   300,    21,
      22,    45,    24,    46,    26,    27,    28,    29,    45,    31,
      32,    33,    34,    35,    52,    37,    52,    46,    52,    45,
     250,    52,     6,   253,     7,    46,     5,    45,    15,     8,
       9,    10,    46,    46,    46,    14,    15,    46,     2,     2,
       2,   271,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    66,    31,    32,    33,    34,    35,   260,    37,   126,
     290,   291,   292,    85,    -1,    -1,    -1,    -1,    47,    -1,
     300,    -1,    -1,    52,    -1,     5,    55,    56,     8,     9,
      10,    -1,    -1,    -1,    14,    15,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    85,    37,    -1,    -1,
      -1,     5,    -1,    -1,     8,     9,    10,    47,    -1,    -1,
      14,    15,    52,    -1,    -1,    55,    56,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    -1,    37,    -1,    -1,    -1,     5,    -1,    -1,
       8,     9,    10,    -1,    48,    85,    14,    15,    -1,    -1,
      -1,    55,    56,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    -1,    37,
     213,   214,    -1,     5,    -1,    -1,     8,     9,    10,    47,
      -1,    85,    14,    15,    -1,    -1,    -1,    55,    56,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    -1,   252,
      -1,   254,   255,    -1,    -1,    -1,    48,    85,   261,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,   278,   279,    24,   281,    26,
      -1,    28,    29,    -1,    31,    32,   289,    34,    35,    -1,
      20,    -1,    -1,    85,    24,    -1,    26,    -1,    28,    29,
      -1,    31,    32,    -1,    34,    35,    -1,    21,    22,    -1,
      24,    -1,    26,    27,    28,    29,    46,    31,    32,    33,
      34,    35,    -1,    37,    54,    -1,    -1,    -1,    -1,    21,
      22,    -1,    24,    -1,    26,    27,    28,    29,    85,    31,
      32,    33,    34,    35,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    49,    85,    48,    -1,    53,    -1,
      55,    56,    21,    22,    -1,    24,    -1,    26,    27,    28,
      29,    85,    31,    32,    33,    34,    35,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    -1,    48,
      -1,    21,    22,    85,    24,    -1,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    -1,    -1,    -1,    21,
      22,    -1,    24,    -1,    26,    27,    28,    29,    48,    31,
      32,    33,    34,    35,    -1,    -1,    85,    21,    22,    -1,
      24,    -1,    26,    27,    28,    29,    48,    31,    32,    33,
      34,    35,    -1,    36,    37,    38,    24,    -1,    26,    -1,
      28,    29,    45,    31,    32,    85,    34,    35,    36,    37,
      38,    -1,    55,    56,    -1,    -1,    -1,    45,    61,    -1,
      36,    37,    38,    85,    -1,    -1,    -1,    55,    56,    45,
      -1,    47,    -1,    61,    16,    17,    18,    19,    20,    55,
      56,    85,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    36,    37,    38,    85,    45,    -1,
      -1,    -1,    49,    45,    -1,    39,    -1,    -1,    55,    56,
      -1,    45,    -1,    55,    56,    49,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    39,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    39,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    49,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    20,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    40,    41,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    61,
      -1,    57,    58,    59,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    57,    58,    59,    60,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    22,    24,    26,    27,    28,    29,    31,    32,
      33,    34,    35,    37,    85,    92,    93,    97,    98,    99,
     100,   103,   104,   105,   107,   108,   109,   110,   111,   137,
     138,    37,    16,    17,    18,    19,    20,    21,    27,    33,
     103,   104,   105,   136,    37,    37,    45,     0,     3,    93,
     135,    52,    52,   136,   138,    37,    47,    37,    47,    47,
      37,    47,    37,    37,    37,    37,    47,    37,    47,    20,
      36,    37,    38,    45,    55,    56,    61,   111,   112,   113,
     114,   115,   116,   119,   139,    37,    21,    33,    97,   100,
     102,   102,    37,   106,   102,   106,   102,   113,   136,    45,
     116,    46,    54,    40,    41,    57,    58,    59,    60,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,   117,
     120,   121,   122,    42,    43,    44,   118,   119,   116,   116,
      39,    45,    49,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   123,    52,    52,    48,    97,   100,    48,
      48,    54,    48,    48,    48,    46,    46,   113,   114,   114,
     114,   114,   115,    20,    98,   101,   137,   113,   113,    52,
      52,    37,    37,    37,    37,    46,    54,   136,    50,    47,
      52,   124,    98,    37,   123,     5,     8,     9,    10,    14,
      15,    23,    25,    37,    48,    94,    95,    96,    97,   108,
     119,   125,   128,   129,   130,   132,   133,   134,   137,    47,
      45,    95,   124,    45,    45,   113,    52,    52,    37,    49,
      53,   119,   123,    48,    95,    52,    52,    52,    37,    52,
      52,   136,   113,    37,    96,   113,   119,   131,     9,     9,
     131,    98,   131,    52,   113,    47,   113,    37,    48,    37,
      46,    45,    45,    46,    52,    52,    50,   113,    52,    95,
     124,    45,   131,    52,    95,   124,   131,   131,   123,    48,
       6,     7,   126,   127,   126,   127,   131,    46,    52,    52,
     113,    45,    95,   124,     6,    46,   131,   131,   131,    45,
      46,    46,    46,   131,    95,   124,    95,   124,    95,   124,
      46,   127,   127,    95,   124
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    98,    98,    99,    99,   100,   100,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   104,
     105,   106,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   108,   108,   108,   109,   110,   111,   112,   112,   112,
     112,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     115,   115,   115,   116,   116,   116,   116,   116,   117,   117,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   121,   121,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   130,   130,   131,   131,   132,   133,
     134,   135,   136,   136,   136,   136,   136,   137,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     5,     6,     1,     1,     1,
       1,     1,     1,     3,     5,     6,    10,     7,     7,     0,
       3,     1,     1,     0,     3,     3,     2,     2,     5,     5,
       5,     0,     3,     1,     3,     6,     3,     6,     3,     6,
       3,     1,     1,     1,     3,     3,     4,     0,     3,     1,
       1,     3,     3,     3,     3,     1,     3,     1,     2,     2,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     5,     6,     6,     5,     6,     6,     5,     6,
       6,     5,     6,     5,     6,     2,     2,     6,     7,     5,
       5,     5,     9,     9,     9,     9,     1,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3
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
  case 151: /* endfile: ENDFILE  */
#line 346 "Parser.y"
                                { printf("\nEnd of file\n");   printf("Numero de Linhas: %d\n", linenum);     return 0;}
#line 1568 "Parser.tab.c"
    break;


#line 1572 "Parser.tab.c"

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

#line 385 "Parser.y"


/*
*   Parser Functions
*/

// Error Handling Function:
// Returns line where syntax error was found
int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	return 1;
}

// Parse Function
void parse(void){
	File_Init();
	yyparse();
}
