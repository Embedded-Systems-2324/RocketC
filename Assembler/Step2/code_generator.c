#include <stdio.h>
#include <stdint.h>
#include "../Step2/code_generator.h"
#include "../Util/asm_operations.h"
#include "../Util/symbol_table.h"
#include "../Util/statements_list.h"
#include "../Util/logger.h"
#include "../main.h"

#define IMMED16 16
#define IMMED17 17
#define IMMED22 22
#define IMMED23 23

static void print_code(FILE *fp_hex, FILE *fp_bin, int code, uint8_t inst_size, uint32_t *lc, uint32_t i);
static void print_code_hex(FILE *fp, int code, uint8_t inst_size, uint32_t lc);
static int check_immed(int value, int width, int i);
static void clear_file(char *file_name);


uint32_t generate_code(){
    
    FILE *fp_hex;
    FILE *fp_bin;
    char *file_name_bin = "code.coe";
    uint32_t code = 0;
    statement_t current_statement;
    uint32_t lc = 0;
    uint8_t inst_size = 0;
    uint8_t error = 0;

    fp_hex = fopen("out.hex", "w");
    if (fp_hex == NULL) {
        LOG_DEBUG("Error Opening File: \n", "out");
        return 0;
    }
    
    fp_bin = fopen(file_name_bin, "w");
    if (fp_bin == NULL) {
        LOG_DEBUG("Error Opening File: \n", file_name_bin);
        return 0;
    }

    fprintf(fp_bin, "memory_initialization_radix=2;\n memory_initialization_vector=\n");

    for (uint32_t i = 0; i < get_current_stmt_index(); i++){
        
        inst_size = 4;
        code = 0;
        current_statement = get_statement(i);
        
        switch (current_statement.op_type){
            case NOP_OP:
            case HLT_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                break;


            case NOT_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                code |= (0x1f & get_symbol_value(current_statement.op2)) << 17;
                break;


            case ADD_OP ... AND_OP:
            case XOR_OP ... CMP_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                code |= (0x1f & get_symbol_value(current_statement.op2)) << 17;
                
                if(current_statement.misc == IMMEDIATE){
                    error = check_immed(get_symbol_value(current_statement.op3), IMMED16, i);
                    code |= 1 << 16;
                    code |= (0xffff & get_symbol_value(current_statement.op3));
                }
                else{
                    code |= (0x1f & get_symbol_value(current_statement.op3)) << 11;
                }
                break;


            case BXX_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0xf & current_statement.op_type) << 23;
                
                if(get_symbol_value(current_statement.op1) == 0){
                    printf("Uninitialized symbol %d\n", get_symbol_value(current_statement.op1));
                }
                int brx_displ = get_symbol_value(current_statement.op1) - (lc - 4);
                error = check_immed(brx_displ, IMMED23, i);

                code |= (0x7fffff & brx_displ);
                break;


            case JMP_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                
                if(current_statement.misc == LINK){
                    code |= 1 << 16;
                    code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                }
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 17;
                code |= (0xffff & get_symbol_value(current_statement.op3));
                break;


            case LD_OP ... LDI_OP:
            case ST_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                
                error = check_immed(get_symbol_value(current_statement.op2), IMMED22, i);
                code |= (0x3fffff & get_symbol_value(current_statement.op2));
                break;

            case LDX_OP:
            case STX_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                code |= (0x1f & get_symbol_value(current_statement.op2)) << 17;
                error = check_immed(get_symbol_value(current_statement.op3), IMMED17, i);
                code |= (0x1ffff & get_symbol_value(current_statement.op3));
                break;


            case DOT_BYTE_OP:
                error = check_immed(get_symbol_value(current_statement.op1), 8, i);
                code = get_symbol_value(current_statement.op1) & 0xff;
                inst_size = 1;
                break;


            case DOT_WORD_OP:
                code = get_symbol_value(current_statement.op1) & 0xffffffff;
                break;


            case DOT_ALLOC_OP:
                for (int j = 1; j <= get_symbol_value(current_statement.op1); j++)
                    print_code(fp_hex, fp_bin, 0, 1, &lc, i);
                break;

            case DOT_ORG_OP:
                lc = get_symbol_value(current_statement.op1);
                break;    

            default:
                break;
        }
        
        if (current_statement.op_type < DOT_ALLOC_OP)
            print_code(fp_hex, fp_bin, code, inst_size, &lc, i);
    }

    fclose(fp_hex);
    fclose(fp_bin);

    if(error){
        clear_file("out.hex");
        //clear_file(file_name_bin);
    }
}



static void print_code(FILE *fp_hex, FILE *fp_bin, int code, uint8_t inst_size, uint32_t *lc, uint32_t i){
   
    print_code_hex(fp_hex, code, inst_size, *lc);

    *lc += inst_size;
}



static void print_code_hex(FILE *fp, int code, uint8_t inst_size, uint32_t lc){
    fprintf(fp, "@%04x", lc);

    for(uint8_t j = inst_size; j > 0; j--){
        fprintf(fp, " %02x", (0xff & (code >> (8 * (j-1)))));
    }
    fprintf(fp,"\n");
}




static int check_immed(int value, int width, int i){

    int max_possible = 1 << (width-1);

    if((value >= max_possible) || (value <= -max_possible)){
        printf("The value: %d, must be smaller than: %d", value, max_possible);
        return 1;
    }

    return 0;
}



static void clear_file(char *file_name) {
    FILE *fp = fopen(file_name, "w");
    if (fp != NULL) {
        fclose(fp);
    }
}        