%code top{
	#include<stdio.h>

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
%precedence UPLUS UMINUS LOGICAL_NOT
%left '(' ')' '[' ']' SCOPE_ACCESS

/*** RULES ***/
%%

/*------------------------------------------------------------------------
 * Translation unit
 *------------------------------------------------------------------------*/
program
	: %empty
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
	| IDENTIFIER
	;


literal
	: INTEGER_LITERAL
	| FLOAT_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	| PI
	;

variable_declaration
	: type new_variable_list ';'
	| VAR type new_variable_list ';'
	| CONST type new_variable_list ';'
	;

new_variable_list
	: new_variable
	| new_variable_list ',' new_variable
	;

new_variable
	: IDENTIFIER
	| IDENTIFIER ASSIGN expression
	| IDENTIFIER '(' ')'
	| IDENTIFIER '(' expression_list ')'
	;

function_definition
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
	| function_definition
	| constructor_declaration
	;

constructor_declaration
	: IDENTIFIER '(' args_list ')' compound_statement
	;

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
primary_expression
	: literal
	| variable
	| variable '[' expression ']'
	| variable '(' ')'
	| variable '(' expression_list ')'
	| inbuilt_function_call
	| '(' expression ')'
	;

variable
	: IDENTIFIER
	;

expression
	: primary_expression
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
	| '+' expression %prec UPLUS
	| '-' expression %prec UMINUS
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
	| expression_list ';'
	;

selection_statement
	: IF '(' expression ')' compound_statement
	| IF '(' expression ')' compound_statement ELSE compound_statement
	| SWITCH '(' expression ')' statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE expression ':' statement
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
	| inbuilt_function '(' expression_list ')'
	| inbuilt_member_function '(' ')'
	| inbuilt_member_function '(' expression_list ')'
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