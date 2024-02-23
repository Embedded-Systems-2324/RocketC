#include "globals.h"
#include "scanner.h"
#include "parser.h"

FILE * sourceCode;

int main(int argc, char * argv[]){
    char* mode;     // --flex or --parse
    char pgm[120];

    /* 
    * If the number of command-line arguments is not equal to 2 or 3,
    * print a usage message to stderr indicating the correct usage of the program,
    * and exit the program with a return status of 1. (Correct usage: $ ./MyProgram test.c or $ ./MyProgram test.c --lex/--parse)
    */
    if (argc < 2 || argc > 3){  /* The mode is optional*/
        fprintf(stderr,"usage: %s <filename> --<mode>\n",argv[0]);
        exit(1);
    }else if (argc == 3) mode = argv[2];
    
    /* 
    * Copy the filename provided as a command-line argument to the 'pgm' variable.
    * If the filename does not contain a file extension, append ".c" to it.
    */
    strcpy(pgm,argv[1]);
    if (strchr (pgm, '.') == NULL)  strcat(pgm,".c");
    /*Open the source code file in read mode and checks if it exists or cannot be opened*/
    sourceCode = fopen(pgm,"r");
    if (sourceCode==NULL)
    { 
        fprintf(stderr,"File %s not found\n",pgm);
        exit(1);
    }
    
    if (strcmp(mode, "--lex") == 0) {
        while (getToken() != ENDFILE);          //We use this for a scanner-only compiler because the Parser(using bison) autommaticly fetches the tokens whe he needs them
    } else if (strcmp(mode, "--parse") == 0) {
        parse();
    } else {
        printf("Default Mode\n");               //No mode was selected
        return 0;
    }
  
    fclose(sourceCode); 
    return 0;
}
