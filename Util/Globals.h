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
    NODE_STATEMENT,
    NODE_EXPRESSION
}NodeType_et;

typedef enum
{
    STMT_VAR_DECL,
    STMT_FUNC_IMPL,
    STMT_FUNC_PROTOTYPE
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

typedef union
{
    TreeNode_st* treeNode;
    
    union 
    {
        double fVal;
        long int dVal;
        char* sVal;
        char* sId;
    }tokenData;
}ParserObject_ut;

#endif
