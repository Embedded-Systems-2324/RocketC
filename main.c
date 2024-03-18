#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Util/Logger.h"
#include "Util/Globals.h"
#include "Lexer/Scanner.h"

static TreeNode_st pTreeRoot;
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
            while (getToken() != TOKEN_EOF);          //We use this for a scanner-only compiler because the Parser(using bison) autommaticly fetches the tokens whe he needs them
        }
        else if (strcmp(pMode, "--parse") == 0)
        {
//        syntaxTree = parse();
//        if (syntaxTree == NULL)
//            printf(" [DEBUG: Tree is empty]\n");
//        printTree(syntaxTree);
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
