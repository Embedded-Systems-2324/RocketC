#include "SymbolTable.h"

#define SHIFT   4

// Hash function
static int hash(const char *key)
{
    int hashValue = 0;
    int i = 0;
    while (key[i] != '\0')
        hashValue = ((hashValue << SHIFT) + key[i++]) % SIZE;

    return hashValue;
}

// Function to create a new symbol table
// Note: Global scope recommended to receive enclosingScope = NULL
int createSymbolTable(SymbolTable_st **ppSymTable, SymbolTable_st *enclosingScope)
{
    ymbolEntry_st *symTable;

    if (!ppSymTable)
        return -EINVAL;

    *ppSymTable = (SymbolTable_st*) calloc(1, sizeof(SymbolTable_st));

    if (!(*ppSymEntry))
    {
        LOG_ERROR("Failed to allocate memory for new symbol!\n");
        return -ENOMEM;
    }

    symTable = (SymbolTable_st*) (*(ppSymTable));

    symTable->enclosingScope = enclosingScope;

    // Initialize hash table
    for (int i = 0; i < SIZE; ++i)
    {
        symTable->table[i] = NULL;      // Initialize each entry to NULL
    }
    return symTable;
}

// TODO: Make it work
// Function to properly initialize Entry Node
int createSymbolEntry(SymbolEntry_st **ppSymEntry, SymbolType_et symType)
{
    SymbolEntry_st *symEntry;

    if (!ppSymEntry)
        return -EINVAL;

    *ppSymEntry = (SymbolEntry_st*) calloc(1, sizeof(SymbolEntry_st));

    if (!(*ppSymEntry))
    {
        LOG_ERROR("Failed to allocate memory for new symbol!\n");
        return -ENOMEM;
    }

    symEntry = (SymbolEntry_st*) (*(ppSymEntry));
    
    symEntry->symbolType = symType;

    return symEntry;
}

// Function to insert a symbol into the symbol table
void insertSymbol(SymbolTable_st *symTable, SymbolEntry_st *symEntry)
{
    int index = hash(symEntry->name);

    if (symTable->table[index] == NULL)
    {
        symTable->table[index] = symEntry;
    }
    else    // In case of collision
    {
        symEntry->next = symTable->table[index];
        symTable->table[index] = symEntry;
    }
}


// Function to get symbol from symbol table
// Returns the Symbol if exists in the current scope or enclosing scopes and NULL if it doesn't
int fetchSymbol(SymbolTable_st *pSymTable, SymbolEntry_st **ppSymbol, int onlyCurrentScope, char *name)
{
    int index = hash(name);  // Assuming you have a separate hash function

    // Traverse the linked list at the hash index
    SymbolEntry_st *symIterator = symTable->table[index];

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
    if (symTable->enclosingScope != NULL && !onlyCurrentScope)
    {
        return  fetchSymbol(symTable->enclosingScope, ppSymbol, FALSE, name);
    }

    return SYMBOL_NOT_FOUND;                    // Symbol not found
}


// Function to free the memory allocated for a symbol table
void freeSymbolTable(SymbolTable_st *symTable)
{
    for (int i = 0; i < SIZE; ++i)
    {
        SymbolEntry_st *entry = symTable->table[i];
        while (entry != NULL)
        {
            SymbolEntry_st *temp = entry;
            entry = entry->next;
            free(temp->name);
            free(temp);
        }
    }
    free(symTable);
}
