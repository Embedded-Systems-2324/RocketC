#include <errno.h>
#include "Util.h"
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

/*preorder - symbol table*/
/*postoder - type checking da AST*/

static void traverse (TreeNode_st* pNode, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ))
{
    /*Precisa começar do nodo inicial até ao nodo final para ser uma função recursiva*/
    if (pNode != NULL)
    {
        preOrder(pNode);                                                      //primeiramente faz o preorder para fazer a travessia da tabela de símbolos
            for ( int i = 0 ; pNode->childNumber ; i++ )
                traverse (&pNode->pChilds[i] , preOrder, postOrder);               
        postOrder(pNode);                                                     //depois efetua a travessia para o typechecking
        traverse (pNode->pSibling,preOrder,postOrder);                                                        
    }
}

static void nullProc(TreeNode_st * st)
{ 
    if (st==NULL) 
        return;
    else 
        return;
}


static void typeChecking(TreeNode_st * st)
{
    switch (st->nodeData.dVal)
    { 
        case NODE_VAR_DECLARATION:          // check symbol table        
            break;

        case NODE_VISIBILITY:               // check symbol table                                 
            break;

        case NODE_MODIFIER:                 // check symbol table                             
            break;

        case NODE_SIGN:                     // check symbol table                     
            break;

        case NODE_TYPE:                     // check symbol table  
            break;

        case NODE_OPERATOR:                 // typechecking                                  
            break;

        case NODE_TERNARY:                  // typechecking 
            break;

        case NODE_ARRAY_INDEX:              // check symbol table e type checking (child tem de ser inteiro);
            break;

        case NODE_TYPE_CAST:                // check symbol table (pode ser um tipo ou uma estrutura)
            break;

        case NODE_IDENTIFIER:               // check symbol table
            break;

        case NODE_FUNCTION_CALL:            // check symbol table (verify name, return type, number of args and type of args)
	        break;

        case NODE_FUNCTION:                 
            break;

        case NODE_IF:
            break;

        case NODE_WHILE:
            break;

        case NODE_DO_WHILE:
            break;

        case NODE_SWITCH:
            break;

        case NODE_CASE:
            break;

        case NODE_DEFAULT:
            break;

        case NODE_POINTER:
            break;
        
        case NODE_POINTER_CONTENT:
            break;

        case NODE_REFERENCE:
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
            break;
    }
}

void TypeCheckTraverse(TreeNode_st * syntaxTree)
{
    traverse(syntaxTree,nullProc,checkNode);
}

void SymbolTableTraverse(TreeNode_st * syntaxTree)
{
    traverse(syntaxTree,nullProc,checkNode);
}
