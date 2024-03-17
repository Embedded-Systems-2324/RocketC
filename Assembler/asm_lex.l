%option noyywrap
%x INCOMMENT   

%{
#include "asm_globals.h"

#define YY_BUFFER_SIZE 32                      // alter to define the value of the input buffer
static char yy_buffer[YY_BUFFER_SIZE];
static char* yy_buf_pos = yy_buffer;
static size_t yy_buf_size = 0;
static int endOfFileReached = 0;

/*
   1st IF: The macro checks if the current position (yy_buf_pos) in the buffer
   has reached the end. If so, it refills the buffer by reading a block
   of characters from the input file.

   2nd IF: If the buffer is fully consumed and the file has no more characters,
   it indicates end-of-file by setting 'result' to YY_NULL, and the
   scanning loop is terminated.

   3rd IF: Characters are then copied from the buffer to the provided 'buf' until
   'max_size' is reached. The 'yy_buf_pos' is updated to point to the
   next position in the buffer.
*/
#define YY_INPUT(buf,result,max_size) \
{ \
    if (!endOfFileReached && yy_buf_pos >= yy_buffer + yy_buf_size) { \
        memset(yy_buffer, 0, YY_BUFFER_SIZE); \
        yy_buf_size = fread(yy_buffer, 1, YY_BUFFER_SIZE, yyin); \
        yy_buf_pos = yy_buffer; \
        if (yy_buf_size <= 0) { \
            endOfFileReached = 1; \
            result = YY_NULL; \
        } \
    } \
    size_t n = YY_BUFFER_SIZE - (yy_buf_pos - yy_buffer); \
    if (n > max_size) n = max_size; \
    memcpy(buf, yy_buf_pos, n); \
    yy_buf_pos += n; \
    result = n; \
    /*printf("\n----[BUFFER] buf:\n%s\n", buf);*/ \
}



%}

digit       [0-9]
hex         [a-fA-F]
number      {digit}+
hex_number  0x({digit}|{hex})+
letter      [a-zA-Z]

register    [rR]{digit}+
identifier  [a-zA-Z_][a-zA-Z0-9_]*

special_char [,#:$]

newline     \n
whitespace  [ \t]+
carriage    \r

%%
"ADD"   { printf(" ADD");                       return ADD;   }
"SUB"   { printf(" SUB");                       return SUB;   }
"OR"    { printf(" OR");                        return OR;    }
"AND"   { printf(" AND");                       return AND;   }
"NOT"   { printf(" NOT");                       return NOT;   }
"CMP"   { printf(" CMP");                       return CMP;   }
        
"BRA"   { printf(" BRANCH_ALWAYS");            /* yyval=BRA_COND;  */   return BRANCH;  }
"BCC"   { printf(" BRANCH_CARRY_CLEAR");       /* yyval=BNE_COND;  */   return BRANCH;  }
"BVC"   { printf(" BRANCH_OVERFLOW_CLEAR");    /* yyval=BVC_COND;  */   return BRANCH;  }
"BEQ"   { printf(" BRANCH_EQUAL");             /* yyval=BEQ_COND;  */   return BRANCH;  }
"BGE"   { printf(" BRANCH_GREATER_EQUAL");     /* yyval=BGE_COND;  */   return BRANCH;  }
"BGT"   { printf(" BRANCH_GREATER");           /* yyval=BGT_COND;  */   return BRANCH;  }
"BPL"   { printf(" BRANCH_PLUS");              /* yyval=BPL_COND;  */   return BRANCH;  }
"BNV"   { printf(" BRANCH_NEVER");             /* yyval=BNV_COND;  */   return BRANCH;  }
"BCS"   { printf(" BRANCH_CARRY_SET");         /* yyval=BCS_COND;  */   return BRANCH;  }
"BVS"   { printf(" BRANCH_OVERFLOW_SET");      /* yyval=BVS_COND;  */   return BRANCH;  }
"BNE"   { printf(" BRANCH_NOT_EQUAL");         /* yyval=BNE_COND;  */   return BRANCH;  }
"BLT"   { printf(" BRANCH_LESS");              /* yyval=BLT_COND;  */   return BRANCH;  }
"BLE"   { printf(" BRANCH_LESS_EQUAL");        /* yyval=BLE_COND;  */   return BRANCH;  }
"BMI"   { printf(" BRANCH_MINUS");             /* yyval=BMI_COND;  */   return BRANCH;  }

"MOV"   { printf(" MOVE");             return MOVE;            }
"JMP"   { printf(" JUMP");             return JUMP;            }
"JMPL"  { printf(" JUMP_LONG");        return JUMP_LONG;       }
"LD"    { printf(" LOAD_DIRECT");      return LOAD_DIRECT;     }
"LDI"   { printf(" LOAD_IMMEDIATE");   return LOAD_IMMEDIATE;  }
"LDX"   { printf(" LOAD_INDIRECT");    return LOAD_INDIRECT;   }
"ST"    { printf(" STORE_DIRECT");     return STORE_DIRECT;    }
"STX"   { printf(" STORE_INDIRECT");   return STORE_INDIRECT;  }
"PUSH"  { printf(" PUSH");             return PUSH;            }
"POP"   { printf(" POP");              return POP;             }

"RETI"  { printf(" RETI");             return RETI;            }
"HALT"  { printf(" HALT");             return HALT;            }
"NOP"   { printf(" NOP");              return NOP;             }

".byte"  { printf(" .byte");           return BYTE;            }
".word"  { printf(" .word");           return WORD;            }
".alloc" { printf(" .alloc");          return ALLOC;           }
".org"   { printf(" .org");            return ORG;             }
".equ"   { printf(" .equ");            return EQU;             }

"\0"    {/*return ENDFILE;*/} 

{number}        { printf(" [NUM]");               return NUMBER;        }
{register}      { printf(" [REGISTER]");          return REG;           }
{identifier}    { printf(" [IDENTIFIER]");        return IDENTIFIER;    }
{special_char}  { printf(" %c", *yytext);         return *yytext;       }
{hex_number}    { printf(" [HEX_NUMBER]");        return NUMBER;        }
{newline}       { printf(" \n");                  linenum++;            }
{whitespace}    { /*  ignore */}  
{carriage}      { /*  ignore */}

"//".*         { /* When "//" is found, zero or more occurrences of any character are ignored */}

<INITIAL>{      // INITIAL Lexical state
  "/*"          { printf(" [In comment]");} BEGIN(INCOMMENT);      
}

<INCOMMENT>{    // INCOMMENT Lexical state
  <<EOF>>       { printf(" Error: Unterminated comment\n");
                  return ERROR; 
                }
  "*/"          { printf(" [Out comment]");}BEGIN(INITIAL);
  "\n"          { ++linenum;}
  [^*\n]+         ; // Consume characters within the comment block
}

<<EOF>>         {yyterminate();  return ENDFILE;}

. {printf("Error, [%s] is an invalid token\n",yytext); YY_FATAL_ERROR("Unrecoverable error in lexer"); return ERROR;}
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