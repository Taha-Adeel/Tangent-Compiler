D               [0-9]
L               [a-zA-Z]


%{
#include <stdio.h>
#include "token.h"
void comment();
void count();
%}

%%
"#"                     {comment();}
"Circle"                {count(); return(CIRCLE);}
"clear"                 {count(); return(CLEAR);}
"Colour"                {count(); return(COLOUR);}
"Curve"                 {count(); return(CURVE);}
"draw"                  {count(); return(DRAW);}
"Ellipse"               {count(); return(ELLIPSE);}
"Image"                 {count(); return(IMAGE);}
"Path"                  {count(); return(PATH);}
"Pi"                    {count(); return(PI);}
"Point"                 {count(); return(POINT);}
"Polygon"               {count(); return(POLYGON);}
"Rectangle"             {count(); return(RECTANGLE);}
"bool"                  {count(); return(BOOL);}
"break"                 {count(); return(BREAK);}
"case"                  {count(); return(CASE);}
"ceil"                  {count(); return(CEIL);}
"const"                 {count(); return(CONST);}
"continue"              {count(); return(CONTINUE);}
"else"                  {count(); return(ELSE);}
"false"                 {count(); return(BOOL_LITERAL);}
"family"                {count(); return(FAMILY);}
"float"                 {count(); return(FLOAT);}
"floor"                 {count(); return(FLOOR);}
"for"                   {count(); return(FOR);}
"func"                  {count(); return(FUNC);}
"if"                    {count(); return(IF);}
"int"                   {count(); return(INT);}
"me"                    {count(); return(ME);}
"print"                 {count(); return(PRINT);}
"private"               {count(); return(PRIVATE);}
"public"                {count(); return(PUBLIC);}
"string"                {count(); return(STRING);}
"switch"                {count(); return(SWITCH);}
"send"                  {count(); return(SEND);} /* this isn't listed as a keyword in the language spec, pls add */
"to_float"              {count(); return(TO_FLOAT);}
"true"                  {count(); return(BOOL_LITERAL);}
"var"                   {count(); return(VAR);}
"void"                  {count(); return(VOID);}
"while"                 {count(); return(WHILE);}

{L}({L}|{D}|_)*         {count(); return(IDENTIFIER);}
{D}+                    {count(); return(INTEGER_LITERAL);}
{D}+"."{D}+             {count(); return(FLOAT_LITERAL);}

"_x"                    {count(); return(POINT_X);}
"_y"                    {count(); return(POINT_Y);}
"_dims"                 {count(); return(IMG_DIMS);}
"_drawables"            {count(); return(IMG_DRAWS);}
"_length"               {count(); return(RECT_LENGTH);}
"_breadth"              {count(); return(RECT_BREADTH);}
"_center"               {count(); return(CENTER);}
"_rotation"             {count(); return(ROTATION);}
"_radius"               {count(); return(RADIUS);}
"_a"                    {count(); return(ELLIPSE_A);}
"_b"                    {count(); return(ELLIPSE_B);}
"_sides"                {count(); return(POLYGON_SIZE);}
"_side_len"             {count(); return(POLYGON_LENGTH);}
"_ctrl_pts"             {count(); return(CURVE_POINTS);}
"_get_x"                {count(); return(GET_X);}
"_get_y"                {count(); return(GET_Y);}
"_get_points"           {count(); return(GET_POINTS);}
"_get_width"            {count(); return(GET_WIDTH);}
"_get_length"           {count(); return(GET_CENTER);}
"_get_center"           {count(); return(GET_SIDES);}
"_get_sides"            {count(); return(GET_SIDES);}
"_get_side_length"      {count(); return(GET_SIDE_LENGTH);}
"_get_rotation"         {count(); return(GET_ROTATION);}
"_get_radius"           {count(); return(GET_RADIUS);}
"_get_colour"           {count(); return(GET_COLOUR);}
"_get_border_colour"    {count(); return(GET_BORDER_COLOUR);}
"_set_x"                {count(); return(SET_X);}
"_set_y"                {count(); return(SET_Y);}
"_set_points"           {count(); return(SET_POINTS);}
"_set_width"            {count(); return(SET_WIDTH);}
"_set_length"           {count(); return(SET_LENGTH);}
"_set_center"           {count(); return(SET_CENTER);}
"_set_sides"            {count(); return(SET_SIDES);}
"_set_side_length"      {count(); return(SET_SIDE_LENGTH);}
"_set_rotation"         {count(); return(SET_ROTATION);}
"_set_radius"           {count(); return(SET_RADIUS);}
"_set_colour"           {count(); return(SET_COLOUR);}
"_set_border_colour"    {count(); return(SET_BORDER_COLOUR);}
"_add_point"            {count(); return(ADD_POINT);}
"_make_point"           {count(); return(MAKE_POINT);}

\"([^\\\"]|\\.)*\"      {count(); return(STRING_LITERAL);}

">>"                    {count(); return(SCOPE_ACCESS);}
"&"                     {count(); return(LOGICAL_AND);}
"|"                     {count(); return(LOGICAL_OR);}
"!"                     {count(); return(LOGICAL_NOT);}
"<="                    {count(); return(LS_THAN_EQ);}
">="                    {count(); return(GR_THAN_EQ);}
"<"                     {count(); return(LS_THAN);}
">"                     {count(); return(GR_THAN);}
"="                     {count(); return(EQ);}
"!="                    {count(); return(NOT_EQ);}
";"                     {count(); return(';');}
"(:"                    {count(); return('{');}
":)"                    {count(); return('}');}
("<:"|"(")                    {count(); return('(');}
(":>"|")")                    {count(); return(')');}
","                     {count(); return(',');}
"["                     {count(); return('[');}
"]"                     {count(); return(']');}
"-"			            {count(); return('-');}
"+"			            {count(); return('+');}
"*"			            {count(); return('*');}
"/"			            {count(); return('/');}
"%"			            {count(); return('%');}

[ \t\v\n\f]             {count();}
.                       { }

%%

int column = 0;
void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}
int yywrap()
{
	return 1;
}
int main(int argc, char* argv[]){
        if(argc != 2)return -1; //number of input args
        yyin = fopen(argv[1], "r");
        yyout = fopen("output.txt", "w");
        yylex();
        fclose(yyin);
        fclose(yyout);
        return 0;
}

void comment(){
        char c;
        while( (c = input()) != '\n' ){
                /* eats up any line starting with '#' */
        }
        return;
}
