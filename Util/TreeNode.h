#ifndef ROCKETC_TREENODE_H
#define ROCKETC_TREENODE_H

#include "../SemanticAnalyzer/SymbolTable.h"

#include "../Util/Globals.h"

typedef struct TreeNode
{
    struct TreeNode* pChilds;
    struct TreeNode* pSibling;
    size_t childNumber;
    size_t lineNumber;

    NodeType_et nodeType;
    NodeData_ut nodeData;

    VarType_et nodeVarType;
    SymbolTable_st* scopeTable;
    SymbolEntry_st* pSymbol;
}TreeNode_st;


typedef union
{
    TreeNode_st* treeNode;
    NodeData_ut nodeData;
}ParserObject_ut;

#endif