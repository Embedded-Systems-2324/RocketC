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
#line 1 "Step1/asm_parser.y"

#include "../Util/asm_globals.h"
#include "../Step1/asm_scanner.h"
#include "../Output/asm_parser.tab.h"
#include "../Util/statements_list.h"
#include "../Util/symbol_table.h"
#include "../Util/opcodes.h"
#include "../Util/asm_operations.h"
#include "../main.h"

int yylex();
int yyerror(char *str);

#define NULL_ARG    0


#line 88 "asm_parser.tab.c"

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

#include "asm_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ADD = 3,                        /* ADD  */
  YYSYMBOL_SUB = 4,                        /* SUB  */
  YYSYMBOL_OR = 5,                         /* OR  */
  YYSYMBOL_AND = 6,                        /* AND  */
  YYSYMBOL_NOT = 7,                        /* NOT  */
  YYSYMBOL_XOR = 8,                        /* XOR  */
  YYSYMBOL_CMP = 9,                        /* CMP  */
  YYSYMBOL_BRANCH = 10,                    /* BRANCH  */
  YYSYMBOL_JUMP = 11,                      /* JUMP  */
  YYSYMBOL_JUMP_LINK = 12,                 /* JUMP_LINK  */
  YYSYMBOL_MOVE = 13,                      /* MOVE  */
  YYSYMBOL_LOAD_DIRECT = 14,               /* LOAD_DIRECT  */
  YYSYMBOL_LOAD_IMMEDIATE = 15,            /* LOAD_IMMEDIATE  */
  YYSYMBOL_LOAD_INDEXED = 16,              /* LOAD_INDEXED  */
  YYSYMBOL_STORE_DIRECT = 17,              /* STORE_DIRECT  */
  YYSYMBOL_STORE_INDEXED = 18,             /* STORE_INDEXED  */
  YYSYMBOL_PUSH = 19,                      /* PUSH  */
  YYSYMBOL_POP = 20,                       /* POP  */
  YYSYMBOL_RETI = 21,                      /* RETI  */
  YYSYMBOL_HALT = 22,                      /* HALT  */
  YYSYMBOL_NOP = 23,                       /* NOP  */
  YYSYMBOL_NUMBER = 24,                    /* NUMBER  */
  YYSYMBOL_REG = 25,                       /* REG  */
  YYSYMBOL_IDENTIFIER = 26,                /* IDENTIFIER  */
  YYSYMBOL_ENDFILE = 27,                   /* ENDFILE  */
  YYSYMBOL_ERROR = 28,                     /* ERROR  */
  YYSYMBOL_COMMA = 29,                     /* COMMA  */
  YYSYMBOL_CARDINAL = 30,                  /* CARDINAL  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_DOLAR = 32,                     /* DOLAR  */
  YYSYMBOL_BYTE = 33,                      /* BYTE  */
  YYSYMBOL_WORD = 34,                      /* WORD  */
  YYSYMBOL_ALLOC = 35,                     /* ALLOC  */
  YYSYMBOL_ORG = 36,                       /* ORG  */
  YYSYMBOL_EQU = 37,                       /* EQU  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_prog = 39,                      /* prog  */
  YYSYMBOL_stmt = 40,                      /* stmt  */
  YYSYMBOL_add_stmt = 41,                  /* add_stmt  */
  YYSYMBOL_sub_stmt = 42,                  /* sub_stmt  */
  YYSYMBOL_or_stmt = 43,                   /* or_stmt  */
  YYSYMBOL_and_stmt = 44,                  /* and_stmt  */
  YYSYMBOL_xor_stmt = 45,                  /* xor_stmt  */
  YYSYMBOL_not_stmt = 46,                  /* not_stmt  */
  YYSYMBOL_cmp_stmt = 47,                  /* cmp_stmt  */
  YYSYMBOL_branch_stmt = 48,               /* branch_stmt  */
  YYSYMBOL_move_stmt = 49,                 /* move_stmt  */
  YYSYMBOL_jump_stmt = 50,                 /* jump_stmt  */
  YYSYMBOL_load_stmt = 51,                 /* load_stmt  */
  YYSYMBOL_store_stmt = 52,                /* store_stmt  */
  YYSYMBOL_push_stmt = 53,                 /* push_stmt  */
  YYSYMBOL_pop_stmt = 54,                  /* pop_stmt  */
  YYSYMBOL_reti_stmt = 55,                 /* reti_stmt  */
  YYSYMBOL_halt_stmt = 56,                 /* halt_stmt  */
  YYSYMBOL_nop_stmt = 57,                  /* nop_stmt  */
  YYSYMBOL_byte_stmt = 58,                 /* byte_stmt  */
  YYSYMBOL_word_stmt = 59,                 /* word_stmt  */
  YYSYMBOL_alloc_stmt = 60,                /* alloc_stmt  */
  YYSYMBOL_org_stmt = 61,                  /* org_stmt  */
  YYSYMBOL_equ_stmt = 62,                  /* equ_stmt  */
  YYSYMBOL_label = 63                      /* label  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    59,    60,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    91,    95,
     102,   106,   113,   117,   123,   127,   134,   138,   145,   149,
     156,   162,   172,   178,   182,   189,   194,   198,   205,   209,
     216,   222,   228,   233,   239,   245,   252,   259,   265,   271,
     284
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
  "\"end of file\"", "error", "\"invalid token\"", "ADD", "SUB", "OR",
  "AND", "NOT", "XOR", "CMP", "BRANCH", "JUMP", "JUMP_LINK", "MOVE",
  "LOAD_DIRECT", "LOAD_IMMEDIATE", "LOAD_INDEXED", "STORE_DIRECT",
  "STORE_INDEXED", "PUSH", "POP", "RETI", "HALT", "NOP", "NUMBER", "REG",
  "IDENTIFIER", "ENDFILE", "ERROR", "COMMA", "CARDINAL", "COLON", "DOLAR",
  "BYTE", "WORD", "ALLOC", "ORG", "EQU", "$accept", "prog", "stmt",
  "add_stmt", "sub_stmt", "or_stmt", "and_stmt", "xor_stmt", "not_stmt",
  "cmp_stmt", "branch_stmt", "move_stmt", "jump_stmt", "load_stmt",
  "store_stmt", "push_stmt", "pop_stmt", "reti_stmt", "halt_stmt",
  "nop_stmt", "byte_stmt", "word_stmt", "alloc_stmt", "org_stmt",
  "equ_stmt", "label", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-25)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,   -24,   -23,     3,     5,     6,     7,    38,    39,    41,
      51,    52,    56,    57,    58,    59,    60,    61,    62,   -25,
     -25,   -25,    -6,    36,    64,    63,    66,    65,     0,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,    67,    68,    69,    70,    71,    72,    73,
     -25,    74,    75,    76,    77,    78,    79,    80,    81,   -25,
     -25,   -25,   -25,   -25,    87,   -25,    83,   -25,   -25,   -25,
      88,    89,    90,    91,    -1,    92,    93,    94,    95,    96,
      97,    98,   100,    99,   101,   -25,   106,   102,   103,   104,
     105,   -25,   111,   107,   -25,   113,   109,   -25,   115,   116,
     112,   118,   114,   -25,    34,    37,    48,    49,   -25,    50,
     -25,   117,   -25,   -25,   119,   -25,   120,   -25,   121,   -25,
     122,   -25,   124,   -25,   127,   -25,   128,   129,   130,   131,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      53,    54,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,    10,     9,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    60,    55,    56,     0,    58,     0,     1,     2,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       0,    38,     0,     0,    40,     0,     0,    42,     0,     0,
       0,     0,     0,    59,     0,     0,     0,     0,    39,     0,
      43,     0,    45,    46,     0,    48,     0,    28,     0,    30,
       0,    32,     0,    34,     0,    36,     0,     0,     0,     0,
      29,    31,    33,    35,    37,    44,    47,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -25,   -25,   132,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      77,    53,    54,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   101,    71,    22,    78,    55,   102,
      56,    57,    58,    23,    24,    25,    26,    27,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   127,
      72,    22,   129,    59,   128,    60,    61,   130,    23,    24,
      25,    26,    27,   131,   133,   135,    62,    63,   132,   134,
     136,    64,    65,    66,    67,    68,    69,    70,    73,    74,
      75,    76,     0,     0,     0,     0,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   103,   104,     0,
     106,   107,     0,     0,   105,   110,   112,   108,   109,   111,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,   140,   141,   137,   142,   138,
     139,   143,   144,   145,   146,   147,     0,     0,     0,     0,
      79
};

static const yytype_int8 yycheck[] =
{
       0,    25,    25,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    25,    31,    26,    27,    25,    30,
      25,    25,    25,    33,    34,    35,    36,    37,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    25,
      24,    26,    25,    25,    30,    26,    25,    30,    33,    34,
      35,    36,    37,    25,    25,    25,    25,    25,    30,    30,
      30,    25,    25,    25,    25,    25,    25,    25,    24,    26,
      24,    26,    -1,    -1,    -1,    -1,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    24,    29,    25,    25,    25,    25,    25,    25,    -1,
      25,    25,    -1,    -1,    30,    25,    25,    30,    30,    30,
      24,    29,    29,    29,    29,    24,    29,    24,    29,    24,
      24,    29,    24,    29,    -1,    24,    24,    30,    24,    30,
      30,    24,    24,    24,    24,    24,    -1,    -1,    -1,    -1,
      28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    26,    33,    34,    35,    36,    37,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    25,    25,    25,    25,    25,    25,    25,
      26,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    31,    24,    24,    26,    24,    26,     0,    27,    40,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    24,    29,    25,    25,    25,
      25,    25,    30,    25,    25,    30,    25,    25,    30,    30,
      25,    30,    25,    24,    29,    29,    29,    29,    24,    29,
      24,    29,    24,    24,    29,    24,    29,    25,    30,    25,
      30,    25,    30,    25,    30,    25,    30,    30,    30,    30,
      24,    24,    24,    24,    24,    24,    24,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    39,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    41,    41,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    48,    49,    50,    50,    51,    51,    51,    52,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     7,
       6,     7,     6,     7,     6,     7,     6,     7,     4,     5,
       4,     2,     4,     5,     7,     5,     5,     7,     5,     7,
       2,     2,     1,     1,     1,     2,     2,     3,     2,     4,
       2
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
  case 28: /* add_stmt: ADD REG COMMA REG COMMA REG  */
#line 92 "Step1/asm_parser.y"
                    {  
                        add_statement(ADD_OP, ADD_OPCODE, yyvsp[-4], yyvsp[-2], yyvsp[0], NO_TYPE); 
                    }
#line 1235 "asm_parser.tab.c"
    break;

  case 29: /* add_stmt: ADD REG COMMA REG COMMA CARDINAL NUMBER  */
#line 96 "Step1/asm_parser.y"
                    {
                        add_statement(ADD_OP, ADD_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], IMMEDIATE); 
                    }
#line 1243 "asm_parser.tab.c"
    break;

  case 30: /* sub_stmt: SUB REG COMMA REG COMMA REG  */
#line 103 "Step1/asm_parser.y"
                    { 
                        add_statement(SUB_OP, SUB_OPCODE, yyvsp[-4], yyvsp[-2], yyvsp[0], NO_TYPE);  
                    }
#line 1251 "asm_parser.tab.c"
    break;

  case 31: /* sub_stmt: SUB REG COMMA REG COMMA CARDINAL NUMBER  */
#line 107 "Step1/asm_parser.y"
                    { 
                        add_statement(SUB_OP, SUB_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], IMMEDIATE); 
                    }
#line 1259 "asm_parser.tab.c"
    break;

  case 32: /* or_stmt: OR REG COMMA REG COMMA REG  */
#line 114 "Step1/asm_parser.y"
                    { 
                        add_statement(OR_OP, OR_OPCODE, yyvsp[-4], yyvsp[-2], yyvsp[0], NO_TYPE);    
                    }
#line 1267 "asm_parser.tab.c"
    break;

  case 33: /* or_stmt: OR REG COMMA REG COMMA CARDINAL NUMBER  */
#line 118 "Step1/asm_parser.y"
                    { 
                        add_statement(OR_OP, OR_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], IMMEDIATE);   
                    }
#line 1275 "asm_parser.tab.c"
    break;

  case 34: /* and_stmt: AND REG COMMA REG COMMA REG  */
#line 124 "Step1/asm_parser.y"
                    { 
                        add_statement(AND_OP, AND_OPCODE, yyvsp[-4], yyvsp[-2], yyvsp[0], NO_TYPE);  
                    }
#line 1283 "asm_parser.tab.c"
    break;

  case 35: /* and_stmt: AND REG COMMA REG COMMA CARDINAL NUMBER  */
#line 128 "Step1/asm_parser.y"
                    { 
                        add_statement(AND_OP, AND_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], IMMEDIATE); 
                    }
#line 1291 "asm_parser.tab.c"
    break;

  case 36: /* xor_stmt: XOR REG COMMA REG COMMA REG  */
#line 135 "Step1/asm_parser.y"
                    { 
                        add_statement(XOR_OP, XOR_OPCODE, yyvsp[-4], yyvsp[-2], yyvsp[0], NO_TYPE);  
                    }
#line 1299 "asm_parser.tab.c"
    break;

  case 37: /* xor_stmt: XOR REG COMMA REG COMMA CARDINAL NUMBER  */
#line 139 "Step1/asm_parser.y"
                    { 
                        add_statement(XOR_OP, XOR_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], IMMEDIATE); 
                    }
#line 1307 "asm_parser.tab.c"
    break;

  case 38: /* not_stmt: NOT REG COMMA REG  */
#line 146 "Step1/asm_parser.y"
                    { 
                        add_statement(NOT_OP, NOT_OPCODE, yyvsp[-2], yyvsp[0], NULL_ARG, NO_TYPE);   
                    }
#line 1315 "asm_parser.tab.c"
    break;

  case 39: /* not_stmt: NOT REG COMMA CARDINAL NUMBER  */
#line 150 "Step1/asm_parser.y"
                    { 
                        add_statement(NOT_OP, NOT_OPCODE, yyvsp[-3], yyvsp[0], NULL_ARG, IMMEDIATE); 
                    }
#line 1323 "asm_parser.tab.c"
    break;

  case 40: /* cmp_stmt: CMP REG COMMA REG  */
#line 157 "Step1/asm_parser.y"
                    { 
                        add_statement(CMP_OP, CMP_OPCODE, yyvsp[-2], yyvsp[0], NULL_ARG, NO_TYPE);
                    }
#line 1331 "asm_parser.tab.c"
    break;

  case 41: /* branch_stmt: BRANCH IDENTIFIER  */
#line 163 "Step1/asm_parser.y"
                    {
                        add_statement(BXX_OP, yylval, yyvsp[0], NULL_ARG, NULL_ARG, NO_TYPE); 
                    }
#line 1339 "asm_parser.tab.c"
    break;

  case 42: /* move_stmt: MOVE REG COMMA REG  */
#line 173 "Step1/asm_parser.y"
                    {
                        add_statement(ADD_OP, ADD_OPCODE, yyvsp[-2], yyvsp[0], 0, IMMEDIATE);
                    }
#line 1347 "asm_parser.tab.c"
    break;

  case 43: /* jump_stmt: JUMP REG COMMA CARDINAL NUMBER  */
#line 179 "Step1/asm_parser.y"
                    { 
                        add_statement(JMP_OP, JMP_OPCODE, yyvsp[-3], yyvsp[0], NULL_ARG, NO_TYPE); 
                    }
#line 1355 "asm_parser.tab.c"
    break;

  case 44: /* jump_stmt: JUMP_LINK REG COMMA REG COMMA CARDINAL NUMBER  */
#line 183 "Step1/asm_parser.y"
                    {
                        add_statement(JMP_OP, JMP_OPCODE, yyvsp[-5], yyvsp[-3] , yyvsp[0], LINK);
                    }
#line 1363 "asm_parser.tab.c"
    break;

  case 45: /* load_stmt: LOAD_DIRECT REG COMMA CARDINAL NUMBER  */
#line 190 "Step1/asm_parser.y"
                    { 
                        add_statement(LD_OP, LD_OPCODE, yyvsp[-3], NULL_ARG, yyvsp[0], NO_TYPE); 
                    }
#line 1371 "asm_parser.tab.c"
    break;

  case 46: /* load_stmt: LOAD_IMMEDIATE REG COMMA CARDINAL NUMBER  */
#line 195 "Step1/asm_parser.y"
                    {
                        add_statement(LDI_OP, LDI_OPCODE, yyvsp[-3], yyvsp[0], NULL_ARG, NO_TYPE); 
                    }
#line 1379 "asm_parser.tab.c"
    break;

  case 47: /* load_stmt: LOAD_INDEXED REG COMMA REG COMMA CARDINAL NUMBER  */
#line 199 "Step1/asm_parser.y"
                    { 
                        add_statement(LDX_OP, LDX_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], NO_TYPE); 
                    }
#line 1387 "asm_parser.tab.c"
    break;

  case 48: /* store_stmt: STORE_DIRECT REG COMMA CARDINAL NUMBER  */
#line 206 "Step1/asm_parser.y"
                    { 
                        add_statement(ST_OP,ST_OPCODE, yyvsp[-3], yyvsp[0], NULL_ARG, NO_TYPE); 
                    }
#line 1395 "asm_parser.tab.c"
    break;

  case 49: /* store_stmt: STORE_INDEXED REG COMMA REG COMMA CARDINAL NUMBER  */
#line 210 "Step1/asm_parser.y"
                    { 
                        add_statement(STX_OP, ST_OPCODE, yyvsp[-5], yyvsp[-3], yyvsp[0], NO_TYPE);
                    }
#line 1403 "asm_parser.tab.c"
    break;

  case 50: /* push_stmt: PUSH REG  */
#line 217 "Step1/asm_parser.y"
                    { 
                        add_statement(PUSH_OP,PUSH_OPCODE,yyvsp[0], NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1411 "asm_parser.tab.c"
    break;

  case 51: /* pop_stmt: POP REG  */
#line 223 "Step1/asm_parser.y"
                    { 
                        add_statement(POP_OP, POP_OPCODE,yyvsp[0], NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1419 "asm_parser.tab.c"
    break;

  case 52: /* reti_stmt: RETI  */
#line 229 "Step1/asm_parser.y"
                    {
                        add_statement(RETI_OP, RETI_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1427 "asm_parser.tab.c"
    break;

  case 53: /* halt_stmt: HALT  */
#line 234 "Step1/asm_parser.y"
                    { 
                        add_statement(HLT_OP, HLT_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1435 "asm_parser.tab.c"
    break;

  case 54: /* nop_stmt: NOP  */
#line 240 "Step1/asm_parser.y"
                    { 
                        add_statement(NOP_OP, NOP_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1443 "asm_parser.tab.c"
    break;

  case 55: /* byte_stmt: BYTE NUMBER  */
#line 246 "Step1/asm_parser.y"
                    { 
                        /*sym_table[$1].value = sym_table[$3].value; 
                        $$ = $1;*/
                    }
#line 1452 "asm_parser.tab.c"
    break;

  case 56: /* word_stmt: WORD NUMBER  */
#line 253 "Step1/asm_parser.y"
                    { 
                        /*sym_table[$1].value = sym_table[$3].value; 
                        $$ = $1;*/
                    }
#line 1461 "asm_parser.tab.c"
    break;

  case 57: /* alloc_stmt: ALLOC IDENTIFIER NUMBER  */
#line 260 "Step1/asm_parser.y"
                    {

                    }
#line 1469 "asm_parser.tab.c"
    break;

  case 58: /* org_stmt: ORG NUMBER  */
#line 266 "Step1/asm_parser.y"
                    {
                        add_statement(DOT_ORG_OP, DOT_ORG_OP, yyvsp[0], NULL_ARG, NULL_ARG, NO_TYPE);
                    }
#line 1477 "asm_parser.tab.c"
    break;

  case 59: /* equ_stmt: EQU IDENTIFIER COMMA NUMBER  */
#line 272 "Step1/asm_parser.y"
                    {
                         if(get_symbol_value(yyvsp[-3]) != UNINITIALIZED_VALUE){
                            printf("ERROR: Constant redefinition: %s in line %ld\n", get_symbol_name(yyvsp[-3]), get_line_number());
                        }
                        else{
                            set_symbol_value(yyvsp[-3], get_symbol_value(yyvsp[0]));
                            yyval = yyvsp[-3];
                        }
                    }
#line 1491 "asm_parser.tab.c"
    break;

  case 60: /* label: IDENTIFIER COLON  */
#line 285 "Step1/asm_parser.y"
                    { 
                        if(get_symbol_value(yyvsp[-1]) != UNINITIALIZED_VALUE){
                            printf("ERROR: Label redefinition: %s in line %ld\n", get_symbol_name(yyvsp[-1]), get_line_number());
                        }
                        else{
                            set_symbol_value(yyvsp[-1], get_location_counter());
                            yyval = yyvsp[-1];
                        }
                    }
#line 1505 "asm_parser.tab.c"
    break;


#line 1509 "asm_parser.tab.c"

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

#line 294 "Step1/asm_parser.y"



int yyerror(char *str)
{
  	fprintf (stderr, "%s in line number : %ld\n", str, get_line_number());
	return 1;
}
