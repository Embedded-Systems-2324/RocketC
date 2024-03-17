#include "asm_globals.h"
#include "asm_scanner.h"

FILE * sourceCode;
int linenum = 1;    //Line number zero doesnt exist

int main(int argc, char * argv[]){

    char pgm[120];

    if (argc == 0){
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
        
    strcpy(pgm, argv[1]);
    if (strchr(pgm, '.') == NULL)
        strcat(pgm, ".asm");

    sourceCode = fopen(pgm,"r");
    if(sourceCode == NULL)
    {
        fprintf(stderr, "File %s not found\n", pgm);
        exit(1);
    }

    while (getToken())

    //File_Init();

    //yyparse();

    fclose(sourceCode);
    return 0;
}