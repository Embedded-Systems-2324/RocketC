//--------------------------------------------------------------------------------------------------------------------//
// Prologue
//--------------------------------------------------------------------------------------------------------------------//

%code requires {
#include "../Util/Globals.h"
}

%{
#include <stdint.h>
#include <errno.h>
#include "../main.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

int yylex();
int yyerror(char* pStr);
const char* getTokenName(int tokenValue);
%}

%token TOKEN_IF
%token TOKEN_ELSEIF
%token TOKEN_EOF
%token TOKEN_ERROR
%token TOKEN_ELSE
%token TOKEN_DO
%token TOKEN_WHILE
%token TOKEN_FOR
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_DEFAULT
%token TOKEN_RETURN
%token TOKEN_BREAK
%token TOKEN_INT
%token TOKEN_FLOAT
%token TOKEN_DOUBLE
%token TOKEN_CHAR
%token TOKEN_VOID
%token TOKEN_STRUCT
%token TOKEN_TYPEDEF
%token TOKEN_CONTINUE
%token TOKEN_EXTERN
%token TOKEN_GOTO
%token TOKEN_LONG
%token TOKEN_ENUM
%token TOKEN_REGISTER
%token TOKEN_SHORT
%token TOKEN_SIZEOF
%token TOKEN_STATIC
%token TOKEN_SIGNED
%token TOKEN_UNION
%token TOKEN_UNSIGNED
%token TOKEN_VOLATILE
%token TOKEN_ASSIGN
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_OVER
%token TOKEN_PERCENT
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LEFT_BRACE
%token TOKEN_RIGHT_BRACE
%token TOKEN_LEFT_BRACKET
%token TOKEN_RIGHT_BRACKET
%token TOKEN_TERNARY
%token TOKEN_SEMI
%token TOKEN_COLON
%token TOKEN_COMMA
%token TOKEN_INCREMENT
%token TOKEN_DECREMENT
%token TOKEN_BITWISE_AND
%token TOKEN_BITWISE_OR
%token TOKEN_LOGICAL_AND
%token TOKEN_BITWISE_NOT
%token TOKEN_BITWISE_XOR
%token TOKEN_LOGICAL_NOT
%token TOKEN_LOGICAL_OR
%token TOKEN_EQUAL
%token TOKEN_NOT_EQUAL
%token TOKEN_LESS_THAN
%token TOKEN_GREATER_THAN
%token TOKEN_LESS_THAN_OR_EQUAL
%token TOKEN_GREATER_THAN_OR_EQUAL
%token TOKEN_RIGHT_SHIFT
%token TOKEN_LEFT_SHIFT
%token TOKEN_PLUS_ASSIGN
%token TOKEN_MINUS_ASSIGN
%token TOKEN_LEFT_SHIFT_ASSIGN
%token TOKEN_RIGHT_SHIFT_ASSIGN
%token TOKEN_BITWISE_AND_ASSIGN
%token TOKEN_BITWISE_OR_ASSIGN
%token TOKEN_BITWISE_XOR_ASSIGN
%token TOKEN_MULTIPLY_ASSIGN
%token TOKEN_DIVIDE_ASSIGN
%token TOKEN_MODULUS_ASSIGN
%token TOKEN_CARDINAL
%token TOKEN_ARROW
%token TOKEN_DEFINE
%token TOKEN_CONSTANT
%token TOKEN_ASTERISK
%token TOKEN_ADDRESS_OF
%token TOKEN_OTHER
%token TOKEN_DOT
%token TOKEN_QUOTE
%token TOKEN_FNUM
%token TOKEN_NUM
%token TOKEN_STR
%token TOKEN_ID

%define api.value.type {ParserObject_ut}

//--------------------------------------------------------------------------------------------------------------------//
// Grammar Rules
//--------------------------------------------------------------------------------------------------------------------//

%%
//Rules for the overall program
R_PROGRAM: R_PROGRAM R_EOF | R_PROGRAM R_GLOBAL_STATEMENT | R_GLOBAL_STATEMENT;

//TODO: Add missing cases: Func. Implementations
R_GLOBAL_STATEMENT: R_VAR_DECLARATION | R_FUNC_PROTOTYPE ;

R_VAR_DECLARATION: R_FUNC_PREAMBLE TOKEN_SEMI
{
    
};

//Start of a function prototype or definition. Example: char* getString, static int getNumber
R_FUNC_PREAMBLE: R_TYPE_ALL TOKEN_ID 
{
    LOG_DEBUG("Type preamble found! | Name: %s\n", $2.tokenData.sId);
} 
| R_FUNC_QUALIFIER R_TYPE_ALL TOKEN_ID 
{
    LOG_DEBUG("Type preamble found! | Name: %s\n", $3.tokenData.sId);  
};

//Functions can be marked as either static or extern, never both at the same time.
R_FUNC_QUALIFIER: TOKEN_STATIC | TOKEN_EXTERN;

//Function signature i.e. the function format. Doesn't include the ; or the {. Example: int addNumbers(int x, int y)
R_FUNC_SIGNATURE: R_FUNC_PREAMBLE TOKEN_LPAREN R_ARG_LIST TOKEN_RPAREN

//Function prototype is just a function signature followed by a semi
R_FUNC_PROTOTYPE: R_FUNC_SIGNATURE TOKEN_SEMI 
{
    LOG_DEBUG("Function prototype found!\n");
};

//Function argument list. Note: The argument list can be empty. Example: int x | int x, int y
R_ARG_LIST: R_ARG | R_ARG_LIST TOKEN_COMMA R_ARG | ;

//Function argument type. Example: int x | const char* pString
R_ARG: R_TYPE_ALL TOKEN_ID 
{
    LOG_DEBUG("Function argument found! | Name: %s\n", $2.tokenData.sId);
}
| R_TYPE_QUALIFIER R_TYPE_ALL TOKEN_ID
{
    LOG_DEBUG("Function argument found! | Name: %s: | Qualifier: %d\n", $3.tokenData.sId, $$.tokenData.dVal);
};

//Standard C data types. Doesn't account for user defined types (aka typedefs), as this will need a symbol table
//         char         short          int        long         float          double           long double
R_TYPE: TOKEN_CHAR | TOKEN_SHORT | TOKEN_INT | TOKEN_LONG | TOKEN_FLOAT | TOKEN_DOUBLE | TOKEN_LONG TOKEN_DOUBLE;

//Standard C data types but with pointer. This rule implements support for pointers of n length. Example: int*** ...
R_TYPE_PTR: R_TYPE_PTR TOKEN_ASTERISK | R_TYPE TOKEN_ASTERISK;

//Union between the pointer and standard types.
R_TYPE_ALL: R_SIGN_QUALIFIER R_TYPE | R_SIGN_QUALIFIER R_TYPE_PTR;

//Types can be marked as constant or volatile. There is also some other more advanced qualifiers not being considered.
R_TYPE_QUALIFIER: TOKEN_CONSTANT
{
    $$.tokenData.dVal = (long int) TOKEN_CONSTANT;
    LOG_DEBUG("Qualifier found: %s\n", getTokenName($$.tokenData.dVal));
} 
| TOKEN_VOLATILE
{
    $$.tokenData.dVal = (long int) TOKEN_VOLATILE;    
    LOG_DEBUG("Qualifier found: Volatile\n");
};

R_SIGN_QUALIFIER: | TOKEN_SIGNED
{
    LOG_DEBUG("Signed qualifier found!\n");
} 
| TOKEN_UNSIGNED
{
    LOG_DEBUG("Unsigned qualifier found!\n");
};

R_EOF: TOKEN_EOF
{
    LOG_DEBUG("Reached end of file!\n");
    return 0;
};
%%

//--------------------------------------------------------------------------------------------------------------------//
// Code
//--------------------------------------------------------------------------------------------------------------------//
int executeParser(TreeNode_st** pTreeRoot)
{
    int ret;

    if (!pTreeRoot)
        return -EINVAL;
    
    ret = initLexer();
    if (ret < 0)
    {
        LOG_ERROR("Failed to get source file!\n");
        return ret; 
    }

    LOG_WARNING("\n--------------Parser Start--------------\n");

    return yyparse();
}

int yyerror(char* pStr)
{
    if (!pStr)
        return -EINVAL;

    LOG_ERROR("Error at line: %lu | Error was: %s\n", getLineNumber(), pStr);

    return 0;
}

const char* getTokenName(int tokenValue) 
{
    return yysymbol_name(YYTRANSLATE(tokenValue));
}