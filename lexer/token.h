/*
contains the tokens to be used in lexel.l

aman:
    Types of Tokens:
    Keywords, Identifiers, literals(numeric, boolean and pointer), literals (strings), user-defined literals, operators, punctuators.

    Keywords:
    tokens,33 separate  find in the language specification

taha:
    Identifiers:
    One grammar rule, one token

    Numeric, boolean and pointer literals:
    One grammar rule, one token

    String literal:
    One grammar rule, one token

    User defined literal:
    ??rules, one token

    Operators:
    17 rules and tokens

    Punctuators:
*/

enum keywords
{
    INT = 0,
    FLOAT,
    STRING,
    BOOL,
    VOID,
    VAR,
    FAMILY,
    IF,
    ELSE,
    FOR,
    WHILE,
    SWITCH,
    CASE,
    BREAK,
    CONTINUE,
    SEND,
    CONST,
    ME,
    PUBLIC,
    PRIVATE,
    POINT,
    PATH,
    IMAGE,
    RECTANGLE,
    CIRCLE,
    ELLIPSE,
    POLYGON,
    CURVE,
    FUNC,
    PI,
    COLOUR
};

enum operators
{
  ASSIGN=200,
  EQ,
  NOT_EQ,
  LS_THAN,
  LS_THAN_EQ,
  GR_THAN,
  GR_THAN_EQ,
  LOGICAL_AND,
  LOGICAL_OR,
  LOGICAL_NOT,
  PLUS,
  MINUS,
  STAR,
  MODULO,
  INCREMENT,
  DECREMENT,
};

enum special_symbols
{
  DELIMITER=300,
  OPEN_PAR,
  CLOSE_PAR,
  OPEN_BRACES,
  CLOSE_BRACES,
  OPEN_SQ_BRKT,
  CLOSE_SQ_BRKT,
  COMMA,
  SCOPE_ACCESS,
};

enum IDENTIFIER
{
  IDENTIFIER=400
};

enum literals
{
  INTEGER_LITERAL = 500,
  FLOAT_LITERAL,
  STRING_LITERAL,
  BOOL_LITERAL,
};
