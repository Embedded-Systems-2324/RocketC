#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../main.h"
#include "../SemanticAnalyzer/traverse.h"

SymbolTable_st* pGlobalSymTable;
SymbolTable_st* pCurrentScope;
static bool initialized = false;

static int semanticError(TreeNode_st* pNode, char * message)
{ 
     if (!message)
        return -EINVAL;

    LOG_ERROR("Semantic error at line %d: %s\n", pNode->lineNumber, message);

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


static int setMemoryLocation(int* varLocation, VarType_et varType, int multiplier)
{
    static int currentLocation = 0;
    
    *varLocation = currentLocation; 

    switch(varType)
    {
        case TYPE_CHAR:
            currentLocation += 1*multiplier;
            break;

        case TYPE_SHORT:
            currentLocation += 2*multiplier;
            break;    
  
        case TYPE_LONG:
        case TYPE_INT:
        case TYPE_FLOAT:
            currentLocation += 4*multiplier;
            break;

        case TYPE_DOUBLE:
            currentLocation += 8*multiplier;
            break;   

        case TYPE_LONG_DOUBLE:
            currentLocation += 16*multiplier;
            break; 

        default:
            LOG_DEBUG("Invalid variable type");
            break;                                 
    }
}


static void setVariblesType(TreeNode_st* pNode, VarType_et* type, SignQualifier_et* sign, ModQualifier_et* modifier, VisQualifier_et* visibility)
{
    TreeNode_st* pNodeTemp = pNode;
    *sign = 0;
    *modifier = 0;
    *visibility = 0;

    while (pNodeTemp != NULL)
    {
        switch(pNodeTemp->nodeType)
        {
            case NODE_TYPE:
                *type = pNodeTemp->nodeData.dVal;
                break;

            case NODE_SIGN:
                *sign = pNodeTemp->nodeData.dVal;
                break;

            case NODE_MODIFIER:
                *modifier = pNodeTemp->nodeData.dVal;
                break;

            case NODE_VISIBILITY:
                *visibility = pNodeTemp->nodeData.dVal;
                break;       

            default:
                LOG_DEBUG("Invalid node");
                break;
        }
        pNodeTemp = pNodeTemp->pSibling;
    }
}


static void buildSymbolTables(TreeNode_st* pNode)
{
    SymbolEntry_st* pNewSymbol;

    pNode->scopeTable = pCurrentScope;

    switch (pNode->nodeType)
    {
        case NODE_VAR_DECLARATION:
            if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_VARIABLE) == SYMBOL_ADDED)
            { 
                TreeNode_st* pNodeTemp = pNode->pChilds;
        
                setMemoryLocation(&pNewSymbol->symbolContent_u.SymbolVar_s.memoryLocation, pNodeTemp->nodeData.dVal, 1);
                pNode->scopeTable = pCurrentScope;

                setVariblesType(pNodeTemp, 
                                &pNewSymbol->symbolContent_u.SymbolVar_s.varType,
                                &pNewSymbol->symbolContent_u.SymbolVar_s.varSign,
                                &pNewSymbol->symbolContent_u.SymbolVar_s.varMod,
                                &pNewSymbol->symbolContent_u.SymbolVar_s.varVis);
            }
            else
            {
                semanticError(pNode, "Symbol Redefinition!");
            }
            
            break;

        case NODE_ARRAY_DECLARATION:
            if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_ARRAY) == SYMBOL_ADDED)
            { 
                TreeNode_st* pNodePreamble = &pNode->pChilds[0];
                TreeNode_st* pNodeSize = &pNode->pChilds[1];
        
                int arraySize = pNodeSize->nodeData.dVal;
                pNewSymbol->symbolContent_u.SymbolArray_s.arraySize = arraySize;
                
                setMemoryLocation(&pNewSymbol->symbolContent_u.SymbolVar_s.memoryLocation, pNodePreamble->nodeData.dVal, arraySize);

                setVariblesType(pNodePreamble, 
                                &pNewSymbol->symbolContent_u.SymbolArray_s.arrayType,
                                &pNewSymbol->symbolContent_u.SymbolArray_s.arraySign,
                                &pNewSymbol->symbolContent_u.SymbolArray_s.arrayMod,
                                &pNewSymbol->symbolContent_u.SymbolArray_s.arrayVis);
            }
            else
            {
                semanticError(pNode, "Symbol Redefinition!");
            }
            break;

        case NODE_FUNCTION:
            if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_FUNCTION) == SYMBOL_ADDED)
            {
                TreeNode_st* pNodePreamble = &pNode->pChilds[0];
                TreeNode_st* pNodeArgs;

                if(pNode->pChilds[1].nodeType != NODE_NULL)
                    pNodeArgs = &pNode->pChilds[1];
                else    
                    pNodeArgs = NULL; 

                setVariblesType(pNodePreamble, 
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.returnType,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.returnSign,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.funcMod,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.funcVis); 


                while (pNodeArgs != NULL)
                {
                    parameter_st pParam;
                    VisQualifier_et notUsed;

                    pParam.name = pNodeArgs->nodeData.sVal;

                    setVariblesType(pNodeArgs->pChilds, 
                                    &pParam.varType,
                                    &pParam.varSign,
                                    &pParam.varMod,
                                    &notUsed);

                    addFunctionParams(pNewSymbol, &pParam);

                    pNodeArgs = pNodeArgs->pSibling;
                }


                if(pNode->childNumber > 2)
                {
                    SymbolTable_st* ppsymTable;

                    pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented = true;

                    createSymbolTable(&ppsymTable, pCurrentScope);
                    pCurrentScope = ppsymTable;

                    if(pNode->pChilds[1].nodeType != NODE_NULL)
                    {
                        parameter_st* paramList = pNewSymbol->symbolContent_u.SymbolFunction_s.parameters;
                        SymbolEntry_st* pParamSym;

                        for(int i = 0; i < pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
                        {
                            insertSymbol(pCurrentScope, &pParamSym, paramList[i].name, SYMBOL_VARIABLE);

                            pParamSym->symbolContent_u.SymbolVar_s.memoryLocation = NO_MEMORY;
                        }
                    }
                }
                else
                {
                    pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented = false;
                }
            }
            break;

        case NODE_POINTER_CONTENT:
        case NODE_REFERENCE:
        case NODE_GOTO:
        case NODE_IDENTIFIER:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol Not Defined!");
            }

            break;
        
        case NODE_LABEL:
            if(insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_LABEL) == SYMBOL_ERROR)    // Might be incomplete
            {
                semanticError(pNode, "Symbol Redefinition!");
            }
            break;

        case NODE_ARRAY_INDEX:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeIndex = &pNode->pChilds[0];
                uint32_t arrSize = pNewSymbol->symbolContent_u.SymbolArray_s.arraySize;
                if (pNodeIndex->nodeData.dVal > arrSize)
                {
                    semanticError(pNode, "Index exceeds array size!");
                }
            }
            else
            {
                semanticError(pNode, "Symbol Not Defined!");
            }
            break;       

        case NODE_FUNCTION_CALL:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeParameters  = &pNode->pChilds[0];
                int functionParameterNumber = pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber;
                int parameterCount = 0;

                while(pNodeParameters != NULL)
                {
                    parameterCount++;
                    pNodeParameters = pNodeParameters->pSibling;
                }

                if(parameterCount != functionParameterNumber)
                {
                    char errorMessage[100];
                    snprintf(errorMessage, sizeof(errorMessage), "%s arguments for function call, expected %d, have %d \n",
                                                 (parameterCount > functionParameterNumber ? "Too many" : "Too few"),
                                                 functionParameterNumber, parameterCount);
                    semanticError(pNode, errorMessage);
                }
            }
            else
            {
                semanticError(pNode, "Function Not Defined!");
            }
            break;             

        case NODE_START_SCOPE:
            if(pNode->pSibling->nodeType != NODE_FUNCTION)
            {
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);

                pCurrentScope = ppsymTable;
            }
            break;


        case NODE_END_SCOPE:
            pCurrentScope = pCurrentScope->enclosingScope;
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