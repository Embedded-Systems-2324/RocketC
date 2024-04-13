#include <errno.h>
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

static const char* nodeNameLut[] =
{
    "PROGRAM",
    "GLOBAL_STATEMENT",
    "IDENTIFIER",
    "QUALIFIER",
    "VAR_PREAMBLE",
    "VAR_DECLARATION",
    "ARR_DECLARATION",
    "TYPE",
    "MOD_QUAL",
    "VIS_QUAL",
    "SIGN_QUAL",
    "MISC",
    "FUNC_PROTOTYPE",
    "WHILE",
    "FOR",
    "DO_WHILE",
    "SIZEOF",
    "SIZEOF_BODY"
};

int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType)
{
    TreeNode_st* pNode;

    if (!ppNewNode)
        return -EINVAL;

    *ppNewNode = (TreeNode_st*) calloc(1, sizeof(TreeNode_st));

    if (!(*ppNewNode))
    {
        LOG_ERROR("Failed to allocate memory!\n");
        return -ENOMEM;
    }

    pNode = (TreeNode_st*) (*(ppNewNode));

    pNode->nodeType = nodeType;
    pNode->lineNumber = getLineNumber();

    return 0;
}


int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild)
{
    TreeNode_st* pTemp;

    if (!pParent || !pChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->pChilds, pParent->childNumber + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->pChilds = pTemp;
    memcpy(&pParent->pChilds[pParent->childNumber++], pChild, sizeof(TreeNode_st));
    free(pChild);

    return 0;
}


int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType)
{
    TreeNode_st* pTemp;

    if (!pParent || !ppNewChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->pChilds, pParent->childNumber + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->pChilds = pTemp;
    (*ppNewChild) = &pParent->pChilds[pParent->childNumber++];

    memset(*ppNewChild, 0, sizeof(TreeNode_st));
    (*ppNewChild)->nodeType = nodeType;
    (*ppNewChild)->lineNumber = getLineNumber();

    return 0;
}


int StringCreateAndCopy(char** ppDest, char* pSrc, size_t strLen)
{
    if (!ppDest || !pSrc)
        return -EINVAL;

    if (strLen == 0)
        strLen = strlen(pSrc);

    (*ppDest) = malloc(strLen * sizeof(char));
    if (!(*ppDest))
    {
        LOG_ERROR("Failed to allocate memory while trying to create a new string!\n");
        return -ENOMEM;
    }
    
    memcpy(*ppDest, pSrc, strLen);

    return 0;
}


/*void PrintNode(TreeNode_st* pNode, int depth)
{
    if (pNode == NULL)
    {
        LOG_ERROR("NULL Node!!\n");
    }
    for (int i = 0; i < depth; i++) 
    {
        LOG_DEBUG("    ");
    }

    switch (pNode->nodeType)
    {
        case NODE_PARAM_DESC:
            TreeNodeParam_st* cNode1 = (TreeNodeParam_st*)pNode;
            LOG_DEBUG("%d %d %s", &cNode1->modQualifier, &cNode1->paramType, &cNode1->paramId);
        case NODE_VAR_DECLARATION: 
            TreeNodeVarDecl_st* cNode2 = (TreeNodeVarDecl_st*)pNode;
            if(&cNode2->miscFlags != NULL)
            {
                LOG_DEBUG("%d ", &cNode2->miscFlags);
            }
            LOG_DEBUG("%d, %d, %d, %d, %d", &cNode2->visQualifier, &cNode2->modQualifier, &cNode2->signQualifier, &cNode2->varType, &cNode2->varId);
            break;
        case NODE_FUNC_PROTOTYPE:
            TreeNodeFuncPrototype_st* cNode3 = (TreeNodeFuncPrototype_st*) cNode3;
            
            break;
        case NODE_EXPRESSION:
            break;
        case NODE_NUMBER:
            break;
        default:
            break;
    }


    if (pNode->pLeftChild != NULL)
    {
        PrintNode(pNode->pLeftChild, depth+1);
    }
    if (pNode->pRightChild != NULL)
    {
        PrintNode(pNode->pRightChild, depth+1);
    }    

    if(pNode->pSibling != NULL) 
    {
        PrintNode(pNode->pSibling, depth);
    }
}*/


/*

typedef struct __attribute__((packed)) TreeNodeParam
{
    NODE_BODY();

    char* paramId;
    VarType_et paramType;
    ModQualifier_et modQualifier;
}TreeNodeParam_st;
*/

void PrintNode(TreeNode_st* pNode, int depth)
{
    if (pNode == NULL)
    {
        LOG_ERROR("NULL Node!!\n");
        return;
    }

    LOG_DEBUG("\ndebug\n");

    LOG_DEBUG("\n NODE TYPE -> %d \n", pNode->nodeType);

    LOG_DEBUG("\ndebug\n");

    switch (pNode->nodeType) {
        case NODE_PARAM:
            break;
        case NODE_VAR_DECLARATION:
            //PrintNode(pNode->pChilds[0], depth);
            break;
        case NODE_VAR_NAME:
            break;
        case NODE_MISC:
            break;
        case NODE_VISIBILITY:
            break;
        case NODE_MODIFIER:
            break;
        case NODE_SIGN:
            break;
        case NODE_TYPE:
            break;
        case NODE_OP_TYPE:
            break;
        case NODE_TERNARY:
            break;
        case NODE_ARRAY_INDEX:
            break;
        case NODE_TYPE_CAST:
            break;
        case NODE_ID:
            break;
        case NODE_VAR_ASSIGNMENT:
            break;
        case NODE_FUNC_PROTOTYPE:
            break;
        case NODE_EXPRESSION:
            break;
        case NODE_INTEGER:
            break;
        case NODE_FLOAT:
            break;
        case NODE_IF:
            break;
        case NODE_WHILE:
            break;
        case NODE_DO_WHILE:
            break;
        case NODE_FOR:
            break;
        case NODE_RETURN:
            break;
        case NODE_CONTINUE:
            break;
        case NODE_BREAK:
            break;
        case NODE_GOTO:
            break;
        case NODE_SWITCH:
            break;
        case NODE_CASE:
            break;
        case NODE_DEFAULT:
            break;
        case NODE_POINTER:
            break;
        case NODE_POST_DEC:
            break;
        case NODE_PRE_DEC:
            break;
        case NODE_POST_INC:
            break;
        case NODE_PRE_INC:
            break;
        default:
            LOG_ERROR("\nUNKNOWN NODE TYPE!\n");
            break;
    }
    return;
}