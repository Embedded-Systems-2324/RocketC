#ifndef _ASM_SCANNER_H_
#define _ASM_SCANNER_H_

#include "../Util/asm_globals.h"

//int yyparse();
void init_lexer();
TokenType getToken(void);

#endif