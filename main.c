#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer/Lexer.h"

#include "Parser/Parser.h"

#include "Output/Parser.tab.h"

#include "SemanticAnalyzer/SymbolTable.h"
#include "SemanticAnalyzer/traverse.h"

#include "Util/Globals.h"
#include "Util/TreeNode.h"
#include "Util/Logger.h"
#include "Util/Util.h"



static TreeNode_st* pTreeRoot;
static SymbolTable_st* pGlobalSymTable;
static FILE* pSourceFile;
static size_t lineNumber = 1;
static bool bReady = 0;



size_t getLineNumber()
{
    return lineNumber;
}

size_t incrementLineNumber(size_t n)
{
    lineNumber += n;
    return lineNumber;
}

int getSourceFile(FILE** ppSourceFile)
{
    if (!ppSourceFile)
        return -EINVAL;

    if (!bReady)
        return -EPERM;

    *ppSourceFile = pSourceFile;

    return 0;
}

int main(int argc, char *argv[])
{
    char* pMode;

    if (argc < 2 || argc > 3)
    {
        LOG_ERROR("Usage: %s <source_file> --<mode>\n", argv[0]);
        exit(-1);
    }
    else if (argc == 3)
    {
        pMode = argv[2];
    }

    pSourceFile = fopen(argv[1], "r");
    if (!pSourceFile)
    {
        LOG_ERROR("Failed to open source file!\n");
        exit(-1);
    }

    bReady = true;

    if (argc == 3)
    {
        if (strcmp(pMode, "--lex") == 0)
        {
            while (getToken() != TOKEN_EOF);
        }
        else if (strcmp(pMode, "--parse") == 0)
        {
            (void) executeParser(&pTreeRoot);
            LOG_WARNING_SHORT("\n-------------------AST-------------------\n\n");
            PrintNode(pTreeRoot);
            LOG_WARNING_SHORT("\n\n-----------------AST END-----------------\n\n\n");


            
            if(executeSemanticAnalisys(pTreeRoot, &pGlobalSymTable) == SEMANTIC_OK)
            {
                LOG_WARNING_SHORT("\n\n-----------------SYMBOLS-----------------\n");
                printSymbolTables();
                LOG_WARNING_SHORT("\n\n-----------------SYMBOLS END-----------------\n");
            }
        }
    }
    else
    {
        //TODO: Reserved for future use, for complete compiling process
        LOG_ERROR("Usage: %s <source_file> --<mode>\n", argv[0]);
    }

    fclose(pSourceFile);

    return 0;
}



