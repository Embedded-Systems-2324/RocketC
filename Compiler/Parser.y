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
assignment_stmt:  ID assign_op expr                                         // a = b;
               |  unary_op ID                                               // ++a;
               |  ID unary_op                                               // a++;
               |  ID assign_op LEFT_BRACE expr RIGHT_BRACE                  // a = {2, b + c, ...};
               |  ID LEFT_BRACKET expr RIGHT_BRACKET assign_op expr         // a[n] = b;
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
variable_declaration:  prefixes type ID                     // const int a;
                    |  prefixes type ID assign_op expr      // const int a = b;
                    ;

// Array
array_declaration:  prefixes type ID LEFT_BRACKET expr RIGHT_BRACKET                                            // const int a[n];
                 |  prefixes type ID LEFT_BRACKET expr RIGHT_BRACKET assign_op LEFT_BRACE expr RIGHT_BRACE      // const int a[n] = {2, b + c, ...};
                 ;

// Functions
func_declaration:  prefixes type ID LPAREN func_parameters_declaration RPAREN compound_stmt     // const int func(...) { ... }
                |  prefixes type ID LPAREN func_parameters_declaration RPAREN SEMI              // const int func(...);
                ;

func_parameters_declaration:                                                                    // ( )
                           |  func_parameters_declaration COMMA variable_declaration            // (const int a, unsigned int b, ...)
                           |  variable_declaration                                              // (const int a)
                           |  VOID                                                              // (void)
                           ;

// Struct, Union
data_struct_stmts:                                              // { }
                 |  data_struct_stmts declaration_stmt SEMI     // {const int a; unsigned int b; ...}
                 |  data_struct_stmts func_declaration SEMI     // {const int func(...); ...}
                 |  declaration_stmt SEMI                       // {const int a;}
                 |  func_declaration SEMI                       // {const int func(...);}
                 ;

struct_declaration:  STRUCT ID LEFT_BRACE data_struct_stmts RIGHT_BRACE     // struct strct { ... };
		          ;

union_declaration:  UNION ID LEFT_BRACE data_struct_stmts RIGHT_BRACE       // union un { ... };
		         ;

// Enum
enum_declaration:  ENUM ID LEFT_BRACE enum_parameters RIGHT_BRACE           // enum en { ... };
		        ;

enum_parameters:                                // { }
               |  enum_parameters COMMA ID      // {en1, en2, ...}
               |  ID                            // {en1}
               ;

// Typedef
typeDef_declaration:  TYPEDEF enum_declaration ID                                   // typedef enum en;
                   |  TYPEDEF ENUM LEFT_BRACE enum_parameters RIGHT_BRACE ID        // typedef enum { ... } en;
                   |  TYPEDEF union_declaration ID                                  // typedef union un;
                   |  TYPEDEF UNION LEFT_BRACE data_struct_stmts RIGHT_BRACE ID     // typedef union { ... } un;
                   |  TYPEDEF struct_declaration ID                                 // typedef struct strct;
                   |  TYPEDEF STRUCT LEFT_BRACE data_struct_stmts RIGHT_BRACE ID    // typedef struct { ... } strct;
                   |  TYPEDEF type ID                                               // typedef int a;
                   ;
            
/*
*   Instantiation
*/
instantiation_stmt:  struct_inst
                  |  union_inst
                  |  func_inst
                  ;

struct_inst:  STRUCT ID ID      // struct strct st1;
           ;

union_inst:  UNION ID ID        // union un un1;
          ;

func_inst:  ID LPAREN func_inst_parameters RPAREN   // func( ... );
         ;

func_inst_parameters:                                       // ( )
                    |  func_inst_parameters COMMA expr      // (a, b+c, ...)
                    |  expr                                 // (b)
                    |  VOID                                 // (void)
                    ;

/*
*   Expressions
*/
expr:  expr op term             // a + b
    |  expr comp_op term        // a == b
    |  expr bitwise_op term     // a & b
    |  expr logical_op term     // a && b
    |  term                     // a
    ;

term:  term prio_op operand     // a * b
    |  operand                  // a
    ;

operand:  unary_op factor       // ++a
       |  factor unary_op       // a++
       |  type_cast factor      // (int) a
       |  LOGICAL_NOT factor    // !a
       |  factor                // a
       ;

factor:  LPAREN expr RPAREN     // (a)
      |  NUM                    // 2
      |  ID                     // a
      |  FNUM                   // 1.5
      |  func_inst              // func(...);
      |  size_of_stmt           // sizeof(...)
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
compound_stmt:  LEFT_BRACE stmts RIGHT_BRACE        // {a = b; ...}
             |  LEFT_BRACE RIGHT_BRACE              // { }
             ;

// If
if_stmt:   IF LPAREN condition RPAREN compound_stmt                        // if (a==b) { ... }
        |  IF LPAREN condition RPAREN compound_stmt elseif_stmt            // if (a==b) { ... } else if (a==c) { ... } else { ... }
        |  IF LPAREN condition RPAREN compound_stmt else_stmt              // if (a==b) { ... } else { ... }   
        |  IF LPAREN condition RPAREN stmt                                 // if (a==b) a = c;
        |  IF LPAREN condition RPAREN stmt elseif_stmt                     // if (a==b) a = c; else if (a==c) { ... } else { ... }   
        |  IF LPAREN condition RPAREN stmt else_stmt                       // if (a==b) a = c; else { ... }   
        |  IF LPAREN condition RPAREN SEMI                                 // if (a==b);
        ;

elseif_stmt:  elseif_stmt ELSEIF LPAREN condition RPAREN stmt              // else if (a==c) a = b; ...
           |  elseif_stmt ELSEIF LPAREN condition RPAREN compound_stmt     // else if (a==c) { ... }
           |  ELSEIF LPAREN condition RPAREN stmt                          // else if (a==c) a = b;
           |  ELSEIF LPAREN condition RPAREN stmt else_stmt                // else if (a==c) a = b; else { ... }
           |  ELSEIF LPAREN condition RPAREN compound_stmt                 // else if (a==c) { ... }
           |  ELSEIF LPAREN condition RPAREN compound_stmt else_stmt       // else if (a==c) { ... } else { ... } 
           ; 

else_stmt: ELSE stmt                                                       // else a = b;
        |  ELSE compound_stmt                                              // else { ... }
        ;

// While
do_while_stmt:  DO compound_stmt WHILE LPAREN condition RPAREN      // do { ... } while (a==b);
       |  DO stmt WHILE LPAREN LPAREN condition RPAREN              // do a++ while (a==b);
       ;

while_stmt:  WHILE LPAREN condition RPAREN compound_stmt            // while(a==b) { ... }
          |  WHILE LPAREN condition RPAREN stmt                     // while(a==b) a++;
          |  WHILE LPAREN condition RPAREN SEMI                     // while(a==b);
          ;

// For
for_stmt:  FOR LPAREN condition SEMI condition SEMI condition RPAREN compound_stmt              // for(a = 0; a<b; a++) {...}
        |  FOR LPAREN condition SEMI condition SEMI condition RPAREN stmt                       // for(a = 0; a<b; a++) a++;
        |  FOR LPAREN variable_declaration SEMI condition SEMI condition RPAREN compound_stmt   // for(int a=0; a<b; a++) {...}
        |  FOR LPAREN variable_declaration SEMI condition SEMI condition RPAREN stmt            // for(int a=0; a<b; a++) a++;
        ;                                                                                       // Separated since there can't be variable declarations on camps 2 and 3

// Statements suported by all camps
condition: expr             
        |  assignment_stmt
        ;

// Switch
switch_case:  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list RIGHT_BRACE                      // switch (a) { ... }
           |  SWITCH LPAREN ID RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE         // switch (a) { case 0: ... default: ... }
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list RIGHT_BRACE                    // swicth (a+b) { ... }
           |  SWITCH LPAREN expr RPAREN LEFT_BRACE case_list case_default RIGHT_BRACE       // switch (a+b) { case 0: ... default: ... }
           ;

case_list:  case_list case                  // {case 0: ... case 1: ... case 2: ...}
         |  case                            // {case 0: ...}
         ;

case:  CASE NUM COLON stmts BREAK           // case 0: a = b; ... break;
    |  CASE NUM COLON stmt                  // case 0: a = b;
    ;

case_default:  DEFAULT COLON stmts BREAK    // default: a = b; ... break;
            |  DEFAULT COLON stmt           // default: a = b;
            ;

// Return
return_stmt:  RETURN expr                   // return (a + b);
		   ;

// Other
goto_stmt: GOTO ID SEMI ;                               // goto(a);

size_of_stmt: SIZEOF LPAREN ID RPAREN                   // sizeof(a);
			| SIZEOF LPAREN type RPAREN                 // sizeof(int)
			| SIZEOF LPAREN special_type ID RPAREN      // sizeof(struct strct);
			;

label: ID COLON ;               // LABEL:

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
type_cast: LPAREN type RPAREN ;         // (int) a

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