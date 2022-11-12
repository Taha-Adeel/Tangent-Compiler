/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    INTEGER_LITERAL = 259,
    FLOAT_LITERAL = 260,
    STRING_LITERAL = 261,
    BOOL_LITERAL = 262,
    PI = 263,
    INT = 264,
    FLOAT = 265,
    STRING = 266,
    BOOL = 267,
    VOID = 268,
    CONST = 269,
    VAR = 270,
    ASSIGN = 271,
    MUL_ASSIGN = 272,
    DIV_ASSIGN = 273,
    MOD_ASSIGN = 274,
    ADD_ASSIGN = 275,
    SUB_ASSIGN = 276,
    EQ = 277,
    NOT_EQ = 278,
    LS_THAN = 279,
    LS_THAN_EQ = 280,
    GR_THAN = 281,
    GR_THAN_EQ = 282,
    LOGICAL_AND = 283,
    LOGICAL_OR = 284,
    LOGICAL_NOT = 285,
    IF = 286,
    ELSE = 287,
    FOR = 288,
    WHILE = 289,
    SWITCH = 290,
    CASE = 291,
    DEFAULT = 292,
    BREAK = 293,
    CONTINUE = 294,
    SEND = 295,
    FAMILY = 296,
    ME = 297,
    INHERITS = 298,
    SCOPE_ACCESS = 299,
    PUBLIC = 300,
    PRIVATE = 301,
    POINT = 302,
    IMAGE = 303,
    RECTANGLE = 304,
    CIRCLE = 305,
    ELLIPSE = 306,
    POLYGON = 307,
    CURVE = 308,
    PATH = 309,
    POINT_X = 310,
    POINT_Y = 311,
    IMG_DIMS = 312,
    IMG_DRAWS = 313,
    FUNC = 314,
    CLEAR = 315,
    DRAW = 316,
    PRINT = 317,
    FLOOR = 318,
    CEIL = 319,
    TO_FLOAT = 320,
    ADD_POINT = 321,
    MAKE_POINT = 322,
    GET_X = 323,
    GET_Y = 324,
    GET_POINTS = 325,
    GET_WIDTH = 326,
    GET_CENTER = 327,
    GET_SIDES = 328,
    GET_SIDE_LENGTH = 329,
    GET_ROTATION = 330,
    GET_RADIUS = 331,
    GET_COLOUR = 332,
    GET_BORDER_COLOUR = 333,
    SET_X = 334,
    SET_Y = 335,
    SET_POINTS = 336,
    SET_WIDTH = 337,
    SET_LENGTH = 338,
    SET_CENTER = 339,
    SET_SIDES = 340,
    SET_SIDE_LENGTH = 341,
    SET_ROTATION = 342,
    SET_RADIUS = 343,
    SET_COLOUR = 344,
    SET_BORDER_COLOUR = 345,
    SET_DIMENSION = 346,
    COLOUR = 347,
    RED = 348,
    BLUE = 349,
    GREEN = 350,
    GET_COLOUR_FROM_RGB = 351,
    DRIVER = 352
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
