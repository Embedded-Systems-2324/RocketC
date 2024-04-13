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
TreeNode_st** ppTreeRoot;


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
R_PROGRAM               :   R_PROGRAM R_EOF 
                            {
                                *ppTreeRoot = $1.treeNode;
                            }
                        |   R_PROGRAM R_GLOBAL_STATEMENT 
                            {
                                $$.treeNode = $2.treeNode;
                            }
                        |   R_GLOBAL_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Global statements
R_GLOBAL_STATEMENT      :   R_VAR_DECLARATION 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_ARR_DECLARATION 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_FUNC_PROTOTYPE 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_FUNC_IMPL
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Local statement list
R_LOCAL_STATEMENT_LIST  :   %empty
                            {
                                $$.treeNode = NULL;
                            }
                        |
                            R_LOCAL_STATEMENT_LIST R_LOCAL_STATEMENT
                            {
                                $1.treeNode->pSibling = $2.treeNode;
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_LOCAL_STATEMENT
                            { 
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Local statements
R_LOCAL_STATEMENT       :   R_IF_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_GOTO
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_SWITCH
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_CASE
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_DEFAULT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_BREAK
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_CONTINUE
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_DO_WHILE_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }
                            
                        |   R_WHILE_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }
                            
                        |   R_FOR_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_COMPOUND_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_RETURN
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_ARR_DECLARATION
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_VAR_DECLARATION
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_ARR_ASSIGNMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_VAR_ASSIGNMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Statements with braces                                                                 // Examples:
R_COMPOUND_STATEMENT    :   TOKEN_LEFT_BRACE R_LOCAL_STATEMENT_LIST TOKEN_RIGHT_BRACE     // { ... }
                            {
                                $$.treeNode = $2.treeNode;
                            }

                        |   TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE                            // {}
                        ;

//--------------------------------------------------------------------------------------------------------------------//
// Flow Control
//--------------------------------------------------------------------------------------------------------------------//

// Flow control statements                      // Examples:
R_CONTINUE  :   TOKEN_CONTINUE TOKEN_SEMI       // continue;
                {
                    NodeCreate(&($$.treeNode), NODE_CONTINUE);
                }
            ;

R_BREAK     :   TOKEN_BREAK TOKEN_SEMI          // break;
                {
                    NodeCreate(&($$.treeNode), NODE_BREAK);
                }
            ;

R_GOTO      :   TOKEN_GOTO R_LABEL TOKEN_SEMI   // goto label;
                {
                    NodeCreate(&($$.treeNode), NODE_GOTO);
                    $$.nodeData.sVal = $2.nodeData.sVal;
                }
            ;

// Rule to any SWITCH CASE implementation                               // Example: switch(var) { ... }                                                              
R_SWITCH    :   TOKEN_SWITCH TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_LEFT_BRACE R_SWITCH_BODY TOKEN_RIGHT_BRACE    
                {
                    NodeCreate(&($$.treeNode), NODE_SWITCH);
                    NodeAddChild($$.treeNode, $3.treeNode);
                    NodeAddChild($$.treeNode, $6.treeNode);
                }
            ;

// A SWITCH body can be composed by: a list of cases, a default only, or a list of cases and a default 
R_SWITCH_BODY   :   R_CASE_LIST                             //Examples:     // case 0:  ... case 1: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }

                |   R_DEFAULT                                // default: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }

                |   R_CASE_LIST R_DEFAULT                    // case 0:  ... default: ...
                    {
                        $1.treeNode->pSibling = $2.treeNode;
                        $$.treeNode = $1.treeNode;
                    }
                ;

// One or multiple CASEs                   // Examples:
R_CASE_LIST     :   R_CASE                 // case 0: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }

                |   R_CASE_LIST R_CASE     // case 0: ... case 1: ... case 2: ...
                    {
                        $$.treeNode->pSibling = $1.treeNode;
                    }
                ;   


// CASE format - case 1: stmts
R_CASE          :   TOKEN_CASE TOKEN_NUM TOKEN_COLON R_LOCAL_STATEMENT_LIST
                    {
                        NodeCreate(&($$.treeNode), NODE_CASE);
                        $$.nodeData.dVal = $2.nodeData.dVal;

                        NodeAddChild($$.treeNode, $4.treeNode);
                    }
                ;
                

// CASE "default" format - default: stmts    
R_DEFAULT       :   TOKEN_DEFAULT TOKEN_COLON R_LOCAL_STATEMENT_LIST
                    {
                        NodeCreate(&($$.treeNode), NODE_DEFAULT);

                        NodeAddChild($$.treeNode, $3.treeNode);
                    }
                ;

// An IF statement can only be a simple IF or a IF ELSE                                                     
// The commonly seen ELSE IF is just a new IF statement inside the first ELSE                                   // Examples: 
R_IF_STATEMENT  :   TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT_LIST       // if (var==1) { stmts }
                    {
                        NodeCreate(&($$.treeNode), NODE_IF);
                        NodeAddChild($$.treeNode, $3.treeNode);                      // Condition:
                        NodeAddChild($$.treeNode, $5.treeNode);                      // if true
                    }

                |   TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT_LIST TOKEN_ELSE  R_LOCAL_STATEMENT_LIST     // if (var==1) { stmts } else { stmts }
                    {
                        NodeCreate(&($$.treeNode), NODE_IF);
                        NodeAddChild($$.treeNode, $3.treeNode);                      // Condition:
                        NodeAddChild($$.treeNode, $5.treeNode);                      // if true
                        NodeAddChild($$.treeNode, $7.treeNode);                      // else 
                    }
                ;

// The return statement can be used to return void or a value                         // Examples:
R_RETURN        :   TOKEN_RETURN TOKEN_SEMI                                           // return;
                    {
                        NodeCreate(&($$.treeNode), NODE_RETURN);
                    }
                    
                |   TOKEN_RETURN R_EXP TOKEN_SEMI                                     // return var;
                    {
                        NodeCreate(&($$.treeNode), NODE_RETURN);
                        NodeAddChild($$.treeNode, $2.treeNode);
                    }
                ;

//--------------------------------------------------------------------------------------------------------------------//
// Loop Statements
//--------------------------------------------------------------------------------------------------------------------//

R_WHILE_LOOP        :   TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT 
                        {

                            NodeCreate(&($$.treeNode), NODE_WHILE);
                        
                            NodeAddChild($$.treeNode, $3.treeNode);      // Condition

                            NodeAddChild($$.treeNode, $5.treeNode);      // if true

                        }
                        
                    |   TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI
                        {

                            NodeCreate(&($$.treeNode), NODE_WHILE);
                        
                            NodeAddChild($$.treeNode, $3.treeNode);      // Condition

                        }
                    ;


R_DO_WHILE_LOOP     :   TOKEN_DO R_LOCAL_STATEMENT TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES
                        {

                            NodeCreate(&($$.treeNode), NODE_DO_WHILE);
                        
                            NodeAddChild($$.treeNode, $2.treeNode);      // Condition

                            NodeAddChild($$.treeNode, $5.treeNode);      // if true
                            
                        }
                    ;


R_FOR_LOOP          :   TOKEN_FOR TOKEN_LEFT_PARENTHESES R_FOR_INIT_FIELD TOKEN_SEMI R_FOR_CONDITION_FIELD TOKEN_SEMI R_FOR_ASSIGNMENT_FIELD TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT                     //for(int i=0;i<10;i++)
                        {
                            
                        };


R_FOR_INIT_FIELD    :   R_VAR_PREAMBLE R_ASSIGN_OPERATOR R_EXP  //static int i = 1+1;
                        {

                        }

                    |   TOKEN_ID R_ASSIGN_OPERATOR R_EXP // i = 0;
                        {
                            
                        }
                    ;

                    

R_FOR_CONDITION_FIELD   :   R_EXP
                            {
                                $$ = $1;
                            }
                        ;


R_FOR_ASSIGNMENT_FIELD  :   TOKEN_ID R_ASSIGN_OPERATOR R_EXP 
                            {

                            }

                        |   R_INC_DEC
                            {

                            }
                        ; 

//--------------------------------------------------------------------------------------------------------------------//
// Data manipulation Statements
//--------------------------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------------------------//
// Expressions
//--------------------------------------------------------------------------------------------------------------------//

// Main expression rule
R_EXP       :   TOKEN_MINUS R_EXP
                {           
                    NodeCreate(&($$.treeNode), NODE_EXPRESSION);
                    $$.treeNode->nodeData.dVal = OP_MINUS;

                    NodeAddChild($$.treeNode, $2.treeNode);  
                }

            |   R_EXP R_ARITHMETIC_OPERATOR R_TERM
                {
                    NodeCreate(&($$.treeNode), NODE_EXPRESSION);

                    NodeAddChild($$.treeNode, $2.treeNode); 

                    NodeAddChild($$.treeNode, $3.treeNode); 
                }

            |   R_EXP R_CONDITION_OPERATOR R_TERM
                {
                    NodeCreate(&($$.treeNode), NODE_EXPRESSION);

                    NodeAddChild($$.treeNode, $2.treeNode); 

                    NodeAddChild($$.treeNode, $3.treeNode);    
                }

            |   R_EXP R_BITWISE_OPERATOR R_TERM
                {
                    NodeCreate(&($$.treeNode), NODE_EXPRESSION);

                    NodeAddChild($$.treeNode, $2.treeNode); 

                    NodeAddChild($$.treeNode, $3.treeNode); 
                }

            |   R_EXP R_LOGIC_OPERATOR R_TERM
                {
                    NodeCreate(&($$.treeNode), NODE_EXPRESSION);

                    NodeAddChild($$.treeNode, $2.treeNode); 

                    NodeAddChild($$.treeNode, $3.treeNode); 
                }

            |   R_EXP TOKEN_TERNARY R_EXP TOKEN_COLON R_EXP
                {
                    NodeCreate(&($$.treeNode), NODE_TERNARY);

                    NodeAddChild($$.treeNode, $1.treeNode); 

                    NodeAddChild($$.treeNode, $2.treeNode); 

                    NodeAddChild($$.treeNode, $3.treeNode);   
                }

            |   R_TERM
                {
                    $$.treeNode = $1.treeNode;
                }
            ;

// Rule for expression list, expressions separated by ','   // Examples:
R_EXP_LIST  :   %empty                                      // 

            |   R_EXP                                       // exp
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_EXP_LIST TOKEN_COMMA R_EXP                // exp , exp
                {
                    $1.treeNode->pSibling = $3.treeNode;
                    $$.treeNode = $1.treeNode;
                }
            ;

// Prioritize operators, and minimize rule duplication
R_TERM      :   R_TERM R_PRIORITY_OPERATOR R_OPERAND 
                {
                    TreeNode_st* pNode;

                    NodeAddNewChild($$.treeNode, &pNode, NODE_OP_TYPE);
                    pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                    NodeAddChild($$.treeNode, $3.treeNode);
                    NodeAddChild($$.treeNode, $1.treeNode);

                }
                
            |   R_OPERAND
                {
                    $$.treeNode =  $1.treeNode;
                }
            ;

// Simplify parsing, prioritize operators, and minimize rule duplication
R_OPERAND   :   R_INC_DEC
                {
                    $$.treeNode =  $1.treeNode;
                }

            |   TOKEN_LOGICAL_NOT R_FACTOR
                {
                    
                    
                }

            |   R_TYPE_CAST R_FACTOR
                {

                }

            |   R_FACTOR
                {
                    $$.treeNode =  $1.treeNode; 
                }
            ;
            
//Factor contains the atomic units within expressions, like numbers, IDs, etc.  // Examples:
R_FACTOR    :   TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES            // (exp)
                {
                    $$.treeNode =  $2.treeNode;
                }

            |   TOKEN_ID TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET           // a[x]
                {
                    TreeNode_st* pNode;

                    NodeCreate(&($$.treeNode), NODE_ARRAY_INDEX);

                    NodeAddNewChild($$.treeNode, &pNode, NODE_ID);
                    pNode->nodeData.sVal = $1.nodeData.sVal;

                    NodeAddChild($$.treeNode, $3.treeNode);  
                }
                
            |   TOKEN_NUM                                                       // 1
                {   
                    NodeCreate(&($$.treeNode), NODE_INTEGER);
                    $$.treeNode->nodeData.dVal = $1.nodeData.dVal;
                }

            |   TOKEN_ID                                                        // a
                {
                    NodeCreate(&($$.treeNode), NODE_ID);
                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                }
                
            |   TOKEN_FNUM                                                      // 1.5
                {
                    NodeCreate(&($$.treeNode), NODE_FLOAT);
                    $$.treeNode->nodeData.fVal = $1.nodeData.fVal;
                }       

            |   TOKEN_STR                                                       // "abc"
                {
                    NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                }

            |   TOKEN_BITWISE_AND TOKEN_ID                                      // &a
                {
                    NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                    $$.treeNode->nodeData.dVal = OP_BITWISE_AND;

                    NodeAddChild($$.treeNode, $2.treeNode);
                }

            |   R_SIZEOF                                                        // sizeof(type)
                {
                    
                }
            ;

// Increment/Decrement group
R_INC_DEC   :   R_PRE_INCREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_POST_INCREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_PRE_DECREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_POST_DECREMENT
                {
                    $$.treeNode = $1.treeNode;
                }
            ;

// Increment/Decrement types                                            // Examples:
R_PRE_INCREMENT     :   TOKEN_INCREMENT TOKEN_ID                        // ++a
                        {
                            NodeCreate(&($$.treeNode), NODE_PRE_INC);
                            $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                        }
                    ;


R_POST_INCREMENT    :   TOKEN_ID TOKEN_INCREMENT                        // a++
                        {
                            NodeCreate(&($$.treeNode), NODE_POST_INC);
                            $$.treeNode->nodeData.sVal = $1.nodeData.sVal; 
                        }
                    ;


R_PRE_DECREMENT     :   TOKEN_DECREMENT TOKEN_ID                        // --a
                        {
                            NodeCreate(&($$.treeNode), NODE_PRE_DEC);
                            $$.treeNode->nodeData.sVal = $2.nodeData.sVal; 
                        }
                    ;


R_POST_DECREMENT    :   TOKEN_ID TOKEN_DECREMENT                        // a--
                        {
                            NodeCreate(&($$.treeNode), NODE_POST_DEC);
                            $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                        }
                    ;

//--------------------------------------------------------------------------------------------------------------------//
// Operators
//--------------------------------------------------------------------------------------------------------------------//

// Arithmetic operators                                             // Operators:
R_ARITHMETIC_OPERATOR   :   TOKEN_PLUS                              // +    
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_PLUS;
                            } 

                        |   TOKEN_MINUS                             // -
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_MINUS;
                            }

                        |   TOKEN_RIGHT_SHIFT                       // >>
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_RIGHT_SHIFT;
                            }

                        |   TOKEN_LEFT_SHIFT                        // <<
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LEFT_SHIFT;
                            }
                        ;

// Priority operators                                               // Operators:
R_PRIORITY_OPERATOR     :   TOKEN_ASTERISK                          // *
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_MULTIPLY;
                            }

                        |   TOKEN_OVER                              // /
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_DIVIDE;
                            }

                        |   TOKEN_PERCENT                           // %
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_REMAIN;
                            }
                        ;

// Condition operators                                              // Operators:
R_CONDITION_OPERATOR    :   TOKEN_GREATER_THAN                      // >
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_GREATER_THAN;
                            }

                        |   TOKEN_LESS_THAN_OR_EQUAL                // <=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LESS_THAN_OR_EQUAL;
                            }

                        |   TOKEN_GREATER_THAN_OR_EQUAL             // >=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_GREATER_THAN_OR_EQUAL;
                            }

                        |   TOKEN_LESS_THAN                         // <
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LESS_THAN;
                            }

                        |   TOKEN_EQUAL                             // ==
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_EQUAL;
                            }

                        |   TOKEN_NOT_EQUAL                         // !=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_NOT_EQUAL;
                            }
                        ;

// Logic operators                                                  // Operators:
R_LOGIC_OPERATOR        :   TOKEN_LOGICAL_AND                       // &&
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LOGICAL_AND;
                            }

                        |   TOKEN_LOGICAL_OR                        // ||
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LOGICAL_OR;
                            }
                        ;

// Bitwise operators                                                // Operators:
R_BITWISE_OPERATOR      :   TOKEN_BITWISE_AND                       // &
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_AND;
                            }

                        |   TOKEN_BITWISE_NOT                       // ~
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_NOT;
                            }

                        |   TOKEN_BITWISE_OR                        // |
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_OR;
                            }

                        |   TOKEN_BITWISE_XOR                       // ^
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_XOR;
                            }
                        ;

// Assign operators                                                 // Operators:
R_ASSIGN_OPERATOR       :   TOKEN_ASSIGN                            // =
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_ASSIGN;
                            }

                        |   TOKEN_PLUS_ASSIGN                       // +=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_PLUS_ASSIGN;
                            }

                        |   TOKEN_MINUS_ASSIGN                      // -=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_MINUS_ASSIGN;
                            }
                            
                        |   TOKEN_MODULUS_ASSIGN                    // %=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_MODULUS_ASSIGN;
                            }
                            
                        |   TOKEN_LEFT_SHIFT_ASSIGN                 //<<=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_LEFT_SHIFT_ASSIGN;
                            }

                        |   TOKEN_RIGHT_SHIFT_ASSIGN                // >>=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_RIGHT_SHIFT_ASSIGN;
                            }
                            
                        |   TOKEN_BITWISE_AND_ASSIGN                // &=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_AND_ASSIGN;
                            }

                        |   TOKEN_BITWISE_OR_ASSIGN                 // |=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_OR_ASSIGN;
                            }

                        |   TOKEN_BITWISE_XOR_ASSIGN                // ^=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_XOR_ASSIGN;
                            }

                        |   TOKEN_MULTIPLY_ASSIGN                   // *=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_MULTIPLY_ASSIGN;
                            }

                        |   TOKEN_DIVIDE_ASSIGN                     // /=
                            {
                                NodeCreate(&($$.treeNode), NODE_OP_TYPE);
                                $$.treeNode->nodeData.dVal = OP_DIVIDE_ASSIGN;
                            }
                        ;

// Sizeof rule
R_SIZEOF                :   TOKEN_SIZEOF TOKEN_LEFT_PARENTHESES R_SIZEOF_BODY TOKEN_RIGHT_PARENTHESES       // sizeof(exp);
                            {

                            }
                        ;

// The expressions, identifiers, or types that can be evaluated by sizeof()
R_SIZEOF_BODY           :   R_TYPE_ALL
                            {

                            }
                            
                        |   R_SIGN_QUALIFIER R_TYPE_ALL
                            {
                                
                            }
                            
                        |   R_EXP
                            {

                            }
                        ;

//--------------------------------------------------------------------------------------------------------------------//
// Misc
//--------------------------------------------------------------------------------------------------------------------//

// Label definition for the goto statement.             // Example: 
R_LABEL                 :   TOKEN_ID TOKEN_COLON        // primaDoFredo:
                            {
                                
                            }
                        ;

// Type cast
R_TYPE_CAST             :   TOKEN_LEFT_PARENTHESES R_TYPE_ALL TOKEN_RIGHT_PARENTHESES
                            {
                                NodeCreate(&($$.treeNode), NODE_TYPE_CAST);
                                $$.treeNode->nodeData.dVal = OP_DIVIDE_ASSIGN;
                            }
                        ;

//--------------------------------------------------------------------------------------------------------------------//
// Function Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Function signature i.e. the function format. Doesn't include the ; or the {. Example: int addNumbers(int x, int y)
R_FUNC_SIGNATURE        :   R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
                            {
                                TreeNode_st* pNode;

                                NodeCreate(&($$.treeNode), NODE_FUNC_PROTOTYPE);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddChild($$.treeNode, $6.treeNode);
                                
                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = $2.nodeData.dVal;
                               
                                NodeAddNewChild($$.treeNode, &pNode, NODE_TYPE);
                                pNode->nodeData.dVal = $3.nodeData.dVal;

                            }

                        |   R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_FUNC_PROTOTYPE);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                NodeAddChild($$.treeNode, $5.treeNode);

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_TYPE);
                                pNode->nodeData.dVal = $2.nodeData.dVal;
                             
                            }

                        |   R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_FUNC_PROTOTYPE);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;
                                
                                NodeAddChild($$.treeNode, $5.treeNode);

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_TYPE);
                                pNode->nodeData.dVal = $2.nodeData.dVal;
                          
                            }

                        |   R_TYPE_ALL TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
                            {

                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_FUNC_PROTOTYPE);
                                $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                                
                                NodeAddChild($$.treeNode, $4.treeNode);

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                            }
                        ;

// Function prototype is just a function signature followed by a semi
R_FUNC_PROTOTYPE        :   R_FUNC_SIGNATURE TOKEN_SEMI 
                            {
                                
                            }
                        ;

// Function implementation containing the function signature and a compound statement where it is implemented
R_FUNC_IMPL             :   R_FUNC_SIGNATURE R_COMPOUND_STATEMENT
                            {

                            }
                        ;

// TODO: CHECK R_ARG_LIST AND R_ARG_LIST_INTERNAL
// Function argument list. Note: The argument list can be empty. Example: int x | int x, int y
R_ARG_LIST              :   %empty 
//                            {
//                                $$.treeNode = NULL;
//                            }

                        |   R_ARG_LIST_INTERNAL
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;


R_ARG_LIST_INTERNAL     :   R_ARG 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_ARG_LIST TOKEN_COMMA R_ARG
                            {
                                $3.treeNode->pSibling = $1.treeNode->pSibling;
                                $1.treeNode->pSibling = $3.treeNode;
                                
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Function argument type. Example: int x | const char* pString.
R_ARG                   :   R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID 
                            {
                                
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_PARAM);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;
                                
                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_TYPE);
                                pNode->nodeData.dVal = $2.nodeData.dVal;

                            }

                        |   R_TYPE_ALL TOKEN_ID 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_PARAM);
                                $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                                
                                NodeAddNewChild($$.treeNode, &pNode, NODE_TYPE);
                                pNode->nodeData.dVal = $1.nodeData.dVal;

                            }
                        ;

//--------------------------------------------------------------------------------------------------------------------//
// Variable Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Variable declarations can have a visibility qualifier (extern/static), a type qualifier (volatile/const), a sign qualifier.
// (signed/unsigned) and must explicitly specify a type (short, int, float...).                                             // Examples:
R_VAR_PREAMBLE          :   TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID      // register static const unsigned int var
                            {   
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $6.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $3.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $4.nodeData.dVal;

                                NodeAddChild($$.treeNode, $5.treeNode); 
                            }

                        |   TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID                       // register static const int var
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $3.nodeData.dVal;

                                NodeAddChild($$.treeNode, $4.treeNode); 
                            }        
                                   
                        |   TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                      // register static signed int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $3.nodeData.dVal;

                                NodeAddChild($$.treeNode, $4.treeNode); 
                            }    
                                         
                        |   TOKEN_REGISTER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                             // register const signed int var     
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $3.nodeData.dVal;

                                NodeAddChild($$.treeNode, $4.treeNode); 
                            }   
                                             
                        |   TOKEN_REGISTER R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID                                       // register static int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $4.treeNode); 
                            }   
                                                     
                        |   TOKEN_REGISTER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID                                              // register const int var    
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $3.treeNode); 
                            }                      
                                         
                        |   TOKEN_REGISTER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                                             // register signed int var         
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $3.treeNode); 
                            }       
                                                       
                        |   TOKEN_REGISTER R_TYPE_ALL TOKEN_ID                                                              // register int var
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MISC);
                                pNode->nodeData.dVal = (long int) FLAG_REGISTER;

                                NodeAddChild($$.treeNode, $2.treeNode); 
                            }                               
                                             
                        |   R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                     // static const unsigned int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $5.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $3.nodeData.dVal;

                                NodeAddChild($$.treeNode, $4.treeNode); 
                            }
                                                
                        |   R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID                                      // static const int var
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $3.treeNode); 
                            }                 
                                            
                        |   R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                                     // static signed int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $3.treeNode); 
                            }               
                                            
                        |   R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                                            // const signed int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $2.nodeData.dVal;

                                NodeAddChild($$.treeNode, $3.treeNode); 
                            }          
                                                       
                        |   R_VISIBILITY_QUALIFIER R_TYPE_ALL TOKEN_ID                                                      // static int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_VISIBILITY);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddChild($$.treeNode, $2.treeNode); 
                            }                 
                                                    
                        |   R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID                                                             // const int var  
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_MODIFIER);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddChild($$.treeNode, $2.treeNode); 
                            }                                                
                                      
                        |   R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID                                                            // signed int var  
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                NodeAddNewChild($$.treeNode, &pNode, NODE_SIGN);
                                pNode->nodeData.dVal = (long int) $1.nodeData.dVal;

                                NodeAddChild($$.treeNode, $2.treeNode); 
                            }                                      
                                                 
                        |   R_TYPE_ALL TOKEN_ID                                                                             // int var 
                            {
                                TreeNode_st* pNode;
                                
                                NodeCreate(&($$.treeNode), NODE_VAR_NAME);
                                $$.treeNode->nodeData.sVal = $2.nodeData.sVal;

                                NodeAddChild($$.treeNode, $1.treeNode); 
                            }
                        ;                                                                           

// Variable declaration (simple or followed by its assignment).                         // Examples:
R_VAR_DECLARATION       :   R_VAR_PREAMBLE TOKEN_SEMI                                   // int var;
                            {   
                                NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
                                
                                NodeAddChild($$.treeNode, $1.treeNode);
                            }
                                                      
                        |   R_VAR_PREAMBLE R_ASSIGN_OPERATOR R_EXP TOKEN_SEMI       // int var = 1;  
                            {
                                NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
                            
                                NodeAddChild($$.treeNode, $1.treeNode);

                                NodeAddChild($$.treeNode, $3.treeNode);
                            }
                        ;                               

// Array declaration                                                                                // Examples:
R_ARR_DECLARATION           :   R_VAR_PREAMBLE R_ARR_SIZE TOKEN_SEMI                                // int var [2];
                                {

                                }      

                            |   R_VAR_PREAMBLE R_ARR_SIZE R_ASSIGN_OPERATOR R_ARR_ARGS TOKEN_SEMI   // var [] = {1, 2, 3};
                                {
                                    
                                }
                            ;   

// Dimensions of the array                                                                  // Examples:
R_ARR_SIZE                  :   R_ARR_SIZE TOKEN_LEFT_BRACKET TOKEN_RIGHT_BRACKET           // [][][]
                                {

                                }

                            |   R_ARR_SIZE TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET     // [2][3]
                                {

                                }

                            |   TOKEN_LEFT_BRACKET TOKEN_RIGHT_BRACKET                      // []
                                {

                                }

                            |   TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET                // [2]
                                {

                                }
                            ;

// Arguments of the array                                                                               // Examples:
R_ARR_ARGS                  :   R_ARR_ARGS TOKEN_COMMA TOKEN_LEFT_BRACE R_ARR_ARGS TOKEN_RIGHT_BRACE    // {{{...},{...},{...}},{{...},{...}}}
                                {

                                }
                                
                            |   TOKEN_LEFT_BRACE R_ARR_ARGS TOKEN_RIGHT_BRACE                           // {...}
                                {
                                    
                                }

                            |   R_ARR_ARGS TOKEN_COMMA TOKEN_LEFT_BRACE R_EXP_LIST TOKEN_RIGHT_BRACE    // {}
                                {

                                }
                                
                            |   TOKEN_LEFT_BRACE R_EXP_LIST TOKEN_RIGHT_BRACE
                                {
                                    
                                }
                            ;

// Rule to assign a value to a variable.                                                        // Example:
R_VAR_ASSIGNMENT            :   TOKEN_ID R_ASSIGN_OPERATOR R_EXP TOKEN_SEMI                     // var = 1;
                                {
                                    NodeCreate(&($$.treeNode), NODE_VAR_ASSIGNMENT);
                                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;

                                    NodeAddChild($$.treeNode, $3.treeNode);
                                }
                            ;      

// Rule to assign values to an array.                                                           // Example: 
R_ARR_ASSIGNMENT            :   TOKEN_ID R_ARR_SIZE R_ASSIGN_OPERATOR R_ARR_ARGS TOKEN_SEMI     // var[1] = {1};
                                {
                                    
                                }
                            ;

// Standard C data types. 
// Doesn't account for user defined types (aka typedefs), as this will need a symbol table.     // Data Types:
R_TYPE                      :   TOKEN_CHAR                                                      // Char  
                                {
                                    $$.nodeData.dVal = TYPE_CHAR;
                                }

                            |   TOKEN_SHORT                                                     // Short
                                {
                                    $$.nodeData.dVal = TYPE_SHORT;
                                }

                            |   TOKEN_INT                                                       // Int
                                {
                                    $$.nodeData.dVal = TYPE_INT;
                                }

                            |   TOKEN_LONG                                                      // Long
                                {
                                    $$.nodeData.dVal = TYPE_LONG;
                                }

                            |   TOKEN_FLOAT                                                     // Float
                                {
                                    $$.nodeData.dVal = TYPE_FLOAT;
                                }
                                
                            |   TOKEN_DOUBLE                                                    // Double
                                {
                                    $$.nodeData.dVal = TYPE_DOUBLE;
                                }

                            |   TOKEN_LONG TOKEN_DOUBLE                                         // Long Double
                                {
                                    $$.nodeData.dVal = TYPE_LONG_DOUBLE;
                                }
                            ;

// Standard C data types but with pointer. This rule implements support for pointers of n length. Example: int*** ...
R_TYPE_PTR                  :   R_TYPE_PTR TOKEN_ASTERISK
                                {
                                    TreeNode_st* pNode;

                                    NodeAddNewChild($1.treeNode, &pNode, NODE_POINTER);    

                                    $$.treeNode = $1.treeNode;   
                                }

                            |   R_TYPE TOKEN_ASTERISK
                                {  
                                    TreeNode_st* pNode;

                                    NodeAddNewChild($1.treeNode, &pNode, NODE_POINTER);    

                                    $$.treeNode = $1.treeNode;                              
                                }
                            ;

// Union between the pointer and standard types.
R_TYPE_ALL                  :   R_TYPE 
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = $1.nodeData.dVal;   
                                }
                                
                            |   R_TYPE_PTR
                                {
                                    $$.nodeData.dVal = $1.nodeData.dVal;
                                }
                            ;

// Functions and variables can be marked as either static or extern, never both at the same time.
R_VISIBILITY_QUALIFIER      :   TOKEN_STATIC
                                {
                                    $$.nodeData.dVal = (long int) VIS_STATIC;     
                                }

                            |   TOKEN_EXTERN
                                {
                                    $$.nodeData.dVal = (long int) VIS_EXTERN;     
                                }
                            ;

// Types can be marked as constant, volatile, or have no type qualifier.
// Here is also some other more advanced qualifiers not being considered.
R_MOD_QUALIFIER             :   TOKEN_CONSTANT
                                {
                                    $$.nodeData.dVal = (long int) MOD_CONST;  
                                } 

                            |   TOKEN_VOLATILE
                                {
                                    $$.nodeData.dVal = (long int) MOD_VOLATILE;  
                                }
                            ;

// Types can be marked as signed or unsigned, in C, if none is specified, the type defaults to signed.
R_SIGN_QUALIFIER            :   TOKEN_SIGNED 
                                {
                                    $$.nodeData.dVal = (long int) SIGN_SIGNED;
                                }

                            |   TOKEN_UNSIGNED
                                {
                                    $$.nodeData.dVal = (long int) SIGN_UNSIGNED;
                                }
                            ;

// End of file (EOF).
R_EOF                       :   TOKEN_EOF
                                {
                                    LOG_DEBUG("Reached end of file!\n");
                                    return 0;
                                }
                            ;
%%

//--------------------------------------------------------------------------------------------------------------------//
// Code
//--------------------------------------------------------------------------------------------------------------------//
int executeParser(TreeNode_st** _ppTreeRoot)
{
    int ret;

    if (!_ppTreeRoot)
        return -EINVAL;
    
    ret = initLexer();
    if (ret < 0)
    {
        LOG_ERROR("Failed to get source file!\n");
        return ret; 
    }

    LOG_WARNING("\n--------------Parser Start--------------\n");

    ppTreeRoot = _ppTreeRoot;

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