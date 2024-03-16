#ifndef __ASM_GLOBALS_H__
#define __ASM_GLOBALS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* sourceCode; 
extern int linenum;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int TokenType; 

#endif