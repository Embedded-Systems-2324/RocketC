#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.tab.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

extern FILE* sourceCode;  /* source code text file */
extern int linenum;       /* line counter */

typedef int TokenType; 

#endif
