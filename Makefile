default:all

setup:
	mkdir -p Output

lexer:
	flex -l --outfile="Output/lex.yy.c" Lexer/LexScanner.l

parser:
	bison -dv -k --graph Parser/Parser.y
	mv Parser.* Output/

src:
	gcc -o Output/RocketC Util/Util.c Util/Logger.c SemanticAnalyzer/SymbolTable.c SemanticAnalyzer/traverse.c Output/Parser.tab.c Output/lex.yy.c CodeGeneration/CodeGeneration.c main.c

clean:
	rm -r Output

prog:
	./Output/RocketC TestSrc3.c --parse

run: clean all prog

all: setup parser lexer src