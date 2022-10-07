CC = gcc

SRC_DIR = ./src
BUILD_DIR = ./build
TESTS_DIR = ./tests
TESTS_OUTPUT_DIR = $(TESTS_DIR)/test_outputs

.PHONY : all compiler parser lexer clean

all: compiler
compiler: parser

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l
	mkdir -p $(@D)
	flex -o $@ $<

$(BUILD_DIR)/parser.tab.c \
$(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	mkdir -p $(@D)
	bison -o $(BUILD_DIR)/parser.tab.c $< -d

# Build an executable to scan the input tangent code and output the matched tokens
lexer: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.h
	$(CC) -o $(BUILD_DIR)/$@ $< -D LEX_TEST 

# Build an executable to parse the input tangent code files according to the grammar rules
parser: $(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/lex.yy.c
	$(CC) -o $(BUILD_DIR)/$@ $^

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