default:all

setup:
	mkdir -p Output

lexer:
	flex -l --outfile="Output/lex.yy.c" Step1/asm_lex.l

parser:
	bison -dv -k --graph Step1/asm_parser.y;
	mv asm_parser.* Output/

src:
	gcc -o Output/VASM Util/logger.c Output/asm_parser.tab.c Output/lex.yy.c Util/statements_list.c  Util/symbol_table.c main.c

clean:
	rm -r Output

prog:
	./Output/VASM test.asm

run: clean all prog

all: setup parser lexer src