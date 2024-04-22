#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../main.h"
#include "../SemanticAnalyzer/traverse.h"

SymbolTable_st* pGlobalSymTable;
SymbolTable_st* pCurrentScope;
static bool initialized = false;
static uint32_t errorCounter = 0;

static void traverse (TreeNode_st* pNode, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ));
static void nullProc(TreeNode_st * st);
static void buildSymbolTables(TreeNode_st* pNode);
static void checkNode(TreeNode_st * pNode);

/**
 * @brief Post-order traversal of the AST, running a type-checking function at each node
 */
static void TypeCheckTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,nullProc,checkNode);
}

/**
 * @brief Pre-order traversal of the AST, running a symbol table function at each node 
 *        and building symbol tables for each scope
 */
static void SymbolTableTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,buildSymbolTables,nullProc);
}

/**
 * @brief reports a semantic error encountered during AST traverse
 */
static int semanticError(TreeNode_st* pNode, char * message)
{ 
     if (!message)
        return -EINVAL;

    errorCounter++;
    LOG_ERROR("Semantic error at line %d: %s\n", pNode->lineNumber, message);
    return 0;  
}

/**
 * @brief depth-first traversal of an AST

 * @param pNode pointer to the current AST node
 * @param preOrder pointer to the pre-order function to be applied at each node
 * @param postOrder pointer to the post-order function to be applied at each node
 */
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

/**
 * @brief placeholder function that doesn't really do anything
 */
static void nullProc(TreeNode_st * st)
{ 
    if (st==NULL) 
        return;
    else 
        return;
}

/**
 * @brief executes a semantic analysis on the AST, including
 *        symbol tables construction, type checking and errors report
 */
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
        
    // type checking is not performed if errors are detected during symbol tables construction
    if(errorCounter == 0)
    {
        TypeCheckTraverse(pTreeRoot);
    }

    if(errorCounter > 0)
    {
        LOG_ERROR(": %d error(s) found during semantic analisys!\n", errorCounter);
        return SEMANTIC_ERROR;
    }

    LOG_DEBUG("%d error(s) found during semantic analisys!\n", errorCounter);
    return SEMANTIC_OK;
}


/******************************************************************************************
******************************       TYPE CHECKING      **********************************
******************************************************************************************/

/**
 * @brief Checks the type of an operator, the operation validity
 *        and the type and compatibility of the operands
 *
 * @param pNode pointer to the operator AST node
 */
static int checkOperator(TreeNode_st * pNode)
{
    SymbolEntry_st* pEntryAux;
    TreeNode_st* pChild1;
    TreeNode_st* pChild2;
    bool errorFlag = false;

    int varType1;
    int varType2;

    switch(pNode->nodeData.dVal)
    {
        // Valid examples:  !int_var
        case OP_LOGICAL_NOT:
            pChild1 = &pNode->pChilds[0];

            varType1 = pChild1->nodeVarType;
            
            if (varType1 == TYPE_VOID || varType1 == TYPE_STRING || varType1 == TYPE_DOUBLE ||
                varType1 == TYPE_FLOAT || varType1 == TYPE_LONG_DOUBLE)
            {
                errorFlag = true;
            }
            else
            {
                pNode->nodeVarType = pChild1->nodeVarType;
            }
            break;

        // Valid examples:  pointer = pointer           char* char_var = "string"
        //                  pointer = &array[2]         int_var = int_var
        case OP_ASSIGN:
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;
            varType2 = pChild2->nodeVarType;

            if(pChild1->nodeType == NODE_POINTER) 
            {
                if(pChild2->nodeType == NODE_IDENTIFIER)   
                {
                    if(fetchSymbol(pNode->scopeTable, &pEntryAux, pChild2->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                    {
                        semanticError(pNode, "Symbol not found! \n");
                        pNode->nodeVarType = TYPE_VOID;
                    }
                    else
                    {
                        if(pEntryAux->symbolType != SYMBOL_POINTER || (varType1 != varType2))
                        {
                            errorFlag = true;
                        }
                        else
                        {
                            pNode->nodeVarType = varType1;
                        }
                    }
                }
                else if(pChild2->nodeType != NODE_REFERENCE || (varType1 != varType2))
                {
                    errorFlag = true;
                    pNode->nodeVarType = TYPE_VOID;
                }
            }

            else if ((varType1 == TYPE_CHAR))
            {
                if (varType2 == TYPE_STRING)
                {
                    if((fetchSymbol(pNode->scopeTable, &pEntryAux, pChild1->nodeData.sVal, false) == SYMBOL_NOT_FOUND) || 
                      (pEntryAux->symbolType != SYMBOL_POINTER))
                    {
                        semanticError(pNode, "Symbol not found or not a Symbol Pointer\n");
                        pNode->nodeVarType = TYPE_VOID;
                    }
                    else
                    {
                        pNode->nodeVarType = varType1;
                    }                    
                }
                else if (varType2 == TYPE_INT)
                {
                    pNode->nodeVarType = varType1;
                }
            } 
            else
            {
                if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                    (varType2 == TYPE_STRING || varType2 == TYPE_VOID ) ||
                    (varType1 != varType2)) 
                {
                    errorFlag = true;
                }
                else
                {
                    pNode->nodeVarType = varType1;
                }
            }
            break;

        // Valid examples:  char_var / char_var     double_var / double_var
        //                  int_var / int_var       float_var / float_var
        case OP_DIVIDE:
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            // can't divide by zero
            if(((pChild2->nodeType == NODE_INTEGER) && (pChild2->nodeData.dVal == 0)) || ((pChild2->nodeType == NODE_FLOAT) && (pChild2->nodeData.fVal == 0.0)))
            {
                semanticError(pNode, "Division by zero is not supported\n");
                pNode->nodeVarType = TYPE_VOID;

                // PARAR!!!!!!
            }
            else
            {
                varType1 = pChild1->nodeVarType;
                varType2 = pChild2->nodeVarType;

                if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                    (varType2 == TYPE_STRING || varType2 == TYPE_VOID ) ||
                    (varType1 != varType2)) 
                {
                    errorFlag = true;
                }
                else
                {
                    pNode->nodeVarType = varType1;
                }
            }
            break;

        // Valid examples:  int_var + int_var       char_var == char_var
        //                  float_var % float_var   double_var >= double_var
        case OP_PLUS:
        case OP_MINUS:
        case OP_MULTIPLY:
        case OP_REMAIN:
        case OP_EQUAL:
        case OP_NOT_EQUAL:
        case OP_GREATER_THAN:
        case OP_LESS_THAN:
        case OP_LESS_THAN_OR_EQUAL:
        case OP_GREATER_THAN_OR_EQUAL:
        case OP_LOGICAL_AND:
        case OP_LOGICAL_OR:  
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;
            varType2 = pChild2->nodeVarType;

            if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                (varType2 == TYPE_STRING || varType2 == TYPE_VOID ) ||
                (varType1 != varType2)) 
            {
                
                errorFlag = true;
            }
            else
            {
                pNode->nodeVarType = varType1;
            }
            break;

        // Valid examples:  int_var & int_var       char_var << char_var
        case OP_BITWISE_AND_ASSIGN:
        case OP_BITWISE_OR_ASSIGN:
        case OP_BITWISE_XOR_ASSIGN:
        case OP_BITWISE_AND:
        case OP_BITWISE_NOT:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
        case OP_RIGHT_SHIFT:
        case OP_LEFT_SHIFT:
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;
            varType2 = pChild1->nodeVarType;

            if (!(varType1 == TYPE_INT || varType1 == TYPE_CHAR || varType1 == TYPE_SHORT || varType1 == TYPE_LONG) ||
                !(varType2 == TYPE_INT || varType2 == TYPE_CHAR || varType2 == TYPE_SHORT || varType2 == TYPE_LONG)) 
            {
                errorFlag = true;
            }
            else if(varType1 != varType2)
            {
                errorFlag = true;
            }
            else
            {
                pNode->nodeVarType = varType1;
            }
            break;   
    }

    if (errorFlag == true)
    {
        semanticError(pNode, "Operands types don't match!\n");
    }
}

/**
 * @brief Checks the semantic validity of an AST node and specifies its type
 *
 * @param pNode pointer to the AST node to be checked
 */
static void checkNode(TreeNode_st * pNode)
{   
    SymbolEntry_st* pEntryAux;
    TreeNode_st* pChild1;
    TreeNode_st* pChild2;
    bool errorFlag = false;

    switch(pNode->nodeType)
    {
        case NODE_OPERATOR:
            checkOperator(pNode);
            break;

        case NODE_IDENTIFIER:
            if(fetchSymbol(pNode->scopeTable, &pEntryAux, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol not found!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolVar_s.varType;  
            break;


        case NODE_FUNCTION_CALL:
            if(pNode->childNumber > 0)
            {
                pChild1 = &pNode->pChilds[0];

                if(fetchSymbol(pNode->scopeTable, &pEntryAux, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                {
                    semanticError(pNode, "Symbol not found\n");
                    pNode->nodeVarType = TYPE_VOID;
                }   
                else
                {
                    parameter_st* pParam = pEntryAux->symbolContent_u.SymbolFunction_s.parameters;

                    for(int i = 0; i < pEntryAux->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
                    {
                        if(pChild1->nodeVarType != pParam[i].varType)
                        {
                            semanticError(pNode, "Parameters types don't match\n");
                        }
                        pChild1 = pChild1->pSibling;
                    }
                }
            }

            pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolFunction_s.returnType;
            break;  

        case NODE_STRING:
            pNode->nodeVarType = TYPE_STRING;
            break;

        case NODE_INTEGER:
            pNode->nodeVarType = TYPE_INT;
            break;

        case NODE_FLOAT:
            pNode->nodeVarType = TYPE_FLOAT;
            break;

        // Valid examples:  array[int_var]      array[short_var]
        case NODE_ARRAY_INDEX:
            if(fetchSymbol(pNode->scopeTable, &pEntryAux, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol not found\n");
                pNode->nodeVarType = TYPE_VOID;
            } 
            else
            {   
                if ((pNode->pChilds->nodeVarType != TYPE_INT) && (pNode->pChilds->nodeVarType != TYPE_LONG) && (pNode->pChilds->nodeVarType != TYPE_SHORT))
                {
                    semanticError(pNode, "Array's index must be an INT, LONG or SHORT!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
                else
                {
                    pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolArray_s.arrayType;
                }
            }
            break;

        // Valid examples:  pointer ++      -- double_var
        case NODE_POST_DEC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_PRE_INC:
            if(fetchSymbol(pNode->scopeTable, &pEntryAux, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol not found\n");
                pNode->nodeVarType = TYPE_VOID;
            } 
            else if((pEntryAux->symbolType == SYMBOL_POINTER) || (pEntryAux->symbolType == SYMBOL_VARIABLE))
            {   
                pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolVar_s.varType;
            }
            else
            {
                semanticError(pNode, "Operand type not supported!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            break;

        // Valid examples:  case 2      case char_var
        case NODE_CASE:
            if((pNode->pChilds[0].nodeVarType != TYPE_INT) || (pNode->pChilds[0].nodeVarType != TYPE_CHAR))
            {
                semanticError(pNode, "Case condition type must be a INT or CHAR!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            break;

        case NODE_DO_WHILE:
        case NODE_SWITCH:
        case NODE_WHILE:
        case NODE_IF:
            if((pNode->pChilds[0].nodeVarType == TYPE_STRING) || (pNode->pChilds[0].nodeVarType == TYPE_VOID))
            {
                semanticError(pNode, "Condition type can't be a STRING or VOID!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            break;

        // Valid examples:  (double_var) ? float_var : float_var
        case NODE_TERNARY:
            if((pNode->pChilds[0].nodeVarType == TYPE_STRING) || (pNode->pChilds[0].nodeVarType == TYPE_VOID))
            {
                semanticError(pNode, "Condition type can't be a STRING or VOID!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            else
            {
                pChild1 = &pNode->pChilds[1];
                pChild2 = &pNode->pChilds[2];
                int varType1 = pChild1->nodeVarType;
                int varType2 = pChild2->nodeVarType;

                if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                    (varType2 == TYPE_STRING || varType2 == TYPE_VOID ) ||
                    (varType1 != varType2)) 
                {
                    errorFlag = true;
                }
                else
                {
                    pNode->nodeVarType = varType1;
                }
            }
            break;    

        case NODE_RETURN:
            if(fetchSymbol(pGlobalSymTable, &pEntryAux, pNode->nodeData.sVal, true) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol not found\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            else
            {
                pChild1 = &pNode->pChilds[0];

                int varType = pEntryAux->symbolContent_u.SymbolFunction_s.returnType;

                if(pChild1->nodeVarType == varType)
                {
                    pNode->nodeVarType = varType;
                }
                else
                {
                    semanticError(pNode, "Return type don't match!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            }
            break;   

        // Valid_examples:  &pointer      &array
        case NODE_REFERENCE:
            TreeNode_st* pNodeAux;
            
            if(pNode->pChilds->nodeType == NODE_ARRAY_INDEX)
            {
                pNodeAux = pNode->pChilds;
            }
            else
            {
                pNodeAux = pNode;
            }

            if(fetchSymbol(pNodeAux->scopeTable, &pEntryAux, pNodeAux->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNodeAux, "Symbol not found\n");
                pNodeAux->nodeVarType = TYPE_VOID;
            }
            else
            {
                pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolVar_s.varType;
            }
            break;

        // Valid examples:  *pointer
        case NODE_POINTER_CONTENT:
            if(fetchSymbol(pNode->scopeTable, &pEntryAux, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol not found\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            else if(pEntryAux->symbolType == SYMBOL_POINTER)
            {
                pNode->nodeVarType = pEntryAux->symbolContent_u.SymbolVar_s.varType;
            }
            else 
            {
                semanticError(pNode, "Can't reference a non pointer variable!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            break; 

        /*case NODE_TYPE_CAST:
            pChild1 = &pNode->pChilds[0];

            pNode->nodeVarType = pChild1->nodeData.dVal;


            ///PENSAR COMO PASSAR PARA OS OPERANDOS
            break; */

    }

    if (errorFlag == true)
    {
        semanticError(pNode, "Type checking error!\n");
    }
}




/*****************************************************************************************
 ****************************       BUILD SYMBOLS TABLES       ***************************
******************************************************************************************/

/**
 * @brief sets the memory offset accordingly variable type

 * @param varLocation save the current memory offset 
 * @param varType varibale type
 * @param multiplier  used in arrays - array size
 * */
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


/**
 * @brief goes through all the siblings in the preamble and saves qualifiers

 * @param pNode current node
 * @param type 
 * @param sign 
 * @param modifier
 * @param visibility
 */
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


/**
 * @brief generate the symbol tables, according to the current node 

 * @param pNode current node 
 */
static void buildSymbolTables(TreeNode_st* pNode)
{
    /*
    Flag to signal that you have entered a new scope (when '{') but not created the table
    Tables are only created if there are new declarations in the scope 
    */
    static bool tablePending = false; 
    
    /*
    Flag to signal that it is a function
    In functions, the tables are created when the signature appears to pass the parameters
    */
    static bool tableFunction = false;
    SymbolEntry_st* pNewSymbol;

    switch (pNode->nodeType)
    {
        // Variables declaration
        case NODE_VAR_DECLARATION:
            if(tablePending)
            {
                //Create a new symbol table if tablePending = 1
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);
                pCurrentScope = ppsymTable;
                tablePending = false;
            }

            TreeNode_st* pNodeChild = pNode->pChilds;
            SymbolType_et symType;

            //If it's a pointer, the type is in the child of that node
            if(pNodeChild->nodeType == NODE_POINTER)
            {
                pNodeChild = pNodeChild->pChilds;
                symType = SYMBOL_POINTER;
            }
            else
            {
                symType = SYMBOL_VARIABLE;
            }
            
            //inserts the new symbol into the table if it doesn't exist
            if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, symType) == SYMBOL_ADDED)
            { 
                setMemoryLocation(&pNewSymbol->symbolContent_u.SymbolVar_s.memoryLocation, pNodeChild->nodeData.dVal, 1);
                pNode->scopeTable = pCurrentScope;

                setVariblesType(pNodeChild, 
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

        //Array declaration
        case NODE_ARRAY_DECLARATION:
                /*case NODE_POINTER:
                ////fazer   
                break; */      

            if(tablePending)
            {
                //Create a new symbol table if tablePending = 1
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);
                pCurrentScope = ppsymTable;
                tablePending = false;
            }

            //inserts the new symbol into the table if it doesn't exist
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


        //Function prototip and implementation
        case NODE_FUNCTION:
            //inserts the new symbol into the table if it doesn't exist
            if(insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_FUNCTION) == SYMBOL_ADDED)
            {
                TreeNode_st* pNodePreamble = &pNode->pChilds[0];
                TreeNode_st* pNodeArgs;

                if(pNode->pChilds[1].nodeType != NODE_NULL)
                    pNodeArgs = &pNode->pChilds[1];
                else    
                    pNodeArgs = NULL; 

                //sets the return type
                setVariblesType(pNodePreamble, 
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.returnType,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.returnSign,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.funcMod,
                                &pNewSymbol->symbolContent_u.SymbolFunction_s.funcVis); 


                //adds the function arguments 
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
            }

            if(pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented == true)
            {
                semanticError(pNode, "Function already implemented");
            }
            else
            {
                //if has three children you have the implementation of the function
                if(pNode->childNumber > 2)
                {
                    pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented = true;

                    //creates a new symbol table 
                    SymbolTable_st* ppsymTable;
                    createSymbolTable(&ppsymTable, pCurrentScope);
                    pCurrentScope = ppsymTable;
                    tableFunction = true;

                    //puts all parameters in the new scopes
                    if(pNode->pChilds[1].nodeType != NODE_NULL)
                    {
                        parameter_st* paramList = pNewSymbol->symbolContent_u.SymbolFunction_s.parameters;
                        SymbolEntry_st* pParamSym;

                        for(int i = 0; i < pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
                        {
                            insertSymbol(pCurrentScope, &pParamSym, paramList[i].name, SYMBOL_VARIABLE);
                            pParamSym->symbolContent_u.SymbolVar_s.varType = paramList[i].varType;
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

        //pointer content (*p), go to and identifier
        case NODE_POINTER_CONTENT:
        case NODE_GOTO:
        case NODE_IDENTIFIER:
            //check if the token already exists
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
            {
                semanticError(pNode, "Symbol Not Defined!");
            }
            break;

        //variable refernce (&a)
        case NODE_REFERENCE:
            //if it has no children, the name of the token is in the node data
            if(pNode->childNumber = 0)
            {
                if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                {
                    semanticError(pNode, "Symbol Not Defined!");
                }  
            }
            break;    
        
        //label (init:)
        case NODE_LABEL:
            if(tablePending)
            {
                //Create a new symbol table if tablePending = 1
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);
                pCurrentScope = ppsymTable;
                tablePending = false;
            }

            //inserts the label into the table if it doesn't exist
            if(insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_LABEL) == SYMBOL_ERROR) 
            {
                semanticError(pNode, "Symbol Redefinition!");
            }
            break;


        //Array value (array[x])
        case NODE_ARRAY_INDEX:
            //check if the token exists
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeIndex = &pNode->pChilds[0];
                uint32_t arrSize = pNewSymbol->symbolContent_u.SymbolArray_s.arraySize;
                
                //checks if the index excced the array size
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

        //function call
        case NODE_FUNCTION_CALL:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeParameters  = &pNode->pChilds[0];
                int functionParameterNumber = pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber;
                int parameterCount = 0;

                //checks if is passed the correct arguments number
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
            if(!tableFunction)
                tablePending = true;
            else 
                tableFunction = false;    
            break;

        case NODE_END_SCOPE:
            if(!tablePending)
                pCurrentScope = pCurrentScope->enclosingScope;
            else    
                tablePending = false;    
            break;            


        case NODE_POST_DEC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_PRE_INC:
            
            break;


        default:
            break;
    }

    pNode->scopeTable = pCurrentScope;  //sets the scope in the node struct
}


