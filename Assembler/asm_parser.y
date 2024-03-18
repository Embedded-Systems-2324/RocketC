%{
#include "asm_globals.h"

int yylex();
int yyerror(char *s);
%}

/* book-keeping tokens */
%token ENDFILE ERROR

/* Instruction Tokens */
%token ADD SUB OR AND XOR NOT CMP BRANCH MOVE JUMP JUMP_LONG
%token LOAD_DIRECT LOAD_IMMEDIATE LOAD_INDIRECT STORE_DIRECT STORE_INDIRECT PUSH POP
%token RETI HALT NOP

/*Directives tokens*/
%token BYTE WORD ALLOC ORG EQU

/* Data Tokens */
%token REG IDENTIFIER NUMBER

%%

/* Program */
prog : stmt
     | prog stmt
     ;

/* Statement */

stmt: add_stmt
    | sub_stmt
    | or_stmt
    | and_stmt
    | not_stmt
    | xor_stmt
    | cmp_stmt
    | branch_stmt
    | move_stmt
    | jump_stmt
    | load_dir_stmt
    | load_immd_stmt
    | load_indir_stmt
    | store_dir_stmt
    | store_indir_stmt
    | push_stmt
    | pop_stmt
    | reti_stmt
    | halt_stmt
    | nop_stmt
    | byte_stmt
    | word_stmt
    | alloc_stmt
    | org_stmt
    | equ_stmt
    | label
    ;

/* Instructions */

add_stmt : ADD REG ',' REG ',' REG          { add_stmt(ADD_OP,ADD_CODE, $2, $4, $6,REG_TYPE,WORD_SIZE);  } 
         | ADD REG ',' REG ',' '#'NUMBER    { add_stmt(ADD_OP,ADD_CODE, $2, $4, $7,IMMEDIATE,WORD_SIZE); }

sub_stmt : SUB REG ',' REG ',' REG          { add_stmt(SUB_OP,SUB_CODE, $2, $4, $6,REG_TYPE,WORD_SIZE);  }
         | SUB REG ',' REG ',' '#'NUMBER    { add_stmt(SUB_OP,SUB_CODE, $2, $4, $7,IMMEDIATE,WORD_SIZE); }

or_stmt : OR REG ',' REG ',' REG            { add_stmt(OR_OP,OR_CODE, $2, $4, $6,REG_TYPE,WORD_SIZE);    }
        | OR REG ',' REG ',' '#'NUMBER      { add_stmt(OR_OP,OR_CODE, $2, $4, $7,IMMEDIATE,WORD_SIZE);   }

and_stmt : AND REG ',' REG ',' REG          { add_stmt(AND_OP,AND_CODE, $2, $4, $6,REG_TYPE,WORD_SIZE);  }
         | AND REG ',' REG ',' '#'NUMBER    { add_stmt(AND_OP,AND_CODE, $2, $4, $7,IMMEDIATE,WORD_SIZE); }

not_stmt : NOT REG ',' REG          { add_stmt(ADD_OP,ADD_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);   }
         | NOT REG ',' '#'NUMBER    { add_stmt(ADD_OP,ADD_CODE,$2,$5,zero_ptr, IMMEDIATE,WORD_SIZE); }

xor_stmt : XOR REG ',' REG          { add_stmt(XOR_OP,XOR_CODE, $2, $4,REG_TYPE,WORD_SIZE);  }
         | XOR REG ',' '#'NUMBER    { add_stmt(XOR_OP,XOR_CODE, $2, $5,IMMEDIATE,WORD_SIZE); }

cmp_stmt : CMP REG ',' REG { add_stmt(CMP_OP,CMP_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE); }

branch_stmt : BRANCH REG ',' IDENTIFIER { add_stmt(BRANCH_OP,yylval,$2,zero_ptr,zero_ptr,$1,WORD_SIZE); }

move_stmt : MOVE REG ',' REG        { add_stmt(MOV_OP,MOV_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);  }
          | MOVE REG ',' '#'NUMBER  { add_stmt(MOV_OP,MOV_CODE,$2,$5,zero_ptr,IMMEDIATE,WORD_SIZE); } 

jump_stmt : JUMP REG ',' '#'NUMBER                 { add_stmt(JMP_OP,JMP_CODE,$2,$5,zero_ptr,IMMEDIATE,WORD_SIZE); }
          | JUMP_LONG REG ',' REG ',' '#'NUMBER    { add_stmt(JMP_OP,JMP_CODE,$2,$4,$7,zero_ptr,IMMEDIATE,WORD_SIZE);}

load_dir_stmt : LOAD_DIRECT REG ',' '#'NUMBER { add_stmt(LD_OP,LD_CODE,$2,zero_ptr,$5,IMMEDIATE,WORD_SIZE); }

load_immd_stmt : LOAD_IMMEDIATE REG ',' '#'NUMBER { add_stmt(LDI_OP,LDI_CODE,$2,zero_ptr,$5,IMMEDIATE,WORD_SIZE); }

load_indir_stmt : LOAD_INDIRECT REG ',' REG ',' '#'NUMBER { add_stmt(LDX_OP,LDX_CODE, $2, $4, $7, IMMEDIATE, WORD_SIZE); }

store_dir_stmt : STORE_DIRECT REG ',' '#'NUMBER { add_stmt(ST_OP,ST_CODE, $2, $5, IMMEDIATE, WORD_SIZE); }

store_indir_stmt : STORE_INDIRECT REG ',' REG ',' '#'NUMBER { add_stmt(ST_OP,ST_CODE, $2, zero_ptr, $4, $7, IMMEDIATE, WORD_SIZE); }

push_stmt : PUSH REG { add_stmt(NOP_OP,PUSH_CODE,$2, zero_ptr, zero_ptr, zero_ptr,WORD_SIZE);}

pop_stmt : POP REG { add_stmt(POP_OP,POP_CODE,$2, zero_ptr, zero_ptr, zero_ptr ,WORD_SIZE);}

reti_stmt : RETI { add_stmt(RETI_OP,RETI_CODE,$2, zero_ptr, zero_ptr, zero_ptr,WORD_SIZE);}

halt_stmt : HALT { add_stmt(HLT_OP,HLT_CODE,$2,zero_ptr, zero_ptr, zero_ptr, WORD_SIZE);}

nop_stmt : NOP { add_stmt(NOP_OP,NOP_CODE,$2, zero_ptr, zero_ptr, zero_ptr ,WORD_SIZE);}

byte_stmt : BYTE NUMBER { sym_table[$1].value = sym_table[$3].value; $$ = $1;}

word_stmt : WORD NUMBER { sym_table[$1].value = sym_table[$3].value; $$ = $1;}

alloc_stmt : ALLOC IDENTIFIER NUMBER {}

org_stmt : ORG NUMBER {}

equ_stmt : IDENTIFIER EQU NUMBER { sym_table[$1].value = sym_table[$3].value; $$ = $1;}

/* Labels */

label : IDENTIFIER ':' { sym_table[$1].value = lc; $$ = $1;}

%%

int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	return 1;
}