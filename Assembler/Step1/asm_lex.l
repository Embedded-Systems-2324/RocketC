%option noyywrap
%x INCOMMENT   

%{
#include <stdio.h> 
#include <stdbool.h> 
#include "../Util/asm_globals.h"
#include "../Util/logger.h"
#include "../Step1/asm_scanner.h"
#include "../main.h"
#include "../Output/asm_parser.tab.h"

#define YY_BUFFER_SIZE 32                      // alter to define the value of the input buffer

static char yy_buffer[YY_BUFFER_SIZE];
static char* yy_buf_pos = yy_buffer;
static size_t yy_buf_size = 0;
static int endOfFileReached = 0;

static int symbol_value_to_insert = 0;

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
}

%}

digit           [0-9]
hex             [a-fA-F]

dec_number      {digit}+
bin_number      [01]+b
hex_number_x    0x({digit}|{hex})+
hex_number_h    ({digit}|{hex})+[hH]

register        R({digit}|[12]{digit}|3[01])
identifier      [a-zA-Z_][a-zA-Z0-9_]*

newline         \n
carriage        \r
whitespace      [ \t]+


%%
"BRA"   { printf(" BRANCH_ALWAYS");             /*yylval=BRA_COND;*/    return BRANCH;  }
"BCC"   { printf(" BRANCH_CARRY_CLEAR");        /*yylval=BNE_COND;*/    return BRANCH;  }
"BVC"   { printf(" BRANCH_OVERFLOW_CLEAR");     /*yylval=BVC_COND;*/    return BRANCH;  }
"BEQ"   { printf(" BRANCH_EQUAL");              /*yylval=BEQ_COND;*/    return BRANCH;  }
"BGE"   { printf(" BRANCH_GREATER_EQUAL");      /*yylval=BGE_COND;*/    return BRANCH;  }
"BGT"   { printf(" BRANCH_GREATER");            /*yylval=BGT_COND;*/    return BRANCH;  }
"BPL"   { printf(" BRANCH_PLUS");               /*yylval=BPL_COND;*/    return BRANCH;  }
"BNV"   { printf(" BRANCH_NEVER");              /*yylval=BNV_COND;*/    return BRANCH;  }
"BCS"   { printf(" BRANCH_CARRY_SET");          /*yylval=BCS_COND;*/    return BRANCH;  }
"BVS"   { printf(" BRANCH_OVERFLOW_SET");       /*yylval=BVS_COND;*/    return BRANCH;  }
"BNE"   { printf(" BRANCH_NOT_EQUAL");          /*yylval=BNE_COND;*/    return BRANCH;  }
"BLT"   { printf(" BRANCH_LESS");               /*yylval=BLT_COND;*/    return BRANCH;  }
"BLE"   { printf(" BRANCH_LESS_EQUAL");         /*yylval=BLE_COND;*/    return BRANCH;  }
"BMI"   { printf(" BRANCH_MINUS");              /*yylval=BMI_COND;*/    return BRANCH;  }

"ADD"   { printf(" ADD");                       return ADD;             }
"SUB"   { printf(" SUB");                       return SUB;             }
"OR"    { printf(" OR");                        return OR;              }
"AND"   { printf(" AND");                       return AND;             }
"NOT"   { printf(" NOT");                       return NOT;             }
"XOR"   { printf(" XOR");                       return XOR;             }
"CMP"   { printf(" CMP");                       return CMP;             }

"MOV"   { printf(" MOVE");                      return MOVE;            }
"JMP"   { printf(" JUMP");                      return JUMP;            }
"JMPL"  { printf(" JUMP_LINK");                 return JUMP_LINK;       }
"LD"    { printf(" LOAD_DIRECT");               return LOAD_DIRECT;     }
"LDI"   { printf(" LOAD_IMMEDIATE");            return LOAD_IMMEDIATE;  }
"LDX"   { printf(" LOAD_INDEXED ");             return LOAD_INDEXED;    }
"ST"    { printf(" STORE_DIRECT");              return STORE_DIRECT;    }
"STX"   { printf(" STORE_INDEXED");             return STORE_INDEXED;   }
"PUSH"  { printf(" PUSH");                      return PUSH;            }
"POP"   { printf(" POP");                       return POP;             }

"RETI"  { printf(" RETI");                      return RETI;            }
"HALT"  { printf(" HALT");                      return HALT;            }
"NOP"   { printf(" NOP");                       return NOP;             }

".byte"  { printf(" .byte");                    return BYTE;            }
".word"  { printf(" .word");                    return WORD;            }
".alloc" { printf(" .alloc");                   return ALLOC;           }
".org"   { printf(" .org");                     return ORG;             }
".equ"   { printf(" .equ");                     return EQU;             }

","      { printf(" COMMA");                    return COMMA;           }
"#"      { printf(" CARDINAL");                 return CARDINAL;        }
":"      { printf(" COLON");                    return COLON;           }
"$"      { printf(" DOLAR");                    return DOLAR;           }
"\0"     {return ENDFILE;} 



{dec_number}    { printf(" [NUMBER]");          yylval = add_symbol(yytext); sscanf(yytext, "%d", &value_to_insert);    set_symbol_value(yylval, value_to_insert); return NUMBER;          }
{hex_number_x}  { printf(" [HEX_NUMBER]");      yylval = add_symbol(yytext); sscanf(yytext, "0x%x", &value_to_insert);  set_symbol_value(yylval, value_to_insert); return NUMBER;          }
{hex_number_h}  { printf(" [HEX_NUMBER]");      yylval = add_symbol(yytext); sscanf(yytext, "%xh", &value_to_insert);   set_symbol_value(yylval, value_to_insert); return NUMBER;          }
{bin_number}    { printf(" [BIN_NUMBER]");      yylval = add_symbol(yytext); sscanf(yytext, "%db", &value_to_insert);   set_symbol_value(yylval, value_to_insert); return NUMBER;          }
{register}      { printf(" [REGISTER]");        yylval = add_symbol(yytext); sscanf(yytext, "R%d", &value_to_insert);   set_symbol_value(yylval, value_to_insert); return REG;             }
{identifier}    { printf(" [IDENTIFIER]");      yylval = add_symbol(yytext); return IDENTIFIER;      }
{newline}       { printf(" \n");                increment_line_number(1);}
{whitespace}    { /*  ignore */}  
{carriage}      { /*  ignore */}

"//".*          { printf(" Comment "); /* When "//" is found, zero or more occurrences of any character are ignored */}
";".*           { printf(" Comment "); /* When ";" is found, zero or more occurrences of any character are ignored */}

<INITIAL>{      // INITIAL Lexical state
  "/*"          { printf(" [In comment]");} BEGIN(INCOMMENT);      
}

<INCOMMENT>{    // INCOMMENT Lexical state
  <<EOF>>       { printf(" Error: Unterminated comment\n");
                  return ERROR; 
                }
  "*/"          { printf(" [Out comment]");} BEGIN(INITIAL);
  "\n"          { increment_line_number(1);}
  [^*\n]+         ; // Consume characters within the comment block
}

<<EOF>>         {yyterminate();  return ENDFILE;}

. {printf("Error, [%s] is an invalid token\n",yytext); YY_FATAL_ERROR("Unrecoverable error in lexer"); return ERROR;}
%%


void init_lexer()
{
    get_source_file(&yyin);
}



TokenType getToken(void)
{ 
  static bool firstTime = true;
  TokenType currentToken;

  if (firstTime){ 
    firstTime = false;
    init_lexer();
  }

  currentToken = yylex();
  return currentToken;
}