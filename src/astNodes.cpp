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


TYPE Expression::get_type()
{
    return TYPE{(int)value.index()};
}


/* Evaluate and print functions for Literals*/
datatype Literal::evaluate()
{
    return value;
}

void IntegerLiteral::print()
{
    cout<<"int literal\n{";
    cout << get<int>(value);
    cout<<"\n}\n";
}
void FloatLiteral::print()
{
    cout<<"float literal\n{";
    cout << get<float>(value);
    cout<<"\n}\n";
}
void StringLiteral::print()
{
    cout<<"string literal\n{";
    cout << get<string>(value);
    cout<<"\n}\n";
}
void BooleanLiteral::print()
{
    cout<<"bool literal\n{";
    cout << get<bool>(value);
    cout<<"\n}\n";
}

void Identifier::print()
{
    cout<<"Identifier\n{";
    cout << id;
    cout<<"\n}\n";
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
    cout<<"int literal\n{";
        cout<<"array name:\n{";
            array_name->print();
        cout<<"\n}\n";
        
        cout<<"index:\n{";
            index->print();
        cout<<"\n}\n";
    cout<<"\n}\n";
}
datatype ArrayAccess::evaluate()
{
    return value;
}

void FunctionCall::print()
{
    cout<<"function call:\n{";
        func_name->print();
        cout << "\narguments{\n";
        for (auto const &v : args_list)
        {
            cout<<"(\n";
                v->print();
            cout << "\n)\n";
        }
        cout << "}";
    cout<<"\n}\n";
    
}
datatype FunctionCall::evaluate()
{
    return datatype(0);//temp
}

void AssignmentExp::print()
{
    cout<<"assignment expr\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
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
    cout<<"add assign\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype AddAssign::evaluate()
{
    return value;
}

void SubAssign::print()
{
    cout<<"subtract assign\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype SubAssign::evaluate()
{
    return value;
}

void MulAssign::print()
{
    cout<<"multiply assign\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype MulAssign::evaluate()
{
    return value;
}

void DivAssign::print()
{
    cout<<"div assign\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype DivAssign::evaluate()
{
    return value;
}

void ModAssign::print()
{
    cout<<"modulus assign\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype ModAssign::evaluate()
{
    return value;
}

void Addition::print()
{
    cout<<"addition\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype Addition::evaluate()
{
    return value;
}

void Subtraction::print()
{
    cout<<"subtraction\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype Subtraction::evaluate()
{
    return value;
}

void Multiplication::print()
{
    cout<<"multiplication\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype Multiplication::evaluate()
{
    return value;
}

void Division::print()
{
    cout<<"division\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype Division::evaluate()
{
    return value;
}

void ModularDiv::print()
{
    cout<<"modular division\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";

}
datatype ModularDiv::evaluate()
{
    return value;
}

void UnaryPlus::print()
{
    cout<<"Unary +\n{\n";
    exp->print();
    cout<<"\n}\n";
}
datatype UnaryPlus::evaluate()
{
    return value;
}

void UnaryMinus::print()
{
    cout<<"Unary -\n{\n";
    exp->print();
    cout<<"\n}\n";
}
datatype UnaryMinus::evaluate()
{
    return value;
}

void LogicalAND::print()
{
    cout<<"logical and\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype LogicalAND::evaluate()
{
    return value;
}

void LogicalOR::print()
{
    cout<<"logical or\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
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
    return value;
}

void LogicalNOT::print()
{
    cout<<"logical not -\n{\n";
    exp->print();
    cout<<"\n}\n";
}
datatype LogicalNOT::evaluate()
{
    return value;
}

void CompGT::print()
{
    cout<<"CompGT\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompGT::evaluate()
{
    return value;
}

void CompLT::print()
{
    cout<<"CompLT\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompLT::evaluate()
{
    return value;
}

void CompGE::print()
{
    cout<<"CompGE\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompGE::evaluate()
{
    return value;
}

void CompLE::print()
{
    cout<<"CompLE\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompLE::evaluate()
{
    return value;
}

void CompEQ::print()
{
    cout<<"CompEQ\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompEQ::evaluate()
{
    return value;
}

void CompNEQ::print()
{
    cout<<"CompNEQ\n{";
        cout<<"LHS\n{\n";
            LHS->print();
        cout<<"\n}\n";

        cout<<"LHS\n{\n";
            RHS->print();
        cout<<"\n}\n";        
    cout<<"\n}\n";
}
datatype CompNEQ::evaluate()
{
    return value;
}

/**************************************
 * STATEMENTS
 **************************************/

void ExpressionStatement::print()
{
    cout << "Expression Statement:\n{ \n->";
    cout<<"expressions:\n";
    for(auto &i:*exp)
    {
        cout<<"{\n";
        i->print();
        cout<<"\n}\n";
    }
    cout << "\n}\n";
}

list<Expression *> ExpressionStatement::getValue()
{
    return *exp;
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
    
    cout << "\nReturn type : \n";
    return_type.print();
    
    cout << "\nlist of arguments\n";
    for (auto &ele : arg_list)
    {
        cout << "\n";
        ele->print();
    }
    
    cout << "\nfunction body:\n";
    func_body->print();
    
    cout << "\n}\n";
}

void VariableDeclaration::print()
{
    cout << "Variable Declaration: {\n";
    cout << "type : \n";
    variable_type.print();

    cout << "\nlist of identifiers:\n";
    for (auto &ele : variable_list)
    {
        ele->print();
        cout << "\n";
    }
    cout<<"\n}\n";
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
    cout << "type: \n";
    variable_type.print();
    cout<<"initialisation:\n";
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

void IfElseStatement::print()
{
    cout << "If else block:\n{\n";
    
    cout << "condition :\n";
    if_condition->print();

    if(if_block)
    {
        cout<<"If block:\n";
        if_block->print();
    }

    if(else_block)
    {
        cout<<"else block:\n";
        else_block->print();
    }
    
    cout << "\n}\n";
}

void SwitchStatement::print()
{
    cout << "switch block:\n{\n";
    cout << "expression:\n";
    exp->print();
    cout << "cases:\n";
    if(block)block->print();
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