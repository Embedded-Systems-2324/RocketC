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
%token GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL RIGHT_SHIFT LEFT_SHIFT PLUS_ASSIGN MINUS_ASSIGN MODULO LEFT_SHIFT_ASSIGN 
%token RIGHT_SHIFT_ASSIGN BITWISE_AND_ASSIGN BITWISE_OR_ASSIGN BITWISE_XOR_ASSIGN
%token MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULUS_ASSIGN

/* additional tokens */
%token PREPROCESSOR ARROW DEFINE
%token CONSTANT POINTER ADDRESS_OF OTHER

%token AUTO
%token DOT
%token STRINGliteral

%union{
    char identifier[20];
    int intval;              // For integer literals
    double floatval;         // For floating-point literals
    char *strval;            // For string literals or identifiers
    char charval;            // For single character tokens
}

/* data types */
%type <identifier> ID
%type <intval> NUM
%type <floatval> FNUM

%%
// Program
prog:  stmts endfile
    ;

//all possible statements
stmts:
     |  stmt SEMI stmts
     |  stmts stmt SEMI
     ;

// Statement Types
stmt:  if_stmt
    |  while_stmt
    |  do_stmt
    |  for_stmt
    |  return_stmt
    |  declaration_stmt
    |  compound_stmt
    |  expr
    ;

// Verify and reorganize declaraction_stmt for either fit all types of declarations or completly remove it
declaration_stmt:  type ID                          { printf("The type you entered is "); }
                |  type ID ASSIGN expr
                ;

compound_stmt:  LEFT_BRACE stmts RIGHT_BRACE
		     ;

// Functions
function_declaration:  base_declaration LPAREN function_parameters RPAREN compound_stmt
                    |  base_declaration LPAREN function_parameters RPAREN
                    ;

function_parameters:
                   |  function_parameters COLON base_declaration
                   |  base_declaration
                   |  VOID
                   ;

base_declaration:  prefixes type ID ;

// Instantiation

function_inst:  ID LPAREN function_inst_parameters RPAREN ;

function_inst_parameters:  function_inst_parameters COLON expr
                        |  expr
                        ;

// Expressions
expr:  arith_expr
	|  cond_expr
	;

cond_expr:  cond_expr cond_op factor
		 |  LOGICAL_NOT cond_expr
		 |  factor
		 ;

arith_expr:  arith_expr op term
          |  term
          ;

term:  term prio_op operand
    |  operand
    ;

operand:  unary_op factor
       |  factor unary_op
       |  type_cast factor
       |  factor
       ;

factor:  LPAREN arith_expr RPAREN
      |  NUM
      |  ID
      |  FNUM
      |  function_inst
      ;

// Operators
op:  PLUS
  |  MINUS
  |  RIGHT_SHIFT
  |  LEFT_SHIFT
  ;
  
prio_op:  TIMES
       |  OVER
       |  PERCENT
       ;

unary_op: INCREMENT
        | DECREMENT
        ;

cond_op:  GREATER_THAN
       |  LESS_THAN_OR_EQUAL
       |  GREATER_THAN_OR_EQUAL
       |  LESS_THAN
       |  LOGICAL_AND
       |  LOGICAL_OR
       |  EQUAL
       |  NOT_EQUAL
       ;

// Flow Control
if_stmt:   IF LPAREN expr RPAREN compound_stmt                                   //{printf("IF statement: %s", $2);}
		|  IF LPAREN expr RPAREN compound_stmt elseif_list                       //{printf("IF statement: %s", $2);}
		|  IF LPAREN expr RPAREN compound_stmt ELSE compound_stmt                //{printf("IF statement: %s", $2);}
        |  IF LPAREN expr RPAREN compound_stmt elseif_list ELSE compound_stmt    //{printf("IF statement: %s", $2);}
        ;

elseif_list:  elseif_list ELSEIF LPAREN expr RPAREN compound_stmt
           |  ELSEIF LPAREN expr RPAREN compound_stmt
           ;

do_stmt:  DO compound_stmt WHILE expr
       |  DO stmt WHILE expr
       ;

while_stmt:  WHILE LPAREN expr RPAREN compound_stmt
          |  WHILE LPAREN expr RPAREN stmt
          ;

for_stmt:  FOR LPAREN expr SEMI expr SEMI expr RPAREN compound_stmt
        |  FOR LPAREN expr SEMI expr SEMI expr RPAREN stmt
        ;

switch_case:  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list RIGHT_BRACE
           |  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list RIGHT_BRACE
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE
           ;

case_list:  case_list case
         |  case
         ;

case:  CASE NUM COLON stmts BREAK ;

case_default:  DEFAULT NUM COLON stmts BREAK ;


struct_stmt: STRUCT ID LEFT_BRACE stmts RIGHT_BRACE SEMI
		   ;

enum_stmt: ENUM ID LEFT_BRACE stmts RIGHT_BRACE SEMI
		 ;

union_stmt: UNION ID LEFT_BRACE stmts RIGHT_BRACE SEMI
		 ;

goto_stmt: GOTO ID SEMI;

typeDef_stmt: TYPEDEF enum_stmt ID SEMI
			| TYPEDEF struct_stmt ID SEMI
			;  

size_of_stmt: SIZEOF LPAREN ID RPAREN
			| SIZEOF LPAREN type RPAREN
			| SIZEOF LPAREN special_type ID RPAREN
			;

return_stmt:  RETURN expr
		   ;

endfile:  ENDFILE               { printf("\nEnd of file\n");   printf("Numero de Linhas: %d\n", linenum);     return 0;};

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

type_cast: LPAREN type RPAREN ;

%%

// Parser Functions
int yyerror(char *s)
{
  	fprintf (stderr, "%s in line number : %d\n", s, linenum);
	return 1;
}

void parse(void){
	File_Init();
	yyparse();
}
