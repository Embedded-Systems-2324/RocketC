#include "asm_globals.h"

int main(int argc, char * argv[]){

    if (argc == 0){
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
        
    return 0;
}