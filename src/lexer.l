D               [0-9]
L               [a-zA-Z]


%{
#include <stdio.h>
#include "parser.tab.h"
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
"send"                  {count(); return(SEND);} 
"to_float"              {count(); return(TO_FLOAT);}
"true"                  {count(); return(BOOL_LITERAL);}
"var"                   {count(); return(VAR);}
"void"                  {count(); return(VOID);}
"while"                 {count(); return(WHILE);}
"driver"                {count(); return(DRIVER);}


"get_x"                {count(); return(GET_X);}
"get_y"                {count(); return(GET_Y);}
"get_points"           {count(); return(GET_POINTS);}
"get_width"            {count(); return(GET_WIDTH);}
"get_length"           {count(); return(GET_CENTER);}
"get_center"           {count(); return(GET_SIDES);}
"get_sides"            {count(); return(GET_SIDES);}
"get_side_length"      {count(); return(GET_SIDE_LENGTH);}
"get_rotation"         {count(); return(GET_ROTATION);}
"get_radius"           {count(); return(GET_RADIUS);}
"get_colour"           {count(); return(GET_COLOUR);}
"get_border_colour"    {count(); return(GET_BORDER_COLOUR);}
"set_x"                {count(); return(SET_X);}
"set_y"                {count(); return(SET_Y);}
"set_points"           {count(); return(SET_POINTS);}
"set_width"            {count(); return(SET_WIDTH);}
"set_length"           {count(); return(SET_LENGTH);}
"set_center"           {count(); return(SET_CENTER);}
"set_sides"            {count(); return(SET_SIDES);}
"set_side_length"      {count(); return(SET_SIDE_LENGTH);}
"set_rotation"         {count(); return(SET_ROTATION);}
"set_radius"           {count(); return(SET_RADIUS);}
"set_colour"           {count(); return(SET_COLOUR);}
"set_border_colour"    {count(); return(SET_BORDER_COLOUR);}
"add_point"            {count(); return(ADD_POINT);}
"make_point"           {count(); return(MAKE_POINT);}
"get_color_from_rgb"   {count(); return(GET_COLOUR_FROM_RGB);}


":="                    {count(); return(ASSIGN);}
"*="                    {count(); return(MUL_ASSIGN);}
"/="                    {count(); return(DIV_ASSIGN);}
"%="                    {count(); return(MOD_ASSIGN);}
"+="                    {count(); return(ADD_ASSIGN);}
"-="                    {count(); return(SUB_ASSIGN);}
"-"                     {count(); return('-');}
"+"                     {count(); return('+');}
"*"                     {count(); return('*');}
"/"                     {count(); return('/');}
"%"                     {count(); return('%');}
"<="                    {count(); return(LS_THAN_EQ);}
">="                    {count(); return(GR_THAN_EQ);}
"<"                     {count(); return(LS_THAN);}
">"                     {count(); return(GR_THAN);}
"="                     {count(); return(EQ);}
"!="                    {count(); return(NOT_EQ);}
"&"                     {count(); return(LOGICAL_AND);}
"|"                     {count(); return(LOGICAL_OR);}
"!"                     {count(); return(LOGICAL_NOT);}
">>"                    {count(); return(SCOPE_ACCESS);}
"(:"                    {count(); return('{');}
":)"                    {count(); return('}');}
("<:"|"(")              {count(); return('(');}
(":>"|")")              {count(); return(')');}
","                     {count(); return(',');}
"["                     {count(); return('[');}
"]"                     {count(); return(']');}
";"                     {count(); return(';');}

{L}({L}|{D}|_)*         {count(); return(IDENTIFIER);}
{D}+                    {count(); return(INTEGER_LITERAL);}
{D}+"."{D}+             {count(); return(FLOAT_LITERAL);}

\"([^\\\"]|\\.)*\"      {count(); return(STRING_LITERAL);}

[ \t\v\n\f]*             {count();}
.                       { }

%%
//SOME REMOVED PATTERNS
//"x"                    {count(); return(POINT_X);}
//"y"                    {count(); return(POINT_Y);}
//"length"               {count(); return(RECT_LENGTH);}
//"breadth"              {count(); return(RECT_BREADTH);}
//"center"               {count(); return(CENTER);}
//"rotation"             {count(); return(ROTATION);}
//"radius"               {count(); return(RADIUS);}
//"a"                    {count(); return(ELLIPSE_A);}
//"b"                    {count(); return(ELLIPSE_B);}
//"sides"                {count(); return(POLYGON_SIZE);}
//"side_len"             {count(); return(POLYGON_LENGTH);}
//"ctrl_pts"             {count(); return(CURVE_POINTS);}

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
// int main(int argc, char* argv[]){
//         if(argc != 2)return -1; //number of input args
//         yyin = fopen(argv[1], "r");
//         yyout = fopen("output.txt", "w");
//         while(yylex());
//         fclose(yyin);
//         fclose(yyout);
//         return 0;
// }

void comment(){
        char c;
        while( (c = input()) != '\n' ){
                /* eats up any line starting with '#' */
        }
        return;
}
