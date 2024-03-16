default:
	clear
	flex -l asm_lex.l
	gcc -o test lex.yy.c main.c
clean:
	rm -f lex.yy.c test