

all: tangent

parser.tab.c parser.tab.h: src/parser.y
	bison -t -g -v --debug -d src/parser.y

lex.yy.c: src/lexer.l parser.tab.h
	flex src/lexer.l

tangent: lex.yy.c parser.tab.c parser.tab.h
	gcc -o parser parser.tab.c lex.yy.c -lfl

test: all parser
	mkdir -p test_outputs
	for num in 1 2 3 4 5 6 7 8 9 10 11; do \
		touch test_outputs/output$$num.txt ; \
		./parser < Parser-Tests/test$$num.tngt > test_outputs/output$$num.txt ; \
	done

error: parser
	mkdir -p test_outputs
	for num in 1 2 3 4 5 6 ; do \
		touch test_outputs/erroroutput$$num.txt ; \
		./parser < Parser-Tests/errortest$$num.tngt > test_outputs/erroroutput$$num.txt ; \
	done

clean:
	rm parser parser.tab.c lex.yy.c parser.tab.h parser.output parser.dot
	rm -r tests/Test_Outputs