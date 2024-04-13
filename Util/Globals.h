#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "Types.h"

#define FLAG_REGISTER 1

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
    RIGHT_PARENTHESIS,
    LEFT_PARENTHESIS,
    RIGHT_BRACE,
    LEFT_BRACE
}MiscTokens_et;

typedef enum
{
    NODE_PARAM,

    NODE_VAR_DECLARATION,
    NODE_VAR_NAME,
    NODE_MISC,
    NODE_VISIBILITY,
    NODE_MODIFIER,
    NODE_SIGN,
    NODE_TYPE,
    NODE_OP_TYPE,
    NODE_TERNARY,
    NODE_ARRAY_INDEX,
    NODE_TYPE_CAST,
    NODE_ID,

    NODE_VAR_ASSIGNMENT,
    NODE_FUNC_PROTOTYPE,
    NODE_EXPRESSION, 
    NODE_INTEGER,
    NODE_FLOAT,
    NODE_IF,
    NODE_WHILE,
    NODE_DO_WHILE,
    NODE_FOR,
    NODE_RETURN,
    NODE_CONTINUE, 
    NODE_BREAK,
    NODE_GOTO,
    NODE_SWITCH,
    NODE_CASE,
    NODE_DEFAULT,
    NODE_POINTER,

    NODE_POST_DEC,
    NODE_PRE_DEC,
    NODE_POST_INC,
    NODE_PRE_INC
}NodeType_et;

typedef union
{
    double fVal;
    long int dVal;
    char* sVal;
}NodeData_ut;


typedef struct TreeNode
{
    struct TreeNode* pChilds;
    struct TreeNode* pSibling;
    size_t childNumber;
    size_t lineNumber;

    NodeType_et nodeType;
    NodeData_ut nodeData;

}TreeNode_st;


typedef union
{
    TreeNode_st* treeNode;
    NodeData_ut nodeData;
}ParserObject_ut;

#endif