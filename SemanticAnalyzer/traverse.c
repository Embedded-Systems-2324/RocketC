#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../main.h"
#include "../SemanticAnalyzer/traverse.h"

SymbolTable_st* pGlobalSymTable;
SymbolTable_st* pCurrentScope;
static bool initialized = false;

static int semanticError(char * message)
{ 
     if (!message)
        return -EINVAL;

    LOG_ERROR("Semantic error at line %d: %s\n",getLineNumber(),message);

    return 0;  
}

static void traverse (TreeNode_st* pNode, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ))
{
    if (pNode != NULL)
    {
        preOrder(pNode);                                                      
  
        for ( int i = 0 ; i < pNode->childNumber ; i++ )
        {
            traverse (&pNode->pChilds[i], preOrder, postOrder); 
        }

        postOrder(pNode);                                                 
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


static int setMemoryLocation(uint32_t* varLocation, VarType_et varType)
{
    static uint32_t currentLocation = 0;
    
    *varLocation = currentLocation; 

    switch(varType)
    {
        case TYPE_CHAR:
            currentLocation += 1;
            break;

        case TYPE_SHORT:
            currentLocation += 2;
            break;    
  
        case TYPE_LONG:
        case TYPE_INT:
        case TYPE_FLOAT:
            currentLocation += 4;
            break;

        case TYPE_DOUBLE:
            currentLocation += 8;
            break;   

        case TYPE_LONG_DOUBLE:
            currentLocation += 16;
            break; 

        default:
            LOG_DEBUG("Invalid variable type");
            break;                                 
    }
}


static void buildSymbolTables(TreeNode_st* pNode)
{
    switch (pNode->nodeType)
    {
        case NODE_VAR_DECLARATION:
            SymbolEntry_st* pNewSymbol;


            if( insertSymbol(pGlobalSymTable, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_VARIABLE) == SYMBOL_ADDED)
            { 
                TreeNode_st* pNodeTemp = pNode->pChilds;

                setMemoryLocation(&pNewSymbol->symbolContent_u.SymbolVar_s.memoryLocation, pNodeTemp->nodeType);

                while (pNodeTemp != NULL)
                {
                    switch(pNodeTemp->nodeType)
                    {
                        case NODE_TYPE:
                            pNewSymbol->symbolContent_u.SymbolVar_s.varType = pNodeTemp->nodeData.dVal;
                            break;

                        case NODE_SIGN:
                            pNewSymbol->symbolContent_u.SymbolVar_s.varSign = pNodeTemp->nodeData.dVal;
                            break;

                        case NODE_MODIFIER:
                            pNewSymbol->symbolContent_u.SymbolVar_s.varMod = pNodeTemp->nodeData.dVal;
                            break;

                        case NODE_VISIBILITY:
                            pNewSymbol->symbolContent_u.SymbolVar_s.varVis = pNodeTemp->nodeData.dVal;
                            break;       

                        default:
                            LOG_DEBUG("Invalid node");
                            break;
                    }

                    pNodeTemp = pNodeTemp->pSibling;
                }
            }
            else
            {
                semanticError("Symbol Redefinition!");
            }
            
            break;

        case NODE_ARRAY_DECLARATION:
            break;

        case NODE_FUNCTION:
            break;

        case NODE_IDENTIFIER:
            break;        
        
        case NODE_ARRAY_INDEX:
            break;

        case NODE_POINTER_CONTENT:
            break; 

        case NODE_REFERENCE:
            break;        
        
        case NODE_GOTO:
            break;

        case NODE_FUNCTION_CALL:
            break;           

        default:
            break;
    }
}


static void TypeCheckTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,nullProc,typeChecking);
}

static void SymbolTableTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,buildSymbolTables,nullProc);
}


int executeSemanticAnalisys(TreeNode_st* pTreeRoot, SymbolTable_st** ppGlobalTable)
{
    if (!ppGlobalTable || !pTreeRoot)
        return -EINVAL;


    if(!initialized)
    {
        if(createSymbolTable(&pGlobalSymTable, NULL))
        {
            return 1;   //error creating symbol table
        }

        initialized = true;
    }

    *ppGlobalTable = pGlobalSymTable;
    pCurrentScope = pGlobalSymTable;

    SymbolTableTraverse(pTreeRoot);
    //TypeCheckTraverse(*pTreeRoot);
    
    return 0;
}