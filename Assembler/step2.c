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
    uint8_t inst_size = 0;
    uint8_t error = 0;

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
                    if(check_immed(get_symbol_value(current_statement.op3), IMMED16, i)) error = 1;
                    code |= 1 << 16;
                    code |= (0xffff & get_symbol_value(current_statement.op3));
                }
                else{
                    code |= (0x1f & get_symbol_value(current_statement.op3)) << 11;
                }
                break;

            case BXX_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0xf & current_statement.misc) << 23;
                if(get_symbol_value(current_statement.op1) == 0)
                    printf("Uninitialized symbol %s\n", table->sym_table[current_statement.op1].name);
                int brx_displ = get_symbol_value(current_statement.op1) - (lc - 4);
                if(check_immed(brx_displ, IMMED23, i)) error = 1;
                code |= (0x7fffff & brx_displ);
                break;


            case JMP_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                if(current_statement.misc == IMMEDIATE){
                    code |= 1 << 16;
                    code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                }
                code |= (0x1f & table->sym_table[current_statement.op2].value) << 17;
                code |= (0xffff & table->sym_table[current_statement.op3].value);
                break;


            case LD_OP ... LDI_OP:
            case ST_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                if(check_immed(table->sym_table[current_statement.op2].value, IMMED22, i)) error = 1;
                code |= (0x3fffff & table->sym_table[current_statement.op2].value);
                break;

            case LDX_OP:
            case STX_OP:
                code |= (0x1f & current_statement.op_code) << 27;
                code |= (0x1f & table->sym_table[current_statement.op1].value) << 22;
                code |= (0x1f & table->sym_table[current_statement.op2].value) << 17;
                if(check_immed(table->sym_table[current_statement.op3].value, IMMED17, i)) error = 1;
                code |= (0x1ffff & table->sym_table[current_statement.op3].value);
                break;


            case DOT_BYTE_OP:
                if(check_immed(table->sym_table[current_statement.op1].value, 8, i)) error = 1;
                code = table->sym_table[current_statement.op1].value & 0xff;
                inst_size = 1;
                break;


            case DOT_WORD_OP:
                code = table->sym_table[current_statement.op1].value & 0xffffffff;
                break;


            case DOT_ALLOC_OP:
                for (int j = 1; j <= table->sym_table[current_statement.op1].value; j++)
                    print_code(fp_hex, fp_bin, 0, 1, &lc, i);
                break;

            case DOT_ORG_OP:
                lc = table->sym_table[current_statement.op1].value;
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
        clear_file(file_name_hex);
        clear_file(file_name_bin);
    }
}

static void print_code(FILE *fp_hex, FILE *fp_bin, int code, uint8_t inst_size, uint32_t *lc, uint32_t i){
   
    print_code_hex(fp_hex, code, inst_size, lc);
    print_code_bin(fp_bin, code, inst_size, i);

    *lc += inst_size;
}

static void print_code_hex(FILE *fp, int code, uint8_t inst_size, uint32_t lc){
    fprintf(fp, "@%04x\n", lc);

    for(uint8_t j = inst_size; j > 0; j--){
        fprintf(fp, "%02x", (0xff & (code >> (8 * (j-1)))));
    }
    fprintf(fp,"\n");
}

static void print_code_binary(FILE *fp, int code, int inst_size, uint32_t i){

    for(uint8_t j = inst_size * 8; j > 0; j--){
        fprintf(fp, "%d", (code >> (j - 1)) & 1); 
    }

    if (i < get_current_stmt_index()-1)
        fprintf(fp, ",\n");
    else 
        fprintf(fp, ";");
}

// check_immed limpar ficheiro
// ter em atencao a linha

static int check_immed(int value, int width, int i){

    int max_possible = 1 << (width-1);

    if((value >= max_possible) || (value <= -max_possible)){
        LOG_DEBUG("The value: %d, must be smaller than: %d", value, max_possible);
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
