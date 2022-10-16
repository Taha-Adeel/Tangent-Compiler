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

%token IDENTIFIER INTEGER_LITERAL FLOAT_LITERAL STRING_LITERAL BOOL_LITERAL PI

/* Primitive data types */
%token INT FLOAT STRING BOOL VOID
%token CONST VAR

/* Operators */
%token ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token EQ NOT_EQ LS_THAN LS_THAN_EQ GR_THAN GR_THAN_EQ
%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT

/* Control flow keywords */
%token IF ELSE FOR WHILE SWITCH CASE DEFAULT BREAK CONTINUE SEND

/* Derived data types and their member fields */
%token FAMILY ME INHERITS
%token SCOPE_ACCESS PUBLIC PRIVATE 
%token POINT IMAGE RECTANGLE CIRCLE ELLIPSE POLYGON CURVE PATH
%token POINT_X POINT_Y
%token IMG_DIMS IMG_DRAWS
//%token RECT_LENGTH RECT_BREADTH
//%token CENTER ROTATION RADIUS
//%token ELLIPSE_A ELLIPSE_B
//%token POLYGON_SIZE POLYGON_LENGTH
//%token CURVE_POINTS

/* Functions */
%token FUNC CLEAR DRAW PRINT FLOOR CEIL TO_FLOAT
%token ADD_POINT MAKE_POINT
%token GET_X GET_Y GET_POINTS GET_WIDTH GET_CENTER GET_SIDES GET_SIDE_LENGTH GET_ROTATION GET_RADIUS GET_COLOUR GET_BORDER_COLOUR
%token SET_X SET_Y SET_POINTS SET_WIDTH SET_LENGTH SET_CENTER SET_SIDES SET_SIDE_LENGTH SET_ROTATION SET_RADIUS SET_COLOUR SET_BORDER_COLOUR SET_DIMENSION
%token COLOUR RED BLUE GREEN
%token GET_COLOUR_FROM_RGB

/* Driver keyword */
%token DRIVER

%start program

/*** RULES ***/
%%

/*------------------------------------------------------------------------
 * Translation unit
 *------------------------------------------------------------------------*/
program
	:					{$$ = new Program(); root = $$;}
	| translation_unit	{$$ = new Program($1); root = $$;}
	;
	
translation_unit
	: external_declaration		{$$ = new list <Statement*>(); $$->push_back($1);}
	| translation_unit external_declaration	{$$ = $1; $$->push_back($2);}
	;

external_declaration
	: driver_definition		//{$$ = $1;}
	| function_definition	//{$$ = $1;}
	| variable_declaration	//{$$ = $1;}
	| class_declaration		//{$$ = $1;}
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
	| POINT
	| IMAGE 
	| RECTANGLE
	| CIRCLE 
	| ELLIPSE 
	| POLYGON
	| CURVE
	| PATH	
	;


literal
	: INTEGER_LITERAL
	| FLOAT_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	| PI
	;

variable_declaration
	: VAR type variable_list ';'	{$$ = VariableDeclaration($2, $3);}	
	| CONST type variable_list ';'	{$$ = VariableDeclaration($2, $3);} // store variables as const}	
	;

variable_declaration_list
	: variable_declaration			{}
	| variable_declaration_list variable_declaration
	;

variable_list
	: variable						{$$ = new list <Expression*>(); $$->push_back($1);}
	| variable_list ',' variable	{$$ = $1; $$->push_back($3);}
	;

variable
	: IDENTIFIER ';'				{$$ = new Identifier();} //pass the identifier name somehow
	| IDENTIFIER ASSIGN expression
	;


function_definition
	: type IDENTIFIER '(' args_list ')' compound_statement
	| type IDENTIFIER '(' ')' compound_statement
	;


args_list
	: arg
	| args_list ',' arg
	;

arg
	: VAR type IDENTIFIER
	| CONST type IDENTIFIER
	;


/*------------------------------------------------------------------------
 * Classes
 *------------------------------------------------------------------------*/
class_declaration
	: FAMILY IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER INHERITS IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER INHERITS access_specifier class_definition ';'
	;

access_specifier
	: PUBLIC
	| PRIVATE
	;

class_definition
	: '{' '}'
	| '{' class_members '}'
	;
class_members
	: class_members access_specifier class_member
	| class_members class_member
	| access_specifier class_member
	| class_member
	;

class_member
	: variable_declaration
	| function_definition
	| constructor_declaration
	;

constructor_declaration
	: IDENTIFIER '(' ')' compound_statement
	| IDENTIFIER '(' args_list ')' compound_statement
	;


/*---------------------------------------------------------------------
 *	Objects
 *----------------------------------------------------------------------*/

object_declaration
	: VAR IDENTIFIER IDENTIFIER ';'
	| VAR IDENTIFIER IDENTIFIER '(' ')'
	| VAR IDENTIFIER IDENTIFIER '(' expression ')'
	;

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: IDENTIFIER
	| literal
	| '(' expression ')'
	;

unary_expression
	: primary_expression
	| unary_expression '[' expression ']'
	| unary_expression '(' ')'
	| unary_expression '(' expression ')'
	| unary_expression SCOPE_ACCESS IDENTIFIER 
	| unary_expression SCOPE_ACCESS IDENTIFIER '(' ')'
	| unary_expression SCOPE_ACCESS IDENTIFIER '(' expression ')'
	| inbuilt_function_call
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression
	| multiplicative_expression '/' unary_expression
	| multiplicative_expression '%' unary_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

relational_expression
	: additive_expression
	| relational_expression LS_THAN additive_expression
	| relational_expression GR_THAN additive_expression
	| relational_expression LS_THAN_EQ additive_expression
	| relational_expression GR_THAN_EQ additive_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	| equality_expression NOT_EQ relational_expression
	;

logical_not_expression
	: equality_expression
	| LOGICAL_NOT equality_expression
	;

logical_and_expression
	: logical_not_expression
	| logical_and_expression LOGICAL_AND logical_not_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression LOGICAL_OR logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;


/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| variable_declaration_list
	| object_declaration
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
	| expression ';' {$$ = new ExpressionStatement($1);}
	;

selection_statement
	: IF '(' expression ')' compound_statement
	| IF '(' expression ')' compound_statement ELSE compound_statement
	| SWITCH '(' expression ')' statement
	;

labeled_statement
	: IDENTIFIER ':' statement	{$$ = new LabeledStatement($1, $3);}
	| CASE constant_expression ':' statement	{$$ = new CaseLabel($2, $4);}
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

/*------------------------------------------------------------------------
 * Inbuilt Functions
 *------------------------------------------------------------------------*/
inbuilt_function_call
	: inbuilt_function '(' ')'
	| inbuilt_function '(' expression ')'
	| inbuilt_member_function '(' ')'
	| inbuilt_member_function '(' expression ')'
	;
inbuilt_function
	: CLEAR
	| DRAW
	| PRINT
	| FLOOR
	| CEIL
	| TO_FLOAT
	| ADD_POINT
	| MAKE_POINT
	| GET_COLOUR_FROM_RGB
	;
inbuilt_member_function
	: inbuilt_get_function
	| inbuilt_set_function
	;	
inbuilt_get_function
	: GET_X
	| GET_Y 
	| GET_POINTS
	| GET_WIDTH
	| GET_CENTER
	| GET_SIDES
	| GET_SIDE_LENGTH
	| GET_ROTATION
	| GET_RADIUS
	| GET_COLOUR
	| GET_BORDER_COLOUR
	;
inbuilt_set_function
	: SET_X
	| SET_Y
	| SET_POINTS
	| SET_WIDTH
	| SET_LENGTH
	| SET_CENTER
	| SET_SIDES
	| SET_SIDE_LENGTH
	| SET_ROTATION
	| SET_RADIUS
	| SET_COLOUR
	| SET_BORDER_COLOUR
	| SET_DIMENSION
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