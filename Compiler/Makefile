default:
	clear
	flex -l LexScanner.l
	bison -dv Parser.y 
	gcc -o test Parser.tab.c lex.yy.c main.c -lfl
clean:
	rm -f test.tab.c lex.yy.c test.tab.h test.output test