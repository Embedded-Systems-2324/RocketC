%{
#define YYPARSER 

/*Includes/*

#define YYSTYPE TreeNode *
static TreeNode * savedTree; /*aramazenamento da árvore sintático*/
static int yylex(void);
int yyerror(char *message);
char *scope = "";
char * idtype = "";
char * datatype = "";
%}

//Alfabeto de Tokens recebidos pelo Parser
%start init
%token INT CHAR 
%token VOID RETURN BREAK SWITCH CASE DEFAULT DO WHILE FOR IF ELSE TYPEDEF STRUCT
%token INCREMENT DECREMENT LOGICAL_AND LOGICAL_OR 
%token EQUAL NOT_EQUAL LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token RIGHT_SHIFT LEFT_SHIFT 
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN
%token SEMI COMMA COLON LPAREN RPAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACE TERNARY PREPROCESSOR ARROW
%token DEFINE EXIT
%left PLUS MINUS
%left TIMES OVER
%left PERCENT 
%left BITWISE_AND BITWISE_OR BITWISE_NOT BITWISE_XOR LOGICAL_NOT
%left LESS_THAN GREATER_THAN 
%nonassoc RPAREN RIGHT_BRACE RIGHT_BRACE
%nonassoc ELSE CASE BREAK DEFAULT

