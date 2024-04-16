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
    OP_PLUS,                    // 0
    OP_MINUS,                   // 1
    OP_RIGHT_SHIFT,             // 2
    OP_LEFT_SHIFT,              // 3
    OP_MULTIPLY,                // 4
    OP_DIVIDE,                  // 5
    OP_REMAIN,                  // 6
    OP_GREATER_THAN,            // 7
    OP_LESS_THAN_OR_EQUAL,      // 8
    OP_GREATER_THAN_OR_EQUAL,   // 9
    OP_LESS_THAN,               // 10
    OP_EQUAL,                   // 11
    OP_NOT_EQUAL,               // 12
    OP_LOGICAL_AND,             // 13
    OP_LOGICAL_OR,              // 14
    OP_LOGICAL_NOT,             // 15
    OP_BITWISE_AND,             // 16
    OP_BITWISE_NOT,             // 17
    OP_BITWISE_OR,              // 18
    OP_BITWISE_XOR,             // 19
    OP_ASSIGN,                  // 20
    OP_PLUS_ASSIGN,             // 21
    OP_MINUS_ASSIGN,            // 22
    OP_MODULUS_ASSIGN,          // 23
    OP_LEFT_SHIFT_ASSIGN,       // 24
    OP_RIGHT_SHIFT_ASSIGN,      // 25
    OP_BITWISE_AND_ASSIGN,      // 26
    OP_BITWISE_OR_ASSIGN,       // 27
    OP_BITWISE_XOR_ASSIGN,      // 28
    OP_MULTIPLY_ASSIGN,         // 29
    OP_DIVIDE_ASSIGN,           // 30
    OP_SIZEOF                   // 31
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
    NODE_PARAM,              // 0

    NODE_VAR_DECLARATION,    // 1
    NODE_VAR_NAME,           // 2
    NODE_MISC,               // 3
    NODE_VISIBILITY,         // 4
    NODE_MODIFIER,           // 5
    NODE_SIGN,               // 6
    NODE_TYPE,               // 7
    NODE_OPERATOR,            // 8
    NODE_TERNARY,            // 9
    NODE_ARRAY_INDEX,        // 10
    NODE_TYPE_CAST,          // 11
    NODE_IDENTIFIER,         // 12

    NODE_ASSIGN,     // 13
    NODE_FUNCTION,     // 14
    NODE_EXPRESSION,         // 15
    NODE_INTEGER,            // 16
    NODE_FLOAT,              // 17
    NODE_IF,                 // 18
    NODE_WHILE,              // 19
    NODE_DO_WHILE,           // 20
    NODE_FOR,                // 21
    NODE_RETURN,             // 22
    NODE_CONTINUE,           // 23
    NODE_BREAK,              // 24
    NODE_GOTO,               // 25
    NODE_SWITCH,             // 26
    NODE_CASE,               // 27
    NODE_DEFAULT,            // 28
    NODE_POINTER,            // 29   visto

    NODE_POST_DEC,           // 30
    NODE_PRE_DEC,            // 31
    NODE_POST_INC,           // 32
    NODE_PRE_INC,             // 33
    NODE_ARRAY
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