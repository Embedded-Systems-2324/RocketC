#include <errno.h>
#include "Util.h"
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
        return;
    }

    switch (pNode->nodeType) {
        case NODE_PARAM:
            break;
        case NODE_VAR_DECLARATION:                                      // tested
            for (int i=0; i<pNode->childNumber; i++)
            {
                PrintNode(&pNode->pChilds[i], depth);
            }
            break;

        case NODE_VAR_NAME:                                             // tested
            for (int i=0; i<pNode->childNumber; i++)
            {
                PrintNode(&pNode->pChilds[i], depth);
            }
            printf("%s ", pNode->nodeData.sVal);
            break;

        case NODE_MISC:                                                 // tested
            printf("%s ", MiscDataStrings[pNode->nodeData.dVal]);
            break;

        case NODE_VISIBILITY:                                           // tested
            printf("%s ", VisQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_MODIFIER:                                             // tested
            printf("%s ", ModQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_SIGN:                                                 // tested
            printf("%s ", SignQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_TYPE:                                                 // tested
            printf("%s ", VarTypeStrings[pNode->nodeData.dVal]);
            break;

        case NODE_OP_TYPE:                                              
            printf("%s ", OperatorStrings[pNode->nodeData.dVal]);
            break;

        case NODE_TERNARY:                                     
            PrintNode(&pNode->pChilds[0], depth);
            printf("? ");
            PrintNode(&pNode->pChilds[1], depth);
            printf(": ");
            PrintNode(&pNode->pChilds[2], depth);
            break;

        case NODE_ARRAY_INDEX:                                  
            PrintNode(&pNode->pChilds[0], depth);
            printf("[");
            PrintNode(&pNode->pChilds[1], depth);
            printf("]");
            break;

        case NODE_TYPE_CAST:                                        // geração nós de TYPECAST estão bem??? 
            break;

        case NODE_ID:                                                       
            printf("%s ", pNode->nodeData.sVal);
            break;

        case NODE_VAR_ASSIGNMENT:
            printf("%s ", pNode->nodeData.sVal);
            for (int i=0; i<pNode->childNumber; i++)
            {
                PrintNode(&pNode->pChilds[i], depth);
            }            
            break;

        case NODE_FUNCTION:
            break;

        case NODE_EXPRESSION:
            for (int i=0; i<pNode->childNumber; i++)
            {
                PrintNode(&pNode->pChilds[i], depth);
            }
            break;

        case NODE_INTEGER:
            printf("%ld ", pNode->nodeData.dVal);
            break;

        case NODE_FLOAT:
            printf("%.10g ", pNode->nodeData.fVal);
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
            printf("return ");
            for (int i=0; i<pNode->childNumber; i++)
            {
                PrintNode(&pNode->pChilds[i], depth);
            }
            break;

        case NODE_CONTINUE:
            printf("continue \n");
            break;

        case NODE_BREAK:
            printf("break \n");
            break;

        case NODE_GOTO:
            printf("goto %s", pNode->nodeData.sVal);
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
            printf("%s--", pNode->nodeData.sVal);
            break;

        case NODE_PRE_DEC:
            printf("--%s", pNode->nodeData.sVal);
            break;

        case NODE_POST_INC:
            printf("%s++ ", pNode->nodeData.sVal);
            break;

        case NODE_PRE_INC:
            printf("++%s", pNode->nodeData.sVal);
            break;

        default:
            LOG_ERROR("\nUNKNOWN NODE TYPE!\n");
            break;
    }
    return;
}*/