#include <errno.h>
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType)
{
    if (!ppNewNode)
        return -EINVAL;

    *ppNewNode = (TreeNode_st *) calloc(1, sizeof(TreeNode_st));
    if (!(*ppNewNode))
    {
        LOG_ERROR("Failed to allocate memory!\n");
        return -ENOMEM;
    }

    (*ppNewNode)->nodeType = nodeType;
    (*ppNewNode)->lineNumber = getLineNumber();

    return 0;
}

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