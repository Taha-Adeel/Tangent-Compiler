%code top{
	#include<stdio.h>

	extern int yylex();
	extern void yyrestart(FILE*);
	extern int yylineno;

	int yyerror(char*s);
}

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
}

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
	:
	| translation_unit
	;
	
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
	: IDENTIFIER ';'
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
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' compound_statement
	| IF '(' expression ')' compound_statement ELSE compound_statement
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
	| FOR '(' variable_declaration expression_statement ')' statement
	| FOR '(' variable_declaration expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| SEND expression_statement
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

int yyerror(char*s){
	fprintf(stderr, "error occured!\n%s\n", s);
}
