%option noyywrap
%x INCOMMENT   

%{
#include "globals.h"

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
number      {digit}+
float_number  {digit}*"."{digit}+({expo}{digit}+)?

identifier  [a-zA-Z_][a-zA-Z0-9_]*

string      \"([^"\\]|\\.)*\"

newline     \n
sign        ([-+])
expo        [eE]{sign}?
whitespace  [ \t]+

%%
"break"         { printf(" BREAK");                 return BREAK;       }
"case"          { printf(" CASE");                  return CASE;        }
"char"          { printf(" CHAR");                  return CHAR;        }
"const"         { printf(" CONST");                 return CONSTANT;    }
"continue"      { printf(" CONTINUE");              return CONTINUE;    }
"default"       { printf(" DEFAULT");               return DEFAULT;     }
"do"            { printf(" DO");                    return DO;          } 
"double"        { printf(" DOUBLE");                return DOUBLE;      }
"if"            { printf(" IF");                    return IF;          }
"else if"       { printf(" ELSEIF");                return ELSEIF;      }
"else"          { printf(" ELSE");                  return ELSE;        }
"enum"          { printf(" ENUM");                  return ENUM;        }
"extern"        { printf(" EXTERN");                return EXTERN;      }
"float"         { printf(" FLOAT");                 return FLOAT;       }
"for"           { printf(" FOR");                   return FOR;         }
"goto"          { printf(" GOTO");                  return GOTO;        }

"int"           { printf(" INT");                   return INT;         }
"long"          { printf(" LONG");                  return LONG;        }
"register"      { printf(" REGISTER");              return REGISTER;    }
"return"        { printf(" RETURN");                return RETURN;      }
"short"         { printf(" SHORT");                 return SHORT;       }
"signed"        { printf(" SIGNED");                return SIGNED;      }
"sizeof"        { printf(" SIZEOF");                return SIZEOF;      }
"static"        { printf(" STATIC");                return STATIC;      }
"struct"        { printf(" STRUCT");                return STRUCT;      }
"switch"        { printf(" SWITCH");                return SWITCH;      }
"typedef"       { printf(" TYPEDEF");               return TYPEDEF;     }
"union"         { printf(" UNION");                 return UNION;       }
"unsigned"      { printf(" UNSIGNED");              return UNSIGNED;    }
"void"          { printf(" VOID");                  return VOID;        }
"volatile"      { printf(" VOLATILE");              return VOLATILE;    }
"while"         { printf(" WHILE");                 return WHILE;       }
"define"        { printf(" DEFINE");                return DEFINE;      }

"+"             { printf(" PLUS");                  return PLUS;        }
"-"             { printf(" MINUS");                 return MINUS;       }
"*"             { printf(" TIMES");                 return TIMES;       }
"/"             { printf(" OVER");                  return OVER;        }
"%"             { printf(" PERCENT");               return PERCENT;     }
"++"            { printf(" INCREMENT");             return INCREMENT;   }
"--"            { printf(" DECREMENT");             return DECREMENT;   }
"&"             { printf(" BITWISE_AND");           return BITWISE_AND; }
"|"             { printf(" BITWISE_OR");            return BITWISE_OR;  }
"~"             { printf(" BITWISE_NOT");           return BITWISE_NOT; }
"^"             { printf(" BITWISE_XOR");           return BITWISE_XOR; }
"!"             { printf(" LOGICAL_NOT");           return LOGICAL_NOT; }
"&&"            { printf(" LOGICAL_AND");           return LOGICAL_AND; }
"||"            { printf(" LOGICAL_OR");            return LOGICAL_OR;  }
"=="            { printf(" EQUAL");                 return EQUAL;       }
"!="            { printf(" NOT_EQUAL");             return NOT_EQUAL;   }
"<"             { printf(" LESS_THAN");             return LESS_THAN;   }
">"             { printf(" GREATER_THAN");          return GREATER_THAN;}
"<="            { printf(" LESS_THAN_OR_EQUAL");    return LESS_THAN_OR_EQUAL;    }
">="            { printf(" GREATER_THAN_OR_EQUAL"); return GREATER_THAN_OR_EQUAL; }
">>"            { printf(" RIGHT_SHIFT");           return RIGHT_SHIFT;           }
"<<"            { printf(" LEFT_SHIFT");            return LEFT_SHIFT;            }
"="             { printf(" ASSIGN");                return ASSIGN;                }
"+="            { printf(" PLUS_ASSIGN");           return PLUS_ASSIGN;           }
"-="            { printf(" MINUS_ASSIGN");          return MINUS_ASSIGN;          }
"*="            { printf(" MULTIPLY_ASSIGN");       return MULTIPLY_ASSIGN;       }
"/="            { printf(" DIVIDE_ASSIGN");         return DIVIDE_ASSIGN;         }
"%="            { printf(" MODULUS_ASSIGN");        return MODULUS_ASSIGN;        }
"&="            { printf(" AND_ASSIGN");           return BITWISE_AND_ASSIGN;     }
">>="           { printf(" RIGHT_SHIFT_ASSIGN");   return RIGHT_SHIFT_ASSIGN;    }
"<<="           { printf(" LEFT_SHIFT_ASSIGN");    return LEFT_SHIFT_ASSIGN;     }
"|="            { printf(" OR_ASSIGN");            return BITWISE_OR_ASSIGN;      }
"^="            { printf(" XOR_ASSIGN");           return BITWISE_XOR_ASSIGN;     }

";"             { printf(" SEMI");                  return SEMI;                  }
","             { printf(" COMMA");                 return COMMA;                 }
":"             { printf(" COLON");                 return COLON;                 }
"."             { printf(" DOT");                   return DOT;                   }




"("             { printf(" LEFT_PAREN");            return LPAREN;                }
")"             { printf(" RIGHT_PAREN");           return RPAREN;                }
"{"             { printf(" LEFT_BRACE");            return LEFT_BRACE;            }
"}"             { printf(" RIGHT_BRACE");           return RIGHT_BRACE;           }
"["             { printf(" LEFT_BRACKET");          return LEFT_BRACKET;          }
"]"             { printf(" RIGHT_BRACKET");         return RIGHT_BRACKET;         }
"?"             { printf(" TERNARY");               return TERNARY;               }
"#"             { printf(" CARDINAL");              return CARDINAL;              }
"->"            { printf(" ARROW");                 return ARROW;                 }
"\0"            {return ENDFILE;} 


{number}        { (yylval.intval=atoi(yytext));          printf(" [NUM: %d]", yylval.intval);    return NUM; }
{identifier}    { sscanf(yytext,"%s",yylval.identifier); printf(" [ID: %s]", yylval.identifier); return ID;  }
{float_number}  { (yylval.floatval=atof(yytext));        printf(" [FNUM: %f]", yylval.floatval);  return FNUM;}
{newline}       { printf(" \n");                         linenum++;                                   }
{string}        { sscanf(yytext,"%s",yylval.strval);     printf(" %s",yytext); return STRINGliteral;  }
{whitespace}    { /*  ignore */}  

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


<<EOF>>         {yyterminate(); return ENDFILE; }

. {printf("Error, [%s] is an invalid token\n",yytext); YY_FATAL_ERROR("Unrecoverable error in lexer"); return ERROR;}
%%


void File_Init() {
  yyin = sourceCode;
}

/* function: getToken()
*  Returns the next token from the input source code.
*  Used only for tests because the parse automaticly calls the lexer when necessary.
*/
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