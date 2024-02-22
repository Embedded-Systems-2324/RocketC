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
%token NUM ID FNUM	

/* special symbols */	
%token ASSIGN PLUS MINUS TIMES OVER PERCENT LPAREN RPAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET TERNARY SEMI COLON COMMA 

/* operators*/
%token INCREMENT DECREMENT BITWISE_AND BITWISE_OR BITWISE_NOT BITWISE_XOR LOGICAL_NOT LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL LESS_THAN
%token GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL RIGHT_SHIFT LEFT_SHIFT PLUS_ASSIGN MINUS_ASSIGN MODULO LEFT_SHIFT_ASSIGN 
%token RIGHT_SHIFT_ASSIGN BITWISE_AND_ASSIGN BITWISE_OR_ASSIGN BITWISE_XOR_ASSIGN
%token MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULUS_ASSIGN

/* additional tokens */
%token PREPROCESSOR ARROW DEFINE EXIT
%token CONSTANT POINTER ADDRESS_OF OTHER

/* data types */
%type <identifier> ID
%type <intval> NUM
%type <floatval> FNUM

%union{
	char identifier[20];
	int intval;              // For integer literals
    double floatval;         // For floating-point literals
    char *strval;            // For string literals or identifiers
    char charval;            // For single character tokens
}

%%
prog:
  stmts endfile
;


stmts:
		| stmt SEMI stmts
		| stmt SEMI endofline stmts
		| stmt SEMI EOL stmts
		| stmts stmt SEMI
		;
stmt:
		if_stmt
		| while_stmt
		| do_stmt
		| for_stmt
		| return_stmt
		| endofline
		| declaration_stmt
		| compound_stmt
		;

		

//remove the type declaration
declaration_stmt:
		type ID{
			printf("The type you entered is ");
		}
		| type ID ASSIGN expr
		;

compound_stmt:
		LEFT_BRACE stmts RIGHT_BRACE
		;

expr_opt:
		| expr
		;

expr:
	ID op ID
	| NUM op NUM
		/* math expression rules */
		;


op: PLUS 
	| MINUS 
	| TIMES 
	| OVER 
	| PERCENT
	;


// to do later
if_stmt: ;

return_stmt:
		RETURN expr_opt
		;

while_stmt: ;


do_stmt:
			DO stmt WHILE LPAREN expr RPAREN
			;

for_stmt:
			FOR LPAREN expr_opt SEMI expr_opt SEMI expr_opt RPAREN stmt
			;

endofline: EOL;


endfile: ENDFILE
{
	printf("End of file\n");
};

//Mulop e Adop devem ser separados por causa das propriedades da matematica (Mult é prioritaria e deve aparecer nos ramos mais abaixo da árvore (Slides 32 a 39 - Parser))

addop:      PLUS | MINUS ;

mullop:     TIMES | OVER ;

boolop:     EQUAL | NOT_EQUAL | LESS_THAN | GREATER_THAN | LESS_THAN_OR_EQUAL | GREATER_THAN_OR_EQUAL ;

logicop:    LOGICAL_NOT | LOGICAL_AND | LOGICAL_OR ;

bitlogicop: BITWISE_AND | BITWISE_OR | BITWISE_NOT | BITWISE_XOR ;

assignop:   ASSIGN | PLUS_ASSIGN | MINUS_ASSIGN ;

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
