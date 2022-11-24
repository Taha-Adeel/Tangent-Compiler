// contains implementations of the member methods and constructors in astNodes.h

#include "astNodes.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "symbolTable.h"
extern SymbolTable* cur_symbol_table;

using namespace std;
////////////////////////////////////////////////////
//            AST traversal and evaluation      ////
////////////////////////////////////////////////////

typedef struct YYLTYPE{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	const char *filename;
} YYLTYPE;
std::string toString(const YYLTYPE* loc){
	if(loc == NULL) return "";
	std::stringstream ss; ss << "<" << loc->first_line << "-" << loc->first_column << ".." << loc->last_line << "-" << loc->last_column << ">";
	return ss.str();
}
extern int yyerror(const char *s);
datatype throwError()
{
    datatype e = new error();
    yyerror("Semantic Error: Type mismatch in eval function");
    return e;
}

ASTNode::ASTNode(YYLTYPE* location, string node_name): location(location), node_name(node_name) {
    if(location != NULL) 
        this->location = new YYLTYPE(*location);
}

Identifier::Identifier(YYLTYPE* location, string name, bool class_member)
    :Variable(location, "Identifier"), id(name)
{
    if(class_member) return;
    symbol = cur_symbol_table->lookUp(id);
    if(symbol == NULL) {
        cur_symbol_table->addSymbol(id, "error-type", location, KIND::ERROR);
        symbol = cur_symbol_table->lookUp(id);
        yyerror(("Semantic Error: Identifier " + id + " at " + toString(location) + " is not declared").c_str());
    }
    typename_of_expression = symbol->getTypeName();
}

MemberAccess::MemberAccess(Variable *v, Identifier id, YYLTYPE* location)
    :Variable(location, "MemberAcess"), object(v), member(id)
{
    Symbol* class_name = global_symbol_table.lookUp(object->get_type());
    if(class_name == NULL) {
        yyerror(("Semantic Error: Class " + object->get_type() + " at " + toString(location) + " is not declared").c_str());
        typename_of_expression = "error-type"; return;
    }
    if(class_name->getKind() != KIND::INBUILT_FAMILY && class_name->getKind() != KIND::FAMILY) {
        yyerror(("Semantic Error: Variable of type " + object->get_type() + " at " + toString(location) + " is not an object").c_str());
        typename_of_expression = "error-type"; return;
    }
    Symbol* member_symbol = global_symbol_table.getSymbolTable(object->get_type())->lookUp(member.ret_id());
    if(member_symbol == NULL) {
        yyerror(("Semantic Error: " + toString(location) + ": Family " + object->get_type() + " has no member named " + member.ret_id()).c_str());
        typename_of_expression = "error-type"; return;
    }
    typename_of_expression = member_symbol->getTypeName();
}

AssignmentExp::AssignmentExp(Variable *L, Expression *R, YYLTYPE* location, string name)
    :Expression(location, name), LHS(L), RHS(R)
{
    if(LHS->get_type() != RHS->get_type()){
        stringstream error;
        error << "Semantic Error: Type mismatch in " << name << " at " << toString(location) << ". Expected " << LHS->get_type() << " but got " << RHS->get_type();
        yyerror(error.str().c_str());
    }
}

TernaryOperator::TernaryOperator(Expression *cond, Expression *t_eval, Expression *f_eval, YYLTYPE* location)
    :Expression(location, "TernaryOperator"), condition(cond), true_eval(t_eval), false_eval(f_eval)
{
    if(condition->get_type() != "bool")
        yyerror(("Semantic Error: Condition in ternary operator at " + toString(location) + " must be of type bool.").c_str());
    if(true_eval->get_type() != false_eval->get_type()){
        stringstream error;
        error << "Semantic Error: Type mismatch in ternary operator at " << toString(location) << ". Types found are " << t_eval->get_type() << " are " << f_eval->get_type();
        yyerror(error.str().c_str());
    }
    typename_of_expression = true_eval->get_type();
}

BinaryOperation::BinaryOperation(Expression *L, Expression *R, YYLTYPE* location, string name)
    :Expression(location, name), LHS(L), RHS(R)
{
    if(LHS->get_type() != RHS->get_type()){
        stringstream error;
        error << "Semantic Error: Type mismatch in " << name << " at " << toString(location) << ". Types found are " << LHS->get_type() << " and " << RHS->get_type();
        yyerror(error.str().c_str());
    }
    typename_of_expression = LHS->get_type();
}

/* Evaluate and print functions for Literals*/
datatype Literal::evaluate()
{
    return value;
}

void indent(ostream &out, int indentation){ for (int i = 0; i < indentation; i++) out << "  "; }

void IntegerLiteral::print(ostream& out, int indentation)
{
    indent(out, indentation); out <<"int literal" << toString(location) << "\n{";
    indent(out, indentation+1); out << get<int>(value);
    indent(out, indentation); out <<"\n}\n";
}

void FloatLiteral::print(ostream& out, int indentation)
{
    indent(out, indentation); out <<"float literal" << toString(location) << "\n{";
    indent(out, indentation+1); out << get<float>(value);
    indent(out, indentation); out <<"\n}\n"; 
}

void StringLiteral::print(ostream& out, int indentation)
{
    indent(out, indentation); out<<"string literal" << toString(location) << "\n{";
    indent(out, indentation+1); out << get<string>(value);
    indent(out, indentation); out<<"\n}\n";
}

void BooleanLiteral::print(ostream& out, int indentation) 
{
    indent(out, indentation); out<<"bool literal\n{";
    indent(out, indentation); out << get<bool>(value);
    indent(out, indentation); out<<"\n}\n";
}

void Identifier::print(ostream& out, int indentation)
{
    indent(out, indentation); out<<"Identifier" << toString(location) << "\n{";
    indent(out, indentation+1); out << id;
    indent(out, indentation); out<<"\n}\n";
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

void ArrayAccess::print(ostream& out, int indentation)
{
    indent(out, indentation); out<<"int literal" << toString(location) << "\n{";
    indent(out, indentation);     out<<"array name:\n{";
                                     array_name->print(out, indentation+1);
    indent(out, indentation);     out<<"\n}\n";
    indent(out, indentation);     
    indent(out, indentation);     out<<"index:\n{";
                                     index->print(out, indentation+1);
    indent(out, indentation);     out<<"\n}\n";
    indent(out, indentation); out<<"\n}\n";
}
datatype ArrayAccess::evaluate()
{
    return value;
}

void FunctionCall::print(ostream& out, int indentation)
{
    out<<"function call:" << toString(location) << "\n{";
        func_name->print(out, indentation+1);
        out << "\narguments{\n";
        for (auto const &v : args_list)
        {
            out<<"(\n";
                v->print(out, indentation+1);
            out << "\n)\n";
        }
        out << "}";
    out<<"\n}\n";
    
}
datatype FunctionCall::evaluate()
{
    return datatype(0);//temp
}

void AssignmentExp::print(ostream& out, int indentation)
{
    out<<"assignment expr" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype AssignmentExp::evaluate()
{
    datatype result = RHS->evaluate();
    // store result in the symbol table
    // symTable[id->ret_id()] = result; 
    value = result;
    return value;
}

void AddAssign::print(ostream& out, int indentation)
{
    out<<"add assign" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype AddAssign::evaluate()
{
    return value;
}

void SubAssign::print(ostream& out, int indentation)
{
    out<<"subtract assign" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype SubAssign::evaluate()
{
    return value;
}

void MulAssign::print(ostream& out, int indentation)
{
    out<<"multiply assign" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype MulAssign::evaluate()
{
    return value;
}

void DivAssign::print(ostream& out, int indentation)
{
    out<<"div assign" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype DivAssign::evaluate()
{
    return value;
}

void ModAssign::print(ostream& out, int indentation)
{
    out<<"modulus assign" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype ModAssign::evaluate()
{
    return value;
}

void Addition::print(ostream& out, int indentation)
{
    out<<"addition" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype Addition::evaluate()
{
    return value;
}

void Subtraction::print(ostream& out, int indentation)
{
    out<<"subtraction" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype Subtraction::evaluate()
{
    return value;
}

void Multiplication::print(ostream& out, int indentation)
{
    out<<"multiplication" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype Multiplication::evaluate()
{
    return value;
}

void Division::print(ostream& out, int indentation)
{
    out<<"division" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype Division::evaluate()
{
    return value;
}

void ModularDiv::print(ostream& out, int indentation)
{
    out<<"modular division" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";

}
datatype ModularDiv::evaluate()
{
    return value;
}

void UnaryPlus::print(ostream& out, int indentation)
{
    out<<"Unary +\n" << toString(location) << "{\n";
    exp->print(out, indentation+1);
    out<<"\n}\n";
}
datatype UnaryPlus::evaluate()
{
    return value;
}

void UnaryMinus::print(ostream& out, int indentation)
{
    out<<"Unary -\n" << toString(location) << "{\n";
    exp->print(out, indentation+1);
    out<<"\n}\n";
}
datatype UnaryMinus::evaluate()
{
    return value;
}

void LogicalAND::print(ostream& out, int indentation)
{
    out<<"logical and" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype LogicalAND::evaluate()
{
    return value;
}

void LogicalOR::print(ostream& out, int indentation)
{
    out<<"logical or" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
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

void LogicalNOT::print(ostream& out, int indentation)
{
    out<<"logical not -\n" << toString(location) << "{\n";
    exp->print(out, indentation+1);
    out<<"\n}\n";
}
datatype LogicalNOT::evaluate()
{
    // datatype temp;
    // if(exp->get_type() == TYPE::ERROR)
    //     return throwError();
    // if(exp->get_type() == TYPE::STRING)
    // {
    //     temp = "";
    //     value = (exp->evaluate() == temp) ? true : false;
    // }
    // else if(exp->get_type() == TYPE::FAMILY)
    //     value = false;
    // else if(exp->get_type() == TYPE::INT)
    // {
    //     temp = 0;
    //     value = (exp->evaluate() == temp) ? true : false;
    // }
    // else if(exp->get_type() == TYPE::FLOAT)
    // {
    //     temp = 0.0f;
    //     value = (exp->evaluate() == temp) ? true : false;
    // }
    // else if(exp->get_type() == TYPE::BOOL)
    // {
    //     temp = false;
    //     value = (exp->evaluate() == temp) ? true : false;
    // }
    return value;
}

void CompGT::print(ostream& out, int indentation)
{
    out<<"CompGT" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompGT::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS->evaluate() != RHS->evaluate());
    return value;
}

void CompLT::print(ostream& out, int indentation)
{
    out<<"CompLT" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompLT::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    // value = (LHS < RHS);
    return value;
}

void CompGE::print(ostream& out, int indentation)
{
    out<<"CompGE" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompGE::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS >= RHS);
    return value;
}

void CompLE::print(ostream& out, int indentation)
{
    out<<"CompLE" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompLE::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS <= RHS);
    return value;
}

void CompEQ::print(ostream& out, int indentation)
{
    out<<"CompEQ" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompEQ::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS == RHS);
    return value;
}

void CompNEQ::print(ostream& out, int indentation)
{
    out<<"CompNEQ" << toString(location) << "\n{";
        out<<"LHS\n{\n";
            LHS->print(out, indentation+1);
        out<<"\n}\n";

        out<<"LHS\n{\n";
            RHS->print(out, indentation+1);
        out<<"\n}\n";        
    out<<"\n}\n";
}
datatype CompNEQ::evaluate()
{
    if(LHS->get_type() == "Unknown" || RHS->get_type() == "Unknown" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS != RHS);
    return value;
}

void MemberAccess::print(ostream& out, int indentation)
{
    out<<"Member Access:\n" << toString(location) << "{\n";
    out<<"accessor name:\n";
    object->print(out, indentation+1);
    out<<"\n accessee name :\n";
    member.print(out, indentation+1);
    out<<"\n}\n";
}
datatype MemberAccess::evaluate()
{
    return value;
}


void Arg::print(ostream& out, int indentation)
{

}
datatype Arg::evaluate()
{
    return value;
}

void UnaryIncrement::print(ostream& out, int indentation)
{

}
datatype UnaryIncrement::evaluate()
{
    return value;
}

void PostfixInc::print(ostream& out, int indentation)
{

}
datatype PostfixInc::evaluate()
{
    return value;
}

void PrefixInc::print(ostream& out, int indentation)
{

}
datatype PrefixInc::evaluate()
{
    return value;
}

void UnaryDecrement::print(ostream& out, int indentation)
{

}
datatype UnaryDecrement::evaluate()
{
    return value;
}

void PostfixDec::print(ostream& out, int indentation)
{

}
datatype PostfixDec::evaluate()
{
    return value;
}

void BinaryOperation::print(ostream& out, int indentation)
{

}
datatype BinaryOperation::evaluate()
{
    return value;
}


datatype BooleanLiteral::evaluate()
{
    return value;
}

datatype StringLiteral::evaluate()
{
    return value;
}
datatype FloatLiteral::evaluate()
{
    return value;
}
datatype IntegerLiteral::evaluate()
{
    return value;
}
datatype TernaryOperator::evaluate()
{
    return value;
}

/**************************************
 * STATEMENTS
 **************************************/

void ExpressionStatement::print(ostream& out, int indentation)
{
    out << "Expression Statement:" << toString(location) << "n->{";
    out<<"expressions:\n";
    for(auto &i:*exp)
    {
        out<<"{\n";
        i->print(out, indentation+1);
        out<<"\n}\n";
    }
    out << "\n}\n";
}

vector<Expression *> ExpressionStatement::getValue()
{
    return *exp;
}

void CompoundStatement::print(ostream& out, int indentation)
{
    out << "Compound Statement:" << toString(location) << "\n{";
    for (auto ele : stmt_list)
    {
        out << "\n->";
        ele->print(out, indentation+1);
    }
    out << "\n}\n";
}

void FunctionDeclaration::print(ostream& out, int indentation)
{
    out << "Function Definition:" << toString(location) << "\n{";
    func_name->print(out, indentation+1);
    
    out << "\nReturn type : \n";
    return_type.print(out, indentation+1);
    
    out << "\nlist of arguments\n";
    for (auto &ele : arg_list)
    {
        out << "\n";
        ele->print(out, indentation+1);
    }
    
    out << "\nfunction body:\n";
    func_body->print(out, indentation+1);
    
    out << "\n}\n";
}

void VariableDeclaration::print(ostream& out, int indentation)
{
    out << "Variable Declaration: " << toString(location) << "{\n";
    out << "type : \n";
    variable_type.print(out, indentation+1);

    out << "\nlist of identifiers:\n";
    for (auto &ele : variable_list)
    {
        ele->print(out, indentation+1);
        out << "\n";
    }
    out<<"\n}\n";
}

void DriverDefinition::print(ostream& out, int indentation)
{
    out << "Driver Definition:\n" << toString(location) << "{\n";
    func_body->print(out, indentation+1);
    out << "\n}\n";
}

void VariableInitialization::print(ostream& out, int indentation)
{
    out << "Variable Initialisation: \n" << toString(location) << "{\n";
    out << "type: \n";
    variable_type.print(out, indentation+1);
    out<<"initialisation:\n";
    exp->print(out, indentation+1);
    out << "}\n";
}

void LabeledStatement::print(ostream& out, int indentation)
{
    out << "Labelled Statement:\n" << toString(location) << "{\n";
    label->print(out, indentation+1);
    stmt->print(out, indentation+1);
    out << "\n}\n";
}

void CaseLabel::print(ostream& out, int indentation)
{
    out << "Case Label " << toString(location) << "{\n";
    label->print(out, indentation+1);
    out << "statements:";
    stmt->print(out, indentation+1);
    out << "\n}\n";
}

void DefaultLabel::print(ostream& out, int indentation)
{
    out << "Default Label \n" << toString(location) << "{\n";
    out << "statements:";
    out << "\n";
    stmt->print(out, indentation+1);
    out << "\n}\n";
}

void IterationStatement::print(ostream& out, int indentation)
{
    out << "Default Label \n" << toString(location) << "{\n";
    out << "body:\n";
    body->print(out, indentation+1);
    out << "condition:\n";
    condition->print(out, indentation+1);
    out << "\n}\n";
}

void WhileLoop::print(ostream& out, int indentation)
{
    out << "While loop:\n" << toString(location) << "{\n";
    out << "condition:\n";
    condition->print(out, indentation+1);
    out << "body:\n";
    body->print(out, indentation+1);
    out << "\n}\n";
}

void ForLoop::print(ostream& out, int indentation)
{
    out << "For loop:\n" << toString(location) << "{\n";
    out << "initialisation:\n";
    if (initialization)
        initialization->print(out, indentation+1);
    else
        out << "empty\n";
    out << "condition:\n";
    if (condition)
        condition->print(out, indentation+1);
    else
        out << "empty\n";
    out << "update:\n";
    if (counter_updation)
        counter_updation->print(out, indentation+1);
    else
        out << "empty\n";
    out << "body:\n";
    if (body)
        body->print(out, indentation+1);
    else
        out << "no body\n";
    out << "\n}\n";
}

void IfStatement::print(ostream& out, int indentation)
{
    out << "If statement: \n" << toString(location) << "{\n";
    out << "condition :\n";
    condition->print(out, indentation+1);
    if(if_block)
    {
        out << "If block:\n";
        if_block->print(out, indentation+1);
    }
    out << "\n}\n";
}

void IfElseStatement::print(ostream& out, int indentation)
{
    out << "If else block:\n" << toString(location) << "{\n";
    
    out << "condition :\n";
    if_condition->print(out, indentation+1);

    if(if_block)
    {
        out<<"If block:\n";
        if_block->print(out, indentation+1);
    }

    if(else_block)
    {
        out<<"else block:\n";
        else_block->print(out, indentation+1);
    }
    
    out << "\n}\n";
}

void SwitchStatement::print(ostream& out, int indentation)
{
    out << "switch block:\n" << toString(location) << "{\n";
    out << "expression:\n";
    exp->print(out, indentation+1);
    out << "cases:\n";
    if(block)block->print(out, indentation+1);
    out << "\n}\n";
}

void TernaryOperator::print(ostream& out, int indentation)
{
    out << "ternary:\n" << toString(location) << "{\n";
    out << "condition:\n";
    condition->print(out, indentation+1);
    out << "if true:\n";
    true_eval->print(out, indentation+1);
    out << "if false:\n";
    false_eval->print(out, indentation+1);
    out << "\n}\n";
}

void ReturnStatement::print(ostream& out, int indentation)
{
    out << "ternary:\n{\nreturns" << toString(location) << ":\n";
    return_val->print(out, indentation+1);
    out << "\n}\n";
}

void FamilyMembers::print(ostream& out, int indentation)
{

}
void FamilyDecl::print(ostream& out, int indentation)
{

}
void ContinueStatement::print(ostream& out, int indentation)
{

}
void BreakStatement::print(ostream& out, int indentation)
{

}
void ConstructorDeclaration::print(ostream& out, int indentation)
{

}

void Program::print(ostream& out, int indentation)
{
    out << "Program:\n" << toString(location) << "{\n";
    out << "global declarations:\n";
    for (auto &ele : *stmt_list)
    {
        ele->print(out, indentation+1);
        out << "\n";
    }
    out << "\n}\n";
}



/*------------------------------------------------------------------------
 *  Functions to print the AST
 *------------------------------------------------------------------------*/

void ASTNode::print(ostream& out, int indentation){
    for(int i = 0; i < indentation-1; i++)
		cout << '\t';
	if(indentation) out << "  ->";
    out << this->node_name << " " << this << " " << toString(location) << "\n";
}