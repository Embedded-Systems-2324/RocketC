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

    switch (nodeType)
    {
        case NODE_PARAM_DESC:
            *ppNewNode = (TreeNode_st*) calloc(1, sizeof(TreeNodeParam_st));
            break;
        case NODE_FUNC_PROTOTYPE:
            *ppNewNode = (TreeNode_st*) calloc(1, sizeof(TreeNodeFuncPrototype_st));
            break;
        case NODE_VAR_DECLARATION:
            *ppNewNode = (TreeNode_st*) calloc(1, sizeof(TreeNodeVarDecl_st));
            break;
        default:
            LOG_ERROR("Received invalid node type! Unable to allocate new node!");
            break;
    }

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

#if 0
int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild)
{
    TreeNode_st* pTemp;

    if (!pParent || !pChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->child, pParent->nofChild + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->child = pTemp;
    memcpy(&pParent->child[pParent->nofChild++], pChild, sizeof(TreeNode_st));
    free(pChild);

    return 0;
}

int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType)
{
    TreeNode_st* pTemp;

    if (!pParent || !ppNewChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->child, pParent->nofChild + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->child = pTemp;
    (*ppNewChild) = &pParent->child[pParent->nofChild++];

    memset(*ppNewChild, 0, sizeof(TreeNode_st));
    (*ppNewChild)->nodeType = nodeType;
    (*ppNewChild)->lineNumber = getLineNumber();

    return 0;
}
#endif

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

int PrintNode(TreeNode_st* pNode)
{
    if (!pNode)
        return -EINVAL;


}