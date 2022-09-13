// TOKEN DECLARATION
%token IDENTIFIER INTEGER_LITERAL FLOAT_LITERAL STRING_LITERAL BOOL_LITERAL CONSTANT PI

/* Primitive data types */
%token INT FLOAT STRING BOOL VOID
%token CONST VAR 

/* Operators */
%token ASSIGN 
%token EQ NOT_EQ LS_THAN LS_THAN_EQ GR_THAN GR_THAN_EQ
%token OPEN_PAR CLOSE_PAR OPEN_BRACES CLOSE_BRACES OPEN_SQ_BRKT CLOSE_SQ_BRKT DELIMITER COMMA
%token PLUS MINUS STAR MODULO INCREMENT DECREMENT
%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT

/* Control flow keywords */
%token IF ELSE FOR WHILE SWITCH CASE BREAK CONTINUE

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

//rules
%%

// Basic grammar rules

primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| unary_operator cast_expression
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
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
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
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

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

// OOPS grammar rules
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

function_definition
	: type IDENTIFIER '(' args_list ')' compound_statement
	| type IDENTIFIER '(' ')' compound_statement
	;

type
	: INT
	| FLOAT
	| STRING
	| BOOL
	| VOID
	;

args_list
	: arg
	| args_list ',' arg
	;

arg
	: type IDENTIFIER
	;

variable_declaration
	: type variable_list ';'
	| CONST type variable_list ';'
	;

variable_list
	: variable
	| variable_list variable
	;

variable
	: IDENTIFIER
	| variable_initialization
	;

variable_initialization
	: IDENTIFIER ASSIGN type_const
	;

type_const
	: INTEGER_LITERAL
	| FLOAT_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	;

access_specifier
	: PUBLIC 
	| PRIVATE
	;

class_declaration
	: FAMILY IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER "::" IDENTIFIER class_definition ';'
	| FAMILY IDENTIFIER "::" access_specifier class_definition ';'
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





// Tangent specific grammar rules
temp: SET_RADIUS
| ADD_POINT
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
