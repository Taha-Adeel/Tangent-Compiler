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

SubAssign::SubAssign(Identifier* name, Expression* R)
{
    AssignmentExp(name, R);
}

void SubAssign::print()
{
    id->print();
    cout << " -= ";
    RHS->print(); 
}

value_pair SubAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == symTable[id->ret_id()].first)
    {
        if(result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue -= result.second.ivalue;
        }
        else if(result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue -= result.second.fvalue;
        }
        else if(result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue -= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

MulAssign::MulAssign(Identifier* name, Expression* R)
{
    AssignmentExp(name, R); 
}

void MulAssign::print()
{
    id->print();
    cout << " *= ";
    RHS->print(); 
}

value_pair MulAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == symTable[id->ret_id()].first)
    {
        if(result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue *= result.second.ivalue;
        }
        else if(result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue *= result.second.fvalue;
        }
        else if(result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue *= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

DivAssign::DivAssign(Identifier* name, Expression* R)
{
    AssignmentExp(name, R); 
}

void DivAssign::print()
{
    id->print();
    cout << " /= ";
    RHS->print(); 
}

value_pair DivAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == symTable[id->ret_id()].first)
    {
        if(result.first == INT_TYPE && result.second.ivalue != 0)
        {
            symTable[id->ret_id()].second.ivalue /= result.second.ivalue;
        }
        else if(result.first == FLOAT_TYPE && result.second.fvalue != 0)
        {
            symTable[id->ret_id()].second.fvalue /= result.second.fvalue;
        }
        else if(result.first == BOOL_TYPE && result.second.bvalue != 0)
        {
            symTable[id->ret_id()].second.bvalue /= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

ModAssign::ModAssign(Identifier* name, Expression* R)
{
    AssignmentExp(name, R); 
}

void ModAssign::print()
{
    id->print();
    cout << " %= ";
    RHS->print(); 
}

value_pair ModAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == symTable[id->ret_id()].first)
    {
        if(result.first == INT_TYPE && result.second.ivalue != 0)
        {
            symTable[id->ret_id()].second.ivalue %= result.second.ivalue;
        }
        else if(result.first == BOOL_TYPE && result.second.bvalue != 0)
        {
            symTable[id->ret_id()].second.bvalue %= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

UnaryOperation::UnaryOperation(Expression* R)
{
    RHS = R;
}

BinaryOperation::BinaryOperation(Expression* L, Expression* R)
{
    LHS = L;
    RHS = R;
}

Addition::Addition(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void Addition::print()
{
    cout << "(";
    LHS->print();
    cout << " + ";
    RHS->print();
    cout << ")";
}

value_pair Addition::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue + right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue + right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue + right_eval.second.bvalue;
        }
        else if(left_eval.first == STRING_TYPE)
        {
            result.first = STRING_TYPE;
            string s1 = left_eval.second.svalue;
            string s2 = right_eval.second.svalue;
            string s = s1+s2;
            result.second.svalue = strcpy(new char[s.length() + 1], s.c_str());
        }
    }
    return result;
}

Subtraction::Subtraction(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void Subtraction::print()
{
    cout << "(";
    LHS->print();
    cout << " - ";
    RHS->print();
    cout << ")";
}

value_pair Subtraction::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue - right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue - right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue - right_eval.second.bvalue;
        }
    }
    return result;
}

Multiplication::Multiplication(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void Multiplication::print()
{
    cout << "(";
    LHS->print();
    cout << " * ";
    RHS->print();
    cout << ")";
}

value_pair Multiplication::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue * right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue * right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue * right_eval.second.bvalue;
        }
    }
    return result;
}

Division::Division(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void Division::print()
{
    cout << "(";
    LHS->print();
    cout << " / ";
    RHS->print();
    cout << ")";
}

value_pair Division::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue / right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE && right_eval.second.fvalue != 0)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue / right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue / right_eval.second.bvalue;
        }
    }
    return result;
}

ModularDiv::ModularDiv(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void ModularDiv::print()
{
    cout << "(";
    LHS->print();
    cout << " % ";
    RHS->print();
    cout << ")";
}

value_pair ModularDiv::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue % right_eval.second.ivalue;
        }
        else if(left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue % right_eval.second.bvalue;
        }
    }
    return result;
}

UnaryPlus::UnaryPlus(Expression* R)
{
    UnaryOperation(R);
}

void UnaryPlus::print()
{
    cout << "+";
    RHS->print();
}

value_pair UnaryPlus::evaluate()
{
    value_pair result = RHS->evaluate();
    return result;
}

UnaryMinus::UnaryMinus(Expression* R)
{
    UnaryOperation(R);
}

void UnaryMinus::print()
{
    cout << "-";
    RHS->print();
}

value_pair UnaryMinus::evaluate()
{
    value_pair result = RHS->evaluate();
    if(result.first == INT_TYPE)
    {
        result.second.ivalue = -result.second.ivalue;
    }
    else if(result.first == FLOAT_TYPE)
    {
        result.second.fvalue = -result.second.fvalue;
    }
    else if(result.first == BOOL_TYPE)
    {
        result.second.bvalue = -result.second.bvalue;
    }
    return result;
}

LogicalAND::LogicalAND(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void LogicalAND::print()
{
    cout << "(";
    LHS->print();
    cout << " & ";
    RHS->print();
    cout << ")";
}

value_pair LogicalAND::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue && right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue && right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue && right_eval.second.bvalue;
        }
    }
    return result;
}

LogicalOR::LogicalOR(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void LogicalOR::print()
{
    cout << "(";
    LHS->print();
    cout << " | ";
    RHS->print();
    cout << ")";
}

value_pair LogicalOR::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue || right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue || right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue || right_eval.second.bvalue;
        }
    }
    return result;
}

LogicalNOT::LogicalNOT(Expression* R)
{
    UnaryOperation(R);
}

void LogicalNOT::print()
{
    cout << "!";
    RHS->print();
}

value_pair LogicalNOT::evaluate()
{
    value_pair result = RHS->evaluate();
    value_pair res;
    if(result.first == INT_TYPE)
    {
        res.first = BOOL_TYPE;
        res.second.bvalue = !result.second.ivalue;
    }
    else if(result.first == FLOAT_TYPE)
    {
        res.first = BOOL_TYPE;
        res.second.bvalue = !result.second.fvalue;
    }
    else if(result.first == BOOL_TYPE)
    {
        res.first = BOOL_TYPE;
        res.second.bvalue = !result.second.bvalue;
    }
    return res;
}

CompGT::CompGT(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompGT::print()
{
    cout << "(";
    LHS->print();
    cout << " > ";
    RHS->print();
    cout << ")";
}

value_pair CompGT::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue > right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue > right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue > right_eval.second.bvalue;
        }
    }
    return result;
}

CompLT::CompLT(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompLT::print()
{
    cout << "(";
    LHS->print();
    cout << " < ";
    RHS->print();
    cout << ")";
}

value_pair CompLT::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue < right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue < right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue < right_eval.second.bvalue;
        }
    }
    return result;
}

CompGE::CompGE(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompGE::print()
{
    cout << "(";
    LHS->print();
    cout << " >= ";
    RHS->print();
    cout << ")";
}

value_pair CompGE::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue >= right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue >= right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue >= right_eval.second.bvalue;
        }
    }
    return result;
}

CompLE::CompLE(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompLE::print()
{
    cout << "(";
    LHS->print();
    cout << " <= ";
    RHS->print();
    cout << ")";
}

value_pair CompLE::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue <= right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue <= right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue <= right_eval.second.bvalue;
        }
    }
    return result;
}

CompEQ::CompEQ(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompEQ::print()
{
    cout << "(";
    LHS->print();
    cout << " = ";
    RHS->print();
    cout << ")";
}

value_pair CompEQ::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue == right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue == right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue == right_eval.second.bvalue;
        }
    }
    return result;
}

CompNEQ::CompNEQ(Expression* L, Expression* R)
{
    BinaryOperation(L, R);
}

void CompNEQ::print()
{
    cout << "(";
    LHS->print();
    cout << " != ";
    RHS->print();
    cout << ")";
}

value_pair CompNEQ::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if(left_eval.first == right_eval.first)
    {
        if(left_eval.first == INT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.ivalue != right_eval.second.ivalue;
        }
        else if(left_eval.first == FLOAT_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.fvalue != right_eval.second.fvalue;
        }
        else if(left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue != right_eval.second.bvalue;
        }
    }
    return result;
}



/**************************************
 * STATEMENTS
 **************************************/


void ExpressionStatement::print()
{
    cout << "Expression Statement:\n{ \n->";
    exp->print();
    cout << "\n}\n";
}

Expression* ExpressionStatement::getValue()
{
    return exp;
}

void CompoundStatement::print()
{
    cout << "Compound Statement:\n{";
    for (auto ele : stmt_list)
    {
        cout<<"\n->";
        ele->print();
    }
    cout << "\n}\n";
}
void FunctionDefinition::print()
{
    cout<<"Function Definition:\n{";
    func_name->print();
    cout<< "\nReturn type : "<<enumtypeToString(return_type)<<"\n";
    cout<<"list of arguments";
    for(auto &ele: arg_list)
    {
        cout<<"\n";
        ele->print();
    }
    cout<<"\nfunction body:\n";
    func_body->print();
    cout<<"}";   
}
void VariableDeclaration::print()
{
    cout<<"Variable Declaration: \n";
    cout<<"type : "<< enumtypeToString(variable_type)<<'\n';
    cout<<"list of identifiers";
    for(auto &ele: variable_list)
    {
        ele->print();
        cout<<"\n";
    }
}


/*------------------------------------------------------------------------
 * Program Root Node 
 *------------------------------------------------------------------------*/

Program :: Program(list <Statement*> *stmts)
{
    stmt_list = stmts;
}