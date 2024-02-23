%{
#include "globals.h"
#include "scanner.h"

int yylex();
int yyerror(char *s);
%}


/* book-keeping tokens */
%token ENDFILE ERROR EOL

/* Reserved Words */
%token IF ELSEIF ELSE DO WHILE FOR SWITCH CASE DEFAULT RETURN BREAK INT FLOAT DOUBLE CHAR VOID STRUCT TYPEDEF 
%token AUTO CONTINUE EXTERN GOTO LONG ENUM REGISTER SHORT SIZEOF STATIC SIGNED UNION UNSIGNED VOLATILE

/* multicharacter tokens */
%token NUM ID FNUM STRINGliteral

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

/* data types */
%type <identifier> ID
%type <intval> NUM
%type <floatval> FNUM
%type <strval> STRINGliteral

%union{
	char identifier[20];
	int intval;              // For integer literals
    double floatval;         // For floating-point literals
    char *strval;            // For string literals or identifiers
    char charval;            // For single character tokens
}

%%
//program
prog:
   stmts endfile
;

//all possible statements
stmts:
		| stmt SEMI stmts
		| stmt SEMI endofline stmts
		| stmt SEMI EOL stmts
		| stmts stmt SEMI
		;

//statement types
stmt:
		if_stmt
		| while_stmt
		| do_stmt
		| for_stmt
		| return_stmt
		| endofline
		| declaration_stmt
		| compound_stmt
		| expr
		;

		

//remove the type declaration
declaration_stmt:
		type ID{
			printf("The type you entered is ");
		}
		| type arith_expr
		;		;

compound_stmt:
		LEFT_BRACE stmts RIGHT_BRACE
		;

//list of all expression types
expr:
	arith_expr
	;


arith_expr:
		NUM op NUM{
				printf("OP between %d and %d\n", $1, $3);
			}
		| ID op ID{
				printf("OP between %s and %s\n", $1, $3);
			}
		| ID op NUM{
				printf("OP between %s and %d\n", $1, $3);
			}
		| NUM op ID{
				printf("OP between %d and %s\n", $1, $3);
			}	

op: PLUS 
	| MINUS 
	| TIMES 
	| OVER 
	| PERCENT
	;

// to do later
if_stmt:
	;
/* if_stmt: LPAREN cond_exp RPAREN stmts {pritf("IF statement: %s", $2);}
		| LPAREN ID RPAREN stmts {pritf("IF statement: %s", $2);}
		| LPAREN cond_exp RPAREN stmts ELSE stmts {pritf("IF statement: %s", $2);}
		

cond_exp: ID cond ID 
		| ID cond NUM 
		| NUM cond ID
		| NUM cond NUM
		| LOGICAL_NOT ID

cond:GREATER_THAN 
	 | LESS_THAN_OR_EQUAL 
	 | GREATER_THAN_OR_EQUAL
	 | LESS_THAN
	 | LOGICAL_AND 
	 | LOGICAL_OR 
	 | EQUAL 
	 | NOT_EQUAL
	; */

return_stmt:
		RETURN expr
		;

while_stmt: ;


do_stmt:
			DO stmt WHILE LPAREN expr RPAREN
			;

for_stmt:
			FOR LPAREN expr SEMI expr SEMI expr RPAREN stmt
			;

endofline: EOL;


endfile: ENDFILE
{
	printf("End of file\n");
};



type:
		INT
		| FLOAT
		| DOUBLE
		| CHAR
		| VOID
		| STRUCT
		| TYPEDEF
		;

%%

int yyerror(char *s)
{
  	fprintf (stderr, "%s\n", s);
	return 0;
}

void parse(void){
	File_Init();
	yyparse();
}
