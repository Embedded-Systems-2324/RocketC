#include <errno.h>
#include "Util.h"
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

/*preorder - symbol table*/
/*postoder - type checking da AST*/

static void traverse (TreeNode_st* st, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ))
{
    /*Precisa começar do nodo inicial até ao nodo final para ser uma função recursiva*/
    if (st != NULL)
    {
        preOrder(st);                                                      //primeiramente faz o preorder para fazer a travessia da tabela de símbolos
            for ( int i = 0 ; st->childNumber ; i++ )
                traverse (&st->pChilds[i] , preOrder, postOrder);               
        postOrder(st);                                                     //depois efetua a travessia para o typechecking
        traverse (st->pSibling,preOrder,postOrder);                                                        
    }
}

static void nullProc(TreeNode_st * st)
{ if (st==NULL) return;
  else return;
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

        case NODE_TERNARY:    
            break;

        case NODE_ARRAY_INDEX:          
            break;

        case NODE_TYPE_CAST:           
            break;

        case NODE_STRING:
            break;

        case NODE_IDENTIFIER:
            break;

        case NODE_FUNCTION_CALL:
	        break;

        case NODE_FUNCTION:
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

void typeCheck(TreeNode_st * syntaxTree)
{
    traverse(syntaxTree,nullProc,checkNode);
}
