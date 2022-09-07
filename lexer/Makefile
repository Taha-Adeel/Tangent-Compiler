all: lexer

lexer: lex.yy.c
	gcc -o lexer lex.yy.c -lfl

lex.yy.c: lexer.l
	flex lexer.l

clean: 
	rm lex.yy.c lexer *.o
