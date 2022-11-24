#ifndef ASTNODES_H
#define ASTNODES_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>

// #include <llvm/IR/Value.h>

#include "symbolTable.h"
extern SymbolTable global_symbol_table;
extern SymbolTable *cur_symbol_table;
using namespace std;

/*------------------------------------------------------------------------
 * Defining the Class Hierarchy

 *------------------------------------------------------------------------*/

/**
 * @brief Base Class for all NOdes in AST
 * 
 */
class ASTNode
{
protected:
    string node_name = "ASTNode";
    YYLTYPE* location = NULL;
public:
    ASTNode(YYLTYPE* location = NULL, string node_name = "ASTNode");
    /// @brief prints the description/properties/value of the current node
    virtual void print(ostream& out_file, int indentation = 0);
};

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/

/**
 * @brief Base Class for all Expression Nodes
 * 
 */
class Expression : public ASTNode
{
protected:
    datatype value;   ///holds the value of the current node as pair of Identifier of value and the actual value

public:
    Expression(YYLTYPE* _location = NULL, string node_name = "Expression"):ASTNode(location, node_name){}
    ~Expression(){}
    
    /// @brief Evaluates the value of the current Expression based on current value and the children of the nodes if they exist
    virtual datatype evaluate() = 0;

    // virtual llvm::Value *codegen() = 0;

    
    string typename_of_expression = "Unknown";
    string get_type(){return typename_of_expression;};
};

////////////////////////////////
/********* Literals ***********/
////////////////////////////////

/**
 * @brief Base Class for all Literals, derives from Expression
*/
class Literal : public Expression
{
public:
    Literal(YYLTYPE* _location = NULL, string node_name = "Literal"):Expression(location, node_name){}

    /// @brief return the evaluated value of the expression 
    datatype evaluate();
};

/**
 * @brief Integer Literal
 * 
 */
class IntegerLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Integer Literal object
     * 
     * @param val the value of the int literal
     */
    IntegerLiteral(int val, YYLTYPE* location = NULL):Literal(location, "IntegerLiteral"){value = val; typename_of_expression = "int";}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};
/**
 * @brief Float Literals
 * 
 */
class FloatLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Floating Point Literal object
     * 
     * @param val value of float literal
     */
    FloatLiteral(float val, YYLTYPE* location = NULL):Literal(location, "FloatLiteral"){value = val; typename_of_expression = "float";}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/**
 * @brief String literals
 * 
 */
class StringLiteral : public Literal
{
public:
    /**
     * @brief Construct a new String Literal object
     * 
     * @param val value of the string literal
     */
    StringLiteral(string val, YYLTYPE* location = NULL):Literal(location, "StringLiteral") {value = val; typename_of_expression = "string";}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};
/**
 * @brief Boolean Literal
 * 
 */
class BooleanLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Boolean Literal object
     * 
     * @param val value of boolean literal
     */
    BooleanLiteral(bool val, YYLTYPE* location = NULL):Literal(location, "BoolLiteral") {value = val; typename_of_expression = "bool";}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/* Identifiers */
/**
 * @brief Represent a variable in the AST
 * 
 */
class Variable : public Expression
{
public:
    Variable(YYLTYPE* location = NULL, string name = "Variable"):Expression(location, name) {value = name;}
};

/**
 * @brief represents an Identifier for a type/variable
 * 
 */
class Identifier : public Variable
{
protected:
    string id;  ///name the identifier
    Symbol* symbol = NULL;

public:
    Identifier(YYLTYPE* location = NULL, string name = "Identifier");
    void print(ostream& out_file, int indentation = 0);
    string ret_id();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/**
 * @brief Represents member access operator '::'
 * 
 */
class MemberAccess : public Variable
{
protected:
    Variable *object;
    Identifier member;

public:
   /**
    * @brief Construct a new Member Access object
    * 
    * @param v 
    * @param s 
    */
    MemberAccess(Variable *v, Identifier id, YYLTYPE* location = NULL);
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/**
 * @brief Array Access i.e. '[]'
 * 
 */
class ArrayAccess : public Variable
{
protected:
    Variable *array_name;   ///name of array
    Expression *index;      ///index to access

public:
    ArrayAccess(Expression *name, Expression *ind, YYLTYPE* location = NULL)
        : Variable(location, "ArrayAccess") ,array_name((Variable*)name),index(ind){typename_of_expression = array_name->get_type();}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class Arg : public Expression
{
protected:
    Identifier t;
    Identifier id;
public:
    Arg(Identifier t_, Identifier id_, YYLTYPE* location = NULL): Expression(location, "Arg"), t(t_), id(id_){}
    string getType(){return t.ret_id();};
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/* Function Call */

class FunctionCall : public Expression
{
protected:
    Variable *func_name;
    vector<Expression *> args_list;

public:
    FunctionCall(Expression *name, vector<Expression *> l = vector<Expression *>(), YYLTYPE* location = NULL)
        :Expression(location, "FunctionCall"), func_name((Variable*)name), args_list(l)
    {typename_of_expression = func_name->get_type().substr(0, func_name->get_type().find("->"));}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/* Assignment */

class AssignmentExp : public Expression
{
protected:
    Variable *LHS;
    Expression *RHS;

public:
    AssignmentExp();
    AssignmentExp(Variable *L, Expression *R, YYLTYPE* location = NULL, string name = "AssignmentExp");
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class AddAssign : public AssignmentExp
{
public:
    AddAssign(Variable *L, Expression *R, YYLTYPE* location = NULL): AssignmentExp(L, R, location, "AddAssign"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class SubAssign : public AssignmentExp
{
public:
    SubAssign(Variable *L, Expression *R, YYLTYPE* location = NULL): AssignmentExp(L, R, location, "SubAssign"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class MulAssign : public AssignmentExp
{
public:
    MulAssign(Variable *L, Expression *R, YYLTYPE* location = NULL):  AssignmentExp(L, R, location, "MulAssign"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class DivAssign : public AssignmentExp
{
public:
    DivAssign(Variable *L, Expression *R, YYLTYPE* location = NULL):  AssignmentExp(L, R, location, "DivAssign"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class ModAssign : public AssignmentExp
{
public:
    ModAssign(Variable *L, Expression *R, YYLTYPE* _location = NULL):  AssignmentExp(L, R, location, "ModAssign"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate(); // evaluation is different from AssignmentExp
};

/* Base Classes for Unary and Binary Operations */

class UnaryOperation : public Expression
{
public:
    UnaryOperation(YYLTYPE* location = NULL, string name = "UnaryOperation"):Expression(location, name){}
};

class UnaryIncrement : public UnaryOperation
{
protected:
    Variable *var;
    UnaryIncrement(Variable* v, YYLTYPE* location = NULL, string name = "UnaryIncrement"):UnaryOperation(location, name), var(v){typename_of_expression = var->get_type();}
public:
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class PostfixInc : public UnaryIncrement
{
public:
    PostfixInc(Variable *v, YYLTYPE* location = NULL):UnaryIncrement(v, location, "PostfixInc"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class PrefixInc : public UnaryIncrement
{
public:
    PrefixInc(Variable *v, YYLTYPE* location = NULL):UnaryIncrement(v, location, "PrefixInc"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class UnaryDecrement : public UnaryOperation
{
protected:
    Variable *var;
    UnaryDecrement(Variable *v, YYLTYPE* location = NULL, string name = "UnaryDecrement"):UnaryOperation(location, name), var(v){typename_of_expression = var->get_type();}
public:
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class PostfixDec : public UnaryDecrement
{
public:
    PostfixDec(Variable *v, YYLTYPE* location = NULL):UnaryDecrement(v, location, "PostfixDec"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class PrefixDec : public UnaryDecrement
{
public:
    PrefixDec(Variable *v, YYLTYPE* location = NULL):UnaryDecrement(v, location, "PrefixDec"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class UnaryPlus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryPlus(Expression *e, YYLTYPE* location = NULL):UnaryOperation(location, "UnaryPlus"), exp(e){typename_of_expression = exp->get_type();}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class UnaryMinus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryMinus(Expression *e, YYLTYPE* location = NULL):UnaryOperation(location, "UnaryMinus"), exp(e){typename_of_expression = exp->get_type();}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/// @brief Class to represent the ternary operator in the AST. Derives from Statement
class TernaryOperator : public Expression
{
protected:
    Expression *condition;
    Expression *true_eval;
    Expression *false_eval;

public:
    /// @brief Constructor for TernaryOperator
    /// @param cond conditon
    /// @param t_eval expression to eval on cond == true
    /// @param f_eval expression to eval on cond == false
    TernaryOperator(Expression *cond, Expression *t_eval, Expression *f_eval, YYLTYPE* location = NULL);
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/* Arithmetic Operations */
class BinaryOperation : public Expression
{
protected:
    Expression *LHS;
    Expression *RHS;
    BinaryOperation();
public:
    BinaryOperation(Expression *L, Expression *R, YYLTYPE* location = NULL, string name = "BinaryOperation");
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class Addition : public BinaryOperation
{
public:
    Addition(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "Addition"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    /*
    Note : in the implmentation of evaluate function, check the type of both expressions
    and proceed accordingly
    Concatenation can be implemented here
    */
   // llvm::Value *codegen() override;
};

class Subtraction : public BinaryOperation
{
public:
    Subtraction(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "Subtraction"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class Multiplication : public BinaryOperation
{
public:
    Multiplication(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "Multiplication"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class Division : public BinaryOperation
{
public:
    Division(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "Division"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class ModularDiv : public BinaryOperation
{
public:
    ModularDiv(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "ModularDiv"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/* Logical Operations */

class LogicalAND : public BinaryOperation
{
public:
    LogicalAND(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "LogicalAND"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class LogicalOR : public BinaryOperation
{
public:
    LogicalOR(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "LogicalOR"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

class LogicalNOT : public UnaryOperation
{
protected:
    Expression *exp;

public:
    LogicalNOT(Expression *e, YYLTYPE* location = NULL):UnaryOperation(location, "LogicalNOT"), exp(e){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
};

/* Comparison Operations */

class CompGT : public BinaryOperation
{
public:
    CompGT(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompGT"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompLT : public BinaryOperation
{
public:
    CompLT(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompLT"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompGE : public BinaryOperation
{
public:
    CompGE(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompGE"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompLE : public BinaryOperation
{
public:
    CompLE(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompLE"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompEQ : public BinaryOperation
{
public:
    CompEQ(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompEQ"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompNEQ : public BinaryOperation
{
public:
    CompNEQ(Expression *L, Expression *R, YYLTYPE* location = NULL):BinaryOperation(L, R, location, "CompNEQ"){}
    void print(ostream& out_file, int indentation = 0);
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
class Statement : public ASTNode
{
    public:
    Statement(YYLTYPE* location = NULL, string name = "Statement"):ASTNode(location, name){}
        // virtual llvm::Value *codegen() = 0;
};
/// @brief Class to represent Expression Statements in the AST. Derives from \ref Statement
class ExpressionStatement : public Statement
{
protected:
    vector<Expression *> *exp;
public:
    /// @brief Constructor for class
    /// @param e input expression
    ExpressionStatement(vector<Expression *>*e = NULL, YYLTYPE* location = NULL):Statement(location, "ExpressionStatement"), exp(e){}
    /// @brief print the content of expression statement
    vector<Expression *> getValue();
    void print(ostream& out_file, int indentation = 0);
};

/// @brief Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
protected:
    vector<Statement *> stmt_list;
    CompoundStatement() = delete;

public:
    /// @brief Constructor for Comppund Statement Class
    /// @param l list of statements
    CompoundStatement(vector<Statement *> l = vector<Statement *>(), YYLTYPE* location = NULL):Statement(location, "CompoundStatement"), stmt_list(l){}
    /// @brief print the content of compound statement
    void print(ostream& out_file, int indentation = 0);
};

/* Family */
enum class ACCESS_SPEC
{
    PUBLIC,
    PRIVATE
};
/// @brief Class to represent family declarations
class FamilyMembers : public Statement
{
protected:
    ACCESS_SPEC access_specifier;
    Statement *member;

public:
    FamilyMembers(ACCESS_SPEC acc_spec, Statement *member_, YYLTYPE* location = NULL):Statement(location, "FamilyMembers"), access_specifier(acc_spec), member(member_){}
    void print(ostream& out_file, int indentation = 0);
};
class FamilyDecl : public Statement
{
protected:
    Identifier fam_name;                                            /// Identifier of the familie
    vector<FamilyMembers *> members = vector<FamilyMembers *>();        /// saves the pouinter to the member vars/ function as a List
    std::optional<pair<Identifier, ACCESS_SPEC>> parent_class = {}; /// saves the Identifier and Access specification of the parent class. if there is no parent class, std::optional is not initialised
public:
    FamilyDecl(Identifier fam_name_, YYLTYPE* _location = NULL): Statement(location, "FamilyDecl"), fam_name(fam_name_){}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param members_ List of pointers to the memeber funcs/vars
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, vector<FamilyMembers *> members_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_ = {}, YYLTYPE* _location = NULL)
        : Statement(location, "FamilyDecl"), fam_name(fam_name_), members(members_), parent_class(parent_class_){}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_, YYLTYPE* _location = NULL)
        : Statement(location, "FamilyDecl"), fam_name(fam_name_), parent_class(parent_class_){}
    void print(ostream& out_file, int indentation = 0);
};
class ConstructorDeclaration : public Statement
{
protected:
    Identifier class_name;
    CompoundStatement *body;
    vector<Arg *> arg_list;

public:
    ConstructorDeclaration(Identifier class_name_, Statement *body_, vector<Arg *> arg_list_, YYLTYPE* location = NULL)
        :Statement(location, "ConstructorDeclaration"), class_name(class_name_), body((CompoundStatement *)body_), arg_list(arg_list_){}
    void print(ostream& out_file, int indentation = 0);
};

/* Declaration Statements */

/// @brief Class to represent Function Definition in the AST. Derives from Statement
class FunctionDeclaration : public Statement
{
protected:
    Identifier *func_name;
    Identifier return_type;
    CompoundStatement *func_body;
    vector<Arg *> arg_list;

public:
    FunctionDeclaration() = delete;
    /// @brief Constructor for Function Definition Class
    /// @param _name function name
    /// @param _t return type
    /// @param _arg_list list of arguments
    /// @param _stmt list of arguments
    FunctionDeclaration(Identifier *_name, Identifier _t, Statement *_stmt, vector<Arg *> _arg_list = vector<Arg *>(), YYLTYPE* location = NULL)
        :Statement(location, "FunctionDeclaration"), func_name(_name), return_type(_t), func_body((CompoundStatement *)_stmt), arg_list(_arg_list){}
    /// @brief print the content of function definition
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent Variable Declaration in the AST. Derives from Statement
class VariableDeclaration : public Statement
{
protected:
    Identifier variable_type;
    vector<Expression *> variable_list;

public:
    /// @brief Constructor for function declaration
    /// @param t type of variable
    /// @param l list of identifires
    VariableDeclaration(Identifier t, vector<Expression *> l = vector<Expression*>(), YYLTYPE* location = NULL)
        :Statement(location, "VariableDeclaration"), variable_type(t), variable_list(l){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent definition of driver function in the AST. Derives from CompoundStatement
class DriverDefinition : public Statement
{
protected:
    CompoundStatement *func_body;

public:
    DriverDefinition() = delete;
    /// @brief Constructor for DriverFunction
    /// @param body the Compound Statements that take make up the driver function
    // DriverDefinition(CompoundStatement* body) : func_body(body) {};
    DriverDefinition(Statement *body, YYLTYPE* location = NULL) 
        :Statement(location, "DriverDefinition"), func_body((CompoundStatement *)body) {}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent variable initialization in the AST. Derives from Statement
class VariableInitialization : public Statement
{
protected:
    Identifier variable_type;
    AssignmentExp *exp;

public:
    /// @brief Constructor for VariableInitiailization
    /// @param t type of variable
    /// @param e paired assignment expression
    VariableInitialization(Identifier t, AssignmentExp *e, YYLTYPE* location = NULL)
        :Statement(location, "VariableInitialization"), variable_type(t), exp(e){}
    void print(ostream& out_file, int indentation = 0);
};

/* Labeled Statements */

/// @brief Class to represent All Labelled Statements in the AST
class LabeledStatement : public Statement
{
protected:
    Expression *label;
    Statement *stmt;

public:
    /// @brief Constructor for LabelledStatement
    LabeledStatement() = default;
    LabeledStatement(Expression *lb, Statement *st, YYLTYPE* location = NULL)
        :Statement(location, "LabeledStatement"), label(lb), stmt(st){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public LabeledStatement
{
public:
    /// @brief Constructor for CaseLabel
    /// @param lb expression to check for in case
    /// @param st_list statement to execute in said case
    CaseLabel(Expression *lb, Statement *st, YYLTYPE* location = NULL)
        :LabeledStatement(lb, st, location){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public LabeledStatement
{
public:
    /// @brief Constructor for DefaultLabel
    /// @param st_list statement in default case
    DefaultLabel(Statement *st, YYLTYPE* location = NULL)
        :LabeledStatement(NULL, st, location){}
    void print(ostream& out_file, int indentation = 0);
};

/* Iteration Statements */

/// @brief Class to represent  iterations in the AST. Derives from Statement. Provides base class to classes like WhileLoop
class IterationStatement : public Statement
{
protected:
    CompoundStatement *body;
    Expression *condition;

public:
    /// @brief Constructor for IterationStatement
    IterationStatement(CompoundStatement *b, Expression *cond, YYLTYPE* location = NULL, string _type = "IterationStatement")
        :Statement(location, _type), body(b), condition(cond){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent while loop in the AST. Derives from Statement
class WhileLoop : public IterationStatement
{
public:
    /// @brief Constructor for WhileLoop
    /// @param b body of while loop
    /// @param cond entry condition for while loop
    WhileLoop(CompoundStatement *b, Expression *cond = NULL, YYLTYPE* location = NULL)
        :IterationStatement(b, cond, location, "WhileLoop"){}
    void print(ostream& out_file, int indentation = 0);
};

/// @brief Class to represent for loop in the AST. Derives from Statement
class ForLoop : public IterationStatement
{
protected:
    ExpressionStatement *initialization;
    ExpressionStatement *condition;
    Expression *counter_updation;

public:
    ForLoop(CompoundStatement *b, ExpressionStatement *init, ExpressionStatement *cond, Expression *update, YYLTYPE* location = NULL)
        :IterationStatement(b, NULL, location, "ForLoop"), initialization(init), condition(cond), counter_updation(update){} 
    void print(ostream& out_file, int indentation = 0);
};

/*********************************************
 * Selection Statements
 * *******************************************/
/// @brief Class to represent if - else statements in the AST. Derives from Statement
class IfStatement : public Statement
{
protected:
    Expression *condition;
    CompoundStatement *if_block;

public:
    IfStatement(Expression *e, CompoundStatement *block, YYLTYPE* location = NULL)
        :Statement(location, "IfStatement"), condition(e), if_block(block){}
    void print(ostream& out_file, int indentation = 0);
    // llvm::Value *codegen() override;
};
class IfElseStatement : public Statement
{
protected:
    Expression *if_condition;
    CompoundStatement *if_block, *else_block;

public:
    IfElseStatement(Expression *cond, CompoundStatement *block1, CompoundStatement *block2, YYLTYPE* location = NULL)
        :Statement(location, "IfElseStatement"), if_condition(cond), if_block(block1), else_block(block2){}
    void print(ostream& out_file, int indentation = 0);
    // llvm::Value *codegen() override;
};
/// @brief Class to represent switch case statement in the AST. Derives from Statement
class SwitchStatement : public Statement
{
protected:
    Expression *exp;
    CompoundStatement *block;

public:
    SwitchStatement(Expression *e, CompoundStatement *b, YYLTYPE* location = NULL)
        :Statement(location, "SwitchStatement"), exp(e), block(b){}
    void print(ostream& out_file, int indentation = 0);
};

/// @brief Provides base class for all jump statements
class JumpStatement : public Statement
{
public:
    JumpStatement(YYLTYPE* location = NULL, string _type = "JumpStatement")
        :Statement(location, _type){}
};
/// @brief Class to represent 'return' in the AST. Derives from Statement.
class ReturnStatement : public JumpStatement
{
protected:
    Expression *return_val;

public:
    ReturnStatement(Expression *val, YYLTYPE* location = NULL): JumpStatement(location, "ReturnStatement"), return_val(val){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent 'break' in the AST. Derives from Statement
class BreakStatement : public JumpStatement
{
public:
    BreakStatement(YYLTYPE* location = NULL): JumpStatement(location, "BreakStatement"){}
    void print(ostream& out_file, int indentation = 0);
};
/// @brief Class to represent 'continue' in the AST. Derives from Statement
class ContinueStatement : public JumpStatement
{
public:
    ContinueStatement(YYLTYPE* location = NULL): JumpStatement(location, "ContinueStatement"){}
    void print(ostream& out_file, int indentation = 0);
};

/*------------------------------------------------------------------------
 * Class to create the AST Root Node
 *------------------------------------------------------------------------*/
/// @brief Class to represent the actual program as the AST. Derives from Statement
class Program : public ASTNode
{
protected:
    vector<Statement *> *stmt_list;

public:
    Program(vector<Statement *> *stmts = new vector<Statement *>(), YYLTYPE* location = NULL)
        :ASTNode(location, "Program"), stmt_list(stmts){}
    void print(ostream& out_file, int indentation = 0);
};

// objects at the base of the tree
extern Program *root;

#endif