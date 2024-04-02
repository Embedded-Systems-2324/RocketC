#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Types.h"

#define TREE_MAX_CHILD 5

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
    MOD_VOLATILE
}ModQualifier_et;

typedef enum
{
    VIS_STATIC,
    VIS_EXTERN,
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
    NODE_PROGRAM,
    NODE_GLOBAL_STATEMENT,
    NODE_IDENTIFIER,
    NODE_QUALIFIER,
    NODE_VAR_PREAMBLE,
    NODE_VAR_DECLARATION,
    NODE_ARR_DECLARATION,
    NODE_TYPE,
    NODE_MOD_QUAL,
    NODE_VIS_QUAL,
    NODE_SIGN_QUAL,
    NODE_MISC,
    NODE_FUNC_PROTOTYPE,
    NODE_FUNC_DECLARATION,
    NODE_WHILE,
    NODE_FOR,
    NODE_DO_WHILE,
    NODE_SIZEOF,
    NODE_SIZEOF_BODY
}NodeType_et;

typedef union
{
    double fVal;
    long int dVal;
    char* sVal;
}NodeData_ut;

typedef struct TreeNode
{
    struct TreeNode* child;
    struct TreeNode* sibling;

    size_t nofChild;
    size_t nofQualifiers;
    size_t lineNumber;

    NodeType_et nodeType;
    NodeData_ut nodeData;
}
TreeNode_st;


typedef struct TreeNodeFunc
{
    struct TreeNode* child;
    struct TreeNode* sibling;

    size_t nofChild;
    size_t nofQualifiers;
    size_t lineNumber;

    NodeType_et nodeType;
    NodeData_ut nodeData;
    VarType_et returnType;
}TreeNodeFunc_st;

typedef union
{
    TreeNode_st* treeNode;
    NodeData_ut nodeData;
}ParserObject_ut;

#endif
