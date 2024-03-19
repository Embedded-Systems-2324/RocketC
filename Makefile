default:all

setup:
	mkdir -p Output

lexer:
	flex -l --outfile="Output/lex.yy.c" Lexer/LexScanner.l

parser:
	bison -dv -k --graph Parser/Parser.y;
	mv Parser.* Output/

src:
	gcc -o Output/RocketC Util/Logger.c Output/Parser.tab.c Output/lex.yy.c main.c

clean:
	rm -r Output

prog:
	./Output/RocketC TestSrc.c --parse

run: clean all prog

all: setup parser lexer src