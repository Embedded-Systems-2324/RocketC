#include <errno.h>
#include "Logger.h"
#include "SymbolTable.h"


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
        LOG_ERROR("Failed to allocate memory for new symbol!\n");
        return -ENOMEM;
    }

    pSymTable = (SymbolTable_st*) (*(ppSymTable));

    pSymTable->enclosingScope = enclosingScope;

    // Initialize hash table
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        pSymTable->table[i] = NULL;      // Initialize each entry to NULL
    }

    return 0;
}


// Function to insert a symbol into the symbol table
void insertSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymEntry, char *symName, SymbolType_et symType)
{
    if (!pSymTable || !ppSymEntry)
        return -EINVAL;

    int index = hash(symName);

    SymbolEntry_st* pEntryAux = pSymTable->table[index];

    while((pEntryAux != NULL) && (strcmp(symName, pEntryAux->name) != 0))
    {
        pEntryAux = pEntryAux->next;
    }

    if(pEntryAux == NULL)
    {
        pEntryAux = (SymbolEntry_st*) calloc(1, sizeof(SymbolEntry_st));

        StringCreateAndCopy(&(pEntryAux->name), symName, 0);
        pEntryAux->symbolType = symType;

        (*ppSymEntry) = &pEntryAux;

        return SYMBOL_NOT_FOUND;
    }

    return SYMBOL_FOUND;
}


// Function to get symbol from symbol table
// Returns the Symbol if exists in the current scope or enclosing scopes and NULL if it doesn't
int fetchSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymbol, char* name, int onlyCurrentScope)
{
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
        return fetchSymbol(pSymTable->enclosingScope, ppSymbol, onlyCurrentScope, name);
    }

    return SYMBOL_NOT_FOUND;                    // Symbol not found
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



