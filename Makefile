CC = gcc

# Input and output directories
SRC_DIR := ./src
BUILD_DIR := ./build
TESTS_DIR := ./tests
TESTS_OUTPUT_DIR := test_outputs

# The testcases
LEXER_CORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Lexer_Tests/Correct_codes/*.tngt))
LEXER_INCORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Lexer_Tests/Incorrect_codes/*.tngt))
PARSER_CORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Parser_Tests/Correct_codes/*.tngt))
PARSER_INCORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Parser_Tests/Incorrect_codes/*.tngt))

.PHONY : all compiler lexer parser parser_documentation tests lexer_tests lexer_correct_codes lexer_incorrect_codes \
	parser_tests parser_correct_codes parser_incorrect_codes clean

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


# Test the compiler against the testcases located in ./tests
tests: lexer_tests parser_tests

# Lexer Tests
lexer_tests: lexer_correct_codes lexer_incorrect_codes

lexer_correct_codes: $(LEXER_CORRECT_CODES) lexer
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	for testcase in $(basename $(notdir $(LEXER_CORRECT_CODES))); do\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/lexer $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
	done

lexer_incorrect_codes: $(LEXER_INCORRECT_CODES) lexer
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	for testcase in $(basename $(notdir $(LEXER_INCORRECT_CODES))); do\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/lexer $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
	done


# Parser Tests
parser_tests: parser parser_correct_codes parser_incorrect_codes

parser_correct_codes: $(PARSER_CORRECT_CODES) parser
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	for testcase in $(basename $(notdir $(PARSER_CORRECT_CODES))); do\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/parser < $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
	done

parser_incorrect_codes: $(PARSER_INCORRECT_CODES) parser
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	for testcase in $(basename $(notdir $(PARSER_INCORRECT_CODES))); do\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/parser < $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
	done


# Remove all generated files
clean:
	rm -rf $(BUILD_DIR) $$(find . -type d -name $(TESTS_OUTPUT_DIR))