#include "assembler_vespa.h"
#include "step1.h"
#include "step2.h"
#include "symbol_table.h"
#include "statements_list.h"

#include <stdio.h>
#include <stdlib.h>

//#include "Parser.tab.h"

static int q_flag = 0;
static int s_flag = 0;

char *output_file;



int init_assembler(int argc, char *argv[]){
    init_symbol_table();
    init_statements_list();
    
    sprintf(output_file, "code.out");

    for(int i = 0; i < argc; i++){
        if(*argv[i] != '-'){
            if((yyin = fopen(argv[i], 'r')) == NULL){
                printf("Input file error\n");

                exit(EXIT_FAILURE);
            }
        }
        else{
            switch(*(argv[i] + 1)){
                case 'o':
                    sprintf(output_file, "%s", argv[i + 1]);
                    //i++;
                    break;

                case 'q':
                    q_flag = 1;
                    break;

                case 's':
                    s_flag = 1;
                    break;

                default:
                    printf("Illegal command line option: -%c", *argv[i + 1]);
                    exit(EXIT_FAILURE);
                    break;
            }
        } 
    }
}



int run_assembler(){
    //verificar se está inicializado
    
    run_step1();
    run_step2();

    if(q_flag){
        
    }

    if(s_flag){
        print_table();
    }

    //
}





