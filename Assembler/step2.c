#include <stdio.h>
#include "step2.h"
#include "asm_operations.h"
#include "symbol_table.h"
#include "statements_list.h"
#include "symbol_table.h"
#include "logger.h"


uint32_t run_step2(char *file_name_hex){
    
    FILE *fp_hex;
    FILE *fp_bin;
    char *file_name_bin = "code.coe";
    uint32_t code = 0;
    statement_t current_statement;
    uint32_t lc = 0;

    fp_hex = fopen(file_name_hex, "w");
    if (fp_hex == NULL) {
        LOG_DEBUG("Error Opening File: \n", file_name_hex);
        return 0;
    }
    
    fp_bin = fopen(file_name_bin, "w");
    if (fp_bin == NULL) {
        LOG_DEBUG("Error Opening File: \n", file_name_bin);
        return 0;
    }

    fprintf(fp_bin, "memory_initialization_radix=2;\n memory_initialization_vector=\n");

    for (uint32_t i = 0; i < get_current_stmt_index(); i++){
        current_statement = get_statement(i);
        
        switch (current_statement.op_type){
            case NOP_OP:
            case HLT_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                print_code(code, 4, &lc);
                break;


            case NOT_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                code |= (0x1f & get_symbol_value(current_statement.op2)) << 17;
                print_code(code, 4, &lc);
                break;


            case ADD_OP ... AND_OP:
            case XOR_OP ... CMP_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & get_symbol_value(current_statement.op1)) << 22;
                code |= (0x1f & get_symbol_value(current_statement.op2)) << 17;
                if(current_statement.misc == IMMEDIATE){
                    check_immed(get_symbol_value(current_statement.op3), IMMED16, i);
                    code |= 1 << 16;
                    code |= (0xffff & get_symbol_value(current_statement.op3));
                }
                else{
                    code |= (0x1f & get_symbol_value(current_statement.op3)) << 11;
                }
                print_code(code, 4, &lc);
                break;


            case BXX_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0xf & current_statement.misc) << 23;
                if(get_symbol_value(current_statement.op1) == 0)
                    printf("Uninitialized symbol %s\n", table->sym_table[current_statement.op1].name);
                int brx_displ = get_symbol_value(current_statement.op1) - (lc - 4);
                check_immed(brx_displ, IMMED23, i);
                code |= (0x7fffff & brx_displ);
                print_code(code, 4, &lc);
                break;


            case JMP_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                if(current_statement.misc == IMMEDIATE){
                    code |= 1 << 16;
                    code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                }
                code |= (0x1f & table->sym_table[current_statement.op2].value) << 17;
                code |= (0xffff & table->sym_table[current_statement.op3].value);
                print_code(code, 4, &lc);
                break;


            case LD_OP ... LDI_OP:
            case ST_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                check_immed(table->sym_table[current_statement.op2].value, IMMED22, i);
                code |= (0x3fffff & table->sym_table[current_statement.op2].value);
                print_code(code, 4, &lc);
                break;

            case LDX_OP:
            case STX_OP:
                code = 0;
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                code |= (0x1f & table->sym_table[current_statement.op2].value) << 17;
                check_immed(table->sym_table[current_statement.op3].value, IMMED17, i);
                code |= (0x1ffff & table->sym_table[current_statement.op3].value);
                print_code(code, 4, &lc);
                break;


            case DOT_BYTE_OP:
                check_immed(table->sym_table[current_statement.op1].value, 8, i);
                code = table->sym_table[current_statement.op1].value & 0xff;
                print_code(code, 1, &lc);
                break;


            case DOT_WORD_OP:
                code = table->sym_table[current_statement.op1].value & 0xffffffff;
                print_code(code, 4, &lc);
                break;


            case DOT_ALLOC_OP:
                for (int j = 1; j <= table->sym_table[current_statement.op1].value; j++)
                    print_code(code, 1, &lc);
                break;


            case DOT_ORG_OP:
                lc = table->sym_table[current_statement.op1].value;
                break;    

            default:
                break;
        }
    }


    fclose(fp_hex);
    fclose(fp_bin);
}

static void print_code(FILE *fp_hex, FILE *fp_bin, int code, int count, int *lc){
   
    print_code_hex(fp_hex, code, count, lc);
    print_code_bin(fp_hex, code, count);

    *lc += count;
}

static void print_code_hex(FILE *fp, int code, int count, int lc){
    fprintf(fp, "@%04x\n", lc);

    for(int j = count; j > 0; j--){
        fprintf(fp, "%02x", (0xff & (code >> (8 * (j-1)))));
    }
    fprintf(fp,"\n");

}

static void print_code_binary(FILE *fp, int code, int count){

    for(int i = count * 8; i > 0; i--){
        fprintf(fp, "%d", (code >> (i - 1)) & 1); 
    }
    fprintf(fp, "\n");

}

// check_immed limpar ficheiro
// ter em atencao a linha

static int check_immed(int value, int width, int i){

    int max_possible = 1 << (width-1);

    if((value >= max_possible) || (value <= -max_possible)){
        printf("The value: %d, must be smaller than: %d", value, max_possible);
        return 1;
    }

    return 0;
}


