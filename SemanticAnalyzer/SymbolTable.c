#include <errno.h>
#include <stdio.h>
#include "../Util/Logger.h"
#include "../Util/Util.h"
#include "../main.h"
#include "../SemanticAnalyzer/SymbolTable.h"

static int tablesNumber = 0;
static SymbolTable_st** allSymbolsTables;

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
    //pSymTable->innerScopesNumber = 0;
    //pSymTable->innerScopes = NULL;

    // Initialize hash table
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        pSymTable->table[i] = NULL;      // Initialize each entry to NULL
    }

    allSymbolsTables = reallocarray(allSymbolsTables, tablesNumber + 1, sizeof(SymbolTable_st*));
    if (!allSymbolsTables)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a table pointer\n");
        return -ENOMEM;
    }

    allSymbolsTables[tablesNumber++] = (*ppSymTable);

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

    if( fetchSymbol(pSymTable, &pEntryAux, symName, true) == SYMBOL_NOT_FOUND)
    {
        SymbolEntry_st* pNewSymbol;
        pNewSymbol = (SymbolEntry_st*) calloc(1, sizeof(SymbolEntry_st));

        pNewSymbol->name = symName;
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

static const char *intToString(int value)
{
    static char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return buffer;
}

static void printSymbol(char* symbolType, const char *name, const char *varType, const char *varSign, const char *varMod,
                 const char *varVis, const char *memoryLocation, const char *arraySize, const char *isImplemented,
                 const char *parameterNumber)
{
    printf("| %10s | %20s | %11s | %10s | %10s | %10s | %10s | %10s | %10s | %10s |\n",
           symbolType,
           name,
           varType != NULL ? varType : "n/a",
           varSign != NULL ? varSign : "n/a",
           varMod != NULL ? varMod : "n/a",
           varVis != NULL ? varVis : "n/a",
           memoryLocation != NULL ? memoryLocation : "n/a",
           arraySize != NULL ? arraySize : "n/a",
           isImplemented != NULL ? isImplemented : "n/a",
           parameterNumber != NULL ? parameterNumber : "n/a"
    );
}

int printSymbolTables()
{
    static uint8_t counter = 0;
    SymbolEntry_st* temp;
    SymbolTable_st* CurrTable;

    for(int j = 0; j < tablesNumber; j++)
    {
        CurrTable = allSymbolsTables[j];

        printf("------------------------------------------------------------ SYMBOL TABLE %u ------------------------------------------------------------------\n", counter++);
        
        printf("\033[38;2;255;197;173m");
        printSymbol("SYMBOL", "NAME", "TYPE", "SIGN", "MODIFIER", "VISIBILITY", "MEM_LOC", "ARRAY SIZE", "IS_IMPL", "PARAM_NUM");
        printf("\033[1;0m");

        for(int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            temp = CurrTable->table[i];
            
            while(temp != NULL)
            {
                switch (temp->symbolType)
                {
                case SYMBOL_VARIABLE:
                    printSymbol("VARIABLE",
                                temp->name,
                                VarTypeStrings[temp->symbolContent_u.SymbolVar_s.varType],
                                SignQualifierStrings[temp->symbolContent_u.SymbolVar_s.varSign],
                                ModQualifierStrings[temp->symbolContent_u.SymbolVar_s.varMod],
                                VisQualifierStrings[temp->symbolContent_u.SymbolVar_s.varVis],
                                intToString(temp->symbolContent_u.SymbolVar_s.memoryLocation),
                                NULL,
                                NULL,
                                NULL
                    );
                    break;
                

                case SYMBOL_FUNCTION:
                    printSymbol("FUNCTION",
                                temp->name,
                                VarTypeStrings[temp->symbolContent_u.SymbolFunction_s.returnType],
                                SignQualifierStrings[temp->symbolContent_u.SymbolFunction_s.returnSign],
                                ModQualifierStrings[temp->symbolContent_u.SymbolFunction_s.funcMod],
                                VisQualifierStrings[temp->symbolContent_u.SymbolFunction_s.funcVis],
                                NULL,
                                NULL,
                                temp->symbolContent_u.SymbolFunction_s.isImplemented ? "True" : "False",
                                intToString(temp->symbolContent_u.SymbolFunction_s.parameterNumber)
                    );

                    parameter_st* parameterAux;
                    if(temp->symbolContent_u.SymbolFunction_s.parameterNumber != 0)
                    {
                        parameterAux = temp->symbolContent_u.SymbolFunction_s.parameters;
                        printf("\tPARAMETERS: ");
                        printf("%15s | %11s | %10s | %10s\n",     
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
                    printSymbol("LABEL",
                                temp->name,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                NULL,
                                NULL
                    );
                    break;
                
                case SYMBOL_POINTER:
                    printSymbol("POINTER",
                                temp->name,
                                VarTypeStrings[temp->symbolContent_u.SymbolVar_s.varType],
                                SignQualifierStrings[temp->symbolContent_u.SymbolVar_s.varSign],
                                ModQualifierStrings[temp->symbolContent_u.SymbolVar_s.varMod],
                                VisQualifierStrings[temp->symbolContent_u.SymbolVar_s.varVis],
                                intToString(temp->symbolContent_u.SymbolVar_s.memoryLocation),
                                NULL,
                                NULL,
                                NULL
                    );
                    break;
                

                case SYMBOL_ARRAY:
                    printSymbol("ARRAY",
                                temp->name,
                                VarTypeStrings[temp->symbolContent_u.SymbolArray_s.arrayType],
                                SignQualifierStrings[temp->symbolContent_u.SymbolArray_s.arraySign],
                                ModQualifierStrings[temp->symbolContent_u.SymbolArray_s.arrayMod],
                                VisQualifierStrings[temp->symbolContent_u.SymbolArray_s.arrayVis],
                                intToString(temp->symbolContent_u.SymbolArray_s.memoryLocation),
                                intToString(temp->symbolContent_u.SymbolArray_s.arraySize),
                                NULL,
                                NULL
                    );
                    break;


                default:

                    break;
                }

                temp = temp->next;
            }
        }

        printf("----------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
    }    
}




int addFunctionParams(SymbolEntry_st* pSymbol, struct parameter* pNewParam)
{
    if (!pSymbol)
        return -EINVAL;
    
    parameter_st* pParamList; 

    pParamList = reallocarray(pSymbol->symbolContent_u.SymbolFunction_s.parameters, pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber + 1, sizeof(parameter_st));
    if (!pParamList)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a new parameter\n");
        return -ENOMEM;
    }

    memcpy(&pParamList[pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber++], pNewParam, sizeof(parameter_st));
    
    pSymbol->symbolContent_u.SymbolFunction_s.parameters = pParamList;
    return 0;
}