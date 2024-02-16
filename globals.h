#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef enum
{
    /* book-keeping tokens */
    ENDFILE, ERROR,

    /* reserved words */
    IF, ELSEIF, ELSE, DO, WHILE, FOR, SWITCH, CASE, DEFAULT, RETURN, BREAK,
    INT, FLOAT, DOUBLE, CHAR, VOID, STRUCT, TYPEDEF,

    /* multicharacter tokens */
    NUM, ID,

    /* special symbols */
    ASSIGN, PLUS, MINUS, TIMES, OVER, PERCENT,LPAREN, RPAREN,LEFT_BRACE, 
    RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET, TERNARY, SEMI, COLON, COMMA,

    /* operators */
    INCREMENT, DECREMENT, BITWISE_AND, BITWISE_OR, BITWISE_NOT, BITWISE_XOR,
    LOGICAL_NOT, LOGICAL_AND, LOGICAL_OR, EQUAL, NOT_EQUAL, LESS_THAN, GREATER_THAN,
    LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, RIGHT_SHIFT, LEFT_SHIFT, PLUS_ASSIGN, MINUS_ASSIGN,
    MODULO, LEFT_SHIFT_ASSIGN, RIGHT_SHIFT_ASSIGN, BITWISE_AND_ASSIGN, BITWISE_OR_ASSIGN,
    BITWISE_XOR_ASSIGN,

    /* preprocessor and functions */
    PREPROCESSOR, ARROW, PRINTF, SCANF, DEFINE, EXIT,

    /* additional tokens  (It is necessary to implement these?) */
    STRING, CONSTANT, POINTER, ADDRESS_OF, LOGICAL_OR_EQ, LOGICAL_AND_EQ,
    UNSIGNED_INT, LONG_INT, SHORT_INT, 

} TokenType;


extern FILE* sourceCode;  /* source code text file */

TokenType getToken(void);

#endif
