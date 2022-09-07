D               [0-9]
L               [a-zA-Z]


%{
#include <stdio.h>
#include 'token.h'

void count();
%}

%%
"#"                     {comment();}
"Circle"                {count(); return(CIRCLE);}
"Colour"                {count(); return(COLOUR);}
"Curve"                 {count(); return(CURVE);}
"Ellipse"               {count(); return(ELLIPSE);}
"Image"                 {count(); return(IMAGE);}
"Path"                  {count(); return(PATH);}
"Pi"                    {count(); return(PI)};
"Point"                 {count(); return(POINT);}
"Polygon"               {count(); return(POLYGON);}
"Rectangle"             {count(); return(RECTANGLE);}
"bool"                  {count(); return(BOOL);}
"break"                 {count(); return(BREAK);}
"case"                  {count(); return(CASE)};
"const"                 {count(); return(CONST);}
"continue"              {count(); return(CONTINUE);}
"else"                  {count(); return(ELSE);}
"false"                 {count(); return(BOOL_LITERAL);}
"family"                {count(); return{FAMILY};}
"float"                 {count(); return(FLOAT);}
"for"                   {count(); return(FOR);}
"func"                  {count(); return(FUNC);}
"if"                    {count(); return(IF);}
"int"                   {count(); return(INT);}
"me"                    {count(); return(ME);}
"private"               {count(); return(PRIVATE);}
"public"                {count(); return(PUBLIC);}
"string"                {count(); return(STRING);}
"switch"                {count(); return(SWITCH);}
"send"                  {count(); return(SEND);} /* this isn't listed as a keyword in the language spec, pls add */
"true"                  {count(); return(BOOL_LITERAL);}
"var"                   {count(); return(VAR);}
"void"                  {count(); return(VOID);}
"while"                 {count(); return(WHILE);}

{L}({L}|{D}|_)*         {count(); return(IDENTIFIER);}
{D}+                    {count(); return(INTEGER_LITERAL);}
{D}+"."{D}+             {count(); return(FLOAT_LITERAL);}

\"([^\\\"]|\\.)*\"      {count(); return(STRING_LITERAL);}

">>"                    {count(); return(SCOPE_ACCESS);}
"&"                     {count(); return(AND_OP);}
"|"                     {count(); return(OR_OP);}
"!"                     {count(); return(NOT_OP);}
"<="                    {count(); return(LE_OP);}
">="                    {count(); return(GE_OP);}
"<"                     {count(); return(LT_OP);}
">"                     {count(); return(GT_OP);}
"="                     {count(); return(EQ_OP);}
"!="                    {count(); return(NE_OP);}
";"                     {count(); return(';');}
"(:"                    {count(); return('{');}
":)"                    {count(); return('}');}
"<:"                    {count(); return('(');}
":>"                    {count(); return(')');}
","                     {count(); return(',');}
"["                     {count(); return('[');}
"]"                     {count(); return(']');}
"!"                     {count(); return(NOT_OP);}
"-"			{count(); return('-');}
"+"			{count(); return('+');}
"*"			{count(); return('*');}
"/"			{count(); return('/');}
"%"			{count(); return('%');}

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

int main(int argc, char* argv[]){
        if(argc != 1)return -1; //number of input args
        yyin = fopen(argv[1], "r");
        yylex();
        fclose(yyin);
        return 0;
}

void comment(){
        char c;
        while( (c = yyinput()) != '\n' ){
                /* eats up any line starting with '#' */
        }
        return;
}
