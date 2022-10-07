CC = gcc

# Input and output directories
SRC_DIR = ./src
BUILD_DIR = ./build
TESTS_DIR = ./tests
TESTS_OUTPUT_DIR = $(TESTS_DIR)/test_outputs

.PHONY : all compiler parser lexer clean

# Default target
all: compiler
compiler: parser

# $@ = build target of the rule (lhs)  ($(@D) = Directory of the $@, and $(@F) = only filename of $@. Similarly for others)
# $^ = dependencies of the rule (rhs)
# $< = first dependency of the rule (first value in the rhs)
$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l
	mkdir -p $(@D)
	flex -o $@ $^

$(BUILD_DIR)/parser.tab.c \
$(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	mkdir -p $(@D)
	bison -o $(BUILD_DIR)/parser.tab.c $^ -d

# Build an executable to scan the input tangent code and output the matched tokens
lexer: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.h
	$(CC) -o $(BUILD_DIR)/$@ $< -D STANDALONE_LEXER

# Build an executable to parse the input tangent code files according to the grammar rules
parser: $(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/lex.yy.c
	$(CC) -o $(BUILD_DIR)/$@ $^

# Generate HTML documentation describing our grammar and the DFA representing the parser.
parser_documentation: $(SRC_DIR)/parser.y
	mkdir -p $(BUILD_DIR)
	bison -o $(BUILD_DIR)/parser.tab.c $< --verbose --xml=$(BUILD_DIR)/$(<F:%.y=%.xml)
	xsltproc $$(bison --print-datadir)/xslt/xml2xhtml.xsl $(BUILD_DIR)/$(<F:%.y=%.xml) > ./documentation/$(<F:%.y=%.html)
	xdg-open ./documentation/$(<F:%.y=%.html)

test: parser
	mkdir -p $(TESTS_OUTPUT_DIR)
	for num in 1 2 3 4 5 6 7 8 9 10 11; do \
		touch $(TESTS_OUTPUT_DIR)/output$$num.txt ; \
		$(BUILD_DIR)/parser < $(TESTS_DIR)/Parser_Tests/Correct_codes/test$$num.tngt > $(TESTS_OUTPUT_DIR)/output$$num.txt ; \
	done

error: parser
	mkdir -p $(TESTS_OUTPUT_DIR)
	for num in 1 2 3 4 5 6 7 8 9 10 11; do \
		touch $(TESTS_OUTPUT_DIR)/erroroutput$$num.txt ; \
		$(BUILD_DIR)/parser < $(TESTS_DIR)/Parser_Tests/Incorrect_codes/errortest$$num.tngt > $(TESTS_OUTPUT_DIR)/output$$num.txt ; \
	done

# Remove all generated files
clean:
	rm -rf $(BUILD_DIR) $(TESTS_OUTPUT_DIR)