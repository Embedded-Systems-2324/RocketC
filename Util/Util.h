#ifndef _UTIL_H_
#define _UTIL_H_

#include "Globals.h"

int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType);
int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild);
int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType);
int NodeAddQualifier(TreeNode_st* pNode, QualifierType_et qualifierType);
int StringCreateAndCopy(char** ppDest, char* pSrc, size_t strLen);

#endif
