#ifndef _PARSER_H_
#define _PARSER_H_

#include "../Util/Globals.h"

int yyerror(char* pStr);
int executeParser(TreeNode_st* pTreeRoot);

#endif