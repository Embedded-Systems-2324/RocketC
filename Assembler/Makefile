default:
	clear
	flex -l asm_lex.l
	bison -dv asm_parser.y
	gcc -o test asm_parser.tab.c lex.yy.c main.c
clean:
	rm -f asm_parser.tab.c asm_parser.tab.h asm_parser.output lex.yy.c test
run:
	./test asm_test.asm