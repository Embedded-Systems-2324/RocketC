%{
#include "asm_globals.h"

int yylex();
int yyerror(char *s);
%}

/* book-keeping tokens */
%token ENDFILE ERROR

/* Instruction Tokens */
%token ADD SUB OR AND NOT CMP BRANCH MOVE JUMP JUMP_LONG
%token LOAD LOAD_IMMEDIATE LOAD_INDIRECT STORE_DIRECT STORE_INDIRECT PUSH POP
%token RETI HALT NOP

/*Directives tokens*/
%token BYTE WORD ALLOC ORG EQU

/* */
%token REG IDENTIFIER NUMBER


/*Data types*/


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
    ;

/* Instructions */

add_stmt : ADD REG ',' REG ',' REG
         | ADD REG ',' REG ',' '#'NUMBER

sub_stmt : SUB 

or_stmt : OR

and_stmt : AND

not_stmt : NOT

cmp_stmt : CMP

branch_stmt : BRANCH

move_stmt : MOVE

jump_stmt : JUMP
          | JUMP_LONG

load_dir_stmt : LOAD

load_immd_stmt : LOAD_IMMEDIATE

load_indir_stmt : LOAD_INDIRECT

store_dir_stmt : STORE_DIRECT

store_indir_stmt : STORE_INDIRECT

push_stmt : PUSH

pop_stmt : POP

reti_stmt : RETI {}

halt_stmt : HALT {}

nop_stmt : NOP {}

byte_stmt :

word_stmt :

alloc_stmt :

org_stmt :

equ_stmt :

/* Labels */

label : IDENTIFIER ':' {}

%%

int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	return 1;
}