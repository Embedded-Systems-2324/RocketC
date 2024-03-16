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
"NOP"   { printf(" NOP");                       return NOP;     }

"ADD"   { printf(" ADD");                       return ADD;     }
"SUB"   { printf(" SUB");                       return SUB;     }
"OR"    { printf(" OR");                        return OR;      }
"AND"   { printf(" AND");                       return AND;     }
"NOT"   { printf(" NOT");                       return NOT;     }
"CMP"   { printf(" CMP");                       return CMP;     }
        
"BRA"   { printf(" BRANCH_ALWAYS");             return BRANCH_ALWAYS;           }
"BCC"   { printf(" BRANCH_CARRY_CLEAR");        return BRANCH_CARRY_CLEAR;      }
"BVC"   { printf(" BRANCH_OVERFLOW_CLEAR");     return BRANCH_OVERFLOW_CLEAR;   }
"BEQ"   { printf(" BRANCH_EQUAL");              return BRANCH_EQUAL;            }
"BGE"   { printf(" BRANCH_GREATER_EQUAL");      return BRANCH_GREATER_EQUAL;    }
"BGT"   { printf(" BRANCH_GREATER");            return BRANCH_GREATER;          }
"BPL"   { printf(" BRANCH_PLUS");               return BRANCH_PLUS;             }
"BNV"   { printf(" BRANCH_NEVER");              return BRANCH_NEVER;            }
"BCS"   { printf(" BRANCH_CARRY_SET");          return BRANCH_CARRY_SET;        }
"BVS"   { printf(" BRANCH_OVERFLOW_SET");       return BRANCH_OVERFLOW_SET;     }
"BNE"   { printf(" BRANCH_NOT_EQUAL");          return BRANCH_NOT_EQUAL;        }
"BLT"   { printf(" BRANCH_LESS");               return BRANCH_LESS;             }
"BLE"   { printf(" BRANCH_LESS_EQUAL");         return BRANCH_LESS_EQUAL;       }
"BMI"   { printf(" BRANCH_MINUS");              return BRANCH_MINUS;            }

"MOV"   { printf(" MOVE");              return MOVE;            }
"JMP"   { printf(" JUMP");              return JUMP;            }
"JMPL"  { printf(" JUMP_LONG");         return JUMP_LONG;       }
"LD"    { printf(" LOAD_DIRECT");       return LOAD_DIRECT;     }
"LDI"   { printf(" LOAD_IMMEDIATE");    return LOAD_IMMEDIATE;  }
"LDX"   { printf(" LOAD_INDIRECT");     return LOAD_INDIRECT;   }
"ST"    { printf(" STORE_DIRECT");      return STORE_DIRECT;    }
"STX"   { printf(" STORE_INDIRECT");    return STORE_INDIRECT;  }
"PUSH"  { printf(" PUSH");              return PUSH;            }
"POP"   { printf(" POP");               return POP;             }

"RETI"  { printf(" RETI");              return RETI;            }
"HALT"  { printf(" HALT");              return HALT;            }

"BYTE"  { printf(" BYTE");              return BYTE;            }
"WORD"  { printf(" WORD");              return WORD;            }
"ALLOC" { printf(" ALLOC");             return ALLOC;           }
"ORG"   { printf(" ORG");               return ORG;             }

"\0"    {return ENDFILE;} 

{number}        { printf(" [NUM]");             return NUM;         }
{identifier}    { printf(" [IDENTIFIER]");      return ID;          }
{register}      { printf(" [REGISTER]");        return REGISTER;    }
{special_char}  { printf(" [SPECIAL_CHAR]");    return SPECIAL_CHAR;}
{newline}       { printf(" \n");                linenum++;          }

<<EOF>>         {yyterminate(); return ENDFILE; }
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