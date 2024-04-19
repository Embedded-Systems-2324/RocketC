#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../main.h"
#include "../SemanticAnalyzer/traverse.h"

static SymbolTable_st* pGlobalSymTable;
static TreeNode_st* pSintaxTree;
static bool initialized = false;

static int typeError(char * message)
{ 
     if (!message)
        return -EINVAL;

    LOG_ERROR("Type error at line %d: %s\n",getLineNumber(),message);

    return 0;  
}

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

static void typeChecking(TreeNode_st * treeNode) 
{
    switch (treeNode->nodeType)  
    { 
       /* case NODE_VISIBILITY:               // check symbol table         //STATIC                           
            break;

        case NODE_MODIFIER:                 // check symbol table           //CONST, VOLATILE                     
            break;

        case NODE_SIGN:                     // check symbol table                             
            break;
        
        *O NODE_OPERATOR é q vai avaliar estes Nós    
        */

        case NODE_OPERATOR:                 // typechecking  NAO PODEM SER STRIGS     
            /*checkar se os sao equivalentes
            *Opçao de type Cast
            *shifts so pode ser char/int
            *assigns bitwise ou nao
            *REGRA GERAL--->  TYPE ID = SOMTHING      ,where SOMTHING must haver the type "TYPE" (STRONG TYPE LANGUAGE ?)
            */

            //if(typeEqual(exp, TYPE_STRING))
            //       typeError("[SEMANTIC ERROR]: String operations are not suported.");
            //else{switch (treeNode->nodeData.dVal)...}
            switch (treeNode->nodeData.dVal)
            {
                case OP_ASSIGN:
                case OP_PLUS_ASSIGN:
                case OP_MINUS_ASSIGN:
                case OP_MODULUS_ASSIGN:
                case OP_MULTIPLY_ASSIGN:
                case OP_DIVIDE_ASSIGN:
                    // a = b        -> a.type = b.type if we decide if its strong stype
                    break;
                case OP_LEFT_SHIFT_ASSIGN:
                case OP_RIGHT_SHIFT_ASSIGN:
                    //a = a<<b      -> a.type e b.type tem de ser INT 
                    break;
                case OP_BITWISE_AND_ASSIGN:
                case OP_BITWISE_OR_ASSIGN:
                case OP_BITWISE_XOR_ASSIGN:

                    break;
                case OP_MINUS:
                case OP_PLUS:
                case OP_MULTIPLY:
                case OP_DIVIDE:
                case OP_REMAIN:
                    break;
                case OP_LOGICAL_NOT:
                case OP_LOGICAL_AND:
                case OP_LOGICAL_OR:
                    break;
                case OP_RIGHT_SHIFT:
                case OP_LEFT_SHIFT:
                    break;
                case OP_GREATER_THAN:
                case OP_LESS_THAN_OR_EQUAL:
                case OP_GREATER_THAN_OR_EQUAL:
                case OP_LESS_THAN:
                case OP_EQUAL:
                case OP_NOT_EQUAL:
                    break;
                case OP_BITWISE_AND:
                case OP_BITWISE_NOT:
                case OP_BITWISE_OR:
                case OP_BITWISE_XOR:

                    break;                                                                                                                                          
                default:
                    break;
            }  
            
            break;

        case NODE_ARRAY_INDEX:              //  Garantir (child tem de ser inteiro); Definir limite max de Inidice;
            break;
            
        case NODE_FUNCTION_CALL:            //  Verificar nome, return type, num de args e tipo dos args)
	        break;

        case NODE_IF:                       //  Garantir q nao é string literal
        case NODE_WHILE:                    //  Garantir q nao é string literal 
        case NODE_DO_WHILE:                 //  Garantir q nao é string literal 
        case NODE_TERNARY:                  //  Garantir q nao é string literal      
            break;
            
        case NODE_RETURN:                   //  Garantir q retorna algo do mesmo tipo da função
            break;

        case NODE_SWITCH:                   //  Garantir q é int ou char
        case NODE_CASE:                     //  Garantir q é int ou char
            break;
        
        case NODE_POST_DEC:                 //  Garantir q é int, float, double
        case NODE_PRE_DEC:                  //  Garantir q é int, float, double
        case NODE_POST_INC:                 //  Garantir q é int, float, double
        case NODE_PRE_INC:                  //  Garantir q é int, float, double
            break;

        default:
            break;
    }
}

static void TypeCheckTraverse()
{
    traverse(pSintaxTree,nullProc,typeChecking);
}

static void SymbolTableTraverse()
{
    traverse(pSintaxTree,nullProc,nullProc);
}

int executeSemanticAnalisys(TreeNode_st** pTreeRoot, SymbolTable_st** ppGlobalTable)
{
    if (!ppGlobalTable)
        return -EINVAL;

    if(!initialized)
    {
        if(!createSymbolTable(&pGlobalSymTable, NULL))
        {
            return 1;   //error creating symbol table
        }

        initialized = true;
    }

    pGlobalSymTable = *ppGlobalTable;
    pSintaxTree = *pTreeRoot;

    SymbolTableTraverse();
    TypeCheckTraverse();
    
    return 0;
}