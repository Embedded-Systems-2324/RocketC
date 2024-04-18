#ifndef _UTIL_H_
#define _UTIL_H_

#include "Globals.h"

static const char *OperatorStrings[] = {
    "+ ",      // 0
    "- ",      // 1
    ">> ",     // 2
    "<< ",     // 3
    "* ",      // 4
    "/ ",      // 5
    "%% ",     // 6
    "> ",      // 7
    "<= ",     // 8
    ">= ",     // 9
    "< ",      // 10
    "== ",     // 11
    "!= ",     // 12
    "&& ",     // 13
    "|| ",     // 14
    "! ",      // 15
    "& ",      // 16
    "| ",      // 17
    "~ ",      // 18
    "^ ",      // 19
    "= ",      // 20
    "+= ",     // 21
    "-= ",     // 22
    "%%= ",    // 23
    "<<= ",    // 24
    ">>= ",    // 25
    "&= ",     // 26
    "|= ",     // 27
    "^= ",     // 28
    "*= ",     // 29
    "/= ",     // 30
    "sizeof"   // 31
};

static const char *VarTypeStrings[] = {
    "char ",
    "short ",
    "int ",
    "long ",
    "float ",
    "double ",
    "long double "
};

static const char *SignQualifierStrings[] = {
    "signed ",
    "unsigned "
};

static const char *ModQualifierStrings[] = {
    "const ",
    "volatile ",
    ""
};

static const char *VisQualifierStrings[] = {
    "static ",
    "extern ",
    ""
};

static const char *MiscDataStrings[] = {
    "",
    "register "
};

static const char *MiscTokensStrings[] = {
    ")",
    "(",
    "]",
    "["
};


int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType);

int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild);
int NodeAddChildCopy(TreeNode_st* pParent, TreeNode_st *pChild);
int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType);


int StringCreateAndCopy(char** ppDest, char* pSrc, size_t strLen);

static void Indentation(void);

void PrintNode(TreeNode_st* pNode);

#endif
