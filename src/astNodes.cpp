#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <cstring>
// contains implementations of the member methods and constructors in astNodes.h

bool is_valid_comparasion(value_pair a, value_pair b)
{
    if (a.first==b.first) return true;//change this when we add families
    
    //int-float
    if (a.first == INT_TYPE && b.first ==FLOAT_TYPE)return true;
    if (b.first == INT_TYPE && a.first ==FLOAT_TYPE)return true;

    //bool-int
    if (a.first == BOOL_TYPE && b.first == INT_TYPE)return true;
    if (b.first == BOOL_TYPE && a.first == INT_TYPE)return true;

    return false;
}
bool is_unary_operation_valid(value_pair& a)
{
    if( a.first==INT_TYPE||
        a.first==FLOAT_TYPE||
        a.first==BOOL_TYPE)
        return true;
    return false;
}
bool is_valid_for_boolean_operation(value_pair& a, value_pair& b)
{
    return is_unary_operation_valid(a)&&is_unary_operation_valid(b);
}

IntegerLiteral::IntegerLiteral(int num)
{
    value.first = INT_TYPE;
    value.second = num;
}
void IntegerLiteral::print()
{
    std::cout << value.second.ivalue;
}
value_pair IntegerLiteral::evaluate()
{
    std::cout << "Integer node: operand = " << value.second.ivalue << endl;
    return value;
}

FloatingPointLiteral::FloatingPointLiteral(float num)
{
    value.first = FLOAT_TYPE;
    value.second.fvalue = num;
}
void FloatingPointLiteral::print()
{
    std::cout << value.second.fvalue;
}
value_pair FloatingPointLiteral::evaluate()
{
    std::cout << "Float node: operand = " << value.second.fvalue << endl;
    return value;
}

StringLiteral::StringLiteral(string s)
{
    value.first = STRING_TYPE;
    value.second.svalue = &s[0];
}
void StringLiteral::print()
{
    std::cout << value.second.svalue;
}
value_pair StringLiteral::evaluate()
{
    std::cout << "String node: operand = " << value.second.svalue << endl;
    return value;
}

BooleanLiteral::BooleanLiteral(bool b)
{
    value.first = BOOL_TYPE;
    value.second.bvalue = b;
}

void BooleanLiteral::print()
{
    std::cout << value.second.bvalue;
}

value_pair BooleanLiteral::evaluate()
{
    std::cout << "Bool node: operand = " << value.second.bvalue << endl;
    return value;
}

Identifier::Identifier(string name)
{
    id = name;
}

void Identifier::print()
{
    std::cout << id;
}

string Identifier::ret_id()
{
    return id;
}

value_pair Identifier::evaluate()
{
    std::cout << "Identifier node: " << id << " = ";
    if (symTable[id].first == INT_TYPE)
    {
        std::cout << symTable[id].second.ivalue << endl;
    }
    else if (symTable[id].first == FLOAT_TYPE)
    {
        std::cout << symTable[id].second.fvalue << endl;
    }
    else if (symTable[id].first == STRING_TYPE)
    {
        std::cout << symTable[id].second.svalue << endl;
    }
    else if (symTable[id].first == BOOL_TYPE)
    {
        std::cout << symTable[id].second.bvalue << endl;
    }
    return symTable[id];
}
ArrayAccess::ArrayAccess(Identifier *name, int i)
{
    array_name = name;
    index = i;
}

void ArrayAccess::print()
{
    array_name->print();
    std::cout << "[" << index << "]";
}

value_pair ArrayAccess::evaluate()
{
}

FunctionCall::FunctionCall(Identifier *name, list<Identifier *> l)
{
    func_name = name;
    args_list.assign(l.begin(), l.end());
}

void FunctionCall::print()
{
    func_name->print();
    std::cout << "(";
    for (auto const &v : args_list)
    {
        v->print();
        std::cout << ",";
    }
    std::cout << ")";
}

value_pair FunctionCall::evaluate()
{
}

AssignmentExp::AssignmentExp(Identifier *name, Expression *R)
{
    id = name;
    RHS = R;
}

void AssignmentExp::print()
{
    id->print();
    std::cout << " = ";
    RHS->print();
}

value_pair AssignmentExp::evaluate()
{
    value_pair result = RHS->evaluate();
    symTable[id->ret_id()] = result;
    return result;
}

AddAssign::AddAssign(Identifier *name, Expression *R)
{
    AssignmentExp(name, R);
}

void AddAssign::print()
{
    id->print();
    std::cout << " += ";
    RHS->print();
}

value_pair AddAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == symTable[id->ret_id()].first)
    {
        if (result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue += result.second.ivalue;
        }
        else if (result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue += result.second.fvalue;
        }
        else if (result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue += result.second.bvalue;
        }
        else if (result.first == STRING_TYPE)
        {
            string s1 = symTable[id->ret_id()].second.svalue;
            string s2 = result.second.svalue;
            s1 += s2;

            symTable[id->ret_id()].second.svalue = strcpy(new char[s1.length() + 1], s1.c_str());
        }
    }
    return symTable[id->ret_id()];
}

SubAssign::SubAssign(Identifier *name, Expression *R)
{
    AssignmentExp(name, R);
}

void SubAssign::print()
{
    id->print();
    std::cout << " -= ";
    RHS->print();
}

value_pair SubAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == symTable[id->ret_id()].first)
    {
        if (result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue -= result.second.ivalue;
        }
        else if (result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue -= result.second.fvalue;
        }
        else if (result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue -= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

MulAssign::MulAssign(Identifier *name, Expression *R)
{
    AssignmentExp(name, R);
}

void MulAssign::print()
{
    id->print();
    std::cout << " *= ";
    RHS->print();
}

value_pair MulAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == symTable[id->ret_id()].first)
    {
        if (result.first == INT_TYPE)
        {
            symTable[id->ret_id()].second.ivalue *= result.second.ivalue;
        }
        else if (result.first == FLOAT_TYPE)
        {
            symTable[id->ret_id()].second.fvalue *= result.second.fvalue;
        }
        else if (result.first == BOOL_TYPE)
        {
            symTable[id->ret_id()].second.bvalue *= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

DivAssign::DivAssign(Identifier *name, Expression *R)
{
    AssignmentExp(name, R);
}

void DivAssign::print()
{
    id->print();
    std::cout << " /= ";
    RHS->print();
}

value_pair DivAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == symTable[id->ret_id()].first)
    {
        if (result.first == INT_TYPE && result.second.ivalue != 0)
        {
            symTable[id->ret_id()].second.ivalue /= result.second.ivalue;
        }
        else if (result.first == FLOAT_TYPE && result.second.fvalue != 0)
        {
            symTable[id->ret_id()].second.fvalue /= result.second.fvalue;
        }
        else if (result.first == BOOL_TYPE && result.second.bvalue != 0)
        {
            symTable[id->ret_id()].second.bvalue /= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

ModAssign::ModAssign(Identifier *name, Expression *R)
{
    AssignmentExp(name, R);
}

void ModAssign::print()
{
    id->print();
    std::cout << " %= ";
    RHS->print();
}

value_pair ModAssign::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == symTable[id->ret_id()].first)
    {
        if (result.first == INT_TYPE && result.second.ivalue != 0)
        {
            symTable[id->ret_id()].second.ivalue %= result.second.ivalue;
        }
        else if (result.first == BOOL_TYPE && result.second.bvalue != 0)
        {
            symTable[id->ret_id()].second.bvalue %= result.second.bvalue;
        }
    }
    return symTable[id->ret_id()];
}

UnaryOperation::UnaryOperation(Expression *R)
{
    RHS = R;
}

BinaryOperation::BinaryOperation(Expression *L, Expression *R)
{
    LHS = L;
    RHS = R;
}

Addition::Addition(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void Addition::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " + ";
    RHS->print();
    std::cout << ")";
}

value_pair Addition::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue + right_eval.second.ivalue;
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue + right_eval.second.fvalue;
        }
        else if (left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue + right_eval.second.bvalue;
        }
        else if (left_eval.first == STRING_TYPE)
        {
            result.first = STRING_TYPE;
            string s1 = left_eval.second.svalue;
            string s2 = right_eval.second.svalue;
            string s = s1 + s2;
            result.second.svalue = strcpy(new char[s.length() + 1], s.c_str());
        }
    }
    return result;
}

Subtraction::Subtraction(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void Subtraction::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " - ";
    RHS->print();
    std::cout << ")";
}

value_pair Subtraction::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue - right_eval.second.ivalue;
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue - right_eval.second.fvalue;
        }
        else if (left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue - right_eval.second.bvalue;
        }
    }
    return result;
}

Multiplication::Multiplication(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void Multiplication::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " * ";
    RHS->print();
    std::cout << ")";
}

value_pair Multiplication::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue * right_eval.second.ivalue;
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue * right_eval.second.fvalue;
        }
        else if (left_eval.first == BOOL_TYPE)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue * right_eval.second.bvalue;
        }
    }
    return result;
}

Division::Division(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void Division::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " / ";
    RHS->print();
    std::cout << ")";
}

value_pair Division::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue / right_eval.second.ivalue;
        }
        else if (left_eval.first == FLOAT_TYPE && right_eval.second.fvalue != 0)
        {
            result.first = FLOAT_TYPE;
            result.second.fvalue = left_eval.second.fvalue / right_eval.second.fvalue;
        }
        else if (left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue / right_eval.second.bvalue;
        }
    }
    return result;
}

ModularDiv::ModularDiv(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void ModularDiv::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " % ";
    RHS->print();
    std::cout << ")";
}

value_pair ModularDiv::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            result.first = INT_TYPE;
            result.second.ivalue = left_eval.second.ivalue % right_eval.second.ivalue;
        }
        else if (left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            result.first = BOOL_TYPE;
            result.second.bvalue = left_eval.second.bvalue % right_eval.second.bvalue;
        }
    }
    return result;
}

UnaryPlus::UnaryPlus(Expression *R)
{
    UnaryOperation(R);
}

void UnaryPlus::print()
{
    std::cout << "+";
    RHS->print();
}

value_pair UnaryPlus::evaluate()
{
    value_pair result = RHS->evaluate();
    return result;
}

UnaryMinus::UnaryMinus(Expression *R)
{
    UnaryOperation(R);
}

void UnaryMinus::print()
{
    std::cout << "-";
    RHS->print();
}

value_pair UnaryMinus::evaluate()
{
    value_pair result = RHS->evaluate();
    if (result.first == INT_TYPE)
    {
        result.second.ivalue = -result.second.ivalue;
    }
    else if (result.first == FLOAT_TYPE)
    {
        result.second.fvalue = -result.second.fvalue;
    }
    else if (result.first == BOOL_TYPE)
    {
        result.second.bvalue = -result.second.bvalue;
    }
    return result;
}

LogicalAND::LogicalAND(Expression *L, Expression *R)
{
    BinaryOperation(L, R);
}

void LogicalAND::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " & ";
    RHS->print();
    std::cout << ")";
}

value_pair LogicalAND::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second && right_eval.second);
    else{} //return error
    return result;
}

LogicalOR::LogicalOR(Expression *L, Expression *R):BinaryOperation(L, R){}
void LogicalOR::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " | ";
    RHS->print();
    std::cout << ")";
}
value_pair LogicalOR::evaluate()
{
    //ill come to this later

    // value_pair left_eval = LHS->evaluate();
    // value_pair right_eval = RHS->evaluate();
    // value_pair result;
    // result.first = BOOL_TYPE;
    // bool left_bool = visit([](auto& a){return a!=0;},left_eval.second);
    // if (is_boolean_operation_valid(left_eval,right_eval))
    // {

    // }
    // else{} //return error
    // return result;
}

LogicalNOT::LogicalNOT(Expression *R):UnaryOperation(R){}

void LogicalNOT::print()
{
    std::cout << "!";
    RHS->print();
}
value_pair LogicalNOT::evaluate()
{
    value_pair result = RHS->evaluate();
    value_pair res;
    res.first = BOOL_TYPE;
    if      (result.first == INT_TYPE)      res.second = ! get<INT_TYPE>(result.second);
    else if (result.first == FLOAT_TYPE)    res.second = ! get<FLOAT_TYPE>(result.second);
    else if (result.first == BOOL_TYPE)     res.second = ! get<BOOL_TYPE>(result.second);
    return res;
}

CompGT::CompGT(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompGT::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " > ";
    RHS->print();
    std::cout << ")";
}
value_pair CompGT::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second > right_eval.second);
    else{} //return error
    return result;
}

CompLT::CompLT(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompLT::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " < ";
    RHS->print();
    std::cout << ")";
}
value_pair CompLT::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second < right_eval.second);
    else{} //return error
    return result;
}

CompGE::CompGE(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompGE::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " >= ";
    RHS->print();
    std::cout << ")";
}

value_pair CompGE::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second >= right_eval.second);
    else{} //return error in comparasion
    return result;
}

CompLE::CompLE(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompLE::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " <= ";
    RHS->print();
    std::cout << ")";
}

value_pair CompLE::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second <= right_eval.second);
    else{} //return error
    return result;
}

CompEQ::CompEQ(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompEQ::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " = ";
    RHS->print();
    std::cout << ")";
}
value_pair CompEQ::evaluate()
{
    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second == right_eval.second);
    else{} //return error
    return result;
}
CompNEQ::CompNEQ(Expression *L, Expression *R):BinaryOperation(L,R){}
void CompNEQ::print()
{
    std::cout << "(";
    LHS->print();
    std::cout << " != ";
    RHS->print();
    std::cout << ")";
}
value_pair CompNEQ::evaluate()
{

    value_pair left_eval = LHS->evaluate();
    value_pair right_eval = RHS->evaluate();
    value_pair result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second != right_eval.second);
    else{} //return error
    return result;
}

/**************************************
 * STATEMENTS
 **************************************/

ExpressionStatement::ExpressionStatement(Expression *e) : exp(e) {}
void ExpressionStatement::print()
{
    std::cout << "Expression Statement:\n{ \n->";
    exp->print();
    std::cout << "\n}\n";
}

Expression *ExpressionStatement::getValue()
{
    return exp;
}

CompoundStatement::CompoundStatement(list<Statement *> l) : stmt_list(l) {}
void CompoundStatement::print()
{
    std::cout << "Compound Statement:\n{";
    for (auto ele : stmt_list)
    {
        std::cout << "\n->";
        ele->print();
    }
    std::cout << "\n}\n";
}

FunctionDeclaration::FunctionDeclaration(Identifier *_name, type _t, list<Identifier *> _arg_list, CompoundStatement *_stmt) : func_name(_name), return_type(_t), arg_list(_arg_list), func_body(_stmt) {}
void FunctionDeclaration::print()
{
    std::cout << "Function Definition:\n{";
    func_name->print();
    std::cout << "\nReturn type : " << enumtypeToString(return_type) << "\n";
    std::cout << "list of arguments";
    for (auto &ele : arg_list)
    {
        std::cout << "\n";
        ele->print();
    }
    std::cout << "\nfunction body:\n";
    func_body->print();
    std::cout << "}";
}

VariableDeclaration::VariableDeclaration(type t, list <Expression*> l): variable_type(t), variable_list(l) {}
void VariableDeclaration::print()
{
    std::cout << "Variable Declaration: {\n";
    std::cout << "type : " << enumtypeToString(variable_type) << '\n';
    std::cout << "list of identifiers";
    for (auto &ele : variable_list)
    {
        ele->print();
        std::cout << "\n";
    }
}

DriverDefinition::DriverDefinition(CompoundStatement *body) : func_body(body) {}
void DriverDefinition::print()
{
    std::cout << "Driver Definition:\n{\n";
    func_body->print();
    std::cout << "\n}\n";
}

VariableInitialization::VariableInitialization(type t, AssignmentExp *e) : variable_type(t), exp(e) {}
void VariableInitialization::print()
{
    std::cout << "Variable Initialisation: \n{\n";
    std::cout << "type: " << enumtypeToString(variable_type) << '\n';
    exp->print();
    std::cout << "}\n";
}

LabeledStatement::LabeledStatement(Expression *lb, Statement *st) : label(lb), stmt(st) {}
void LabeledStatement::print()
{
    std::cout << "Labelled Statement:\n{\n";
    label->print();
    stmt->print();
    std::cout << "\n}\n";
}

CaseLabel::CaseLabel(Expression *lb, Statement *st) : LabeledStatement(lb, st){};
void CaseLabel::print()
{
    std::cout << "Case Label {\n";
    label->print();
    std::cout << "statements:";
    stmt->print();
    std::cout << "\n}\n";
}

DefaultLabel::DefaultLabel(Statement *st) : LabeledStatement(nullptr, st){};
void DefaultLabel::print()
{
    std::cout << "Default Label \n{\n";
    std::cout << "statements:";
    std::cout << "\n";
    stmt->print();
    std::cout << "\n}\n";
}

IterationStatement::IterationStatement(CompoundStatement *b, Expression *cond) : body(b), condition(cond) {}
void IterationStatement::print()
{
    std::cout << "Default Label \n{\n";
    std::cout << "body:\n";
    body->print();
    std::cout << "condition:\n";
    condition->print();
    std::cout << "\n}\n";
}

WhileLoop::WhileLoop(CompoundStatement *b) : IterationStatement(b, nullptr) {}
WhileLoop::WhileLoop(CompoundStatement *b, Expression *cond) : IterationStatement(b, cond) {}
void WhileLoop::print()
{
    std::cout << "While loop:\n{\n";
    std::cout << "condition:\n";
    condition->print();
    std::cout << "body:\n";
    body->print();
    std::cout << "\n}\n";
}

ForLoop::ForLoop(CompoundStatement *b, Expression *cond, Expression *init, Expression *update) : IterationStatement(b, cond), initialization(init), counter_updation(update) {}
void ForLoop::print()
{
    std::cout << "For loop:\n{\n";
    std::cout << "initialisation:\n";
    if (initialization)
        initialization->print();
    else
        std::cout << "empty\n";
    std::cout << "condition:\n";
    if (condition)
        condition->print();
    else
        std::cout << "empty\n";
    std::cout << "update:\n";
    if (counter_updation)
        counter_updation->print();
    else
        std::cout << "empty\n";
    std::cout << "body:\n";
    if (body)
        body->print();
    else
        std::cout << "no body\n";
    std::cout << "\n}\n";
}

// IfElse::IfElse(list <Expression*> l, list <CompoundStatement*> ifs):condition_list(l), if_blocks(ifs){}
IfElse::IfElse(list<Expression *> l, list<CompoundStatement *> ifs, CompoundStatement *elseb = nullptr) : condition_list(l), if_blocks(ifs), else_block(elseb){};
void IfElse::print()
{
    std::cout << "If else block:\n{\n";
    std::cout << "condition list:\n";
    for (auto &ele : condition_list)
    {
        std::cout << "\n";
        ele->print();
    }
    std::cout << "if blocks list:\n";
    for (auto &ele : if_blocks)
    {
        std::cout << "\n";
        ele->print();
    }
    if (else_block)
        else_block->print();
    else
        std::cout << "no else block\n";
    std::cout << "\n}\n";
}

Switch::Switch(Expression *e, list<CaseLabel *> c) : exp(e), cases(c) {}
Switch::Switch(Expression *e, list<CaseLabel *> c, DefaultLabel *_def) : exp(e), cases(c), def(_def) {}
void Switch::print()
{
    std::cout << "switch block:\n{\n";
    std::cout << "expression:\n";
    exp->print();
    std::cout << "cases:\n";
    for (auto &ele : cases)
    {
        std::cout << "\n";
        ele->print();
    }
    if (def)
        def->print();
    else
        std::cout << "no else block\n";
    std::cout << "\n}\n";
}

TernaryOperator::TernaryOperator(Expression *cond, Expression *t_eval, Expression *f_eval) : condition(cond), true_eval(t_eval), false_eval(f_eval) {}
void TernaryOperator::print()
{
    std::cout << "ternary:\n{\n";
    std::cout << "condition:\n";
    condition->print();
    std::cout << "if true:\n";
    true_eval->print();
    std::cout << "if false:\n";
    false_eval->print();
    std::cout << "\n}\n";
}

ReturnStatement::ReturnStatement(Expression *val) : return_val(val) {}
void ReturnStatement::print()
{
    std::cout << "ternary:\n{\nreturns:\n";
    return_val->print();
    std::cout << "\n}\n";
}

/*------------------------------------------------------------------------
 * Program Root Node
 *------------------------------------------------------------------------*/

Program ::Program(list<Statement *> *stmts) : stmt_list(stmts) {}