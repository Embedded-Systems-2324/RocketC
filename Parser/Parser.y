%{
#include "globals.h"
#include "scanner.h"

int yylex();
int yyerror(char *s);
%}

/* book-keeping tokens */
%token ENDFILE ERROR

/* Reserved Words */
%token IF ELSEIF ELSE DO WHILE FOR SWITCH CASE DEFAULT RETURN BREAK INT FLOAT DOUBLE CHAR VOID STRUCT TYPEDEF
%token CONTINUE EXTERN GOTO LONG ENUM REGISTER SHORT SIZEOF STATIC SIGNED UNION UNSIGNED VOLATILE

/* multicharacter tokens */
%token NUM ID FNUM

/* special symbols */
%token ASSIGN PLUS MINUS TIMES OVER PERCENT LPAREN RPAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET TERNARY SEMI COLON COMMA

/* operators*/
%token INCREMENT DECREMENT BITWISE_AND BITWISE_OR BITWISE_NOT BITWISE_XOR LOGICAL_NOT LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL LESS_THAN
%token GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL RIGHT_SHIFT LEFT_SHIFT PLUS_ASSIGN MINUS_ASSIGN LEFT_SHIFT_ASSIGN
%token RIGHT_SHIFT_ASSIGN BITWISE_AND_ASSIGN BITWISE_OR_ASSIGN BITWISE_XOR_ASSIGN
%token MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULUS_ASSIGN

/* additional tokens */
%token CARDINAL ARROW DEFINE
%token CONSTANT POINTER ADDRESS_OF OTHER

%token DOT QUOTE

%union{
    char identifier[20];
    int intval;              // Integer literals
    double floatval;         // Floating-point literals
}

/* Data types */
%type <identifier> ID
%type <intval> NUM
%type <floatval> FNUM

%%

/*
*   Program
*/
prog:  prog endfile
    |  prog global_stmt
    |  global_stmt
    ;

/*
*   Statements
*/
// Global Statements
// Statements supported in the global scope
global_stmt:  func_declaration
           |  declaration_stmt SEMI
           |  instantiation_stmt SEMI
           ;

// Local Statement List
stmts:  stmts stmt
     |  stmt
     ;

// Local Statements
// Statements supported in the local scope
stmt:  goto_stmt
    |  label
    |  if_stmt
    |  for_stmt
    |  while_stmt
    |  switch_case
    |  do_while_stmt SEMI
    |  return_stmt SEMI
    |  declaration_stmt SEMI
    |  assignment_stmt SEMI
    |  instantiation_stmt SEMI
    |  CONTINUE SEMI
    |  BREAK SEMI
    ;

/*
*   Assignment
*/
assignment_stmt:  ID assign_op expr
               |  unary_op ID
               |  ID unary_op
               |  ID assign_op LEFT_BRACE expr RIGHT_BRACE
               |  ID LEFT_BRACKET expr RIGHT_BRACKET assign_op expr
               ;

/*
*   Declarations
*/
declaration_stmt:  variable_declaration
                |  array_declaration
                |  struct_declaration
                |  enum_declaration
                |  union_declaration
                |  typeDef_declaration
                ;

// Variables
variable_declaration:  prefixes type ID
                    |  prefixes type ID assign_op expr
                    ;

// Array
array_declaration:  prefixes type ID LEFT_BRACKET expr RIGHT_BRACKET
                 |  prefixes type ID LEFT_BRACKET expr RIGHT_BRACKET assign_op LEFT_BRACE expr RIGHT_BRACE
                 ;

// Functions
func_declaration:  prefixes type ID LPAREN func_parameters_declaration RPAREN compound_stmt
                |  prefixes type ID LPAREN func_parameters_declaration RPAREN SEMI
                ;

func_parameters_declaration:
                           |  func_parameters_declaration COMMA variable_declaration
                           |  variable_declaration
                           |  VOID
                           ;

// Struct, Union
data_struct_stmts:
                 |  data_struct_stmts declaration_stmt SEMI
                 |  data_struct_stmts func_declaration SEMI
                 |  declaration_stmt SEMI
                 |  func_declaration SEMI
                 ;

struct_declaration:  STRUCT ID LEFT_BRACE data_struct_stmts RIGHT_BRACE
		          ;

union_declaration:  UNION ID LEFT_BRACE data_struct_stmts RIGHT_BRACE
		         ;

// Enum
enum_declaration:  ENUM ID LEFT_BRACE enum_parameters RIGHT_BRACE
		        ;

enum_parameters:
               |  enum_parameters COMMA ID
               |  ID
               ;

// Typedef
typeDef_declaration:  TYPEDEF enum_declaration ID
                   |  TYPEDEF ENUM LEFT_BRACE enum_parameters RIGHT_BRACE ID
                   |  TYPEDEF union_declaration ID
                   |  TYPEDEF UNION LEFT_BRACE data_struct_stmts RIGHT_BRACE ID
                   |  TYPEDEF struct_declaration ID
                   |  TYPEDEF STRUCT LEFT_BRACE data_struct_stmts RIGHT_BRACE ID
                   |  TYPEDEF type ID
                   ;

/*
*   Instantiation
*/
instantiation_stmt:  struct_inst
                  |  union_inst
                  |  func_inst
                  ;

struct_inst:  STRUCT ID ID
           ;

union_inst:  UNION ID ID
          ;

func_inst:  ID LPAREN func_inst_parameters RPAREN
         ;

func_inst_parameters:
                    |  func_inst_parameters COMMA expr
                    |  expr
                    |  VOID
                    ;

/*
*   Expressions
*/
expr:  expr op term
    |  expr comp_op term
    |  expr bitwise_op term
    |  expr logical_op term
    |  term
    ;

term:  term prio_op operand
    |  operand
    ;

operand:  unary_op factor
       |  factor unary_op
       |  type_cast factor
       |  LOGICAL_NOT factor
       |  factor
       ;

factor:  LPAREN expr RPAREN
      |  NUM
      |  ID
      |  FNUM
      |  func_inst
      |  size_of_stmt
      ;

/*
*   Operators
*/
op:  PLUS
  |  MINUS
  |  RIGHT_SHIFT
  |  LEFT_SHIFT
  ;

prio_op:  TIMES
       |  OVER
       |  PERCENT
       ;

unary_op:  INCREMENT
        |  DECREMENT
        ;

comp_op:  GREATER_THAN
       |  LESS_THAN_OR_EQUAL
       |  GREATER_THAN_OR_EQUAL
       |  LESS_THAN
       |  EQUAL
       |  NOT_EQUAL
       ;

logical_op:  LOGICAL_AND
          |  LOGICAL_OR
          ;

bitwise_op:  BITWISE_AND
          |  BITWISE_NOT
          |  BITWISE_OR
          |  BITWISE_XOR
          ;

assign_op:  ASSIGN
         |  PLUS_ASSIGN
         |  MINUS_ASSIGN
         |  MODULUS_ASSIGN
         |  LEFT_SHIFT_ASSIGN
         |  RIGHT_SHIFT_ASSIGN
         |  BITWISE_AND_ASSIGN
         |  BITWISE_OR_ASSIGN
         |  BITWISE_XOR_ASSIGN
         |  MULTIPLY_ASSIGN
         |  DIVIDE_ASSIGN
         ;

/*
*   Flow Control Statements
*/
compound_stmt:  LEFT_BRACE stmts RIGHT_BRACE
             |  LEFT_BRACE RIGHT_BRACE
             ;

// If
if_stmt:   IF LPAREN condition RPAREN compound_stmt
        |  IF LPAREN condition RPAREN compound_stmt elseif_stmt
        |  IF LPAREN condition RPAREN compound_stmt else_stmt
        |  IF LPAREN condition RPAREN stmt
        |  IF LPAREN condition RPAREN stmt elseif_stmt
        |  IF LPAREN condition RPAREN stmt else_stmt
        |  IF LPAREN condition RPAREN SEMI
        ;

elseif_stmt:  elseif_stmt ELSEIF LPAREN condition RPAREN stmt
           |  elseif_stmt ELSEIF LPAREN condition RPAREN compound_stmt
           |  ELSEIF LPAREN condition RPAREN stmt
           |  ELSEIF LPAREN condition RPAREN stmt else_stmt
           |  ELSEIF LPAREN condition RPAREN compound_stmt
           |  ELSEIF LPAREN condition RPAREN compound_stmt else_stmt
           ;

else_stmt: ELSE stmt
        |  ELSE compound_stmt
        ;

// While
do_while_stmt:  DO compound_stmt WHILE LPAREN condition RPAREN
       |  DO stmt WHILE LPAREN LPAREN condition RPAREN
       ;

while_stmt:  WHILE LPAREN condition RPAREN compound_stmt
          |  WHILE LPAREN condition RPAREN stmt
          |  WHILE LPAREN condition RPAREN SEMI
          ;

// For
for_stmt:  FOR LPAREN condition SEMI condition SEMI condition RPAREN compound_stmt
        |  FOR LPAREN condition SEMI condition SEMI condition RPAREN stmt
        |  FOR LPAREN variable_declaration SEMI condition SEMI condition RPAREN compound_stmt
        |  FOR LPAREN variable_declaration SEMI condition SEMI condition RPAREN stmt
        ;

// Statements suported by all camps
condition: expr
        |  assignment_stmt
        ;

// Switch
switch_case:  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list RIGHT_BRACE
           |  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list RIGHT_BRACE
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE
           ;

case_list:  case_list case
         |  case
         ;

case:  CASE NUM COLON stmts BREAK
    |  CASE NUM COLON stmt
    ;

case_default:  DEFAULT COLON stmts BREAK
            |  DEFAULT COLON stmt
            ;

// Return
return_stmt:  RETURN expr
		   ;

// Other
goto_stmt: GOTO ID SEMI ;

size_of_stmt: SIZEOF LPAREN ID RPAREN
			| SIZEOF LPAREN type RPAREN
			| SIZEOF LPAREN special_type ID RPAREN
			;

label: ID COLON ;

endfile:  ENDFILE               { printf("\nEnd of file\n");   printf("Numero de Linhas: %d\n", linenum);     return 0;};

/*
*   Types
*/
// Types
type:  INT
    |  FLOAT
    |  DOUBLE
    |  CHAR
    |  VOID
    ;

special_type: STRUCT
			| TYPEDEF
			| ENUM
			| UNION
			;

// Prefixes/Modifiers
prefixes:
        |  prefixes prefix
        |  prefix
        ;

prefix:  EXTERN
      |  LONG
      |  SHORT
      |  STATIC
      |  SIGNED
      |  UNSIGNED
      |  VOLATILE
      |  REGISTER
      |  CONSTANT
      ;

// Other type related
type_cast: LPAREN type RPAREN ;

%%

/*
*   Parser Functions
*/

// Error Handling Function:
// Returns line where syntax error was found
int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	return 1;
}

// Parse Function
void parse(void){
	File_Init();
	yyparse();
}