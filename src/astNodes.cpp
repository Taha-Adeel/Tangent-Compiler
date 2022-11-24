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
datatype throwError(){
    datatype e = new error();
    yyerror("Semantic Error: Type mismatch in eval function");
    return e;
}

/////////////////////////////////////////////////////////////////
//       AST Constructors with semantic error handeling      ////
/////////////////////////////////////////////////////////////////

ASTNode::ASTNode(YYLTYPE* location, string node_name): location(location), node_name(node_name) {
    if(location != NULL) 
        this->location = new YYLTYPE(*location);
}
ostream* ASTNode::out_file = &cout;

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

////////////////////////////////////////////////////
//          AST expressions eval functions      ////
////////////////////////////////////////////////////

/* Evaluate and print functions for Literals*/
datatype Literal::evaluate()
{
    return value;
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

datatype ArrayAccess::evaluate()
{
    return value;
}

datatype FunctionCall::evaluate()
{
    return datatype(0);//temp
}

datatype AssignmentExp::evaluate()
{
    datatype result = RHS->evaluate();
    // store result in the symbol table
    // symTable[id->ret_id()] = result; 
    value = result;
    return value;
}

datatype AddAssign::evaluate()
{
    return value;
}

datatype SubAssign::evaluate()
{
    return value;
}

datatype MulAssign::evaluate()
{
    return value;
}

datatype DivAssign::evaluate()
{
    return value;
}

datatype ModAssign::evaluate()
{
    return value;
}

datatype Addition::evaluate()
{
    return value;
}

datatype Subtraction::evaluate()
{
    return value;
}

datatype Multiplication::evaluate()
{
    return value;
}

datatype Division::evaluate()
{
    return value;
}

datatype ModularDiv::evaluate()
{
    return value;
}

datatype UnaryPlus::evaluate()
{
    return value;
}

datatype UnaryMinus::evaluate()
{
    return value;
}

datatype LogicalAND::evaluate()
{
    return value;
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

datatype CompGT::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS->evaluate() != RHS->evaluate());
    return value;
}

datatype CompLT::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    // value = (LHS < RHS);
    return value;
}

datatype CompGE::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS >= RHS);
    return value;
}

datatype CompLE::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS <= RHS);
    return value;
}

datatype CompEQ::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS == RHS);
    return value;
}

datatype CompNEQ::evaluate()
{
    if(LHS->get_type() == "error-type" || RHS->get_type() == "error-type" || LHS->get_type() != RHS->get_type())
        return throwError();
    if(cur_symbol_table->lookUp(LHS->get_type())->getKind() != KIND::INBUILT_PRIMITIVE_TYPE)
        return throwError(); // can't perform comparison for these types
    // value = (LHS != RHS);
    return value;
}

datatype MemberAccess::evaluate()
{
    return value;
}

datatype Arg::evaluate()
{
    return value;
}

datatype UnaryIncrement::evaluate()
{
    return value;
}

datatype PostfixInc::evaluate()
{
    return value;
}

datatype PrefixInc::evaluate()
{
    return value;
}

datatype UnaryDecrement::evaluate()
{
    return value;
}

datatype PostfixDec::evaluate()
{
    return value;
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

vector<Expression *> ExpressionStatement::getValue()
{
    return *exp;
}

///////////////////////////////////////////////////////////
////      Functions to traverse and print the AST      ////
///////////////////////////////////////////////////////////

void ASTNode::indent(int indentation){
    for (int i = 0; i < indentation; i++)
        *out_file << "  ";
}

void ASTNode::print(int indentation, ostream& out){
    out_file = &out;
	if(indentation) 
        indent(indentation-1), out << "  `-";
    out << this->node_name << " " << this << " " << toString(location) << " ";

    printData(); out << "\n";
    printMembers(indentation+1);
}

void Expression::printData(){
    // *out_file << "value: " << value;
}

void IntegerLiteral::printData(){
    *out_file << "value: " << get<int>(value);
}

void FloatLiteral::printData(){
    *out_file << "value: " << get<float>(value);
}

void StringLiteral::printData(){
    *out_file << "value: " << get<string>(value);
}

void BooleanLiteral::printData(){
    *out_file << "value: " << get<bool>(value);
}

void Identifier::printData(){
    *out_file << ret_id();
}

void MemberAccess::printMembers(int indentation){
    indent(indentation); *out_file << "object: " << "\n";
    object->print(indentation+1);
    indent(indentation); *out_file << "member: " << "\n";
    member.print(indentation+1);
}

void ArrayAccess::printMembers(int indentation){
    indent(indentation); *out_file << "array name: " << "\n";
    array_name->print(indentation+1);
    indent(indentation); *out_file << "index: " << "\n";
    index->print(indentation+1);
}

void Arg::printMembers(int indentation){
    indent(indentation); *out_file << "type: "; t.print();
    indent(indentation); *out_file << "name: "; id.print();
}

void FunctionCall::printMembers(int indentation){
    indent(indentation); *out_file << "arguments: " << "\n";
    for (auto &ele : args_list)
        ele->print(indentation+1);
}

void AssignmentExp::printMembers(int indentation){
    indent(indentation); *out_file << "lhs: " << "\n";
    LHS->print(indentation+1);
    indent(indentation); *out_file << "rhs: " << "\n";
    RHS->print(indentation+1);
}

void TernaryOperator::printMembers(int indentation){
    indent(indentation); *out_file << "condition: " << "\n";
    condition->print(indentation+1);
    indent(indentation); *out_file << "if true: " << "\n";
    true_eval->print(indentation+1);
    indent(indentation); *out_file << "if false: " << "\n";
    false_eval->print(indentation+1);
}

void BinaryOperation::printMembers(int indentation){
    indent(indentation); *out_file << "lhs: " << "\n";
    LHS->print(indentation+1);
    indent(indentation); *out_file << "rhs: " << "\n";
    RHS->print(indentation+1);
}

void ExpressionStatement::printMembers(int indentation){
    indent(indentation); *out_file << "expression list: " << "\n";
    for(auto& ele : *exp)
        ele->print(indentation+1);
}

void CompoundStatement::printMembers(int indentation){
    indent(indentation); *out_file << "statements: " << "\n";
    for(auto& ele : stmt_list)
        ele->print(indentation+1);
}

void FamilyMembers::printMembers(int indentation){
    indent(indentation); *out_file << "member: "; member->print();
}

void FamilyDecl::printData(){
    *out_file << "name: "; fam_name.print();
}

void FamilyDecl::printMembers(int indentation){
    indent(indentation); *out_file << "members: " << "\n";
    for(auto& ele : members)
        ele->print(indentation+1);
}

void ConstructorDeclaration::printMembers(int indentation){
    indent(indentation); *out_file << "arguments: " << "\n";
    for(auto& ele : arg_list)
        ele->print(indentation+1);
    indent(indentation); *out_file << "body: " << "\n";
    body->print(indentation+1);
}

void FunctionDeclaration::printMembers(int indentation){
    indent(indentation); *out_file << "name: "; func_name->print();
    indent(indentation); *out_file << "arguments: " << "\n";
    for(auto& ele : arg_list)
        ele->print(indentation+1);
    indent(indentation); *out_file << "body: " << "\n";
    func_body->print(indentation+1);
}

void VariableDeclaration::printMembers(int indentation){
    indent(indentation); *out_file << "Declaration typename: "; variable_type.print();
    indent(indentation); *out_file << "New variables: " << "\n";
    for(auto& ele : variable_list)
        ele->print(indentation+1);
}

void DriverDefinition::printMembers(int indentation){
    indent(indentation); *out_file << "body: " << "\n";
    func_body->print(indentation+1);
}

void VariableInitialization::printMembers(int indentation){
    indent(indentation); *out_file << "Declaration typename: "; variable_type.print();
    exp->print(indentation+1);
}

void LabeledStatement::printMembers(int indentation){
    indent(indentation); *out_file << "label: "; label->print();
    indent(indentation); *out_file << "statement: " << "\n";
    stmt->print(indentation+1);
}

void IterationStatement::printMembers(int indentation){
    indent(indentation); *out_file << "condition: " << "\n";
    condition->print(indentation+1);
    indent(indentation); *out_file << "body: " << "\n";
    body->print(indentation+1);
}

void ForLoop::printMembers(int indentation){
    indent(indentation); *out_file << "initialization: " << "\n";
    initialization->print(indentation+1);
    indent(indentation); *out_file << "condition: " << "\n";
    condition->print(indentation+1);
    indent(indentation); *out_file << "counter updation: " << "\n";
    counter_updation->print(indentation+1);
    indent(indentation); *out_file << "body: " << "\n";
    body->print(indentation+1);
}

void IfStatement::printMembers(int indentation){
    indent(indentation); *out_file << "condition: " << "\n";
    condition->print(indentation+1);
    indent(indentation); *out_file << "if block: " << "\n";
    if_block->print(indentation+1);
}

void IfElseStatement::printMembers(int indentation){
    indent(indentation); *out_file << "condition: " << "\n";
    if_condition->print(indentation+1);
    indent(indentation); *out_file << "if block: " << "\n";
    if_block->print(indentation+1);
    indent(indentation); *out_file << "else block: " << "\n";
    else_block->print(indentation+1);
}

void SwitchStatement::printMembers(int indentation){
    indent(indentation); *out_file << "condition: " << "\n";
    exp->print(indentation+1);
    indent(indentation); *out_file << "body: " << "\n";
    block->print(indentation+1);
}

void ReturnStatement::printMembers(int indentation){
    indent(indentation); *out_file << "return expression: " << "\n";
    return_val->print(indentation+1);
}

void Program::printMembers(int indentation){
    *out_file << "declarations: " << "\n";
    for(auto& ele : *stmt_list)
        ele->print(indentation);
}