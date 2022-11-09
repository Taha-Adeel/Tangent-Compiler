CC = gcc

# Input and output directories
SRC_DIR := ./src
BUILD_DIR := ./build

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
	bison -o $(BUILD_DIR)/parser.tab.c $^

# Build an executable to scan the input tangent code and output the matched tokens
lexer: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.h
	$(CC) -o $(BUILD_DIR)/$@ $< -D STANDALONE_LEXER

# Build an executable to parse the input tangent code files according to the grammar rules
parser: $(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/lex.yy.c
	$(CC) -o $(BUILD_DIR)/$@ $^ --debug

# Generate HTML documentation describing our grammar and the DFA representing the parser.
parser_documentation: $(SRC_DIR)/parser.y
	mkdir -p $(BUILD_DIR)
	bison -o $(BUILD_DIR)/parser.tab.c $< --verbose --xml=$(BUILD_DIR)/$(<F:%.y=%.xml)
	xsltproc $$(bison --print-datadir)/xslt/xml2xhtml.xsl $(BUILD_DIR)/$(<F:%.y=%.xml) > ./documentation/$(<F:%.y=%.html)
	xdg-open ./documentation/$(<F:%.y=%.html)


# Remove all generated files
clean:
	rm -rf $(BUILD_DIR) $$(find . -type d -name $(TESTS_OUTPUT_DIR))


#################### TESTING RULES ########################

TESTS_DIR := ./tests
TESTS_OUTPUT_DIR := test_outputs

# The testcases
LEXER_CORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Lexer_Tests/Correct_codes/*.tngt))
LEXER_INCORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Lexer_Tests/Incorrect_codes/*.tngt))
PARSER_CORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Parser_Tests/Correct_codes/*.tngt))
PARSER_INCORRECT_CODES := $(sort $(wildcard $(TESTS_DIR)/Parser_Tests/Incorrect_codes/*.tngt))

BLACK := \e[0;30m
RED := \e[0;31m
GREEN := \e[0;32m
YELLOW := \e[0;33m
BLUE := \e[0;34m
PURPLE := \e[0;35m
CYAN := \e[0;36m
WHITE := \e[0;0m
B := \e[1m
I := \e[3m
U := \e[4m
NC := \e[0m

# Test the compiler against the testcases located in ./tests
tests: lexer_tests parser_tests

# Lexer Tests
lexer_tests: lexer_correct_codes lexer_incorrect_codes

lexer_correct_codes: $(LEXER_CORRECT_CODES) lexer
	@echo "$(WHITE)\n###################################################################################$(NC)\n"; \
	echo "$(BLUE)$(B)$(U)Running testcases with lexicologically correct code for the Lexical Analyzer$(NC)\n"; \
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	TOTAL=0; SUCCESSFUL=0; \
	for testcase in $(basename $(notdir $(LEXER_CORRECT_CODES))); do TOTAL=$$((TOTAL+1)); \
		echo "$(YELLOW)$(I)Running Testcase ($${TOTAL}/$(words $(LEXER_CORRECT_CODES))): $${testcase}.tngt$(NC)$(I) ~> $${testcase}-output.txt$(NC)";\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/lexer $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		if [ $$(grep "Invalid token" $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt | wc -w) -eq 0 ] ; then \
			echo "$(GREEN)   Testcase Passed\n$(NC)"; SUCCESSFUL=$$((SUCCESSFUL+1)); \
		else echo "$(RED)   Testcase Failed\n$(NC)"; fi;\
	done; \
	if [ $${SUCCESSFUL} -eq $${TOTAL} ] ; then \
		echo "$(GREEN)$(B)Success: All valid Lexical Analyzer testcases passed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; \
	else \
		echo "$(RED)Error: Lexical Analyzer testcases failed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; exit 1; fi; \

lexer_incorrect_codes: $(LEXER_INCORRECT_CODES) lexer
	@echo "$(WHITE)\n###################################################################################$(NC)\n"; \
	echo "$(BLUE)$(B)$(U)Running testcases with lexicologically incorrect code for the Lexical Analyzer$(NC)\n"; \
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	TOTAL=0; SUCCESSFUL=0; \
	for testcase in $(basename $(notdir $(LEXER_INCORRECT_CODES))); do TOTAL=$$((TOTAL+1)); \
		echo "$(YELLOW)$(I)Running Testcase ($${TOTAL}/$(words $(LEXER_INCORRECT_CODES))): $${testcase}.tngt$(NC)$(I) ~> $${testcase}-output.txt$(NC)";\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/lexer $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		if [ $$(grep "Invalid token" $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt | wc -w) -gt 0 ] ; then \
			echo "$(GREEN)   Testcase Passed, as the invalid tokens are rejected by the lexer\n$(NC)"; SUCCESSFUL=$$((SUCCESSFUL+1)); \
		else echo "$(RED)   Testcase Failed\n$(NC)"; fi;\
	done; \
	if [ $${SUCCESSFUL} -eq $${TOTAL} ] ; then \
		echo "$(GREEN)$(B)Success: All invalid tokens were rejected by the Lexical Analyzer.$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; \
	else \
		echo "$(RED)Error: Lexical Analyzer testcases failed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; exit 1; fi; \

# Parser Tests
parser_tests: parser parser_correct_codes parser_incorrect_codes

parser_correct_codes: $(PARSER_CORRECT_CODES) parser
	@echo "$(WHITE)\n########################################################################$(NC)\n"; \
	echo "$(BLUE)$(B)$(U)Running testcases with syntactically correct code for the Parser$(NC)\n"; \
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	TOTAL=0; SUCCESSFUL=0; \
	for testcase in $(basename $(notdir $(PARSER_CORRECT_CODES))); do TOTAL=$$((TOTAL+1)); \
		echo "$(YELLOW)$(I)Running Testcase ($${TOTAL}/$(words $(PARSER_CORRECT_CODES))): $${testcase}.tngt$(NC)$(I) ~> $${testcase}-output.txt$(NC)";\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/parser $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		if [ $$(grep "syntax error" $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt | wc -w) -eq 0 ] ; then \
			echo "$(GREEN)   Testcase Passed\n$(NC)"; SUCCESSFUL=$$((SUCCESSFUL+1)); \
		else echo "$(RED)   Testcase Failed\n$(NC)"; fi;\
	done; \
	if [ $${SUCCESSFUL} -eq $${TOTAL} ] ; then \
		echo "$(GREEN)$(B)Success: All syntactically valid testcases passed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; \
	else \
		echo "$(RED)Error: Parser testcases failed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; exit 1; fi; \

parser_incorrect_codes: $(PARSER_INCORRECT_CODES) parser
	@echo "$(WHITE)\n########################################################################$(NC)\n"; \
	echo "$(BLUE)$(B)$(U)Running testcases with syntactically incorrect code for the Parser$(NC)\n"; \
	ROOT_DIR="$$(pwd)"; \
	cd $(<D); \
	mkdir -p $(TESTS_OUTPUT_DIR); \
	TOTAL=0; SUCCESSFUL=0; \
	for testcase in $(basename $(notdir $(PARSER_INCORRECT_CODES))); do TOTAL=$$((TOTAL+1)); \
		echo "$(YELLOW)$(I)Running Testcase ($${TOTAL}/$(words $(PARSER_INCORRECT_CODES))): $${testcase}.tngt$(NC)$(I) ~> $${testcase}-output.txt$(NC)";\
		touch $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		"$${ROOT_DIR}"/$(BUILD_DIR)/parser $${testcase}.tngt > $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt; \
		if [ $$(grep "syntax error" $(TESTS_OUTPUT_DIR)/$${testcase}-output.txt | wc -w) -gt 0 ] ; then \
			echo "$(GREEN)   Testcase Passed. All syntax errors detected\n$(NC)"; SUCCESSFUL=$$((SUCCESSFUL+1)); \
		else echo "$(RED)   Testcase Failed\n$(NC)"; fi;\
	done; \
	if [ $${SUCCESSFUL} -eq $${TOTAL} ] ; then \
		echo "$(GREEN)$(B)Success: All syntax errors were caught by the parser!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; \
	else \
		echo "$(RED)Error: Parser testcases failed!$(NC) (Outputs can be viewed in $(<D)/$(TESTS_OUTPUT_DIR))\n"; exit 1; fi; \