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
    QUAL_NONE,
    QUAL_STATIC,
    QUAL_EXTERN,
    QUAL_SIGNED,
    QUAL_UNSIGNED,
    QUAL_CONST,
    QUAL_VOLATILE,
    QUAL_REGISTER,
}QualifierType_et;

typedef enum
{
    TYPE_CHAR = 0x00,
    TYPE_SHORT = 0x01,
    TYPE_INT = 0x02,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE
}VarType_et;

typedef enum
{
    NODE_PROGRAM,
    NODE_GLOBAL_STATEMENT,
    NODE_IDENTIFIER,
    NODE_QUALIFIER,
    NODE_VAR_PREAMBLE,
    NODE_VAR_DECLARATION,
    NODE_TYPE,
    NODE_FUNC_PROTOTYPE,
    NODE_FUNC_DECLARATION,
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

typedef union
{
    TreeNode_st* treeNode;
    NodeData_ut nodeData;
}ParserObject_ut;

#endif
