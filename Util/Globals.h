#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TREE_MAX_CHILD 5

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
