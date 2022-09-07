all: lexer
LEX = flex
lexer: lex.yy.c
	gcc -o lexer lex.yy.c -lfl

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean: 
	rm lex.yy.c *.o
