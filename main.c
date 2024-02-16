#include "globals.h"

FILE * sourceCode;

int main(int argc, char * argv[]){
    
    char pgm[120];
    /* 
    * If the number of command-line arguments is not equal to 2,
    * print a usage message to stderr indicating the correct usage of the program,
    * and exit the program with a return status of 1. (Correct usage: $ ./MyProgram test.c)
    */
    if (argc != 2){ 
        fprintf(stderr,"usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    
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

    while (getToken() != ENDFILE);  //We use this for a scanner-only compiler because the Parser(using bison) autommaticly fetches the tokens whe he needs them
    
    return 0;
}