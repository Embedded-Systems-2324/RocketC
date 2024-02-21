%option noyywrap 
%x INCOMMENT   
%{
#include "globals.h"
/*defenitions*/

%}

digit       [0-9]
number      {digit}+
identifier  [a-zA-Z_][a-zA-Z_0-9]*
newline     \n
whitespace  [ \t]+

%%
"void"          { printf("[KEYWORD]: VOID\n");                  return VOID; }
"int"           { printf("[KEYWORD]: INT\n");                   return INT; }
"char"          { printf("[KEYWORD]: CHAR\n");                  return CHAR; }
"return"        { printf("[KEYWORD]: RETURN\n");                return RETURN; }
"break"         { printf("[KEYWORD]: BREAK\n");                 return BREAK; }
"switch"        { printf("[KEYWORD]: SWITCH\n");                return SWITCH; }
"case"          { printf("[KEYWORD]: CASE\n");                  return CASE; }
"default"       { printf("[KEYWORD]: DEFAULT\n");               return DEFAULT; }
"do"            { printf("[KEYWORD]: DO\n");                    return DO; }
"while"         { printf("[KEYWORD]: WHILE\n");                 return WHILE; }
"for"           { printf("[KEYWORD]: FOR\n");                   return FOR; }
"if"            { printf("[KEYWORD]: IF\n");                    return IF; }
"else"          { printf("[KEYWORD]: ELSE\n");                  return ELSE; }
"typedef"       { printf("[KEYWORD]: TYPEDEF\n");               return TYPEDEF; }
"struct"        { printf("[KEYWORD]: STRUCT\n");                return STRUCT; }
"const"         { printf("[KEYWORD]: CONST\n");                 return CONSTANT; }
"+"             { printf("[OPERATOR]: PLUS\n");                 return PLUS; }
"-"             { printf("[OPERATOR]: MINUS\n");                return MINUS; }
"*"             { printf("[OPERATOR]: TIMES\n");                return TIMES; }
"/"             { printf("[OPERATOR]: OVER\n");                 return OVER; }
"%"             { printf("[OPERATOR]: PERCENT\n");              return PERCENT; }
"++"            { printf("[OPERATOR]: INCREMENT\n");            return INCREMENT; }
"--"            { printf("[OPERATOR]: DECREMENT\n");            return DECREMENT; }
"&"             { printf("[OPERATOR]: BITWISE_AND\n");          return BITWISE_AND; }
"|"             { printf("[OPERATOR]: BITWISE_OR\n");           return BITWISE_OR; }
"~"             { printf("[OPERATOR]: BITWISE_NOT\n");          return BITWISE_NOT; }
"^"             { printf("[OPERATOR]: BITWISE_XOR\n");          return BITWISE_XOR; }
"!"             { printf("[OPERATOR]: LOGICAL_NOT\n");          return LOGICAL_NOT; }
"&&"            { printf("[OPERATOR]: LOGICAL_AND\n");          return LOGICAL_AND; }
"||"            { printf("[OPERATOR]: LOGICAL_OR\n");           return LOGICAL_OR; }
"=="            { printf("[OPERATOR]: EQUAL\n");                return EQUAL; }
"!="            { printf("[OPERATOR]: NOT_EQUAL\n");            return NOT_EQUAL; }
"<"             { printf("[OPERATOR]: LESS_THAN\n");            return LESS_THAN; }
">"             { printf("[OPERATOR]: GREATER_THAN\n");         return GREATER_THAN; }
"<="            { printf("[OPERATOR]: LESS_THAN_OR_EQUAL\n");   return LESS_THAN_OR_EQUAL; }
">="            { printf("[OPERATOR]: GREATER_THAN_OR_EQUAL\n");return GREATER_THAN_OR_EQUAL; }
">>"            { printf("[OPERATOR]: RIGHT_SHIFT\n");          return RIGHT_SHIFT; }
"<<"            { printf("[OPERATOR]: LEFT_SHIFT\n");           return LEFT_SHIFT; }
"="             { printf("[OPERATOR]: ASSIGN\n");               return ASSIGN; }
"+="            { printf("[OPERATOR]: PLUS_ASSIGN\n");          return PLUS_ASSIGN; }
"-="            { printf("[OPERATOR]: MINUS_ASSIGN\n");         return MINUS_ASSIGN; }
";"             { printf("[DELIMITER]: SEMI\n");                return SEMI; }
","             { printf("[DELIMITER]: COMMA\n");               return COMMA; }
":"             { printf("[DELIMITER]: COLON\n");               return COLON; }
"("             { printf("[PAREN]: LEFT_PAREN\n");              return LPAREN; }
")"             { printf("[PAREN]: RIGHT_PAREN\n");             return RPAREN; }
"{"             { printf("[BRACE]: LEFT_BRACE\n");              return LEFT_BRACE; }
"}"             { printf("[BRACE]: RIGHT_BRACE\n");             return RIGHT_BRACE; }
"["             { printf("[BRACKET]: LEFT_BRACKET\n");          return LEFT_BRACKET; }
"]"             { printf("[BRACKET]: RIGHT_BRACKET\n");         return RIGHT_BRACKET; }
"?"             { printf("[TERNARY]: TERNARY\n");               return TERNARY; }
"#"             { printf("[PREPROCESSOR]: PREPROCESSOR\n");     return PREPROCESSOR; }
"->"            { printf("[OPERATOR]: ARROW\n");                return ARROW; }
"define"        { printf("[PREPROCESSOR]: DEFINE\n");           return DEFINE; }
"exit"          { printf("[FUNCTION]: EXIT\n");                 return EXIT; }

{number}        { printf("[NUM]: %s\n",yytext);                 return NUM;}
{identifier}    { printf("[ID]:  %s\n",yytext);                 return ID;}
{newline}       { printf("[EOL]\n");}
{whitespace}    { /*  ignore */}

"//".*          { /* When "//" is found, zero or more occurrences of any character are ignored */}

<INITIAL>{      // INITIAL Lexical state
  "/*"          { printf("[In comment]\n");} BEGIN(INCOMMENT);      
}

<INCOMMENT>{    // INCOMMENT Lexical state
  <<EOF>>       { printf("Error: Unterminated comment\n");
                  return ERROR; 
                }
  "*/"          { printf("[Out comment]\n");}BEGIN(INITIAL);
  [^*]+         ; // Consume characters within the comment block
}

<<EOF>>         { return ENDFILE; }

. {printf("Error, [%s] is an invalid token\n",yytext); return ERROR;}
%%

/*
 * Initializes the yyin with the source code file so the lexer know what is the input stream 
*/
void File_Init() {
  yyin = sourceCode;
}

/* function: getToken()
*  Returns the next token from the input source code.
*  Used only for tests because the parse automaticly calls the lexer when necessary.
*/
TokenType getToken(void)
{ 
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime){ 
    firstTime = FALSE;
    yyin = sourceCode;
  }
  currentToken = yylex();
  return currentToken;
}

