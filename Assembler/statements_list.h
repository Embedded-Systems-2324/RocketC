#ifndef _STATEMENTS_LIST_H_
#define _STATEMENTS_LIST_H_

#include <stdint.h>

#define NO_TYPE     0
#define REG_TYPE    1
#define IMMEDIATE   2
#define PSEUDO_OP   3


typedef struct{
    uint32_t op_type;
    uint32_t op_code;
    uint32_t op1;
    uint32_t op2;
    uint32_t op3;
    uint32_t misc;
    uint32_t line_num;
}statement_t;



void init_statements_list();
uint8_t add_statement(uint32_t op_type, uint32_t op_code, uint32_t op1, uint32_t op2, uint32_t op3, uint32_t misc);

const uint32_t get_location_counter();
const uint32_t get_current_stmt_index();
const statement_t get_statement(uint8_t index);

void print_statements();

#endif



//colocar a retornar se não inicializado