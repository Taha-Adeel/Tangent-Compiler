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
	Program *pgm;
	list <Statement*> *stmt_list;
	Expression *exp;
	Statement* stmt;
	type t;
	string id;
	int valuei;
	float valuef;
	bool valueb;
	string values;
	ACCESS_SPEC access_spec;
	ClassMember class_member;
	ConstructorDeclaration constructor_decl;
}

/* Declaring types to the different non-terminals */
%type <pgm> program
%type <stmt_list> translation_unit new_variable new_variable_list

%type <stmt> external_declaration 
%type <stmt> driver_definition function_declaration variable_declaration family_declaration
%type <stmt> jump_statement iteration_statement labeled_statement expression_statement
%type <stmt> selection_statement compound_statement variable_declaration_list

%type <exp> expression constant_expression
%type <t> type
%type <access_spec> access_specifier
%type <class_member> class_member class_members
%type <constructor_decl> constructor_declaration
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
	| translation_unit		{$$ = new Program($1); root = $$;}
	;
	
translation_unit
	: external_declaration					{$$ = new list <Statement*>(); $$->push_back($1);}
	| translation_unit external_declaration	{$$ = $1; $$->push_back($2);}
	;

external_declaration
	: driver_definition			// $$ = $1
	| variable_declaration		// $$ = $1
	| function_declaration		// $$ = $1
	| class_declaration			// $$ = $1
	;

driver_definition
	: DRIVER '(' ')' compound_statement {$$ = new DriverDefinition($4);}
	;


/*----------------------------------------------------------------------
 * Declarations
 *----------------------------------------------------------------------*/
type
	: INT			{$$ = INT_TYPE;}
	| FLOAT			{$$ = FLOAT_TYPE;}
	| STRING		{$$ = STRING_TYPE;}
	| BOOL			{$$ = BOOL_TYPE;}
	| VOID			{$$ = VOID_TYPE;}
	| IDENTIFIER  	{$$ = new Identifier($1);}
	;


literal
	: INTEGER_LITERAL	{$$ = new IntegerLiteral($1);}
	| FLOAT_LITERAL		{$$ = new FloatLiteral($1);}
	| STRING_LITERAL	{$$ = new StringLiteral($1);}
	| BOOL_LITERAL		{$$ = new BooleanLiteral($1);}
	;

variable_declaration
	: VAR type new_variable_list ';' 	{$$ = new VariableDeclaration($2, $3);}	
	| CONST type new_variable_list ';' 	{$$ = new VariableDeclaration($2, $3);} // store variables as const}	
	;

new_variable_list
	: new_variable						 {$$ = new list <Expression*>(); $$->push_back($1);}
	| new_variable_list ',' new_variable {$$ = $1; $$->push_back($3);}
	;

new_variable
	: IDENTIFIER {$$ = new Identifier($1);} 
	| IDENTIFIER ASSIGN expression	{$1 = new Identifier($1); $$ = new AssignmentExp($1, $3);}
	| IDENTIFIER '(' ')'	{$1 = new Identifier($1); $$ = new FunctionCall($1);}
	| IDENTIFIER '(' expression_list ')'	{$1 = new Identifier($1); $$ = new FunctionCall($1, $3);}
	;

function_declaration
	: type IDENTIFIER '(' ')' compound_statement	{$2 = new Identifier($2); $$ = FunctionDeclaration($2, $1, $5);}
	| type IDENTIFIER '(' args_list ')' compound_statement	{$2 = new Identifier($2); $$ = FunctionDeclaration($2, $1, $6, $4);}
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
family_declaration
	: FAMILY IDENTIFIER '{' '}' ';'														{$$ = FamilyDecl($2);}
	| FAMILY IDENTIFIER '{' class_members '}' ';' 										{$$ = FamilyDecl($2, $4);}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';' 				{$$ = FamilyDecl($2,optional<pair<Identifier, ACCESS_SPEC>>(make_pair($5, $4)));}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' class_members '}' ';'	{$$ = FamilyDecl($2,$7, optional<pair<Identifier, ACCESS_SPEC>>(make_pair($5, $4)));}
	;

access_specifier
	: %empty
	| PUBLIC 	{$$ = ACCESS_SPEC(ACCESS_SPEC::PUBLIC);}
	| PRIVATE	{$$ = ACCESS_SPEC(ACCESS_SPEC::PRIVATE);}
	;

class_members
	: class_member 					{$$ = new list<ClassMember*>($1);}
	| class_members class_member	{$$ =$1; $$->push_back($2);}
	;

class_member
	: access_specifier variable_declaration	{$$ = new ClassMember($1, $2);}
	| access_specifier function_declaration	{$$ = new ClassMember($1, $2);}
	| constructor_declaration				{$$ = new ClassMember(ACCESS_SPEC::PUBLIC, $1);}
	;

constructor_declaration
	: IDENTIFIER '(' args_list ')' compound_statement {$$ = new ConstructorDeclaration($1, $5, $3);}
	;

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: literal			// $$ = $1
	| variable			// $$ = $1
	| variable '(' ')'	{$$ = new FunctionCall($1);}
	| variable '(' expression_list ')'	{$$ = new FunctionCall($1, $3);}
	| '(' expression ')'	{$$ = $2;}
	;

variable
	: IDENTIFIER		{$$ = new Identifier($1);}
	| variable SCOPE_ACCESS IDENTIFIER	{$$ = new MemberAccess($1, $3);}
	| variable '[' expression ']'	{$$ = new ArrayAccess($1, $3);}
	;

expression
	: primary_expression			//$$ = $1
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
	| variable MUL_ASSIGN expression			{$$ = new MulAssign($1, $3);}
	| variable DIV_ASSIGN expression			{$$ = new DivAssign($1, $3);}
	| variable MOD_ASSIGN expression			{$$ = new ModAssign($1, $3);}
	| variable ADD_ASSIGN expression			{$$ = new AddAssign($1, $3);}
	| variable SUB_ASSIGN expression			{$$ = new SubAssign($1, $3);}
	| expression '?' expression ':' expression	{$$ = new TernaryOperation($1, $3, $5);}
	;

expression_list
	: expression					{$$ = new list <Expression*>(); ($$)->push_back($1);}
	| expression_list ',' expression	{$$ = $1; ($$)->push_back($3);}
	;

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
statement
	: labeled_statement  		//$$ = $1     
	| compound_statement		//$$ = $1
	| variable_declaration		//$$ = $1
	| expression_statement		//$$ = $1
	| selection_statement		//$$ = $1
	| iteration_statement		//$$ = $1
	| jump_statement			//$$ = $1
	| error ';'
	;

compound_statement
	: '{' '}'					{$$ = new CompoundStatement();}
	| '{' statement_list '}'	{$$ = new CompoundStatement($2);}
	;

statement_list
	: statement					{$$ = new list <Statement*>(); ($$)->push_back($1);}
	| statement_list statement	{$$ = $1; ($$)->push_back($2);}
	;

expression_statement
	: ';'			 	  {$$ = new ExpressionStatement(NULL);}
	| expression_list ';' {$$ = new ExpressionStatement($1);}
	;

selection_statement
	: IF '(' expression ')' compound_statement	{$$ = new IfStatement($3, $5);}
	| IF '(' expression ')' compound_statement ELSE compound_statement {$$ = new IfElseStatement($3, $5, $7);}
	| SWITCH '(' expression ')' statement	{$$ = new SwitchStatement($3, $5);}
	;

labeled_statement
	: IDENTIFIER ':' statement	{$$ = new LabeledStatement($1, $3);}
	| CASE expression ':' statement	{$$ = new CaseLabel($2, $4);}
	| DEFAULT ':' statement		{$$ = new DefaultLabel($3);}
	;

iteration_statement
	: WHILE '(' ')' compound_statement 	{$$ = new WhileLoop($4);}
	| WHILE '(' expression ')' compound_statement {$$ = new WhileLoop($5, $3);}
	| FOR '(' expression_statement expression_statement ')' compound_statement {$$ = new ForLoop($6, $3, $4, NULL);}
	| FOR '(' expression_statement expression_statement expression ')' compound_statement {$$ = new ForLoop($7, $3, $4, $5);}
	| FOR '(' variable_declaration expression_statement ')' compound_statement {$$ = new ForLoop($6, $3, $4, NULL);} 
	| FOR '(' variable_declaration expression_statement expression ')' compound_statement {$$ = new ForLoop($7, $3, $4, $5);}
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