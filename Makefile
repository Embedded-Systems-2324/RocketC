default:all

lexer:
	flex -l --outfile="Output/lex.yy.c" Lexer/LexScanner.l

src:
	gcc -o Output/RocketC Util/Logger.c Output/lex.yy.c main.c

all: lexer src