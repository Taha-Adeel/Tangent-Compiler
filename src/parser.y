%{
#include<stdio.h>
%}

//token declarations
%token INT
%token FLOAT
%token STRING
%token BOOL
%token VOID
%token VAR
%token FAMILY
%token IF
%token ELSE
%token FOR
%token WHILE
%token SWITCH
%token CASE
%token BREAK
%token CONTINUE
%token SEND
%token CONST
%token ME
%token PUBLIC
%token PRIVATE
%token POINT
%token PATH
%token IMAGE
%token RECTANGLE
%token CIRCLE
%token ELLIPSE
%token POLYGON
%token CURVE
%token FUNC
%token PI
%token COLOUR
%token DRIVER
%token ASSIGN
%token EQ
%token NOT_EQ
%token LS_THAN
%token LS_THAN_EQ
%token GR_THAN
%token GR_THAN_EQ
%token LOGICAL_AND
%token LOGICAL_OR
%token LOGICAL_NOT
%token PLUS
%token MINUS
%token STAR
%token MODULO
%token INCREMENT
%token DECREMENT
%token DELIMITER
%token OPEN_PAR
%token CLOSE_PAR
%token OPEN_BRACES
%token CLOSE_BRACES
%token OPEN_SQ_BRKT
%token CLOSE_SQ_BRKT
%token COMMA
%token SCOPE_ACCESS
%token IDENTIFIER
%token INTEGER_LITERAL
%token FLOAT_LITERAL
%token STRING_LITERAL
%token BOOL_LITERAL
%token CLEAR
%token DRAW
%token CEIL
%token FLOOR
%token PRINT
%token TO_FLOAT
%token POINT_X
%token POINT_Y
%token IMG_DIMS
%token IMG_DRAWS
%token RECT_LENGTH
%token RECT_BREADTH
%token CENTER
%token ROTATION
%token RADIUS
%token ELLIPSE_A
%token ELLIPSE_B
%token POLYGON_SIZE
%token POLYGON_LENGTH
%token CURVE_POINTS
%token RED
%token BLUE
%token GREEN
%token GET_X
%token GET_Y
%token GET_POINTS
%token GET_WIDTH
%token GET_CENTER
%token GET_SIDES
%token GET_SIDE_LENGTH
%token GET_ROTATION
%token GET_RADIUS
%token GET_COLOUR
%token GET_BORDER_COLOUR
%token SET_X
%token SET_Y
%token SET_POINTS
%token SET_WIDTH
%token SET_LENGTH
%token SET_CENTER
%token SET_SIDES
%token SET_SIDE_LENGTH
%token SET_ROTATION
%token SET_RADIUS
%token SET_COLOUR
%token SET_BORDER_COLOUR
%token ADD_POINT
%token MAKE_POINT
//rules
%%
temp: SET_RADIUS
| ADD_POINT
;
%%

main(int argc, char **argv)
{
	yyparse();
}

yyerror(char*s)
{
	fprintf(stderr, "error occured!\n%s\n", s);
}
