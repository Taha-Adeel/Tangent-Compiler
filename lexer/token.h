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
    TRUE,
    FALSE,
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

enum identifiers
{
    IDENTIFIER = 100
};
