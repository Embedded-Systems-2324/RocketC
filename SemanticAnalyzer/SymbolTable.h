#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Util/Globals.h"

#define HASH_TABLE_SIZE     97
#define SYMBOL_NOT_FOUND    0
#define SYMBOL_FOUND        1
#define SYMBOL_ADDED        1
#define SYMBOL_ERROR        0


typedef enum{
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_LABEL,
    SYMBOL_POINTER,
    SYMBOL_ARRAY
}SymbolType_et;


typedef struct parameter{
    char* name;
    VarType_et varType;
    SignQualifier_et varSign;
    ModQualifier_et varMod;

    struct parameter* nextParam_st;
}parameter_st;



// Symbol entry struct
typedef struct SymbolEntry
{
    SymbolType_et symbolType;
    struct SymbolEntry* next;                   // Next Entry Pointer (linked list to prevent collisions)
    char* name;

    union{
        struct{
            uint32_t memoryLocation;                // Variable Location
            VarType_et varType;                     // Variable Type
            SignQualifier_et varSign;
            ModQualifier_et varMod;
            VisQualifier_et varVis;                    
        }SymbolVar_s;


        struct{
            VarType_et returnType;                  // Function Return Type
            uint8_t parameterNumber;                // Number of Function Params
            parameter_st* parameter;
        }SymbolFunction_s;


        struct{
            uint32_t memoryLocation;                // Variable Location
            VarType_et arrayType;                   // Variable Type
            SignQualifier_et arraySign;
            ModQualifier_et arrayMod;
            VisQualifier_et arrayVis;
            uint32_t arraySize;
        }SymbolArray_s;

    }symbolContent_u;

} SymbolEntry_st;


// Symbol table struct
typedef struct SymbolTable
{
    uint32_t innerScopesNumber;
    struct SymbolEntry* table[HASH_TABLE_SIZE]; // Symbol Table
    struct SymbolTable* enclosingScope;         // Pointer to Symbol Table of Enclosing Scope
    struct SymbolTable* innerScopes;
} SymbolTable_st;


static int hash(const char* key);

int createSymbolTable(SymbolTable_st** ppsymTable, SymbolTable_st* enclosingScope);

int addInnercSope(SymbolTable_st* ppsymTable);

int insertSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymEntry, char *symName, SymbolType_et symType);

int fetchSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymbol, char* name, int onlyCurrentScope);

void freeSymbolTable(SymbolTable_st* symTable);

int printSymbolTables(SymbolTable_st* symTable);

#endif 