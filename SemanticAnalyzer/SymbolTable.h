#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Util/Globals.h"

#define HASH_TABLE_SIZE     199
#define SYMBOL_NOT_FOUND    0
#define SYMBOL_FOUND        1


typedef enum{
    SYMBOL_VAR,
    SYMBOL_FUNCTION,
    SYMBOL_LABEL
}SymbolType_et;


// Attribute Enum
typedef struct ATTRIBUTES
{
    int ATTRIBUTE_STATIC;
    int ATTRIBUTE_EXTERN;
    int ATTRIBUTE_CONSTANT;
    int ATTRIBUTE_VOLATILE;
    int ATTRIBUTE_SIGNED;
    int ATTRIBUTE_UNSIGNED;

} ATTRIBUTES_ET;


typedef struct parameter{
    char* name;
    VarType_et varType;
    SignQualifier_et varSign;
    ModQualifier_et varMod;

    struct parameter *argument_st;
}parameter_st;



// Symbol entry struct
typedef struct SymbolEntry
{
    SymbolType_et symbolType;

    union{
        struct{
            char *varName;                          // Variable Name
            uint32_t memoryLocation;                // Variable Location
            VarType_et varType;                     // Variable Type
            bool isPointer;                         // Variable is a Pointer (1: True, 0: False)                     
        }SymbolVar_s;


        struct{
            char *functionName;                     // Function Name
            VarType_et returnType;                  // Function Return Type
            uint8_t parameterNumber;                // Number of Function Params
            parameter_st* parameter;          
        }SymbolFunction_s;

        struct{
            char *label;                     // Function Name         
        }SymbolLabel_s;

        struct{

        }SymbolArray;

    }symbolContent_u;

    struct SymbolEntry *next;                   // Next Entry Pointer (linked list to prevent collisions)
} SymbolEntry_st;


// Symbol table struct
typedef struct SymbolTable
{
    struct SymbolEntry *table[HASH_TABLE_SIZE]; // Symbol Table
    struct SymbolTable *enclosingScope;         // Pointer to Symbol Table of Enclosing Scope

} SymbolTable_st;


static int hash(const char *key);

int createSymbolTable(SymbolTable_st **ppsymTable, SymbolTable_st *enclosingScope);

int createSymbolEntry(SymbolEntry_st **ppSymEntry, SymbolType_et symType);

void insertSymbol(SymbolTable_st *symTable, SymbolEntry_st *symEntry);

int fetchSymbol(SymbolTable_st *symTable, SymbolEntry_st **ppSymbol, int onlyCurrentScope, char *name);

void freeSymbolTable(SymbolTable_st *symTable);


#endif //HASHTABLE_HASH_H