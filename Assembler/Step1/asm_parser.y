%{
#include "../Util/asm_globals.h"
#include "../Step1/asm_scanner.h"
#include "../Output/asm_parser.tab.h"
#include "../Util/statements_list.h"
#include "../main.h"

int yylex();
int yyerror(char *str);

#define NULL_ARG    0

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
%token DOLAR  
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
                        add_statement(ADD_OP,ADD_CODE, $2, $4, $6,REG_TYPE); 
                    } 
            |   ADD REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        add_statement(ADD_OP,ADD_CODE, $2, $4, $7,IMMEDIATE); 
                    }
            ;        


sub_stmt    :   SUB REG COMMA REG COMMA REG                
                    { 
                        add_statement(SUB_OP,SUB_CODE, $2, $4, $6,REG_TYPE);  
                    }
            |   SUB REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        add_statement(SUB_OP,SUB_CODE, $2, $4, $7,IMMEDIATE); 
                    }
            ;        


or_stmt     :   OR REG COMMA REG COMMA REG                  
                    { 
                        add_statement(OR_OP,OR_CODE, $2, $4, $6,REG_TYPE);    
                    }
            |   OR REG COMMA REG COMMA CARDINAL NUMBER      
                    { 
                        add_statement(OR_OP,OR_CODE, $2, $4, $7,IMMEDIATE);   
                    }
            ;

and_stmt    :   AND REG COMMA REG COMMA REG                
                    { 
                        add_statement(AND_OP,AND_CODE, $2, $4, $6,REG_TYPE);  
                    }
            |   AND REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        add_statement(AND_OP,AND_CODE, $2, $4, $7,IMMEDIATE); 
                    }
            ;


not_stmt    :   NOT REG COMMA REG                          
                    { 
                        add_statement(NOT_OP,NOT_CODE,$2,$4,NULL_ARG,REG_TYPE);   
                    }
            |   NOT REG COMMA CARDINAL NUMBER              
                    { 
                        add_statement(NOT_OP,NOT_CODE,$2,$5,NULL_ARG, IMMEDIATE); 
                    }
            ;        


xor_stmt    :   XOR REG COMMA REG                          
                    { 
                        add_statement(XOR_OP,XOR_CODE, $2, $4,REG_TYPE);  
                    }
            |   XOR REG COMMA CARDINAL NUMBER              
                    { 
                        add_statement(XOR_OP,XOR_CODE, $2, $5,IMMEDIATE); 
                    }
            ;


cmp_stmt    :   CMP REG COMMA REG                          
                    { 
                        add_statement(CMP_OP,CMP_CODE,$2,$4,NULL_ARG,REG_TYPE);
                    };


branch_stmt :   BRANCH REG COMMA IDENTIFIER             
                    {
                        add_statement(BRANCH_OP,yylval,$2,NULL_ARG,NULL_ARG,$1); 
                    };


move_stmt   :   MOVE REG COMMA REG                        
                    {
                        add_statement(MOV_OP,MOV_CODE,$2,$4,NULL_ARG,REG_TYPE);  
                    }
            |   MOVE REG COMMA CARDINAL NUMBER            
                    { 
                        add_statement(MOV_OP,MOV_CODE,$2,$5,NULL_ARG,IMMEDIATE); 
                    } 
            ;        


jump_stmt   :   JUMP REG COMMA CARDINAL NUMBER                   
                    { 
                        add_statement(JMP_OP,JMP_CODE,$2,$5,NULL_ARG,IMMEDIATE); 
                    }
            |   JUMP_LINK REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        add_statement(JMP_OP,JMP_CODE,$2,$4,$7,NULL_ARG,IMMEDIATE);
                    }
            ;        


load_stmt   :   LOAD_DIRECT REG COMMA CARDINAL NUMBER               
                    { 
                        add_statement(LD_OP,LD_CODE,$2,NULL_ARG,$5,IMMEDIATE); 
                    }

            |   LOAD_IMMEDIATE REG COMMA CARDINAL NUMBER           
                    {
                        add_statement(LDI_OP,LDI_CODE,$2,NULL_ARG,$5,IMMEDIATE); 
                    }
            |   LOAD_INDEXED REG COMMA REG COMMA CARDINAL NUMBER  
                    { 
                        add_statement(LDX_OP,LDX_CODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;        


store_stmt  :   STORE_DIRECT REG COMMA CARDINAL NUMBER             
                    { 
                        add_statement(ST_OP,ST_CODE, $2, $5, IMMEDIATE); 
                    }
            |   STORE_INDEXED REG COMMA REG COMMA CARDINAL NUMBER
                    { 
                        add_statement(ST_OP, ST_CODE, $2, $4, $7, IMMEDIATE); 
                    }
            ;        


push_stmt   :   PUSH REG 
                    { 
                        add_statement(PUSH_OP,PUSH_CODE,$2, NULL_ARG, NULL_ARG, NULL_ARG);
                    };


pop_stmt    :   POP REG   
                    { 
                        add_statement(POP_OP, POP_CODE,$2, NULL_ARG, NULL_ARG, NULL_ARG);
                    };


reti_stmt   :   RETI     
                    {
                        add_statement(RETI_OP, RETI_CODE, NULL_ARG, NULL_ARG, NULL_ARG, NULL_ARG);
                    };

halt_stmt   :   HALT 
                    { 
                        add_statement(HLT_OP, HLT_CODE, NULL_ARG, NULL_ARG, NULL_ARG, NULL_ARG);
                    };


nop_stmt    :   NOP 
                    { 
                        add_statement(NOP_OP, NOP_CODE, NULL_ARG, NULL_ARG, NULL_ARG, NULL_ARG);
                    };


byte_stmt   :   BYTE NUMBER 
                    { 
                        /*sym_table[$1].value = sym_table[$3].value; $$ = $1;*/
                    };


word_stmt   :   WORD NUMBER 
                    { 
                        /*sym_table[$1].value = sym_table[$3].value; $$ = $1;*/
                    };


alloc_stmt  :   ALLOC IDENTIFIER NUMBER 
                    {

                    };


org_stmt    :   ORG NUMBER 
                    {

                    };


equ_stmt    :   IDENTIFIER EQU NUMBER 
                    { 
                        /*sym_table[$1].value = sym_table[$3].value; $$ = $1;*/
                    };


/* Labels */
label       :   IDENTIFIER COLON 
                    { 
                        /*sym_table[$1].value = lc; $$ = $1;*/
                    };
%%


int yyerror(char *str)
{
  	fprintf (stderr, "%s in line number : %ld\n", str, get_line_number());
	return 1;
}