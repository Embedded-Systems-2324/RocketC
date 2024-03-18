#ifndef _ASM_OPERATIONS_H_
#define _ASM_OPERATIONS_H_

#define NOP_OP      0
#define ADD_OP      1
#define SUB_OP      2
#define OR_OP       3
#define AND_OP      4
#define NOT_OP      5
#define XOR_OP      6
#define CMP_OP      7
#define BXX_OP      8
#define JMP_OP      9
#define LD_OP       10
#define LDI_OP      11
#define LDX_OP      12
#define ST_OP       13
#define STX_OP      14
#define HLT_OP      31

#define DOT_BYTE_OP 17 
#define DOT_WORD_OP 18
#define DOT_ALLOC_OP 19
#define DOT_ORG_OP 20

#define IMMED16 16
#define IMMED17 17
#define IMMED22 22
#define IMMED23 23

#endif