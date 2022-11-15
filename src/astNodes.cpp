// contains implementations of the member methods and constructors in astNodes.h

#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
using namespace std;

////////////////////////////////////////////////////
//            AST FUNCTION DEFINITION           ////
////////////////////////////////////////////////////

/* Function to return the type of an expression*/
TYPE Expression::get_type()
{
    int t = value.index();
    switch (t)
    {
    case 0:
        return TYPE::INT;
    case 1:
        return TYPE::FLOAT;
    case 2:
        return TYPE::STRING;
    case 3:
        return TYPE::BOOL;
    default:
        return TYPE::VOID;
    }
}

/* Evaluate and print functions for Literals*/
datatype Literal::evaluate()
{
    return value;
}

void IntegerLiteral::print()
{
    cout << get<int>(value);
}
void FloatLiteral::print()
{
    cout << get<float>(value);
}
void StringLiteral::print()
{
    cout << get<string>(value);
}
void BooleanLiteral::print()
{
    cout << get<bool>(value);
}

void Identifier::print()
{
    cout << id;
}

string Identifier::ret_id()
{
    return id;
}
datatype Identifier::evaluate()
{
    // use symbol table
    return value;
}

void ArrayAccess::print()
{
    array_name->print();
    cout << "[" << index << "]";
}
datatype ArrayAccess::evaluate()
{
    return value;
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
datatype FunctionCall::evaluate()
{

}

void AssignmentExp::print()
{
    LHS->print();
    cout << " = ";
    RHS->print();
}
datatype AssignmentExp::evaluate()
{
    datatype result = RHS->evaluate();
    // store result in the symbol table
    // symTable[id->ret_id()] = result; 
    value = result;
    return value;
}

void AddAssign::print()
{
    LHS->print();
    cout << " += ";
    RHS->print();
}
datatype AddAssign::evaluate()
{
    datatype result = RHS->evaluate();
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

void SubAssign::print()
{
    LHS->print();
    cout << " -= ";
    RHS->print();
}
datatype SubAssign::evaluate()
{
    datatype result = RHS->evaluate();
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

void MulAssign::print()
{
    LHS->print();
    cout << " *= ";
    RHS->print();
}
datatype MulAssign::evaluate()
{
    datatype result = RHS->evaluate();
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

void DivAssign::print()
{
    LHS->print();
    cout << " /= ";
    RHS->print();
}
datatype DivAssign::evaluate()
{
    datatype result = RHS->evaluate();
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

void ModAssign::print()
{
    LHS->print();
    cout << " %= ";
    RHS->print();
}
datatype ModAssign::evaluate()
{
    datatype result = RHS->evaluate();
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

void Addition::print()
{
    cout << "(";
    LHS->print();
    cout << " + ";
    RHS->print();
    cout << ")";
}
datatype Addition::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
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

void Subtraction::print()
{
    cout << "(";
    LHS->print();
    cout << " - ";
    RHS->print();
    cout << ")";
}
datatype Subtraction::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
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

void Multiplication::print()
{
    cout << "(";
    LHS->print();
    cout << " * ";
    RHS->print();
    cout << ")";
}
datatype Multiplication::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
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

void Division::print()
{
    cout << "(";
    LHS->print();
    cout << " / ";
    RHS->print();
    cout << ")";
}
datatype Division::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
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

void ModularDiv::print()
{
    cout << "(";
    LHS->print();
    cout << " % ";
    RHS->print();
    cout << ")";
}
datatype ModularDiv::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
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

void UnaryPlus::print()
{
    cout << "+";
    RHS->print();
}
datatype UnaryPlus::evaluate()
{
    datatype result = RHS->evaluate();
    return result;
}

void UnaryMinus::print()
{
    cout << "-";
    RHS->print();
}
datatype UnaryMinus::evaluate()
{
    datatype result = RHS->evaluate();
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

void LogicalAND::print()
{
    cout << "(";
    LHS->print();
    cout << " & ";
    RHS->print();
    cout << ")";
}
datatype LogicalAND::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second && right_eval.second);
    else{} //return error
    return result;
}

void LogicalOR::print()
{
    cout << "(";
    LHS->print();
    cout << " | ";
    RHS->print();
    cout << ")";
}
datatype LogicalOR::evaluate()
{
    //ill come to this later

    // datatype left_eval = LHS->evaluate();
    // datatype right_eval = RHS->evaluate();
    // datatype result;
    // result.first = BOOL_TYPE;
    // bool left_bool = visit([](auto& a){return a!=0;},left_eval.second);
    // if (is_boolean_operation_valid(left_eval,right_eval))
    // {

    // }
    // else{} //return error
    // return result;
}

void LogicalNOT::print()
{
    cout << "!";
    RHS->print();
}
datatype LogicalNOT::evaluate()
{
    datatype result = RHS->evaluate();
    datatype res;
    res.first = BOOL_TYPE;
    if      (result.first == INT_TYPE)      res.second = ! get<INT_TYPE>(result.second);
    else if (result.first == FLOAT_TYPE)    res.second = ! get<FLOAT_TYPE>(result.second);
    else if (result.first == BOOL_TYPE)     res.second = ! get<BOOL_TYPE>(result.second);
    return res;
}

void CompGT::print()
{
    cout << "(";
    LHS->print();
    cout << " > ";
    RHS->print();
    cout << ")";
}
datatype CompGT::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second > right_eval.second);
    else{} //return error
    return result;
}

void CompLT::print()
{
    cout << "(";
    LHS->print();
    cout << " < ";
    RHS->print();
    cout << ")";
}
datatype CompLT::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second < right_eval.second);
    else{} //return error
    return result;
}

void CompGE::print()
{
    cout << "(";
    LHS->print();
    cout << " >= ";
    RHS->print();
    cout << ")";
}
datatype CompGE::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second >= right_eval.second);
    else{} //return error in comparasion
    return result;
}

void CompLE::print()
{
    cout << "(";
    LHS->print();
    cout << " <= ";
    RHS->print();
    cout << ")";
}
datatype CompLE::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second <= right_eval.second);
    else{} //return error
    return result;
}

void CompEQ::print()
{
    cout << "(";
    LHS->print();
    cout << " = ";
    RHS->print();
    cout << ")";
}
datatype CompEQ::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second == right_eval.second);
    else{} //return error
    return result;
}

void CompNEQ::print()
{
    cout << "(";
    LHS->print();
    cout << " != ";
    RHS->print();
    cout << ")";
}
datatype CompNEQ::evaluate()
{
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    datatype result;
    result.first = BOOL_TYPE;
    if (is_valid_comparasion(left_eval,right_eval))
        result.second = bool(left_eval.second != right_eval.second);
    else{} //return error
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

Expression *ExpressionStatement::getValue()
{
    return exp;
}

void CompoundStatement::print()
{
    cout << "Compound Statement:\n{";
    for (auto ele : stmt_list)
    {
        cout << "\n->";
        ele->print();
    }
    cout << "\n}\n";
}

void FunctionDeclaration::print()
{
    cout << "Function Definition:\n{";
    func_name->print();
    cout << "\nReturn type : " << enumtypeToString(return_type) << "\n";
    cout << "list of arguments";
    for (auto &ele : arg_list)
    {
        cout << "\n";
        ele->print();
    }
    cout << "\nfunction body:\n";
    func_body->print();
    cout << "}";
}

void VariableDeclaration::print()
{
    cout << "Variable Declaration: {\n";
    cout << "type : " << enumtypeToString(variable_type) << '\n';
    cout << "list of identifiers";
    for (auto &ele : variable_list)
    {
        ele->print();
        cout << "\n";
    }
}

void DriverDefinition::print()
{
    cout << "Driver Definition:\n{\n";
    func_body->print();
    cout << "\n}\n";
}

void VariableInitialization::print()
{
    cout << "Variable Initialisation: \n{\n";
    cout << "type: " << enumtypeToString(variable_type) << '\n';
    exp->print();
    cout << "}\n";
}

void LabeledStatement::print()
{
    cout << "Labelled Statement:\n{\n";
    label->print();
    stmt->print();
    cout << "\n}\n";
}

void CaseLabel::print()
{
    cout << "Case Label {\n";
    label->print();
    cout << "statements:";
    stmt->print();
    cout << "\n}\n";
}

void DefaultLabel::print()
{
    cout << "Default Label \n{\n";
    cout << "statements:";
    cout << "\n";
    stmt->print();
    cout << "\n}\n";
}

void IterationStatement::print()
{
    cout << "Default Label \n{\n";
    cout << "body:\n";
    body->print();
    cout << "condition:\n";
    condition->print();
    cout << "\n}\n";
}

void WhileLoop::print()
{
    cout << "While loop:\n{\n";
    cout << "condition:\n";
    condition->print();
    cout << "body:\n";
    body->print();
    cout << "\n}\n";
}

void ForLoop::print()
{
    cout << "For loop:\n{\n";
    cout << "initialisation:\n";
    if (initialization)
        initialization->print();
    else
        cout << "empty\n";
    cout << "condition:\n";
    if (condition)
        condition->print();
    else
        cout << "empty\n";
    cout << "update:\n";
    if (counter_updation)
        counter_updation->print();
    else
        cout << "empty\n";
    cout << "body:\n";
    if (body)
        body->print();
    else
        cout << "no body\n";
    cout << "\n}\n";
}

void IfElse::print()
{
    cout << "If else block:\n{\n";
    cout << "condition list:\n";
    for (auto &ele : condition_list)
    {
        cout << "\n";
        ele->print();
    }
    cout << "if blocks list:\n";
    for (auto &ele : if_blocks)
    {
        cout << "\n";
        ele->print();
    }
    if (else_block)
        else_block->print();
    else
        cout << "no else block\n";
    cout << "\n}\n";
}

void Switch::print()
{
    cout << "switch block:\n{\n";
    cout << "expression:\n";
    exp->print();
    cout << "cases:\n";
    for (auto &ele : cases)
    {
        cout << "\n";
        ele->print();
    }
    if (def)
        def->print();
    else
        cout << "no else block\n";
    cout << "\n}\n";
}

void TernaryOperator::print()
{
    cout << "ternary:\n{\n";
    cout << "condition:\n";
    condition->print();
    cout << "if true:\n";
    true_eval->print();
    cout << "if false:\n";
    false_eval->print();
    cout << "\n}\n";
}

void ReturnStatement::print()
{
    cout << "ternary:\n{\nreturns:\n";
    return_val->print();
    cout << "\n}\n";
}

/*------------------------------------------------------------------------
 * Program Root Node
 *------------------------------------------------------------------------*/