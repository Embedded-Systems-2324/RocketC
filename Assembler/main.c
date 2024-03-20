#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "Util/logger.h"
#include "Step1/asm_scanner.h"
#include "Output/asm_parser.tab.h"
#include "Util/statements_list.h"
#include "Util/symbol_table.h"
#include "Step2/code_generator.h"


static FILE* pSourceFile;
static FILE* pOutputFile;
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

void get_output_file(FILE** ppFile){
    *ppFile = pOutputFile;
}


int main(int argc, char *argv[]){
    char* pMode;

    init_statements_list();
    init_symbol_table();
    
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
            init_lexer();
            yyparse();
            generate_code();
        }
    }
    else
    {

    }

    fclose(pSourceFile);

    print_statements();
    print_table();

    return 0;
}