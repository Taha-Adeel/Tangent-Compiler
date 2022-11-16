%require "3.8"
/* %language "c++" */
%code top{
	#include <stdio.h>
	#include <string>
	#include "../src/astNodes.h"
	#include "../src/symbolTable.h"

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
		const char *filename;
	} YYLTYPE;
	#define YYLTYPE_IS_DECLARED 1
	#define YYLTYPE_IS_TRIVIAL 1
}

/* %code{
	#include "symbolTable.h"

	SymbolTable global_symbol_table;
	SymbolTable* cur_symbol_table;
} */
 
/* Listing the different types of the terminals and non-terminals */
%union 
{
	Program *pgm;
	list <Statement*> *stmt_list;
	list <Expression*> *exp_list;
	Expression *exp;
	Statement* stmt;
	Identifier *t;
	string *id;
	int valuei;
	float valuef;
	bool valueb;
	string *values;
	ACCESS_SPEC *access_spec;
	FamilyMembers *class_member;
	list<FamilyMembers*> *class_members;
	Argument* argument;
	list<Argument*>* arg_list;
}

/* Declaring types to the different non-terminals */
%type <pgm> program
%type <stmt_list> translation_unit statement_list
%type <exp_list> new_variable_list expression_list
%type <arg_list> args_list
%type <stmt> external_declaration statement
%type <stmt> driver_definition function_declaration variable_declaration family_declaration
%type <stmt> jump_statement iteration_statement labeled_statement expression_statement
%type <stmt> selection_statement compound_statement
%type <stmt> constructor_declaration /*error*/

%type <exp> expression primary_expression
%type <exp> new_variable literal variable
%type <argument> arg
%type <t> type
%type <access_spec> access_specifier
%type <class_member> class_member 
%type <class_members>class_members

/*** TOKEN DECLARATION ***/
%header


/* data types */
%token CONST VAR
%token <id> BOOL FLOAT INT STRING VOID 
%token <id> POINT PATH IMAGE RECTANGLE CIRCLE ELLIPSE POLYGON CURVE FUNC PI COLOUR
/* Literals */
%token <valuei> INTEGER_LITERAL
%token <valuef> FLOAT_LITERAL
%token <valueb> BOOL_LITERAL
%token <values> STRING_LITERAL

/* Control flow keywords */
%token IF ELSE SWITCH CASE DEFAULT WHILE FOR BREAK CONTINUE SEND

/* Derived data types and their member fields */
%token FAMILY INHERITS
%token PUBLIC PRIVATE 

/* Driver keyword */
%token DRIVER

/* Variables */
%token <id> IDENTIFIER

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
	: driver_definition		{$$ = $1;}
	| variable_declaration	{$$ = $1;}
	| function_declaration	{$$ = $1;}
	| family_declaration	{$$ = $1;}
	;

driver_definition
	: DRIVER '(' ')' compound_statement {$$ = new DriverDefinition($4);}
	;


/*----------------------------------------------------------------------
 * Declarations
 *----------------------------------------------------------------------*/
 type
	: INT   		{$$ = new Identifier(*($1));}
	| FLOAT   		{$$ = new Identifier(*($1));}
	| STRING   		{$$ = new Identifier(*($1));}
	| BOOL   		{$$ = new Identifier(*($1));}
	| VOID		   	{$$ = new Identifier(*($1));}
	| IDENTIFIER   	{$$ = new Identifier(*($1));}
	| POINT 		{$$ = new Identifier(*($1));}
	| PATH			{$$ = new Identifier(*($1));}
	| IMAGE			{$$ = new Identifier(*($1));}
	| RECTANGLE 	{$$ = new Identifier(*($1));}
	| CIRCLE		{$$ = new Identifier(*($1));}
	| ELLIPSE		{$$ = new Identifier(*($1));}
	| POLYGON		{$$ = new Identifier(*($1));}
	| CURVE			{$$ = new Identifier(*($1));}
	| FUNC			{$$ = new Identifier(*($1));}
	| PI			{$$ = new Identifier(*($1));}
	| COLOUR		{$$ = new Identifier(*($1));}
	;

literal
	: INTEGER_LITERAL	{$$ = new IntegerLiteral($1);}
	| FLOAT_LITERAL		{$$ = new FloatLiteral($1);}
	| STRING_LITERAL	{$$ = new StringLiteral(*($1));}
	| BOOL_LITERAL		{$$ = new BooleanLiteral($1);}
	;

variable_declaration
	: VAR type new_variable_list ';' 	{$$ = new VariableDeclaration(*($2), *($3));}	
	| CONST type new_variable_list ';' 	{$$ = new VariableDeclaration(*($2), *($3));} // store variables as const}	
	;

new_variable_list
	: new_variable						 {$$ = new list <Expression*>(); $$->push_back($1);}
	| new_variable_list ',' new_variable {$$ = $1; $$->push_back($3);}
	;

new_variable
	: IDENTIFIER 							{$$ = new Identifier(*($1));} 
	| IDENTIFIER ASSIGN expression			{Variable* temp = new Identifier(*($1)); $$ = new AssignmentExp(temp, $3);}
	| IDENTIFIER '(' ')'					{Variable* temp = new Identifier(*($1)); $$ = new FunctionCall(temp);}
	| IDENTIFIER '(' expression_list ')'	{Variable* temp = new Identifier(*($1)); $$ = new FunctionCall(temp, *($3));}
	;

function_declaration
	: type IDENTIFIER '(' ')' compound_statement			{auto temp = new Identifier(*($2)); $$ = new FunctionDeclaration(temp, *($1), $5);}
	| type IDENTIFIER '(' args_list ')' compound_statement	{auto temp = new Identifier(*($2)); $$ = new FunctionDeclaration(temp, *($1), $6, *($4));}
	;

args_list
	: arg				{$$ = new list <Argument*>(); $$->push_back($1);}
	| args_list ',' arg	{$$ = $1; $$->push_back($3);}
	;

arg
	: type IDENTIFIER		{$$ = new Argument(*($1), Identifier(*($2)));}
	| VAR type IDENTIFIER	{$$ = new Argument(*($2), Identifier(*($3)));}
	| CONST type IDENTIFIER	{$$ = new Argument(*($2), Identifier(*($3)));}
	;

/*------------------------------------------------------------------------
 * Classes
 *------------------------------------------------------------------------*/
family_declaration
	: FAMILY IDENTIFIER '{' '}' ';'														{$$ = new FamilyDecl(Identifier(*$2));}
	| FAMILY IDENTIFIER '{' class_members '}' ';' 										{$$ = new FamilyDecl(Identifier(*$2), *($4));}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';' 				{$$ = new FamilyDecl(Identifier(*($2)),optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*$5), *($4))));}
	| FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' class_members '}' ';'	{$$ = new FamilyDecl(Identifier(*($2)),*($7), optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*$5), *($4))));}
	;

access_specifier
	: PUBLIC 	{$$ = new ACCESS_SPEC(ACCESS_SPEC::PUBLIC);}
	| PRIVATE	{$$ = new ACCESS_SPEC(ACCESS_SPEC::PRIVATE);}
	;

class_members
	: class_member 					{$$ = new list<FamilyMembers*>(); $$->push_back($1);}
	| class_members class_member	{$$ =$1; $$->push_back($2);}
	;

class_member
	: access_specifier variable_declaration	{$$ = new FamilyMembers(*($1), $2);}
	| access_specifier function_declaration	{$$ = new FamilyMembers(*($1), $2);}
	| constructor_declaration				{$$ = new FamilyMembers(ACCESS_SPEC::PUBLIC, $1);}
	;

constructor_declaration
	: IDENTIFIER '(' args_list ')' compound_statement {$$ = new ConstructorDeclaration(Identifier(*($1)), $5, *($3));}
	;

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: literal							{$$ = (Expression*)$1;}
	| variable							{$$ = (Expression*)$1;}
	| variable '(' ')'					{$$ = new FunctionCall($1);}
	| variable '(' expression_list ')'	{$$ = new FunctionCall($1, *($3));}
	| '(' expression ')'				{$$ = $2;}
	;

variable
	: IDENTIFIER						{$$ = new Identifier(*($1));}
	| variable SCOPE_ACCESS IDENTIFIER	{$$ = new MemberAccess((Variable*)$1, *($3));}
	| variable '[' expression ']'		{$$ = new ArrayAccess($1, $3);}
	;

expression
	: primary_expression						//$$ = $1
	| '+' expression %prec UPLUS				{$$ = new UnaryPlus($2);}
	| '-' expression %prec UMINUS				{$$ = new UnaryMinus($2);}
	| expression '*' expression					{$$ = new Multiplication($1, $3);}
	| expression '/' expression					{$$ = new Division($1, $3);}
	| expression '%' expression					{$$ = new ModularDiv($1, $3);}
	| expression '+' expression					{$$ = new Addition($1, $3);}
	| expression '-' expression					{$$ = new Subtraction($1, $3);}
	| expression EQ expression					{$$ = new CompEQ($1, $3);}
	| expression NOT_EQ expression				{$$ = new CompNEQ($1, $3);}
	| expression LS_THAN expression				{$$ = new CompLT($1, $3);}
	| expression LS_THAN_EQ expression			{$$ = new CompLE($1, $3);}
	| expression GR_THAN expression				{$$ = new CompGT($1, $3);}
	| expression GR_THAN_EQ expression			{$$ = new CompGE($1, $3);}
	| expression LOGICAL_AND expression			{$$ = new LogicalAND($1, $3);}
	| expression LOGICAL_OR expression			{$$ = new LogicalOR($1, $3);}
	| LOGICAL_NOT expression					{$$ = new LogicalNOT($2);}
	| INC variable								{$$ = new PrefixInc((Variable*)$2);}
	| DEC variable								{$$ = new PostfixDec((Variable*)$2);}
	| variable INC %prec INC_POST				{$$ = new PostfixInc((Variable*)$1);}
	| variable DEC %prec DEC_POST				{$$ = new PostfixDec((Variable*)$1);}
	| variable ASSIGN expression				{$$ = new AssignmentExp((Variable*)$1, $3);}
	| variable MUL_ASSIGN expression			{$$ = new MulAssign((Variable*)$1, $3);}
	| variable DIV_ASSIGN expression			{$$ = new DivAssign((Variable*)$1, $3);}
	| variable MOD_ASSIGN expression			{$$ = new ModAssign((Variable*)$1, $3);}
	| variable ADD_ASSIGN expression			{$$ = new AddAssign((Variable*)$1, $3);}
	| variable SUB_ASSIGN expression			{$$ = new SubAssign((Variable*)$1, $3);}
	| expression '?' expression ':' expression	{$$ = new TernaryOperator($1, $3, $5);}
	;

expression_list
	: expression						{$$ = new list <Expression*>(); ($$)->push_back($1);}
	| expression_list ',' expression	{$$ = $1; ($$)->push_back($3);}
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
	/* | error ';' */
	;

compound_statement
	: '{' '}'					{$$ = new CompoundStatement(list<Statement*>());}
	| '{' statement_list '}'	{$$ = new CompoundStatement(*($2));}
	;

statement_list
	: statement					{$$ = new list <Statement*>(); ($$)->push_back($1);}
	| statement_list statement	{$$ = $1; ($$)->push_back($2);}
	;

expression_statement
	: ';'			 	  {$$ = new ExpressionStatement();}
	| expression_list ';' {$$ = new ExpressionStatement($1);}
	;

selection_statement
	: IF '(' expression ')' compound_statement							{$$ = new IfStatement($3, (CompoundStatement*)$5);}
	| IF '(' expression ')' compound_statement ELSE compound_statement 	{$$ = new IfElseStatement($3, (CompoundStatement*)$5, (CompoundStatement*)$7);}
	| SWITCH '(' expression ')' statement								{$$ = new SwitchStatement($3, (CompoundStatement*)$5);}
	;

labeled_statement
	: IDENTIFIER ':' statement		{Expression* temp = new Identifier(*($1));$$ = new LabeledStatement(temp, $3);}
	| CASE expression ':' statement	{$$ = new CaseLabel($2, $4);}
	| DEFAULT ':' statement			{$$ = new DefaultLabel($3);}
	;

iteration_statement
	: WHILE '(' ')' compound_statement														{$$ = new WhileLoop((CompoundStatement*)$4);}
	| WHILE '(' expression ')' compound_statement											{$$ = new WhileLoop((CompoundStatement*)$5, $3);}
	| FOR '(' expression_statement expression_statement ')' compound_statement				{$$ = new ForLoop((CompoundStatement*)$6, (ExpressionStatement*)$3, (ExpressionStatement*)$4, NULL);}
	| FOR '(' expression_statement expression_statement expression ')' compound_statement 	{$$ = new ForLoop((CompoundStatement*)$7, (ExpressionStatement*)$3, (ExpressionStatement*)$4, $5);}
	| FOR '(' variable_declaration expression_statement ')' compound_statement 				{$$ = new ForLoop((CompoundStatement*)$6, (ExpressionStatement*)$3, (ExpressionStatement*)$4, NULL);} 
	| FOR '(' variable_declaration expression_statement expression ')' compound_statement 	{$$ = new ForLoop((CompoundStatement*)$7, (ExpressionStatement*)$3, (ExpressionStatement*)$4, $5);}
	;

jump_statement
	: CONTINUE ';' 				{$$ = new ContinueStatement();}
	| BREAK ';'					{$$ = new BreakStatement();}
	| SEND expression_statement	{$$ = new ReturnStatement(((ExpressionStatement*)$2)->getValue());}
	;

%%

void init_yylloc(const char* filename){
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