%option noyywrap

%x INCOMMENT   

%{
#include "globals.h"
/*definitions*/
%}

digit       [0-9]
number      {digit}+
identifier  [a-zA-Z_][a-zA-Z0-9_]*
newline     \n
sign        ([-+])
expo        [eE]{sign}?
float_number  {digit}*"."{digit}+({expo}{digit}+)?
whitespace  [ \t]+


%%
"auto"          { printf("[KEYWORD]: AUTO\n");                  return AUTO; }
"break"         { printf("[KEYWORD]: BREAK\n");                 return BREAK; }
"case"          { printf("[KEYWORD]: CASE\n");                  return CASE; }
"char"          { printf("[KEYWORD]: CHAR\n");                  return CHAR; }
"const"         { printf("[KEYWORD]: CONST\n");                 return CONSTANT; }
"continue"      { printf("[KEYWORD]: CONTINUE\n");              return CONTINUE; }
"default"       { printf("[KEYWORD]: DEFAULT\n");               return DEFAULT; }
"do"            { printf("[KEYWORD]: DO\n");                    return DO; } 
"double"        { printf("[KEYWORD]: DOUBLE\n");                return DOUBLE; }
"else"          { printf("[KEYWORD]: ELSE\n");                  return ELSE; }
"enum"          { printf("[KEYWORD]: ENUM\n");                  return ENUM; }
"extern"        { printf("[KEYWORD]: EXTERN\n");                return EXTERN; }
"float"         { printf("[KEYWORD]: FLOAT\n");                 return FLOAT; }
"for"           { printf("[KEYWORD]: FOR\n");                   return FOR; }
"goto"          { printf("[KEYWORD]: GOTO\n");                  return GOTO; }
"if"            { printf("[KEYWORD]: IF\n");                    return IF; }
"int"           { printf("[KEYWORD]: INT\n");                   return INT; }
"long"          { printf("[KEYWORD]: LONG\n");                  return LONG; }
"register"      { printf("[KEYWORD]: REGISTER\n");              return REGISTER; }
"return"        { printf("[KEYWORD]: RETURN\n");                return RETURN; }
"short"         { printf("[KEYWORD]: SHORT\n");                 return SHORT; }
"signed"        { printf("[KEYWORD]: SIGNED\n");                return SIGNED; }
"sizeof"        { printf("[KEYWORD]: SIZEOF\n");                return SIZEOF; }
"static"        { printf("[KEYWORD]: STATIC\n");                return STATIC; }
"struct"        { printf("[KEYWORD]: STRUCT\n");                return STRUCT; }
"switch"        { printf("[KEYWORD]: SWITCH\n");                return SWITCH; }
"typedef"       { printf("[KEYWORD]: TYPEDEF\n");               return TYPEDEF; }
"union"         { printf("[KEYWORD]: UNION\n");                 return UNION; }
"unsigned"      { printf("[KEYWORD]: UNSIGNED\n");              return UNSIGNED; }
"void"          { printf("[KEYWORD]: VOID\n");                  return VOID; }
"volatile"      { printf("[KEYWORD]: VOLATILE\n");              return VOLATILE; }
"while"         { printf("[KEYWORD]: WHILE\n");                 return WHILE; }

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
"*="            { printf("[OPERATOR]: MULTIPLY_ASSIGN\n");      return MULTIPLY_ASSIGN; }
"/="            { printf("[OPERATOR]: DIVIDE_ASSIGN\n");        return DIVIDE_ASSIGN; }
"%="            { printf("[OPERATOR]: MODULUS_ASSIGN\n");       return MODULUS_ASSIGN; }
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

{number}        { (yylval.intval=atoi(yytext)); return NUM; }
{identifier}    { sscanf(yytext,"%s",yylval.identifier); return ID;}
{float_number}  { (yylval.floatval=atof(yytext)); return FNUM;}
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


void File_Init() {
  yyin = sourceCode;
}

/* function: getToken()
*  Returns the next token from the input source code.
*  Used only for tests because the parse automaticly calls the lexer when necessary.
*/
