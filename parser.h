#ifndef _PARSER_H_
#define _PARSER_H_

/* Function parse returns the newly 
 * constructed syntax tree
 */
//TreeNode * parse(void);

/*
 * Inits the program file and prases it
 * The return type is temporary 
*/
void parse (void);

/* Error Handler */
int yyerror(char *s);
#endif