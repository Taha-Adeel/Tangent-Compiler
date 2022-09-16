all: tangent

parser.tab.c parser.tab.h: parser.y
	bison -t -v --debug -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# lexer:
# 	flex lexer.l
# 	gcc -o lexer lex.yy.c -lfl

tangent: lex.yy.c parser.tab.c parser.tab.h
	gcc -o parser parser.tab.c lex.yy.c -lfl

test: parser
	mkdir -p test_outputs
	for num in 1 2 3 4 5 6; do \
		touch test_outputs/output$$num.txt ; \
		./parser < Parser-Tests/test$$num.tngt > test_outputs/output$$num.txt ; \
	done

error: parser
	mkdir -p test_outputs
	for num in 1 2 3 4 5 6 ; do \
		touch test_outputs/erroroutput$$num.txt ; \
		./parser < Parser-Tests/errortest$$num.tngt > test_outputs/erroroutput$$num.txt ; \
		diff correct_outputs/erroroutput$$num.txt test_outputs/erroroutput$$num.txt ; \
	done

clean:
	rm parser parser.tab.c lex.yy.c parser.tab.h parser.output test_outputs
