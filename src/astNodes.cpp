#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <cstring>
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

string Identifier::ret_id()
{
    return id;
}

value_pair Identifier::evaluate()
{
    cout << "Identifier node: " << id << " = ";
    if(symTable[id].first == INT_TYPE)
    {
        cout << symTable[id].second.ivalue << endl;
    }
    else if(symTable[id].first == FLOAT_TYPE)
    {
        cout << symTable[id].second.fvalue << endl;
    }
    else if(symTable[id].first == STRING_TYPE)
    {
        cout << symTable[id].second.svalue << endl;
    }
    else if(symTable[id].first == BOOL_TYPE)
    {
        cout << symTable[id].second.bvalue << endl;
    }
    return symTable[id];
}

ArrayAccess::ArrayAccess(Identifier* name, int i)
{
    array_name = name;
    index = i;
}

void ArrayAccess::print()
{
    array_name->print();
    cout << "[" << index << "]";  
}

value_pair ArrayAccess::evaluate()
{

}

FunctionCall::FunctionCall(Identifier* name, list <Identifier*> l)
{
    func_name = name;
    args_list.assign(l.begin(), l.end());
}

void FunctionCall::print()
{
    func_name->print();
    cout << "(";
    for (auto const &v : args_list)
    {
        v->print();
        cout << ",";
    }
    cout << ")";
}

value_pair FunctionCall::evaluate()
{

}

AssignmentExp::AssignmentExp(Identifier* name, Expression* R)
{
    id = name;
    RHS = R;
}

void AssignmentExp::print()
{
    id->print();
    cout << " = ";
    RHS->print();
}

value_pair AssignmentExp::evaluate()
{
    value_pair result = RHS->evaluate();
    symTable[id->ret_id()] = result;
    return result;
}

AddAssign::AddAssign(Identifier* name, Expression* R)
{
    AssignmentExp(name, R); 
}

void AddAssign::print()
{
    id->print();
    cout << " += ";
    RHS->print(); 
}

value_pair AddAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == symTable[id->ret_id()].first)
    {
        if(result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue += result.second.ivalue;
        }
        else if(result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue += result.second.fvalue;
        }
        else if(result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue += result.second.bvalue;
        }
        else if(result.first == STRING_TYPE)
        {
            string s1 = symTable[id->ret_id()].second.svalue;
            string s2 = result.second.svalue;
            s1 += s2;

            symTable[id->ret_id()].second.svalue = strcpy(new char[s1.length() + 1], s1.c_str());
        }
    }
    return symTable[id->ret_id()];
}