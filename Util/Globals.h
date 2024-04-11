#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "Types.h"

#define FLAG_REGISTER (1 << 0)

#define NODE_BODY()                 \
    struct TreeNode* pRightChild;   \
    struct TreeNode* pLeftChild;    \
    struct TreeNode* pSibling;      \
    size_t lineNumber;              \
    NodeType_et nodeType            \

typedef enum
{
    OP_PLUS,
    OP_MINUS,
    OP_RIGHT_SHIFT,
    OP_LEFT_SHIFT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_REMAIN,
    OP_GREATER_THAN,
    OP_LESS_THAN_OR_EQUAL,
    OP_GREATER_THAN_OR_EQUAL,
    OP_LESS_THAN,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_LOGICAL_AND,
    OP_LOGICAL_OR,
    OP_BITWISE_AND,
    OP_BITWISE_NOT,
    OP_BITWISE_OR,
    OP_BITWISE_XOR,
    OP_ASSIGN,
    OP_PLUS_ASSIGN,
    OP_MINUS_ASSIGN,
    OP_MODULUS_ASSIGN,
    OP_LEFT_SHIFT_ASSIGN,
    OP_RIGHT_SHIFT_ASSIGN,
    OP_BITWISE_AND_ASSIGN,
    OP_BITWISE_OR_ASSIGN,
    OP_BITWISE_XOR_ASSIGN,
    OP_MULTIPLY_ASSIGN,
    OP_DIVIDE_ASSIGN,
    OP_SIZEOF
}OperatorType_et;

typedef enum
{
    TYPE_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE
}VarType_et;

typedef enum
{
    SIGN_SIGNED,
    SIGN_UNSIGNED
}SignQualifier_et;

typedef enum
{
    MOD_CONST,
    MOD_VOLATILE,
    MOD_NONE
}ModQualifier_et;

typedef enum
{
    VIS_STATIC,
    VIS_EXTERN,
    VIS_NONE
}VisQualifier_et;

typedef enum
{
    MISC_REG_QUAL,
}MiscData_et;

typedef enum
{
    RIGHT_PARENTHESIS,
    LEFT_PARENTHESIS,
    RIGHT_BRACE,
    LEFT_BRACE
}MiscTokens_et;

typedef enum
{
    NODE_PARAM_DESC,
    NODE_VAR_DECLARATION,
    NODE_FUNC_PROTOTYPE,
    NODE_EXPRESSION, 
    NODE_NUMBER
}NodeType_et;

typedef union
{
    double fVal;
    long int dVal;
    char* sVal;
}NodeData_ut;

typedef struct __attribute__((packed)) TreeNode
{
    NODE_BODY();
}TreeNode_st;

typedef struct __attribute__((packed)) TreeNodeVarDecl
{
    NODE_BODY();

    char* varId;
    uint8_t miscFlags;
    VarType_et varType;
    ModQualifier_et modQualifier;
    VisQualifier_et visQualifier;
    SignQualifier_et signQualifier;
}TreeNodeVarDecl_st;

typedef struct __attribute__((packed)) TreeNodeFuncPrototype
{
    NODE_BODY();

    char* funcId;
    uint8_t miscFlags;
    VarType_et returnType;
    VisQualifier_et visQualifier;
    SignQualifier_et signQualifier;
}TreeNodeFuncPrototype_st;

typedef struct __attribute__((packed)) TreeNodeParam
{
    NODE_BODY();

    char* paramId;
    VarType_et paramType;
    ModQualifier_et modQualifier;
}TreeNodeParam_st;

typedef struct __attribute__((packed)) TreeNodeExpression
{
    NODE_BODY();

    OperatorType_et opType;
}TreeNodeExpression_st;


typedef struct __attribute__((packed)) TreeNodeNumber
{
    NODE_BODY();

    VarType_et numberType;   //criar um enum numberTYpe???
                             //se sim, mudar tb na regra R_FACTOR
    union{
        long int dVal;
        double fVal;
    }number_u;
}TreeNodeNumber_st;



typedef union
{
    TreeNode_st* treeNode;
    NodeData_ut nodeData;
}ParserObject_ut;

#endif
