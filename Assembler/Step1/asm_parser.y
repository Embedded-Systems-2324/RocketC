%{
#include "../Util/asm_globals.h"
#include "../Step1/asm_scanner.h"
#include "../Output/asm_parser.tab.h"
#include "../Util/statements_list.h"
#include "../main.h"

int yylex();
int yyerror(char *str);

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
                        /*add_stmt(ADD_OP,ADD_CODE, $2, $4, $6,REG_TYPE)*/; 
                    } 
            |   ADD REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        /*add_stmt(ADD_OP,ADD_CODE, $2, $4, $7,IMMEDIATE)*/; 
                    }
            ;        


sub_stmt    :   SUB REG COMMA REG COMMA REG                
                    { 
                        /*add_stmt(SUB_OP,SUB_CODE, $2, $4, $6,REG_TYPE)*/;  
                    }
            |   SUB REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        /*add_stmt(SUB_OP,SUB_CODE, $2, $4, $7,IMMEDIATE)*/; 
                    }
            ;        


or_stmt     :   OR REG COMMA REG COMMA REG                  
                    { 
                        /*add_stmt(OR_OP,OR_CODE, $2, $4, $6,REG_TYPE)*/;    
                    }
            |   OR REG COMMA REG COMMA CARDINAL NUMBER      
                    { 
                        /*add_stmt(OR_OP,OR_CODE, $2, $4, $7,IMMEDIATE)*/;   
                    }
            ;

and_stmt    :   AND REG COMMA REG COMMA REG                
                    { 
                        /*add_stmt(AND_OP,AND_CODE, $2, $4, $6,REG_TYPE)*/;  
                    }
            |   AND REG COMMA REG COMMA CARDINAL NUMBER    
                    { 
                        /*add_stmt(AND_OP,AND_CODE, $2, $4, $7,IMMEDIATE)*/; 
                    }
            ;


not_stmt    :   NOT REG COMMA REG                          
                    { 
                        /*add_stmt(NOT_OP,ADD_CODE,$2,$4,zero_ptr,REG_TYPE)*/;   
                    }
            |   NOT REG COMMA CARDINAL NUMBER              
                    { 
                        /*add_stmt(NOT_OP,ADD_CODE,$2,$5,zero_ptr, IMMEDIATE)*/; 
                    }
            ;        


xor_stmt    :   XOR REG COMMA REG                          
                    { 
                        /*add_stmt(XOR_OP,XOR_CODE, $2, $4,REG_TYPE)*/;  
                    }
            |   XOR REG COMMA CARDINAL NUMBER              
                    { 
                        /*add_stmt(XOR_OP,XOR_CODE, $2, $5,IMMEDIATE)*/; 
                    }
            ;


cmp_stmt    :   CMP REG COMMA REG                          
                    { 
                        /*add_stmt(CMP_OP,CMP_CODE,$2,$4,zero_ptr,REG_TYPE)*/;
                    };


branch_stmt :   BRANCH REG COMMA IDENTIFIER             
                    {
                        /*add_stmt(BRANCH_OP,yylval,$2,zero_ptr,zero_ptr,$1)*/; 
                    };


move_stmt   :   MOVE REG COMMA REG                        
                    {
                        /*add_stmt(MOV_OP,MOV_CODE,$2,$4,zero_ptr,REG_TYPE)*/;  
                    }
            |   MOVE REG COMMA CARDINAL NUMBER            
                    { 
                        /*add_stmt(MOV_OP,MOV_CODE,$2,$5,zero_ptr,IMMEDIATE)*/; 
                    } 
            ;        


jump_stmt   :   JUMP REG COMMA CARDINAL NUMBER                   
                    { 
                        /*add_stmt(JMP_OP,JMP_CODE,$2,$5,zero_ptr,IMMEDIATE)*/; 
                    }
            |   JUMP_LINK REG COMMA REG COMMA CARDINAL NUMBER    
                    {
                        /*add_stmt(JMP_OP,JMP_CODE,$2,$4,$7,zero_ptr,IMMEDIATE)*/;
                    }
            ;        


load_stmt   :   LOAD_DIRECT REG COMMA CARDINAL NUMBER               
                    { 
                        /*add_stmt(LD_OP,LD_CODE,$2,zero_ptr,$5,IMMEDIATE)*/; 
                    }

            |   LOAD_IMMEDIATE REG COMMA CARDINAL NUMBER           
                    {
                        /*add_stmt(LDI_OP,LDI_CODE,$2,zero_ptr,$5,IMMEDIATE)*/; 
                    }
            |   LOAD_INDEXED REG COMMA REG COMMA CARDINAL NUMBER  
                    { 
                        /*add_stmt(LDX_OP,LDX_CODE, $2, $4, $7, IMMEDIATE)*/; 
                    }
            ;        


store_stmt  :   STORE_DIRECT REG COMMA CARDINAL NUMBER             
                    { 
                        /*add_stmt(ST_OP,ST_CODE, $2, $5, IMMEDIATE)*/; 
                    }
            |   STORE_INDEXED REG COMMA REG COMMA CARDINAL NUMBER
                    { 
                        /*add_stmt(ST_OP,ST_CODE, $2, zero_ptr, $4, $7, IMMEDIATE)*/; 
                    }
            ;        


push_stmt   :   PUSH REG 
                    { 
                        /*add_stmt(NOP_OP,PUSH_CODE,$2, zero_ptr, zero_ptr, zero_ptr)*/;
                    };


pop_stmt    :   POP REG   
                    { 
                        /*add_stmt(POP_OP,POP_CODE,$2, zero_ptr, zero_ptr, zero_ptr)*/;
                    };


reti_stmt   :   RETI     
                    {
                        /*add_stmt(RETI_OP,RETI_CODE,$2, zero_ptr, zero_ptr, zero_ptr)*/;
                    };

halt_stmt   :   HALT 
                    { 
                        /*add_stmt(HLT_OP,HLT_CODE,$2,zero_ptr, zero_ptr, zero_ptr)*/;
                    };


nop_stmt    :   NOP 
                    { 
                        /*add_stmt(NOP_OP,NOP_CODE,$2, zero_ptr, zero_ptr, zero_ptr)*/;
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