%option noyywrap yylineno nodefault

D               [0-9]
L               [a-zA-Z]


%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    void comment();
    void count();
    char* cur_filename;
%}

%%
"#"                     {comment();}
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
"::"                    {count(); return(INHERITS);}  
"(:"                    {count(); return('{');}
":)"                    {count(); return('}');}
("<:"|"(")              {count(); return('(');}
(":>"|")")              {count(); return(')');}
","                     {count(); return(',');}
"["                     {count(); return('[');}
"]"                     {count(); return(']');}
";"                     {count(); return(';');}

{D}+                    {count(); return(INTEGER_LITERAL);}
{D}+"."{D}+             {count(); return(FLOAT_LITERAL);}
\"([^\\\"]|\\.)*\"      {count(); return(STRING_LITERAL);}
"true"                  {count(); return(BOOL_LITERAL);}
"false"                 {count(); return(BOOL_LITERAL);}
"Pi"                    {count(); return(PI);}

"bool"                  {count(); return(BOOL);}
"float"                 {count(); return(FLOAT);}
"int"                   {count(); return(INT);}
"string"                {count(); return(STRING);}

"Circle"                {count(); return(CIRCLE);}
"Colour"                {count(); return(COLOUR);}
"Curve"                 {count(); return(CURVE);}
"draw"                  {count(); return(DRAW);}
"Ellipse"               {count(); return(ELLIPSE);}
"Image"                 {count(); return(IMAGE);}
"Path"                  {count(); return(PATH);}
"Point"                 {count(); return(POINT);}
"Polygon"               {count(); return(POLYGON);}
"Rectangle"             {count(); return(RECTANGLE);}

"break"                 {count(); return(BREAK);}
"clear"                 {count(); return(CLEAR);}
"case"                  {count(); return(CASE);}
"ceil"                  {count(); return(CEIL);}
"const"                 {count(); return(CONST);}
"continue"              {count(); return(CONTINUE);}
"driver"                {count(); return(DRIVER);}
"else"                  {count(); return(ELSE);}
"family"                {count(); return(FAMILY);}
"floor"                 {count(); return(FLOOR);}
"for"                   {count(); return(FOR);}
"func"                  {count(); return(FUNC);}
"if"                    {count(); return(IF);}
"me"                    {count(); return(ME);}
"print"                 {count(); return(PRINT);}
"private"               {count(); return(PRIVATE);}
"public"                {count(); return(PUBLIC);}
"switch"                {count(); return(SWITCH);}
"send"                  {count(); return(SEND);} 
"to_float"              {count(); return(TO_FLOAT);}
"var"                   {count(); return(VAR);}
"void"                  {count(); return(VOID);}
"while"                 {count(); return(WHILE);}

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
"set_dimension"	       {count(); return(SET_DIMENSION);}
"add_point"            {count(); return(ADD_POINT);}
"make_point"           {count(); return(MAKE_POINT);}
"get_color_from_rgb"   {count(); return(GET_COLOUR_FROM_RGB);}

{L}({L}|{D}|_)*        {count(); return(IDENTIFIER);}

[ \t\v\n\f]*           {count();}
.                      {}

%%

int column = 0;
void count(){
    for(int i = 0; yytext[i] != '\0'; i++){
        if(yytext[i] == '\n')
            column = 0;
        else if(yytext[i] == '\t')
            column += 8 - (column % 8);
        else
            column++;
    }
}

void comment(){
        char c;
        while( (c = input()) != '\n' )
            ; /* eats up any line starting with '#' */
        
        return;
}

#ifdef STANDALONE_LEXER

// The token names generated by bison in parser.tab.c. yytname[i] gives the name of the token with enum value 255 + i;
static const char *const yytname[] =
{
    "$end", "error", "$undefined", "IDENTIFIER", "INTEGER_LITERAL",
    "FLOAT_LITERAL", "STRING_LITERAL", "BOOL_LITERAL", "PI", "INT", "FLOAT",
    "STRING", "BOOL", "VOID", "CONST", "VAR", "ASSIGN", "MUL_ASSIGN",
    "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "EQ", "NOT_EQ",
    "LS_THAN", "LS_THAN_EQ", "GR_THAN", "GR_THAN_EQ", "LOGICAL_AND",
    "LOGICAL_OR", "LOGICAL_NOT", "IF", "ELSE", "FOR", "WHILE", "SWITCH",
    "CASE", "DEFAULT", "BREAK", "CONTINUE", "SEND", "FAMILY", "ME",
    "INHERITS", "SCOPE_ACCESS", "PUBLIC", "PRIVATE", "POINT", "IMAGE",
    "RECTANGLE", "CIRCLE", "ELLIPSE", "POLYGON", "CURVE", "PATH", "POINT_X",
    "POINT_Y", "IMG_DIMS", "IMG_DRAWS", "FUNC", "CLEAR", "DRAW", "PRINT",
    "FLOOR", "CEIL", "TO_FLOAT", "ADD_POINT", "MAKE_POINT", "GET_X", "GET_Y",
    "GET_POINTS", "GET_WIDTH", "GET_CENTER", "GET_SIDES", "GET_SIDE_LENGTH",
    "GET_ROTATION", "GET_RADIUS", "GET_COLOUR", "GET_BORDER_COLOUR", "SET_X",
    "SET_Y", "SET_POINTS", "SET_WIDTH", "SET_LENGTH", "SET_CENTER",
    "SET_SIDES", "SET_SIDE_LENGTH", "SET_ROTATION", "SET_RADIUS",
    "SET_COLOUR", "SET_BORDER_COLOUR", "SET_DIMENSION", "COLOUR", "RED",
    "BLUE", "GREEN", "GET_COLOUR_FROM_RGB", "DRIVER" 
};

void print_tokens_matched(){
    int token;
    while(token = yylex()){
        char token_name[20] = "'''";
        if(token < 255) 
            token_name[1] = token;
        else
            strcpy(token_name, yytname[token - 255]);
        printf("%s: Line %d:%d\t%-12s was matched to the token %-20s (= %d) \n", cur_filename, yylineno, column, yytext, token_name, token);
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    if(argc < 2){ /* just read stdin */
        yylineno = 1;
        cur_filename = "(stdin)";
        print_tokens_matched();
    }
    else{
        for(int i = 1; i < argc; i++){
            yylineno = 1;
            cur_filename = argv[i];
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ 
                perror(argv[i]); return 1;
            }
            yyrestart(file);
            print_tokens_matched();
            fclose(file);
        }
    }

    return 0;
}

#endif