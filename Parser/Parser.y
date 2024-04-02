//--------------------------------------------------------------------------------------------------------------------//
// TODO List:
//  -Missing AST for variables of pointer type
//--------------------------------------------------------------------------------------------------------------------//


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
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

int yylex();
int yyerror(char* pStr);
const char* getTokenName(int tokenValue);
TreeNode_st* pTreeRoot;
%}

//--------------------------------------------------------------------------------------------------------------------//
// Token Types
//--------------------------------------------------------------------------------------------------------------------//
%token TOKEN_IF
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
%token TOKEN_STRUCT                 // delayed
%token TOKEN_TYPEDEF                // delayed
%token TOKEN_CONTINUE
%token TOKEN_EXTERN
%token TOKEN_GOTO
%token TOKEN_LONG
%token TOKEN_ENUM                   // delayed
%token TOKEN_REGISTER               
%token TOKEN_SHORT
%token TOKEN_SIZEOF
%token TOKEN_STATIC
%token TOKEN_SIGNED
%token TOKEN_UNION                  // delayed
%token TOKEN_UNSIGNED
%token TOKEN_VOLATILE
%token TOKEN_ASSIGN
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_OVER
%token TOKEN_PERCENT
%token TOKEN_LEFT_PARENTHESES
%token TOKEN_RIGHT_PARENTHESES
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
%token TOKEN_ARROW                  // delayed
%token TOKEN_CONSTANT
%token TOKEN_ASTERISK
%token TOKEN_ADDRESS_OF             // stone layer
%token TOKEN_DOT                    // delayed  
%token TOKEN_FNUM
%token TOKEN_NUM
%token TOKEN_STR
%token TOKEN_ID

// %define api.value.type is prefered over #define YYSTYPE
%define api.value.type {ParserObject_ut}

//--------------------------------------------------------------------------------------------------------------------//
// Grammar Rules
//--------------------------------------------------------------------------------------------------------------------//
%%

// Rules for the overall program
R_PROGRAM: R_PROGRAM R_EOF 
{

}
| R_PROGRAM R_GLOBAL_STATEMENT 
{

}
| R_GLOBAL_STATEMENT
{
    $$.treeNode = $1.treeNode;
};

R_GLOBAL_STATEMENT: 
R_VAR_DECLARATION 
{
    $$.treeNode = $1.treeNode;
}
| R_ARR_DECLARATION 
{

}
| R_FUNC_PROTOTYPE 
{

}
| R_FUNC_IMPL
{

};

R_LOCAL_STATEMENT_LIST: R_LOCAL_STATEMENT_LIST R_LOCAL_STATEMENT
{

    LOG_DEBUG("Local statement list found!\n");
}
| R_LOCAL_STATEMENT
{ 
    LOG_DEBUG("Single local statement found!\n");
};

R_LOCAL_STATEMENT: R_IF_STATEMENT 
                 | R_GOTO
                 | R_SWITCH
                 | R_CASE
                 | R_DEFAULT
                 | R_BREAK
                 | R_CONTINUE
                 | R_DO_WHILE_LOOP
                 | R_WHILE_LOOP
                 | R_FOR_LOOP
                 | R_COMPOUND_STATEMENT
                 | R_RETURN 
                 | R_ARR_DECLARATION
                 | R_VAR_DECLARATION
                 | R_ARR_ASSIGNMENT
                 | R_VAR_ASSIGNMENT
                 {
                    LOG_DEBUG("Var assignment found!\n");
                 };

// Statements with braces                                                           // Examples:
R_COMPOUND_STATEMENT: TOKEN_LEFT_BRACE R_LOCAL_STATEMENT_LIST TOKEN_RIGHT_BRACE     // { ... }
{
    LOG_DEBUG("Compound statement found!\n");
}
| TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE                                                // {}
{
    LOG_DEBUG("Empty statement found!\n");
};

//--------------------------------------------------------------------------------------------------------------------//
// Flow Control Statements
//--------------------------------------------------------------------------------------------------------------------//

// Flow control statements              // Examples:
R_CONTINUE: TOKEN_CONTINUE TOKEN_SEMI;  // continue;
R_BREAK: TOKEN_BREAK TOKEN_SEMI;        // break;
R_GOTO: TOKEN_GOTO R_LABEL TOKEN_SEMI;  // goto label;

// Rule to any SWITCH CASE implementation                               // Example: switch(var) { ... }                                                              
R_SWITCH: TOKEN_SWITCH TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_LEFT_BRACE R_SWITCH_BODY TOKEN_RIGHT_BRACE    
{
    LOG_DEBUG("Switch statement found!\n");
};

// A SWITCH body can be composed by: a list of cases, a default only, or a list of cases and a default 
R_SWITCH_BODY: R_CASE_LIST              //Examples:     // case 0:  ... case 1: ... 
             | R_DEFAULT                                // default: ...
             | R_CASE_LIST R_DEFAULT                    // case 0:  ... default: ...
             ;

// One or multiple CASEs            // Examples:
R_CASE_LIST: R_CASE                 // case 0: ...
           | R_CASE_LIST R_CASE     // case 0: ... case 1: ... case 2: ...
           ;

// CASE format - case 1: stmts
R_CASE: TOKEN_CASE TOKEN_NUM TOKEN_COLON R_LOCAL_STATEMENT_LIST
{
    LOG_DEBUG("Case statement found!\n");
};

// CASE "default" format - default: stmts    
R_DEFAULT: TOKEN_DEFAULT TOKEN_COLON R_LOCAL_STATEMENT_LIST
{
    LOG_DEBUG("Default statement found");
};

// An IF statement can only be a simple IF or a IF ELSE                                                     
// The commonly seen ELSE IF is just a new IF statement inside the first ELSE                               // Examples: 
R_IF_STATEMENT: TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES  R_LOCAL_STATEMENT_LIST       // if (var==1) { stmts }

| TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES  R_LOCAL_STATEMENT_LIST                     // if (var==1) { stmts } else { stmts }
  TOKEN_ELSE  R_LOCAL_STATEMENT_LIST 
;

// The return statement can be used to return void or a value               // Examples:
R_RETURN: TOKEN_RETURN TOKEN_SEMI                                           // return:
        | TOKEN_RETURN R_EXP TOKEN_SEMI;                                    // return var;

//--------------------------------------------------------------------------------------------------------------------//
// Loop Statements
//--------------------------------------------------------------------------------------------------------------------//

R_WHILE_LOOP: 
TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT
{
       

}
| TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI
{
    
};


R_DO_WHILE_LOOP: TOKEN_DO R_LOCAL_STATEMENT TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES
{
    LOG_DEBUG("Do While loop found!\n");
};

R_FOR_LOOP: TOKEN_FOR TOKEN_LEFT_PARENTHESES R_FOR_INIT_FIELD TOKEN_SEMI
            R_FOR_CONDITION_FIELD TOKEN_SEMI R_FOR_ASSIGNMENT_FIELD TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT
{
    LOG_DEBUG("For loop found!\n");
};

R_FOR_INIT_FIELD: %empty | R_VAR_PREAMBLE R_ASSIGN_OPERATOR R_EXP | TOKEN_ID R_ASSIGN_OPERATOR R_EXP ;
R_FOR_CONDITION_FIELD: %empty | R_EXP;
R_FOR_ASSIGNMENT_FIELD: %empty | TOKEN_ID R_ASSIGN_OPERATOR R_EXP | R_INC_DEC; 

//--------------------------------------------------------------------------------------------------------------------//
// Data manipulation Statements
//--------------------------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------------------------//
// Expressions
//--------------------------------------------------------------------------------------------------------------------//

R_EXP: 
TOKEN_MINUS R_EXP
{
    
}
| 
R_EXP R_ARITHMETIC_OPERATOR R_TERM
{

}
| 
R_EXP R_CONDITION_OPERATOR R_TERM
{

}
| 
R_EXP R_BITWISE_OPERATOR R_TERM
{

}
| R_EXP R_LOGIC_OPERATOR R_TERM
{

}
| 
R_EXP TOKEN_TERNARY R_EXP TOKEN_COLON R_EXP
{

}
| R_TERM
{
    
};

R_EXP_LIST: %empty
          | R_EXP
          | R_EXP_LIST TOKEN_COMMA R_EXP;

R_TERM: R_TERM R_PRIORITY_OPERATOR R_OPERAND | R_OPERAND;

R_OPERAND: R_INC_DEC
         | TOKEN_LOGICAL_NOT R_FACTOR
         | R_TYPE_CAST R_FACTOR
         | R_FACTOR;

R_FACTOR: TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES
        | TOKEN_ID TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET
        | TOKEN_NUM
        | TOKEN_ID
        | TOKEN_FNUM
        | TOKEN_STR
        | TOKEN_BITWISE_AND TOKEN_ID
        | R_SIZEOF;

R_INC_DEC: R_PRE_INCREMENT | R_POST_INCREMENT | R_PRE_DECREMENT | R_POST_DECREMENT;

R_PRE_INCREMENT: TOKEN_INCREMENT TOKEN_ID;
R_POST_INCREMENT: TOKEN_ID TOKEN_INCREMENT;

R_PRE_DECREMENT: TOKEN_DECREMENT TOKEN_ID;
R_POST_DECREMENT: TOKEN_ID TOKEN_DECREMENT;

//--------------------------------------------------------------------------------------------------------------------//
// Operators
//--------------------------------------------------------------------------------------------------------------------//

R_ARITHMETIC_OPERATOR: 
TOKEN_PLUS
{
    $$.nodeData.dVal = OP_PLUS;
} 
| TOKEN_MINUS 
{
    $$.nodeData.dVal = OP_MINUS;
}
| TOKEN_RIGHT_SHIFT 
{
    $$.nodeData.dVal = OP_RIGHT_SHIFT;
}
| TOKEN_LEFT_SHIFT 
{
    $$.nodeData.dVal = OP_LEFT_SHIFT;
}
;
  
R_PRIORITY_OPERATOR: 
TOKEN_ASTERISK 
{
    $$.nodeData.dVal =  OP_MULTIPLY;
}
| TOKEN_OVER 
{
    $$.nodeData.dVal = OP_DIVIDE;
}
| TOKEN_PERCENT
{
    $$.nodeData.dVal = OP_REMAIN;
}
;

R_CONDITION_OPERATOR: 
TOKEN_GREATER_THAN 
{
    $$.nodeData.dVal = OP_GREATER_THAN;
}
| TOKEN_LESS_THAN_OR_EQUAL 
{
    $$.nodeData.dVal = OP_LESS_THAN_OR_EQUAL;
}
| TOKEN_GREATER_THAN_OR_EQUAL 
{
    $$.nodeData.dVal = OP_GREATER_THAN_OR_EQUAL;
}
| TOKEN_LESS_THAN 
{
    $$.nodeData.dVal = OP_LESS_THAN;
}
| TOKEN_EQUAL 
{
    $$.nodeData.dVal = OP_EQUAL;
}
| TOKEN_NOT_EQUAL
{
    $$.nodeData.dVal = OP_NOT_EQUAL;
}
;

R_LOGIC_OPERATOR: 
TOKEN_LOGICAL_AND 
{
    $$.nodeData.dVal = OP_LOGICAL_AND;
}
| TOKEN_LOGICAL_OR 
{
    $$.nodeData.dVal = OP_LOGICAL_OR;
}
;

R_BITWISE_OPERATOR:
TOKEN_BITWISE_AND 
{
    $$.nodeData.dVal = OP_BITWISE_AND;
}
| TOKEN_BITWISE_NOT 
{
    $$.nodeData.dVal = OP_BITWISE_NOT;
}
| TOKEN_BITWISE_OR 
{
    $$.nodeData.dVal = OP_BITWISE_OR;
}
| TOKEN_BITWISE_XOR
{
    $$.nodeData.dVal = OP_BITWISE_XOR;
}
;

R_ASSIGN_OPERATOR: 
TOKEN_ASSIGN 
{
    $$.nodeData.dVal = OP_ASSIGN;
}
| TOKEN_PLUS_ASSIGN 
{
    $$.nodeData.dVal = OP_PLUS_ASSIGN;
}
| TOKEN_MINUS_ASSIGN 
{
    $$.nodeData.dVal = OP_MINUS_ASSIGN;
}
| TOKEN_MODULUS_ASSIGN 
{
    $$.nodeData.dVal = OP_MODULUS_ASSIGN;
}
| TOKEN_LEFT_SHIFT_ASSIGN 
{
    $$.nodeData.dVal = OP_LEFT_SHIFT_ASSIGN;
}
| TOKEN_RIGHT_SHIFT_ASSIGN 
{
    $$.nodeData.dVal = OP_RIGHT_SHIFT_ASSIGN;
}
| TOKEN_BITWISE_AND_ASSIGN 
{
    $$.nodeData.dVal = OP_BITWISE_AND_ASSIGN;
}
| TOKEN_BITWISE_OR_ASSIGN 
{
    $$.nodeData.dVal = OP_BITWISE_OR_ASSIGN;
}
| TOKEN_BITWISE_XOR_ASSIGN
{
    $$.nodeData.dVal = OP_BITWISE_XOR_ASSIGN;
}
| TOKEN_MULTIPLY_ASSIGN 
{
    $$.nodeData.dVal = OP_MULTIPLY_ASSIGN;
}
| TOKEN_DIVIDE_ASSIGN 
{
    $$.nodeData.dVal = OP_DIVIDE_ASSIGN;
}
;

R_SIZEOF: 
TOKEN_SIZEOF TOKEN_LEFT_PARENTHESES R_SIZEOF_BODY TOKEN_RIGHT_PARENTHESES       // sizeof(exp);
{

}
;

R_SIZEOF_BODY: 
R_TYPE_ALL
| R_SIGN_QUALIFIER R_TYPE_ALL
| R_EXP
;

//--------------------------------------------------------------------------------------------------------------------//
// Misc
//--------------------------------------------------------------------------------------------------------------------//

// Label definition for the goto statement. Example: primaDoFredo: 
R_LABEL: TOKEN_ID TOKEN_COLON;

R_TYPE_CAST: TOKEN_LEFT_PARENTHESES R_TYPE_ALL TOKEN_RIGHT_PARENTHESES;

//--------------------------------------------------------------------------------------------------------------------//
// Function Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Function signature i.e. the function format. Doesn't include the ; or the {. Example: int addNumbers(int x, int y)
R_FUNC_SIGNATURE:
 R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
 {

 }
| R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
{

}
| R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
{

}
| R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
{
    
};

// Function prototype is just a function signature followed by a semi
R_FUNC_PROTOTYPE: R_FUNC_SIGNATURE TOKEN_SEMI 
{
    LOG_DEBUG("Function prototype found!\n");
};

R_FUNC_IMPL: R_FUNC_SIGNATURE R_COMPOUND_STATEMENT
{
    LOG_DEBUG("Function implementation found!\n");
};

// Function argument list. Note: The argument list can be empty. Example: int x | int x, int y
R_ARG_LIST: %empty | R_ARG | R_ARG_LIST TOKEN_COMMA R_ARG;

// Function argument type. Example: int x | const char* pString
R_ARG:R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID 
{
    
};

//--------------------------------------------------------------------------------------------------------------------//
// Variable Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Variable declarations can have a visibility qualifier (extern/static), a type qualifier (volatile/const), a sign qualifier
// (signed/unsigned) and must explicitly specify a type (short, int, float...).                  //Examples:
R_VAR_PREAMBLE:

// register static const unsigned int var
TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID 
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $6.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $5.nodeData.dVal;
}
// register static const int var
| TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID     
{
   TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;   
}        
// register static signed int var        
| TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID    
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;
}    
// register const signed int var              
| TOKEN_REGISTER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID       
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;
    
    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;
}   
// register static int var                  
| TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID           
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;
}   
// register const int var                         
| TOKEN_REGISTER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID        
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;
}                      
// register signed int var               
| TOKEN_REGISTER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID             
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;
}       
// register int var                           
| TOKEN_REGISTER R_TYPE_ALL TOKEN_ID                    
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MISC);
    pTemp->nodeData.dVal = (long int) MISC_REG_QUAL;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;
}                               
//static const unsigned int var                  
| R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;
}
//static const int var                    
| R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID   
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;
}                 
//static signed int var                 
| R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID     
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $4.nodeData.dVal;
}               
//const signed int var                 
| R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID     
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $3.nodeData.dVal;
}          
//static int var                            
| R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID           
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_VIS_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;
}                 
//const int var                          
| R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_MOD_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;
}                                                
//signed int var            
| R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID
{
    TreeNode_st* pTemp;
    
    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_SIGN_QUAL);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $2.nodeData.dVal;
}                                      
 //int var                      
| R_TYPE_ALL TOKEN_ID
{
    TreeNode_st* pTemp;

    NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
    $$.treeNode->nodeData.sVal = $2.nodeData.sVal;

    NodeAddNewChild($$.treeNode, &pTemp, NODE_TYPE);
    pTemp->nodeData.dVal = (long int) $1.nodeData.dVal;
};                                                                           

// Variable declaration (simple or followed by its assignment).    
 // int var;
R_VAR_DECLARATION: R_VAR_PREAMBLE TOKEN_SEMI
{
    LOG_DEBUG("Found variable declaration!\n");
    $$.treeNode = $1.treeNode;
    $$.treeNode->nodeType = NODE_VAR_DECLARATION;
    LOG_DEBUG("Var ID: %s\n", $$.treeNode->nodeData.sVal);
}
// int var = 1;                                                        
| R_VAR_PREAMBLE R_ASSIGN_OPERATOR R_EXP TOKEN_SEMI
{

}
;                               

// Array declaration                                                                    // Examples:
R_ARR_DECLARATION: 
R_VAR_PREAMBLE R_ARR_SIZE TOKEN_SEMI        // int var [2];
{
    $$.treeNode = $1.treeNode;
    $$.treeNode->nodeType = NODE_ARR_DECLARATION;
    $$.treeNode->nodeData.dVal = $2.nodeData.dVal;
}                                 
| 
R_VAR_PREAMBLE R_ARR_SIZE R_ASSIGN_OPERATOR R_ARR_ARGS TOKEN_SEMI   // var [] = {1, 2, 3};
{

}
;   

// Dimensions of the array                                              // Examples:
R_ARR_SIZE: R_ARR_SIZE TOKEN_LEFT_BRACKET TOKEN_RIGHT_BRACKET           // [][][]
          | R_ARR_SIZE TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET     // [2][3]
          | TOKEN_LEFT_BRACKET TOKEN_RIGHT_BRACKET                      // []
          | TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET                // [2]

// Arguments of the array                                                           // Examples:
R_ARR_ARGS: R_ARR_ARGS TOKEN_COMMA TOKEN_LEFT_BRACE R_ARR_ARGS TOKEN_RIGHT_BRACE    // {{{...},{...},{...}},{{...},{...}}}
          | TOKEN_LEFT_BRACE R_ARR_ARGS TOKEN_RIGHT_BRACE                           // {...}
          | R_ARR_ARGS TOKEN_COMMA TOKEN_LEFT_BRACE R_EXP_LIST TOKEN_RIGHT_BRACE    // {}
          | TOKEN_LEFT_BRACE R_EXP_LIST TOKEN_RIGHT_BRACE;



// Rule to assign a value to a variable                             // Example:
R_VAR_ASSIGNMENT: 
TOKEN_ID R_ASSIGN_OPERATOR R_EXP TOKEN_SEMI
{

};      // var = 1;

// Rule to assign values to an array                // Example: var[1] = {1};
R_ARR_ASSIGNMENT: 
TOKEN_ID 
R_ARR_SIZE R_ASSIGN_OPERATOR R_ARR_ARGS TOKEN_SEMI
{

};


// Standard C data types. Doesn't account for user defined types (aka typedefs), as this will need a symbol table
//         char         short          int        long         float          double           long double
R_TYPE: 
TOKEN_CHAR 
{
    $$.nodeData.dVal = TYPE_CHAR;
}
| TOKEN_SHORT
{
    $$.nodeData.dVal = TYPE_SHORT;
}
| TOKEN_INT 
{
    $$.nodeData.dVal = TYPE_INT;
}
| TOKEN_LONG 
{
    $$.nodeData.dVal = TYPE_LONG;
}
| TOKEN_FLOAT 
{
    $$.nodeData.dVal = TYPE_FLOAT;
}
| TOKEN_DOUBLE 
{
    $$.nodeData.dVal = TYPE_DOUBLE;
}
| TOKEN_LONG TOKEN_DOUBLE
{
    $$.nodeData.dVal = TYPE_LONG_DOUBLE;
};

// Standard C data types but with pointer. This rule implements support for pointers of n length. Example: int*** ...
R_TYPE_PTR: R_TYPE_PTR TOKEN_ASTERISK | R_TYPE TOKEN_ASTERISK;

// Union between the pointer and standard types.
R_TYPE_ALL: 
R_TYPE 
{
    $$ = $1;
}
| R_TYPE_PTR
{

};

// Functions and variables can be marked as either static or extern, never both at the same time.
R_VISIBILITY_QUALIFIER: 
TOKEN_STATIC
{
    $$.nodeData.dVal = (long int) VIS_STATIC;     
}
| TOKEN_EXTERN
{
    $$.nodeData.dVal = (long int) VIS_EXTERN;     
};

// Types can be marked as constant, volatile, or have no type qualifier.
// here is also some other more advanced qualifiers not being considered.
R_MOD_QUALIFIER: 
TOKEN_CONSTANT
{
    $$.nodeData.dVal = (long int) MOD_CONST;  
} 
| TOKEN_VOLATILE
{
    $$.nodeData.dVal = (long int) MOD_VOLATILE;  
};

// Types can be marked as signed or unsigned, in C, if none is specified, the type defaults to signed.
R_SIGN_QUALIFIER: 
TOKEN_SIGNED 
{
    $$.nodeData.dVal = (long int) SIGN_SIGNED;
}
| TOKEN_UNSIGNED
{
    $$.nodeData.dVal = (long int) SIGN_UNSIGNED;
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