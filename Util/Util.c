#include <errno.h>
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

int CreateNodeStatement(TreeNode_st** ppTreeNode, StatementType_et statementType)
{
    if (!ppTreeNode)
        return -EINVAL;

    *ppTreeNode = (TreeNode_st*) calloc(1, sizeof(TreeNode_st));
    if (!(*ppTreeNode))
    {
        LOG_ERROR("Failed to allocate memory!\n");
        return -ENOMEM;
    }

    (*ppTreeNode)->nodeData.statementType = statementType;
    (*ppTreeNode)->nodeType = NODE_STATEMENT;
    (*ppTreeNode)->lineNumber = getLineNumber();

    return 0;
}

int CreateNodeExpression(TreeNode_st** ppTreeNode, ExpressionType_et expressionType)
{
    if (!ppTreeNode)
        return -EINVAL;

    *ppTreeNode = (TreeNode_st*) calloc(1, sizeof(TreeNode_st));
    if (!(*ppTreeNode))
    {
        LOG_ERROR("Failed to allocate memory!\n");
        return -ENOMEM;
    }

    (*ppTreeNode)->nodeData.expressionType = expressionType;
    (*ppTreeNode)->nodeType = NODE_EXPRESSION;
    (*ppTreeNode)->lineNumber = getLineNumber();

    return 0;
}

int TreeLog(TreeNode_st* pTreeRoot)
{
    TreeNode_st* pCurrentNode = pTreeRoot;

    if (!pTreeRoot)
        return -EINVAL;

    while (pCurrentNode)
    {
        switch (pCurrentNode->nodeType)
        {
            case NODE_STATEMENT:
                switch (pCurrentNode->nodeData.statementType)
                {
                    case STMT_IF:
                        LOG_DEBUG("IF");
                        break;
                    case STMT_FOR:
                        LOG_DEBUG("FOR");
                        break;
                    case STMT_GOTO:
                        LOG_DEBUG("GOTO");
                        break;
                    case STMT_LABEL:
                        LOG_DEBUG("LABEL");
                        break;
                    case STMT_WHILE:
                        LOG_DEBUG("WHILE");
                        break;
                    case STMT_SWITCH:
                        LOG_DEBUG("SWITCH");
                        break;
                    case STMT_RETURN:
                        LOG_DEBUG("RETURN");
                        break;
                    case STMT_CONTINUE:
                        LOG_DEBUG("CONTINUE");
                        break;
                    case STMT_DO_WHILE:
                        LOG_DEBUG("DO_WHILE");
                        break;
                    case STMT_COMPOUND:
                        LOG_DEBUG("COMPOUND");
                        break;
                    case STMT_ASSIGNMENT:
                        LOG_DEBUG("ASSIGNMENT");
                        break;
                    case STMT_INVOCATION:
                        LOG_DEBUG("INVOCATION");
                        break;
                    case STMT_DECLARATION:
                        LOG_DEBUG("DECLARATION");
                        break;
                    case STMT_FUNC_DECLARATION:
                        LOG_DEBUG("FUNC_DECLARATION");
                        break;
                }
            case NODE_EXPRESSION:
                switch (pCurrentNode->nodeData.expressionType)
                {
                    case EXP_CONST:
                        LOG_DEBUG("CONST");
                        break;
                    case EXP_OPERATOR:
                        LOG_DEBUG("OPERATOR");
                        break;
                    case EXP_IDENTIFIER:
                        LOG_DEBUG("IDENTIFIER");
                        break;
                }
            default:
                LOG_ERROR("Received invalid node type!\n");
        }

        for (size_t i = 0; i < TREE_MAX_CHILD; ++i)
            (void)TreeLog(pCurrentNode->child[i]);

        pCurrentNode = pCurrentNode->sibling;
    }

    return 0;
}