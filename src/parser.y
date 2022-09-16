/*** TOKEN DECLARATION ***/
%token IDENTIFIER INTEGER_LITERAL FLOAT_LITERAL STRING_LITERAL BOOL_LITERAL CONSTANT PI

/* Primitive data types */
%token INT FLOAT STRING BOOL VOID
%token CONST VAR

/* Operators */
%token ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token EQ NOT_EQ LS_THAN LS_THAN_EQ GR_THAN GR_THAN_EQ
%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT

/* Control flow keywords */
%token IF ELSE FOR WHILE SWITCH CASE DEFAULT BREAK CONTINUE RETURN

/* Derived data types and their member fields */
%token FAMILY ME
%token SCOPE_ACCESS PUBLIC PRIVATE
%token POINT IMAGE RECTANGLE CIRCLE ELLIPSE POLYGON CURVE PATH
%token POINT_X POINT_Y
%token IMG_DIMS IMG_DRAWS
%token RECT_LENGTH RECT_BREADTH
%token CENTER ROTATION RADIUS
%token ELLIPSE_A ELLIPSE_B
%token POLYGON_SIZE POLYGON_LENGTH
%token CURVE_POINTS

/* Functions */
%token FUNC CLEAR DRAW SEND PRINT FLOOR CEIL TO_FLOAT
%token ADD_POINT MAKE_POINT
%token GET_X GET_Y GET_POINTS GET_WIDTH GET_CENTER GET_SIDES GET_SIDE_LENGTH GET_ROTATION GET_RADIUS GET_COLOUR GET_BORDER_COLOUR
%token SET_X SET_Y SET_POINTS SET_WIDTH SET_LENGTH SET_CENTER SET_SIDES SET_SIDE_LENGTH SET_ROTATION SET_RADIUS SET_COLOUR SET_BORDER_COLOUR
%token COLOUR RED BLUE GREEN

/* Driver keyword */
%token DRIVER

%start translation_unit

/*** RULES ***/
%%

/*------------------------------------------------------------------------
 * Translation unit
 *------------------------------------------------------------------------*/
translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: driver_definition
	| function_definition
	| variable_declaration
	| class_declaration
	;

driver_definition
	: DRIVER '(' ')' compound_statement
	;


/*----------------------------------------------------------------------
 * Declarations
 *----------------------------------------------------------------------*/
type
	: INT
	| FLOAT
	| STRING
	| BOOL
	| VOID
	;


literal
	: INTEGER_LITERAL
	| FLOAT_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	| PI
	;

variable_declaration
	: VAR type variable_list ';'
	| CONST type variable_list ';'
	;

variable_declaration_list
	: variable_declaration
	| variable_declaration_list variable_declaration
	;

variable_list
	: variable
	| variable_list ',' variable
	;

variable
	: IDENTIFIER
	| variable_initialization
	;

variable_initialization
	: IDENTIFIER ASSIGN literal
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
	: type IDENTIFIER
	;


/*------------------------------------------------------------------------
 * Classes
 *------------------------------------------------------------------------*/
class_declaration
	: FAMILY IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER SCOPE_ACCESS IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER SCOPE_ACCESS access_specifier class_definition ';'
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
: IDENTIFIER IDENTIFIER ';'


object_initialization
: variable_declaration
| IDENTIFIER SCOPE_ACCESS variable_initialization
;


/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

unary_expression
	: primary_expression
	| unary_expression '[' expression ']'
	| unary_expression '.' IDENTIFIER
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
	: LOGICAL_NOT equality_expression
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
	: '='
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
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' variable_declaration_list '}'
	| '{' variable_declaration_list statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN expression_statement
	;

%%

#include<stdio.h>

extern char yytext[];
extern int column;

int main(int argc, char **argv)
{
	yyparse();
}

yyerror(char*s)
{
	fprintf(stderr, "error occured!\n%s\n", s);
}
