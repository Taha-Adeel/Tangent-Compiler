#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
// contains implementations of the member methods and constructors in astNodes.h


IntegerLiteral::IntegerLiteral(int num)
{
    value.first = INT_TYPE;
    value.second.ivalue = num;
}

void IntegerLiteral::print()
{
    cout << value.second.ivalue;
}

value_pair IntegerLiteral::evaluate()
{
    cout << "Integer node: operand = " << value.second.ivalue << endl;
    return value;
}

FloatingPointLiteral::FloatingPointLiteral(float num)
{
    value.first = FLOAT_TYPE;
    value.second.fvalue = num;
}

void FloatingPointLiteral::print()
{
    cout << value.second.fvalue;
}

value_pair FloatingPointLiteral::evaluate()
{
    cout << "Float node: operand = " << value.second.fvalue << endl;
    return value;
}

StringLiteral::StringLiteral(string s)
{
    value.first = STRING_TYPE;
    value.second.svalue = &s[0];
}

void StringLiteral::print()
{
    cout << value.second.svalue;
}

value_pair StringLiteral::evaluate()
{
    cout << "String node: operand = " << value.second.svalue << endl;
    return value;
}

BooleanLiteral::BooleanLiteral(bool b)
{
    value.first = BOOL_TYPE;
    value.second.bvalue = b;
}

void BooleanLiteral::print()
{
    cout << value.second.bvalue;
}

value_pair BooleanLiteral::evaluate()
{
    cout << "Bool node: operand = " << value.second.bvalue << endl;
    return value;
}

Identifier::Identifier(string name)
{
    id = name;
}

void Identifier::print()
{
    cout << id;
}

value_pair Identifier::evaluate()
{
    cout << "Identifier node: " << id << " = " << symTable[id] << endl;
    return symTable[id];
}