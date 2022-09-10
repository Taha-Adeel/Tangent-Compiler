all: lexer
	
lexer:
	lex lexer.l
	gcc -o lexer lex.yy.c -lfl
clean:
	rm lexer lex.yy.c
