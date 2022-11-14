// contains implementations of the member methods and constructors in astNodes.h

#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>


/////////////////////////////////
//      UTILITY FUNCTIONS      //
/////////////////////////////////
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
// bool is_unary_operation_valid(value_pair& a)
// {
//     if( a.first==INT_TYPE||
//         a.first==FLOAT_TYPE||
//         a.first==BOOL_TYPE)
//         return true;
//     return false;
//}
bool is_valid_for_boolean_operation(value_pair& a, value_pair& b)
{
    return is_unary_operation_valid(a)&&is_unary_operation_valid(b);
}


////////////////////////////////////////////////////
//            AST FUNCTION DEFINITION           ////
////////////////////////////////////////////////////

void IntegerLiteral::print()
{
    std::cout << value.second.ivalue;
}
value_pair IntegerLiteral::evaluate()
{
    std::cout << "Integer node: operand = " << value.second.ivalue << endl;
    return value;
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

void StringLiteral::print()
{
    std::cout << value.second.svalue;
}
value_pair StringLiteral::evaluate()
{
    std::cout << "String node: operand = " << value.second.svalue << endl;
    return value;
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

void ArrayAccess::print()
{
    array_name->print();
    std::cout << "[" << index << "]";
}
value_pair ArrayAccess::evaluate()
{
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

void DriverDefinition::print()
{
    std::cout << "Driver Definition:\n{\n";
    func_body->print();
    std::cout << "\n}\n";
}

void VariableInitialization::print()
{
    std::cout << "Variable Initialisation: \n{\n";
    std::cout << "type: " << enumtypeToString(variable_type) << '\n';
    exp->print();
    std::cout << "}\n";
}

void LabeledStatement::print()
{
    std::cout << "Labelled Statement:\n{\n";
    label->print();
    stmt->print();
    std::cout << "\n}\n";
}

void CaseLabel::print()
{
    std::cout << "Case Label {\n";
    label->print();
    std::cout << "statements:";
    stmt->print();
    std::cout << "\n}\n";
}

void DefaultLabel::print()
{
    std::cout << "Default Label \n{\n";
    std::cout << "statements:";
    std::cout << "\n";
    stmt->print();
    std::cout << "\n}\n";
}

void IterationStatement::print()
{
    std::cout << "Default Label \n{\n";
    std::cout << "body:\n";
    body->print();
    std::cout << "condition:\n";
    condition->print();
    std::cout << "\n}\n";
}

void WhileLoop::print()
{
    std::cout << "While loop:\n{\n";
    std::cout << "condition:\n";
    condition->print();
    std::cout << "body:\n";
    body->print();
    std::cout << "\n}\n";
}

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

void ReturnStatement::print()
{
    std::cout << "ternary:\n{\nreturns:\n";
    return_val->print();
    std::cout << "\n}\n";
}

/*------------------------------------------------------------------------
 * Program Root Node
 *------------------------------------------------------------------------*/