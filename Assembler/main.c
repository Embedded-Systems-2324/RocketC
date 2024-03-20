#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "Util/logger.h"
#include "Step1/asm_scanner.h"
#include "Output/asm_parser.tab.h"


static FILE* pSourceFile;
static size_t lineNumber = 1;


size_t get_line_number()
{
    return lineNumber;
}


size_t increment_line_number(size_t n)
{
    lineNumber += n;
    return lineNumber;
}


void get_source_file(FILE** ppFile){
    *ppFile = pSourceFile;
}


int main(int argc, char *argv[]){
    char* pMode;
    
    if (argc < 2 || argc > 3)
    {
        printf("Usage: %s <source_file> --<mode>\n", argv[0]);
        exit(-1);
    }
    else if (argc == 3)
    {
        pMode = argv[2];
    }

    pSourceFile = fopen(argv[1], "r");
    if (!pSourceFile)
    {
        printf("Failed to open source file!\n");
        exit(-1);
    }

    if (argc == 3)
    {
        if (strcmp(pMode, "--lex") == 0)
        {
            while (getToken() != ENDFILE);
        }
        else if (strcmp(pMode, "--parse") == 0)
        {
            initLexer();
            yyparse();
        }
    }
    else
    {

    }

    fclose(pSourceFile);

    return 0;
}