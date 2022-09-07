all: lexer
LEX = flex
lexer: lex.yy.c
	gcc -o lexer lex.yy.c -lfl

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean: 
	rm lex.yy.c lexer *.o
all:
	lex lexer.l
	gcc lex.yy.c

clean:
	rm lex.yy.c a.out
