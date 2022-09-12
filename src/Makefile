all:
	bison -d parser.y
	flex lexer.l
	gcc -o parser parser.tab.c lex.yy.c  -lfl
lexer:
	lex lexer.l
	gcc -o lexer lex.yy.c -lfl
clean:
	rm lex.yy.c parser parser.tab.c parser.tab.h
