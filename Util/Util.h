#ifndef _UTIL_H_
#define _UTIL_H_

#include "Globals.h"

int CreateNodeStatement(TreeNode_st** ppTreeNode, StatementType_et statementType);
int CreateNodeExpression(TreeNode_st** ppTreeNode, ExpressionType_et expressionType);

#endif
