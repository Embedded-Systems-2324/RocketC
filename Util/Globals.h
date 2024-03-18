#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TREE_MAX_CHILD 5

typedef enum
{
    TOKEN_YYEMPTY                   = -2,
    TOKEN_YYEOF                     = 0,                     /* "end of file"  */
    TOKEN_YYERROR                   = 256,                 /* error  */
    TOKEN_IF                        = 260,                      /* IF  */
    TOKEN_ELSEIF                    = 261,                  /* ELSEIF  */
    TOKEN_YYUNDEF                   = 257,                 /* "invalid token"  */
    TOKEN_EOF                       = 258,                     /* ENDFILE  */
    TOKEN_ERROR                     = 259,                   /* ERROR  */
    TOKEN_ELSE                      = 262,                    /* ELSE  */
    TOKEN_DO                        = 263,                      /* DO  */
    TOKEN_WHILE                     = 264,                   /* WHILE  */
    TOKEN_FOR                       = 265,                     /* FOR  */
    TOKEN_SWITCH                    = 266,                  /* SWITCH  */
    TOKEN_CASE                      = 267,                    /* CASE  */
    TOKEN_DEFAULT                   = 268,                 /* DEFAULT  */
    TOKEN_RETURN                    = 269,                  /* RETURN  */
    TOKEN_BREAK                     = 270,                   /* BREAK  */
    TOKEN_INT                       = 271,                     /* INT  */
    TOKEN_FLOAT                     = 272,                   /* FLOAT  */
    TOKEN_DOUBLE                    = 273,                  /* DOUBLE  */
    TOKEN_CHAR                      = 274,                    /* CHAR  */
    TOKEN_VOID                      = 275,                    /* VOID  */
    TOKEN_STRUCT                    = 276,                  /* STRUCT  */
    TOKEN_TYPEDEF                   = 277,                 /* TYPEDEF  */
    TOKEN_CONTINUE                  = 278,                /* CONTINUE  */
    TOKEN_EXTERN                    = 279,                  /* EXTERN  */
    TOKEN_GOTO                      = 280,                    /* GOTO  */
    TOKEN_LONG                      = 281,                    /* LONG  */
    TOKEN_ENUM                      = 282,                    /* ENUM  */
    TOKEN_REGISTER                  = 283,                /* REGISTER  */
    TOKEN_SHORT                     = 284,                   /* SHORT  */
    TOKEN_SIZEOF                    = 285,                  /* SIZEOF  */
    TOKEN_STATIC                    = 286,                  /* STATIC  */
    TOKEN_SIGNED                    = 287,                  /* SIGNED  */
    TOKEN_UNION                     = 288,                   /* UNION  */
    TOKEN_UNSIGNED                  = 289,                /* UNSIGNED  */
    TOKEN_VOLATILE                  = 290,                /* VOLATILE  */
    TOKEN_NUM                       = 291,                     /* NUM  */
    TOKEN_ID                        = 292,                      /* ID  */
    TOKEN_FNUM                      = 293,                    /* FNUM  */
    TOKEN_ASSIGN                    = 294,                  /* ASSIGN  */
    TOKEN_PLUS                      = 295,                    /* PLUS  */
    TOKEN_MINUS                     = 296,                   /* MINUS  */
    TOKEN_TIMES                     = 297,                   /* TIMES  */
    TOKEN_OVER                      = 298,                    /* OVER  */
    TOKEN_PERCENT                   = 299,                 /* PERCENT  */
    TOKEN_LPAREN                    = 300,                  /* LPAREN  */
    TOKEN_RPAREN                    = 301,                  /* RPAREN  */
    TOKEN_LEFT_BRACE                = 302,              /* LEFT_BRACE  */
    TOKEN_RIGHT_BRACE               = 303,             /* RIGHT_BRACE  */
    TOKEN_LEFT_BRACKET              = 304,            /* LEFT_BRACKET  */
    TOKEN_RIGHT_BRACKET             = 305,           /* RIGHT_BRACKET  */
    TOKEN_TERNARY                   = 306,                 /* TERNARY  */
    TOKEN_SEMI                      = 307,                    /* SEMI  */
    TOKEN_COLON                     = 308,                   /* COLON  */
    TOKEN_COMMA                     = 309,                   /* COMMA  */
    TOKEN_INCREMENT                 = 310,               /* INCREMENT  */
    TOKEN_DECREMENT                 = 311,               /* DECREMENT  */
    TOKEN_BITWISE_AND               = 312,             /* BITWISE_AND  */
    TOKEN_BITWISE_OR                = 313,              /* BITWISE_OR  */
    TOKEN_LOGICAL_AND               = 317,             /* LOGICAL_AND  */
    TOKEN_BITWISE_NOT               = 314,             /* BITWISE_NOT  */
    TOKEN_BITWISE_XOR               = 315,             /* BITWISE_XOR  */
    TOKEN_LOGICAL_NOT               = 316,             /* LOGICAL_NOT  */
    TOKEN_LOGICAL_OR                = 318,              /* LOGICAL_OR  */
    TOKEN_EQUAL                     = 319,                   /* EQUAL  */
    TOKEN_NOT_EQUAL                 = 320,               /* NOT_EQUAL  */
    TOKEN_LESS_THAN                 = 321,               /* LESS_THAN  */
    TOKEN_GREATER_THAN              = 322,            /* GREATER_THAN  */
    TOKEN_LESS_THAN_OR_EQUAL        = 323,      /* LESS_THAN_OR_EQUAL  */
    TOKEN_GREATER_THAN_OR_EQUAL     = 324,   /* GREATER_THAN_OR_EQUAL  */
    TOKEN_RIGHT_SHIFT               = 325,             /* RIGHT_SHIFT  */
    TOKEN_LEFT_SHIFT                = 326,              /* LEFT_SHIFT  */
    TOKEN_PLUS_ASSIGN               = 327,             /* PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN              = 328,            /* MINUS_ASSIGN  */
    TOKEN_LEFT_SHIFT_ASSIGN         = 329,       /* LEFT_SHIFT_ASSIGN  */
    TOKEN_RIGHT_SHIFT_ASSIGN        = 330,      /* RIGHT_SHIFT_ASSIGN  */
    TOKEN_BITWISE_AND_ASSIGN        = 331,      /* BITWISE_AND_ASSIGN  */
    TOKEN_BITWISE_OR_ASSIGN         = 332,       /* BITWISE_OR_ASSIGN  */
    TOKEN_BITWISE_XOR_ASSIGN        = 333,      /* BITWISE_XOR_ASSIGN  */
    TOKEN_MULTIPLY_ASSIGN           = 334,         /* MULTIPLY_ASSIGN  */
    TOKEN_DIVIDE_ASSIGN             = 335,           /* DIVIDE_ASSIGN  */
    TOKEN_MODULUS_ASSIGN            = 336,          /* MODULUS_ASSIGN  */
    TOKEN_CARDINAL                  = 337,                /* CARDINAL  */
    TOKEN_ARROW                     = 338,                   /* ARROW  */
    TOKEN_DEFINE                    = 339,                  /* DEFINE  */
    TOKEN_CONSTANT                  = 340,                /* CONSTANT  */
    TOKEN_POINTER                   = 341,                 /* POINTER  */
    TOKEN_ADDRESS_OF                = 342,              /* ADDRESS_OF  */
    TOKEN_OTHER                     = 343,                   /* OTHER  */
    TOKEN_DOT                       = 344,                     /* DOT  */
    TOKEN_QUOTE                     = 345,                   /* QUOTE  */
    TOKEN_STR                       = 346
}TokenType_et;

typedef enum
{
    NODE_STATEMENT,
    NODE_EXPRESSION
}NodeType_et;

typedef enum
{
    STMT_IF,
    STMT_FOR,
    STMT_GOTO,
    STMT_LABEL,
    STMT_WHILE,
    STMT_SWITCH,
    STMT_RETURN,
    STMT_CONTINUE,
    STMT_DO_WHILE,
    STMT_COMPOUND,
    STMT_ASSIGNMENT,
    STMT_INVOCATION,
    STMT_DECLARATION,
    STMT_FUNC_DECLARATION
}StatementType_et;

typedef enum
{
    EXP_CONST,
    EXP_OPERATOR,
    EXP_IDENTIFIER
}ExpressionType_et;

typedef struct TreeNode
{
    struct TreeNode* child[TREE_MAX_CHILD];
    struct TreeNode* sibling;

    size_t lineNumber;
    NodeType_et nodeType;

    union
    {
        StatementType_et statementType;
        ExpressionType_et expressionType;
    }nodeData;

    union
    {
        int val;
        char* name;
    }nodeAttributes;
}
TreeNode_st;

#endif
