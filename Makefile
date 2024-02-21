default:
	clear
	flex -l LexScanner.l
	bison -dv test.y 
	gcc -o test test.tab.c lex.yy.c main.c -lfl
