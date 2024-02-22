default:
	clear
	flex -l LexScanner.l
	bison -dv Parser.y 
	gcc -o test Parser.tab.c lex.yy.c main.c -lfl
