%option noyywrap
%x INCOMMENT   

%{
#include "asm_globals.h"
%}

digit       [0-9]
hex         [a-fA-F]
number      {digit}+
hex_number  0x({digit}|{hex})+
letter      [a-zA-Z]

register    [rR]{digit}+
identifier  [a-zA-Z_][a-zA-Z0-9_]*

special_char [,#:;$]

newline     \n

%%
"ADD"   { printf(" ADD");                      /* return ADD; */    }
"SUB"   { printf(" SUB");                      /* return SUB; */    }
"OR"    { printf(" OR");                       /* return OR;  */    }
"AND"   { printf(" AND");                      /* return AND; */    }
"NOT"   { printf(" NOT");                      /* return NOT; */    }
"CMP"   { printf(" CMP");                      /* return CMP; */    }
        
"BRA"   { printf(" BRANCH_ALWAYS");            /* yyval=BRA_COND;     return BRANCH; */ }
"BCC"   { printf(" BRANCH_CARRY_CLEAR");       /* yyval=BNE_COND;     return BRANCH; */ }
"BVC"   { printf(" BRANCH_OVERFLOW_CLEAR");    /* yyval=BVC_COND;     return BRANCH; */ }
"BEQ"   { printf(" BRANCH_EQUAL");             /* yyval=BEQ_COND;     return BRANCH; */ }
"BGE"   { printf(" BRANCH_GREATER_EQUAL");     /* yyval=BGE_COND;     return BRANCH; */ }
"BGT"   { printf(" BRANCH_GREATER");           /* yyval=BGT_COND;     return BRANCH; */ }
"BPL"   { printf(" BRANCH_PLUS");              /* yyval=BPL_COND;     return BRANCH; */ }
"BNV"   { printf(" BRANCH_NEVER");             /* yyval=BNV_COND;     return BRANCH; */ }
"BCS"   { printf(" BRANCH_CARRY_SET");         /* yyval=BCS_COND;     return BRANCH; */ }
"BVS"   { printf(" BRANCH_OVERFLOW_SET");      /* yyval=BVS_COND;     return BRANCH; */ }
"BNE"   { printf(" BRANCH_NOT_EQUAL");         /* yyval=BNE_COND;     return BRANCH; */ }
"BLT"   { printf(" BRANCH_LESS");              /* yyval=BLT_COND;     return BRANCH; */ }
"BLE"   { printf(" BRANCH_LESS_EQUAL");        /* yyval=BLE_COND;     return BRANCH; */ }
"BMI"   { printf(" BRANCH_MINUS");             /* yyval=BMI_COND;     return BRANCH; */ }

"MOV"   { printf(" MOVE");             /* return MOVE;           */ }
"JMP"   { printf(" JUMP");             /* return JUMP;           */ }
"JMPL"  { printf(" JUMP_LONG");        /* return JUMP_LONG;      */ }
"LD"    { printf(" LOAD_DIRECT");      /* return LOAD_DIRECT;    */ }
"LDI"   { printf(" LOAD_IMMEDIATE");   /* return LOAD_IMMEDIATE; */ }
"LDX"   { printf(" LOAD_INDIRECT");    /* return LOAD_INDIRECT;  */ }
"ST"    { printf(" STORE_DIRECT");     /* return STORE_DIRECT;   */ }
"STX"   { printf(" STORE_INDIRECT");   /* return STORE_INDIRECT; */ }
"PUSH"  { printf(" PUSH");             /* return PUSH;           */ }
"POP"   { printf(" POP");              /* return POP;            */ }

"RETI"  { printf(" RETI");             /* return RETI;           */ }
"HALT"  { printf(" HALT");             /* return HALT;           */ }
"NOP"   { printf(" NOP");              /* return NOP;            */ }

".byte"  { printf(" .byte");           /*   return BYTE;          */  }
".word"  { printf(" .word");           /*   return WORD;          */  }
".alloc" { printf(" .alloc");          /*   return ALLOC;         */  }
".org"   { printf(" .org");            /*   return ORG;           */  }
".equ"   { printf(" .equ");            /*   return EQU;           */  }

"\0"    {/*return ENDFILE;*/} 

{number}        { printf(" [NUM]");           /*  return NUMBER;         */ }
{identifier}    { printf(" [IDENTIFIER]");    /*  return IDENTIFIER;     */ }
{register}      { printf(" [REGISTER]");      /*  return REGISTER;       */ }
{special_char}  { printf(" [SPECIAL_CHAR]");  /*  return SPECIAL_CHAR;   */ }
{hex_number}    { printf(" [HEX_NUMBER]");    /*  return HEX_NUMBER      */ }
{newline}       { printf(" \n");              /*  linenum++;             */ }

<<EOF>>         {yyterminate(); /* return ENDFILE; */ }
%%

void File_Init() {
    yyin = sourceCode;
}

TokenType getToken(void)
{ 
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime){ 
    firstTime = FALSE;
    yyin = sourceCode;
  }
  currentToken = yylex();
  return currentToken;
}