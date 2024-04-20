#include <errno.h>
#include <stdio.h>
#include "../Util/Logger.h"
#include "../Util/Util.h"
#include "../main.h"
#include "../SemanticAnalyzer/SymbolTable.h"


// Hash function
static int hash(const char *key)
{
    int hashValue = 0;
    int i = 0;
    while (key[i] != '\0')
        hashValue = ((hashValue << 4) + key[i++]) % HASH_TABLE_SIZE;

    return hashValue;
}


// Function to create a new symbol table
// Note: Global scope recommended to receive enclosingScope = NULL
int createSymbolTable(SymbolTable_st** ppSymTable, SymbolTable_st* enclosingScope)
{
    SymbolTable_st* pSymTable;

    if (!ppSymTable)
        return -EINVAL;

    *ppSymTable = (SymbolTable_st*) calloc(1, sizeof(SymbolTable_st));

    if (!(*ppSymTable))
    {
        LOG_DEBUG("Failed to allocate memory for new symbol!\n");
        return -ENOMEM;
    }

    pSymTable = (SymbolTable_st*) (*(ppSymTable));

    pSymTable->enclosingScope = enclosingScope;
    pSymTable->innerScopesNumber = 0;
    //pSymTable->innerScopes = NULL;

    // Initialize hash table
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        pSymTable->table[i] = NULL;      // Initialize each entry to NULL
    }

    return 0;
}


/*int addInnerScope(SymbolTable_st* pSymTable)
{
    if (!pSymTable)
        return -EINVAL;

    SymbolTable_st* pNewTable;
    SymbolTable_st* pInnerScope;

    createSymbolTable(&(pNewTable), pSymTable);

    pInnerScope = reallocarray(pSymTable->innerScopes, pSymTable->innerScopesNumber + 1, sizeof(SymbolTable_st));
    if (!pInnerScope)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a new inner scope\n");
        return -ENOMEM;
    }

    pSymTable->innerScopes = pInnerScope;
    memcpy(&pSymTable->innerScopes[pSymTable->innerScopesNumber++], pNewTable, sizeof(SymbolTable_st));
    free(pNewTable);

    return 0;
}*/


// Function to get symbol from symbol table
// Returns the Symbol if exists in the current scope or enclosing scopes and NULL if it doesn't
int fetchSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymbol, char* name, int onlyCurrentScope)
{
    if (!pSymTable || !ppSymbol)
        return -EINVAL;

    int index = hash(name);  // Assuming you have a separate hash function

    // Traverse the linked list at the hash index
    SymbolEntry_st* symIterator = pSymTable->table[index];   

    while (symIterator != NULL)
    {
        // Ensure symIterator->name is valid before comparison (avoid null pointer dereference)
        if (symIterator->name != NULL && strcmp(symIterator->name, name) == 0)
        {
            (*ppSymbol) = symIterator;
            return SYMBOL_FOUND;
        }
        symIterator = symIterator->next;
    }

    // Symbol not found in the current scope, check enclosing scope (if it exists)
    if (pSymTable->enclosingScope != NULL && !onlyCurrentScope)
    {
        return fetchSymbol(pSymTable->enclosingScope, ppSymbol, name, onlyCurrentScope);
    }

    return SYMBOL_NOT_FOUND;                    // Symbol not found
}



// Function to insert a symbol into the symbol table
int insertSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymEntry, char *symName, SymbolType_et symType)
{   
    if (!pSymTable || !ppSymEntry)
        return -EINVAL;

    int index = hash(symName);

    SymbolEntry_st* pEntryAux;
    //SymbolTable_st* pCurrentTable = pSymTable;   //??????????

    if( fetchSymbol(pSymTable, &pEntryAux, symName, false) == SYMBOL_NOT_FOUND)
    {
        SymbolEntry_st* pNewSymbol;
        pNewSymbol = (SymbolEntry_st*) calloc(1, sizeof(SymbolEntry_st));

        StringCreateAndCopy(&(pNewSymbol->name), symName, 0);
        pNewSymbol->symbolType = symType;

        pEntryAux = pSymTable->table[index];
        pSymTable->table[index] = pNewSymbol;
        pNewSymbol->next = pEntryAux; 

        *ppSymEntry = pNewSymbol;

        return SYMBOL_ADDED;
    }

    *ppSymEntry = pEntryAux;

    return SYMBOL_ERROR;
}



// Function to free the memory allocated for a symbol table
void freeSymbolTable(SymbolTable_st* symTable)
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        SymbolEntry_st* entry = symTable->table[i];
        while (entry != NULL)
        {
            SymbolEntry_st* temp = entry;
            entry = entry->next;
            free(temp->name);
            free(temp);
        }
    }
    free(symTable);
}


int printSymbolTables(SymbolTable_st* symTable)
{

    if (!symTable)
        return -EINVAL;

    static uint8_t counter = 0;
    SymbolEntry_st* temp;
    SymbolTable_st* CurrTable = symTable;

    /*while(CurrTable != NULL)
    {*/
        printf("-----------SYMBOL TABLE %u-----------\n", counter);
        
        for(int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            temp = symTable->table[i];
            
            while(temp != NULL)
            {
                switch (temp->symbolType)
                {
                case SYMBOL_VARIABLE:
                    printf("%10s: %20s | %11s | %9s | %9s | %6s | %5d | %5s | %5s | %5s\n",   "VARIABLE",
                                                               /* Name */   temp->name,
                                                               /* Type */   VarTypeStrings[temp->symbolContent_u.SymbolVar_s.varType],
                                                               /* Sign */   SignQualifierStrings[temp->symbolContent_u.SymbolVar_s.varSign],
                                                           /* Modifier */   ModQualifierStrings[temp->symbolContent_u.SymbolVar_s.varMod],
                                                         /* Visibility */   VisQualifierStrings[temp->symbolContent_u.SymbolVar_s.varVis],
                                                    /* Memory Location */   temp->symbolContent_u.SymbolVar_s.memoryLocation,
                                                         /* Array Size */   "n/a",
                                            /* Is Function Implemented */   "n/a",
                                                   /* Parameter Amount */   "n/a"
                                                                            );
                    break;
                
                case SYMBOL_FUNCTION:
                    printf("%10s: %20s | %11s | %9s | %9s | %6s | %5s | %5s | %5s | %5d\n",     "FUNCTION",
                                                                         /* Functio Name */     temp->name,
                                                                          /* Return Type */     VarTypeStrings[temp->symbolContent_u.SymbolFunction_s.returnType],
                                                                          /* Return Sign */     SignQualifierStrings[temp->symbolContent_u.SymbolFunction_s.returnSign],
                                                                     /* Functio Modifier */     ModQualifierStrings[temp->symbolContent_u.SymbolFunction_s.funcMod],
                                                                   /* Functio Visibility */     VisQualifierStrings[temp->symbolContent_u.SymbolFunction_s.funcVis],
                                                                      /* Memory Location */     "n/a",
                                                                           /* Array Size */     "n/a",
                                                              /* Is Function Implemented */     temp->symbolContent_u.SymbolFunction_s.isImplemented ? "True" : "False",
                                                                     /* Parameter Amount */     temp->symbolContent_u.SymbolFunction_s.parameterNumber
                                                                                                );

                    parameter_st* parameterAux;
                    if(temp->symbolContent_u.SymbolFunction_s.parameterNumber != 0)
                    {
                        parameterAux = temp->symbolContent_u.SymbolFunction_s.parameters;
                        printf("\tPARAMETERS: ");
                        printf("%20s | %11s | %9s | %9s\n",     
                                                     /* Name */     parameterAux->name,
                                                     /* Type */     VarTypeStrings[parameterAux->varType],
                                                     /* Sign */     SignQualifierStrings[parameterAux->varSign],
                                                 /* Modifier */     ModQualifierStrings[parameterAux->varMod]
                                                                    );
                        printf("\t            ");
                        // while(parameterAux != NULL)
                        // {
                        //     printf("%20s | %11s | %9s | %9s\n",     
                        //                              /* Name */     parameterAux->name,
                        //                              /* Type */     VarTypeStrings[parameterAux->varType],
                        //                              /* Sign */     SignQualifierStrings[parameterAux->varSign],
                        //                          /* Modifier */     ModQualifierStrings[parameterAux->varMod]
                        //                                             );
                        //     printf("\t            ");
                        //     parameterAux = parameterAux->next;
                        // }
                        printf("\n");
                    }
                    
                                                        
                    break;
                
                
                case SYMBOL_LABEL:
                    printf("%10s: %20s | %11s | %9s | %9s | %6s | %5s | %5s | %5s | %5s\n",   "LABEL",
                                                                                 /* Name */   temp->name,
                                                                                 /* Type */   "n/a",
                                                                                 /* Sign */   "n/a",
                                                                             /* Modifier */   "n/a",
                                                                           /* Visibility */   "n/a",
                                                                      /* Memory Location */   "n/a",
                                                                           /* Array Size */   "n/a",
                                                              /* Is Function Implemented */   "n/a",
                                                                     /* Parameter Amount */   "n/a"
                                                                                              );
                    break;
                
                case SYMBOL_POINTER:
                    printf("%10s: %20s | %11s | %9s | %9s | %6s | %5d | %5s | %5s | %5s\n",   "POINTER",
                                                                                 /* Name */   temp->name,
                                                                                 /* Type */   VarTypeStrings[temp->symbolContent_u.SymbolVar_s.varType],
                                                                                 /* Sign */   SignQualifierStrings[temp->symbolContent_u.SymbolVar_s.varSign],
                                                                             /* Modifier */   ModQualifierStrings[temp->symbolContent_u.SymbolVar_s.varMod],
                                                                           /* Visibility */   VisQualifierStrings[temp->symbolContent_u.SymbolVar_s.varVis],
                                                                      /* Memory Location */   temp->symbolContent_u.SymbolVar_s.memoryLocation,
                                                                           /* Array Size */   "n/a",
                                                              /* Is Function Implemented */   "n/a",
                                                                     /* Parameter Amount */   "n/a"
                                                                                              );
                    break;
                
                case SYMBOL_ARRAY:
                    printf("%10s: %20s | %11s | %9s | %9s | %6s | %5d | %5d | %5s | %5s\n",  "ARRAY",
                                                                                /* Name */   temp->name,
                                                                                /* Type */   VarTypeStrings[temp->symbolContent_u.SymbolArray_s.arrayType],
                                                                                /* Sign */   SignQualifierStrings[temp->symbolContent_u.SymbolArray_s.arraySign],
                                                                            /* Modifier */   ModQualifierStrings[temp->symbolContent_u.SymbolArray_s.arrayMod],
                                                                          /* Visibility */   VisQualifierStrings[temp->symbolContent_u.SymbolArray_s.arrayVis],
                                                                     /* Memory Location */   temp->symbolContent_u.SymbolArray_s.memoryLocation,
                                                                          /* Array Size */   temp->symbolContent_u.SymbolArray_s.arraySize,
                                                             /* Is Function Implemented */   "n/a",
                                                                    /* Parameter Amount */   "n/a"
                                                                                             );
                    break;

                default:

                    break;
                }

                temp = temp->next;
            }
        }

        printf("------------------------------------\n\n\n");

    //}    
}




int addFunctionParams(SymbolEntry_st** ppSymbol, struct parameter* pNewParam)
{
    if (!ppSymbol)
        return -EINVAL;
    
    parameter_st* pParamList = (*ppSymbol)->symbolContent_u.SymbolFunction_s.parameters;

    pParamList = reallocarray(pParamList, (*ppSymbol)->symbolContent_u.SymbolFunction_s.parameterNumber + 1, sizeof(parameter_st));
    if (!pParamList)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a new parameter\n");
        return -ENOMEM;
    }

    memcpy(&pParamList[(*ppSymbol)->symbolContent_u.SymbolFunction_s.parameterNumber++], pNewParam, sizeof(parameter_st));
    return 0;
}