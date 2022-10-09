%option noyywrap yylineno nodefault

D               [0-9]
L               [a-zA-Z]


%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"

    #define YY_USER_ACTION update_locations(); // Called before each token
    void comment();
    void update_locations();

    extern YYLTYPE yylloc;
%}

%%
"#"                    {comment();}
":="                   {return ASSIGN;}
"*="                   {return MUL_ASSIGN;}
"/="                   {return DIV_ASSIGN;}
"%="                   {return MOD_ASSIGN;}
"+="                   {return ADD_ASSIGN;}
"-="                   {return SUB_ASSIGN;}
"-"                    {return '-';}
"+"                    {return '+';}
"*"                    {return '*';}
"/"                    {return '/';}
"%"                    {return '%';}
"<="                   {return LS_THAN_EQ;}
">="                   {return GR_THAN_EQ;}
"<"                    {return LS_THAN;}
">"                    {return GR_THAN;}
"="                    {return EQ;}
"!="                   {return NOT_EQ;}
"&"                    {return LOGICAL_AND;}
"|"                    {return LOGICAL_OR;}
"!"                    {return LOGICAL_NOT;}
">>"                   {return SCOPE_ACCESS;}
"::"                   {return INHERITS;}  
"(:"                   {return '{';}
":)"                   {return '}';}
("<:"|"(")             {return '(';}
(":>"|")")             {return ')';}
","                    {return ',';}
"["                    {return '[';}
"]"                    {return ']';}
";"                    {return ';';}

{D}+                   {return INTEGER_LITERAL;}
{D}+"."{D}+            {return FLOAT_LITERAL;}
\"([^\\\"]|\\.)*\"     {return STRING_LITERAL;}
"true"                 {return BOOL_LITERAL;}
"false"                {return BOOL_LITERAL;}
"Pi"                   {return PI;}

"bool"                 {return BOOL;}
"float"                {return FLOAT;}
"int"                  {return INT;}
"string"               {return STRING;}

"Circle"               {return CIRCLE;}
"Colour"               {return COLOUR;}
"Curve"                {return CURVE;}
"draw"                 {return DRAW;}
"Ellipse"              {return ELLIPSE;}
"Image"                {return IMAGE;}
"Path"                 {return PATH;}
"Point"                {return POINT;}
"Polygon"              {return POLYGON;}
"Rectangle"            {return RECTANGLE;}

"break"                {return BREAK;}
"clear"                {return CLEAR;}
"case"                 {return CASE;}
"ceil"                 {return CEIL;}
"const"                {return CONST;}
"continue"             {return CONTINUE;}
"driver"               {return DRIVER;}
"else"                 {return ELSE;}
"family"               {return FAMILY;}
"floor"                {return FLOOR;}
"for"                  {return FOR;}
"func"                 {return FUNC;}
"if"                   {return IF;}
"me"                   {return ME;}
"print"                {return PRINT;}
"private"              {return PRIVATE;}
"public"               {return PUBLIC;}
"switch"               {return SWITCH;}
"send"                 {return SEND;} 
"to_float"             {return TO_FLOAT;}
"var"                  {return VAR;}
"void"                 {return VOID;}
"while"                {return WHILE;}

"get_x"                {return GET_X;}
"get_y"                {return GET_Y;}
"get_points"           {return GET_POINTS;}
"get_width"            {return GET_WIDTH;}
"get_length"           {return GET_CENTER;}
"get_center"           {return GET_SIDES;}
"get_sides"            {return GET_SIDES;}
"get_side_length"      {return GET_SIDE_LENGTH;}
"get_rotation"         {return GET_ROTATION;}
"get_radius"           {return GET_RADIUS;}
"get_colour"           {return GET_COLOUR;}
"get_border_colour"    {return GET_BORDER_COLOUR;}
"set_x"                {return SET_X;}
"set_y"                {return SET_Y;}
"set_points"           {return SET_POINTS;}
"set_width"            {return SET_WIDTH;}
"set_length"           {return SET_LENGTH;}
"set_center"           {return SET_CENTER;}
"set_sides"            {return SET_SIDES;}
"set_side_length"      {return SET_SIDE_LENGTH;}
"set_rotation"         {return SET_ROTATION;}
"set_radius"           {return SET_RADIUS;}
"set_colour"           {return SET_COLOUR;}
"set_border_colour"    {return SET_BORDER_COLOUR;}
"set_dimension"	       {return SET_DIMENSION;}
"add_point"            {return ADD_POINT;}
"make_point"           {return MAKE_POINT;}
"get_color_from_rgb"   {return GET_COLOUR_FROM_RGB;}

{L}({L}|{D}|_)*        {return IDENTIFIER;}

[ \t\v\n\f]*           {}

 /* Matches to any invalid tokens not matched to any other rules */
.                      {
                        printf("ERROR: %s: Line %d:%d\t%-12s - Invalid token\n", yylloc.filename, yylineno, yylloc.first_column, yytext);
                        fprintf(stderr, "\033[0;31m   ERROR:\033[0m %s: Line %d:%d - '%s' - Invalid token\n", yylloc.filename, yylineno, yylloc.first_column, yytext);
                        return YYUNDEF;
                       }
%%

void update_locations(){
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = yylloc.last_column;

    for(int i = 0; yytext[i] != '\0'; i++) {
        if(yytext[i] == '\n'){
            yylloc.last_line++;
            yylloc.last_column = 0;
        }
        else if(yytext[i] == '\t')
            yylloc.last_column += 4 - (yylloc.last_column % 4);
        else
            yylloc.last_column++;
    }
}

void comment(){
        char c;
        while( (c = input()) != '\n' )
            ; /* eats up any line starting with '#' */
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
YYLTYPE yylloc;

void print_tokens_matched(){
    int token;
    while(token = yylex()){
        char token_name[20] = "'''";
        if(token < 255) 
            token_name[1] = token;
        else
            strcpy(token_name, yytname[token - 255]);
        printf("%s: Line %d:%d\t%-12s was matched to the token %-20s (= %d) \n", yylloc.filename, yylloc.first_line, yylloc.first_column, yytext, token_name, token);
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    if(argc < 2){ /* just read stdin */
        yylloc.first_line = yylloc.last_line = yylineno = 1;
        yylloc.first_column = yylloc.last_column = 0;
        if(yylloc.filename == NULL) yylloc.filename = "(stdin)";
        print_tokens_matched();
    }
    else{
        for(int i = 1; i < argc; i++){
            yylloc.first_line = yylloc.last_line = yylineno = 1;
            yylloc.first_column = yylloc.last_column = 0;
            yylloc.filename = argv[i];
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ 
                perror(argv[i]); 
                return 1;
            }
            yyrestart(file);
            print_tokens_matched();
            fclose(file);
        }
    }

    return 0;
}

#endif