%{
#include "../Util/asm_globals.h"
#include "../Step1/asm_scanner.h"
#include "../Output/asm_parser.tab.h"
#include "../Util/statements_list.h"
#include "../Util/symbol_table.h"
#include "../Util/opcodes.h"
#include "../Util/asm_operations.h"
#include "../Util/logger.h"
#include "../main.h"

int yylex();
int yyerror(char *str);


#define NULL_ARG    0

static int bra_cond = 0;

%}

/* ---- TOKENS TYPES ----- */
%token ADD
%token SUB
%token OR
%token AND
%token NOT
%token XOR
%token CMP
%token BRANCH
%token JUMP
%token JUMP_LINK
%token MOVE
%token LOAD_DIRECT
%token LOAD_IMMEDIATE
%token LOAD_INDEXED
%token STORE_DIRECT
%token STORE_INDEXED
%token PUSH
%token POP
%token RETI
%token HALT
%token NOP
%token NUMBER
%token REG
%token IDENTIFIER
%token ENDFILE
%token ERROR
%token COMMA
%token CARDINAL
%token COLON
%token DOLLAR  
%token BYTE
%token WORD
%token ALLOC
%token ORG
%token EQU

%%

/* Program */
prog    :   prog ENDFILE
        |   prog stmt
        |   stmt
        ;

/* Statement */
stmt    :   add_stmt
        |   sub_stmt
        |   or_stmt
        |   and_stmt
        |   not_stmt
        |   xor_stmt
        |   cmp_stmt
        |   branch_stmt
        |   move_stmt
        |   jump_stmt
        |   load_stmt
        |   store_stmt
        |   push_stmt
        |   pop_stmt
        |   reti_stmt
        |   halt_stmt
        |   nop_stmt
        |   byte_stmt
        |   word_stmt
        |   alloc_stmt
        |   org_stmt
        |   equ_stmt
        |   label
        ;


/* Instructions */
add_stmt    :   ADD REG COMMA REG COMMA REG                
                    {  
                        add_statement(ADD_OP, ADD_OPCODE, $2, $4, $6, NO_TYPE); 
                    } 
            |   ADD REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        add_statement(ADD_OP, ADD_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;        


sub_stmt    :   SUB REG COMMA REG COMMA REG                
                    { 
                        add_statement(SUB_OP, SUB_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   SUB REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        add_statement(SUB_OP, SUB_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;        


or_stmt     :   OR REG COMMA REG COMMA REG                  
                    { 
                        add_statement(OR_OP, OR_OPCODE, $2, $4, $6, NO_TYPE);    
                    }
            |   OR REG COMMA REG COMMA CARDINAL NUMBER      
                    { 
                        add_statement(OR_OP, OR_OPCODE, $2, $4, $7, IMMEDIATE);   
                    } 
            ;

and_stmt    :   AND REG COMMA REG COMMA REG                
                    { 
                        add_statement(AND_OP, AND_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   AND REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        add_statement(AND_OP, AND_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;


xor_stmt    :   XOR REG COMMA REG COMMA REG                          
                    { 
                        add_statement(XOR_OP, XOR_OPCODE, $2, $4, $6, NO_TYPE);  
                    }
            |   XOR REG COMMA REG COMMA CARDINAL NUMBER              
                    { 
                        add_statement(XOR_OP, XOR_OPCODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;


not_stmt    :   NOT REG COMMA REG                          
                    { 
                        add_statement(NOT_OP, NOT_OPCODE, $2, $4, NULL_ARG, NO_TYPE);   
                    }
            |   NOT REG COMMA CARDINAL NUMBER              
                    { 
                        add_statement(NOT_OP, NOT_OPCODE, $2, $5, NULL_ARG, IMMEDIATE); 
                    }
            ;        


cmp_stmt    :   CMP REG COMMA REG                          
                    { 
                        add_statement(CMP_OP, CMP_OPCODE, $2, $4, NULL_ARG, NO_TYPE);
                    };


branch_stmt :   BRANCH IDENTIFIER             
                    {
                        add_statement(BXX_OP, BXX_OPCODE, $2, NULL_ARG, NULL_ARG, bra_cond); 
                    };
            |   BRANCH REG COMMA CARDINAL NUMBER   
                    {
                        add_statement(BXX_OP, BXX_OPCODE, $2, NULL_ARG, NULL_ARG, bra_cond); 
                    };  
            |   BRANCH DOLLAR
                    {
                        add_statement(BXX_OP, BXX_OPCODE, $2, NULL_ARG, NULL_ARG, bra_cond);
                    };    


move_stmt   :   MOVE REG COMMA REG                        
                    {
                        add_statement(ADD_OP, ADD_OPCODE, $2, $4, 0, IMMEDIATE);
                    };     


jump_stmt   :   JUMP REG COMMA CARDINAL NUMBER                   
                    { 
                        add_statement(JMP_OP, JMP_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   JUMP_LINK REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        add_statement(JMP_OP, JMP_OPCODE, $2, $4 , $7, LINK);
                    }
            ;        


load_stmt   :   LOAD_DIRECT REG COMMA CARDINAL NUMBER               
                    { 
                        add_statement(LD_OP, LD_OPCODE, $2, NULL_ARG, $5, NO_TYPE); 
                    }

            |   LOAD_IMMEDIATE REG COMMA CARDINAL NUMBER           
                    {
                        add_statement(LDI_OP, LDI_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   LOAD_INDEXED REG COMMA REG COMMA CARDINAL NUMBER  
                    { 
                        add_statement(LDX_OP, LDX_OPCODE, $2, $4, $7, NO_TYPE); 
                    }
            ;        


store_stmt  :   STORE_DIRECT REG COMMA CARDINAL NUMBER             
                    { 
                        add_statement(ST_OP,ST_OPCODE, $2, $5, NULL_ARG, NO_TYPE); 
                    }
            |   STORE_INDEXED REG COMMA REG COMMA CARDINAL NUMBER
                    { 
                        add_statement(STX_OP, ST_OPCODE, $2, $4, $7, NO_TYPE);
                    }
            ;        


push_stmt   :   PUSH REG 
                    { 
                        add_statement(PUSH_OP,PUSH_OPCODE,$2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


pop_stmt    :   POP REG   
                    { 
                        add_statement(POP_OP, POP_OPCODE,$2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


reti_stmt   :   RETI     
                    {
                        add_statement(RETI_OP, RETI_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };

halt_stmt   :   HALT 
                    { 
                        add_statement(HLT_OP, HLT_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


nop_stmt    :   NOP 
                    { 
                        add_statement(NOP_OP, NOP_OPCODE, NULL_ARG, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


byte_stmt   :   BYTE NUMBER 
                    { 
                        add_statement(DOT_BYTE_OP, DOT_BYTE_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


word_stmt   :   WORD NUMBER 
                    { 
                        add_statement(DOT_WORD_OP, DOT_WORD_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


alloc_stmt  :   ALLOC IDENTIFIER NUMBER
                    {
                        add_statement(DOT_ALLOC_OP, DOT_ALLOC_OP, $3, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


org_stmt    :   ORG NUMBER 
                    {
                        add_statement(DOT_ORG_OP, DOT_ORG_OP, $2, NULL_ARG, NULL_ARG, NO_TYPE);
                    };


equ_stmt    :   EQU IDENTIFIER COMMA NUMBER 
                    {
                         if(get_symbol_value($1) != UNINITIALIZED_VALUE){
                            printf("ERROR: Constant redefinition: %s in line %ld\n", get_symbol_name($1), get_line_number());
                        }
                        else{
                            set_symbol_value($1, get_symbol_value($4));
                            $$ = $1;
                        }
                    };

/* Labels */
label       :   IDENTIFIER COLON 
                    { 
                        if(get_symbol_value($1) != UNINITIALIZED_VALUE){
                            printf("ERROR: Label redefinition: %s in line %ld\n", get_symbol_name($1), get_line_number());
                        }
                        else{
                            set_symbol_value($1, get_location_counter());
                            $$ = $1;
                        }
                    };
%%

int yyerror(char *str)
{
  	fprintf (stderr, "%s in line number : %ld\n", str, get_line_number());
	return 1;
}

int set_branch_condition(int condition)
{
    return bra_cond = condition;
}