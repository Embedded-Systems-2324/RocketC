default:all

setup:
	mkdir -p Output

lexer:
	flex -l --outfile="Output/lex.yy.c" Lexer/LexScanner.l

src:
	gcc -o Output/RocketC Util/Logger.c Output/lex.yy.c main.c

clean:
	rm -r Output

all: setup lexer src