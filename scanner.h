#ifndef _SCANNER_H_
#define _SCANNER_H_

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the string of each token */
extern char tokenString[MAXTOKENLEN+1];

/* function getToken returns the 
 * next token in source file
 * Its only used for tests without parser(Bison automaticly fethces the tokens)
 */
TokenType getToken(void);


/*
 * Initializes the yyin with the source code file so the lexer know what is the input stream 
*/
void File_Init();

#endif