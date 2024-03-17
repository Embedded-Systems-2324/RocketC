#ifndef __ASM_GLOBALS_H__
#define __ASM_GLOBALS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm_parser.tab.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

extern FILE* sourceCode; 
extern int linenum;

typedef int TokenType; 

#endif