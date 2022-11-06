%code top{
	#include<stdio.h>
	#include "astNodes.h"

	extern int yylex();
	extern void yyrestart(FILE*);
	extern int yylineno;

	void yyerror(const char*s);
	#define YYFPRINTF(f, fmt, ...)  printf(fmt, ##__VA_ARGS__)
}

%define parse.error detailed
%define parse.trace

%locations
%code requires{
	#define YYLTYPE YYLTYPE
	typedef struct YYLTYPE
	{
		int first_line;
		int first_column;
		int last_line;
		int last_column;
		char *filename;
	} YYLTYPE;
	#define YYLTYPE_IS_DECLARED 1
	#define YYLTYPE_IS_TRIVIAL 1
}

/* Listing the different types of the terminals and non-terminals*/
%union 
{
	Program *pgm
	list <Statement*> *stmt_list;
	Expression *exp;
	Statement* stmt;
	type t;
	string id;
	int valuei;
	float valuef;
	bool valueb;
	string values;
}

/* Declaring types to the different non-terminals */
%type <pgm> program
%type <stmt_list> translation_unit

%type <stmt> external_declaration 
%type <stmt> driver_definition function_definition variable_declaration class_declaration
%type <stmt> jump_statement iteration_statement labeled_statement expression_statement
%type <stmt> selection_statement compound_statement variable_declaration_list

%type <exp> expression constant_expression
%type <t> type

/*** TOKEN DECLARATION ***/
%header


/* Primitive data types */
%token CONST VAR
%token BOOL FLOAT INT STRING VOID 

/* Literals */
%token BOOL_LITERAL FLOAT_LITERAL INTEGER_LITERAL STRING_LITERAL

/* Control flow keywords */
%token IF ELSE SWITCH CASE DEFAULT WHILE FOR BREAK CONTINUE SEND

/* Derived data types and their member fields */
%token FAMILY INHERITS
%token PUBLIC PRIVATE 

/* Driver keyword */
%token DRIVER

/* Variables */
%token IDENTIFIER

/* The operator precedence and associativity rules for the language. The higher precedence operators are listed below the lower precedence rules. */
%left ','
%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%right '?' ':'
%left LOGICAL_OR
%left LOGICAL_AND
%left EQ NOT_EQ
%left LS_THAN LS_THAN_EQ GR_THAN GR_THAN_EQ
%left '+' '-'
%left '*' '/' '%'
%precedence INC DEC
%precedence INC_POST DEC_POST UPLUS UMINUS LOGICAL_NOT
%left '(' ')' '[' ']' SCOPE_ACCESS

/*** RULES ***/
%%

/*------------------------------------------------------------------------
 * Translation unit
 *------------------------------------------------------------------------*/
program
	: %empty				{$$ = new Program(); root = $$;}
	| translation_unit	{$$ = new Program($1); root = $$;}
	;
	
translation_unit
	: external_declaration		{$$ = new list <Statement*>(); $$->push_back($1);}
	| translation_unit external_declaration	{$$ = $1; $$->push_back($2);}
	;

external_declaration
	: driver_definition			{}
	| function_declaration		{}
	| variable_declaration		{}
	| class_declaration			{}
	;

driver_definition
	: DRIVER '(' ')' compound_statement {$$ = new DriverDefinition($4);}
	;


/*----------------------------------------------------------------------
 * Declarations
 *----------------------------------------------------------------------*/
type
	: INT		{$$ = INT_TYPE;}
	| FLOAT		{$$ = FLOAT_TYPE;}
	| STRING	{$$ = STRING_TYPE;}
	| BOOL		{$$ = BOOL_TYPE;}
	| VOID		{$$ = VOID_TYPE;}
	| IDENTIFIER  {$$ = new Identifier($1);}
	;


literal
	: INTEGER_LITERAL
	| FLOAT_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	;

variable_declaration
	: VAR type new_variable_list ';' {$$ = VariableDeclaration($2, $3);}	
	| CONST type new_variable_list ';' {$$ = VariableDeclaration($2, $3);} // store variables as const}	
	;

new_variable_list
	: new_variable {$$ = new list <Expression*>(); $$->push_back($1);}
	| new_variable_list ',' new_variable {$$ = $1; $$->push_back($3);}
	;

new_variable
	: IDENTIFIER {$$ = new Identifier($1);} //pass the identifier name somehow
	| IDENTIFIER ASSIGN expression
	| IDENTIFIER '(' ')'
	| IDENTIFIER '(' expression_list ')'
	;

function_declaration
	: type IDENTIFIER '(' ')' compound_statement
	| type IDENTIFIER '(' args_list ')' compound_statement
	;

args_list
	: arg
	| args_list ',' arg
	;

arg
	: type IDENTIFIER
	| VAR type IDENTIFIER
	| CONST type IDENTIFIER
	;

/*------------------------------------------------------------------------
 * Classes
 *------------------------------------------------------------------------*/
class_declaration
	: FAMILY IDENTIFIER '{' '}' ';'
	| FAMILY IDENTIFIER '{' class_members '}' ';'
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';'
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' class_members '}' ';'
	;

access_specifier
	: %empty
	| PUBLIC
	| PRIVATE
	;

class_members
	: access_specifier class_member
	| class_members access_specifier class_member
	;

class_member
	: variable_declaration
	| function_declaration
	| constructor_declaration
	;

constructor_declaration
	: IDENTIFIER '(' args_list ')' compound_statement
	;

/*
family my_class
{
	public int a;
	private int b;
	public int c;
};
*/


/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: literal
	| variable
	| variable '(' ')'
	| variable '(' expression_list ')'
	| '(' expression ')'
	;

variable
	: IDENTIFIER
	| variable SCOPE_ACCESS IDENTIFIER
	| variable '[' expression ']'
	;

expression
	: primary_expression
	| '+' expression %prec UPLUS
	| '-' expression %prec UMINUS
	| expression '*' expression
	| expression '/' expression
	| expression '%' expression
	| expression '+' expression
	| expression '-' expression
	| expression EQ expression
	| expression NOT_EQ expression
	| expression LS_THAN expression
	| expression LS_THAN_EQ expression
	| expression GR_THAN expression
	| expression GR_THAN_EQ expression
	| expression LOGICAL_AND expression
	| expression LOGICAL_OR expression
	| LOGICAL_NOT expression
	| INC variable
	| DEC variable
	| variable INC %prec INC_POST
	| variable DEC %prec DEC_POST
	| variable ASSIGN expression
	| variable MUL_ASSIGN expression
	| variable DIV_ASSIGN expression
	| variable MOD_ASSIGN expression
	| variable ADD_ASSIGN expression
	| variable SUB_ASSIGN expression
	| expression '?' expression ':' expression
	;

expression_list
	: expression
	| expression_list ',' expression
	;

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
statement
	: labeled_statement
	| compound_statement
	| variable_declaration
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| error ';'
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'			 
	| expression_list ';' {$$ = new ExpressionStatement($1);}
	;

selection_statement
	: IF '(' expression ')' compound_statement
	| IF '(' expression ')' compound_statement ELSE compound_statement
	| SWITCH '(' expression ')' statement
	;

labeled_statement
	: IDENTIFIER ':' statement	{$$ = new LabeledStatement($1, $3);}
	| CASE expression ':' statement	{$$ = new CaseLabel($2, $4);}
	| DEFAULT ':' statement		{$$ = new DefaultLabel($3);}
	;

iteration_statement
	: WHILE '(' ')' compound_statement 	{$$ = new WhileLoop($4);}
	| WHILE '(' expression ')' compound_statement {$$ = new WhileLoop($5, $3);}
	| FOR '(' expression_statement expression_statement ')' compound_statement 
	| FOR '(' expression_statement expression_statement expression ')' compound_statement 
	| FOR '(' variable_declaration expression_statement ')' compound_statement 
	| FOR '(' variable_declaration expression_statement expression ')' compound_statement
	;

jump_statement
	: CONTINUE ';' 	{$$ = new ContinueStatement();}
	| BREAK ';'		{$$ = new BreakStatement();}
	| SEND expression_statement	{$$ = new ReturnStatement(($2).getValue());}
	;

%%

void init_yylloc(char* filename){
	yylloc.first_line = yylloc.last_line = yylineno = 1;
	yylloc.first_column = yylloc.last_column = 0;
	yylloc.filename = filename;
}

int main(int argc, char **argv){
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
	
	if(argc < 2){
		init_yylloc("(stdin)");
		yyparse();
	}
    else{
        for(int i = 1; i < argc; i++){
            init_yylloc(argv[i]);
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ perror(argv[i]); return -1; }
            yyrestart(file);

			yyparse();

            fclose(file);
        }
    }
}

void yyerror(const char*s){
	fprintf(stdout, "   %s: Line %d:%d:\n\t %s\n", yylloc.filename, yylloc.first_line, yylloc.first_column, s);
	fprintf(stderr, "   %s: Line %d:%d:\n\t %s\n", yylloc.filename, yylloc.first_line, yylloc.first_column, s);
}