#ifndef ASTNODES_H
#define ASTNODES_H

#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <variant>
#include <optional>

using namespace std;

//enum class TYPE {INT, FLOAT, STRING, BOOL, VOID};
typedef variant<int, float, string, bool> datatype;
/*------------------------------------------------------------------------
 * Defining the Class Hierarchy
 *------------------------------------------------------------------------*/
class ASTNode
{
public:
    /// @brief prints the description/properties/value of the current node
    virtual void print() = 0;
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
    Expression();
    ~Expression();
    /**
     * @brief Evaluates the value of the current Expression based on current value and the children of the nodes if they exist
     * 
     * @return datatype 
     */
    virtual datatype evaluate() = 0;
    datatype get_type();
};

/********* Literals ***********/
/**
 * @brief Base Class for all Literals, derives from Expression
*/
class Literal : public Expression
{
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
    IntegerLiteral(int val);
    void print();
    datatype evaluate();
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
    FloatLiteral(float val);
    void print();
    datatype evaluate();
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
    StringLiteral(string val);
    void print();
    datatype evaluate();
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
    BooleanLiteral(bool val);
    void print();
    datatype evaluate();
};

/* Identifiers */
/**
 * @brief Represent a variable in the AST
 * 
 */
class Variable : public Expression
{
};

/**
 * @brief represents an Identifier for a type/variable
 * 
 */
class Identifier : public Variable
{
protected:
    string id;  ///name the identifier

public:
    Identifier(char* name):id(string(name)){};
    Identifier(string name):id(name){};
    void print();
    string ret_id();
    datatype evaluate();
};

/**
 * @brief Represents member access operator '::'
 * 
 */
class MemberAccess : public Variable
{
protected:
    Variable *accessor_name;
    string id;

public:
   /**
    * @brief Construct a new Member Access object
    * 
    * @param v 
    * @param s 
    */
    MemberAccess(Variable *v, string s);
    void print();
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
    ArrayAccess(Identifier *name, Expression *ind):array_name((Variable*)name),index(ind){}
    void print();
    datatype evaluate();
};

class Argument : public Expression
{
protected:
    Identifier t;
    Identifier id;
public:
    Argument(Identifier t_, Identifier id_);
    void print();
    datatype evaluate();
};

/* Function Call */

class FunctionCall : public Expression
{
protected:
    Variable *func_name;
    list<Expression *> args_list;

public:
    FunctionCall(Variable *name, list<Expression *> l = list<Expression *>());
    void print();
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
    AssignmentExp(Variable *L, Expression *R);
    void print();
    datatype evaluate();
};

class AddAssign : public AssignmentExp
{
public:
    AddAssign(Variable *L, Expression *R); // uses the constructor if AssignmentExp
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class SubAssign : public AssignmentExp
{
public:
    SubAssign(Variable *L, Expression *R); // uses the constructor if AssignmentExp
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class MulAssign : public AssignmentExp
{
public:
    MulAssign(Variable *L, Expression *R); // uses the constructor if AssignmentExp
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class DivAssign : public AssignmentExp
{
public:
    DivAssign(Variable *L, Expression *R); // uses the constructor if AssignmentExp
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class ModAssign : public AssignmentExp
{
public:
    ModAssign(Variable *L, Expression *R); // uses the constructor if AssignmentExp
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

/* Base Classes for Unary and Binary Operations */

class UnaryOperation : public Expression
{
};

class UnaryIncrement : public UnaryOperation
{
protected:
    Variable *var;
};

class PostfixInc : public UnaryIncrement
{
public:
    PostfixInc(Variable *v);
    void print();
    datatype evaluate();
};

class PrefixInc : public UnaryIncrement
{
public:
    PrefixInc(Variable *v);
    void print();
    datatype evaluate();
};

class UnaryDecrement : public UnaryOperation
{
protected:
    Variable *var;

public:
    UnaryDecrement(Variable *v);
    void print();
    datatype evaluate();
};

class PostfixDec : public UnaryDecrement
{
public:
    PostfixDec(Variable *v);
    void print();
    datatype evaluate();
};

class PrefixDec : public UnaryDecrement
{
public:
    PrefixDec(Variable *v);
    void print();
    datatype evaluate();
};

class UnaryPlus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryPlus(Expression *e);
    void print();
    datatype evaluate();
};

class UnaryMinus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryMinus(Expression *e);
    void print();
    datatype evaluate();
};

class BinaryOperation : public Expression
{
protected:
    Expression *LHS;
    Expression *RHS;

public:
    BinaryOperation();
    BinaryOperation(Expression *L, Expression *R);
    void print();
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
    TernaryOperator(Expression *cond, Expression *t_eval, Expression *f_eval);
    void print();
};

/* Arithmetic Operations */

class Addition : public BinaryOperation
{
public:
    Addition(Expression *L, Expression *R);
    void print();
    datatype evaluate();
    /*
    Note : in the implmentation of evaluate function, check the type of both expressions
    and proceed accordingly
    Concatenation can be implemented here
    */
};

class Subtraction : public BinaryOperation
{
public:
    Subtraction(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class Multiplication : public BinaryOperation
{
public:
    Multiplication(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class Division : public BinaryOperation
{
public:
    Division(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class ModularDiv : public BinaryOperation
{
public:
    ModularDiv(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

// class UnaryPlus : public UnaryOperation
// {
//     public:
//         UnaryPlus(Expression* R);
//         void print();
//         datatype evaluate();
// };

// class UnaryMinus : public UnaryOperation
// {
//     public:
//         UnaryMinus(Expression* R);
//         void print();
//         datatype evaluate();
// };

/* Logical Operations */

class LogicalAND : public BinaryOperation
{
public:
    LogicalAND(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class LogicalOR : public BinaryOperation
{
public:
    LogicalOR(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class LogicalNOT : public UnaryOperation
{
protected:
    Expression *exp;

public:
    LogicalNOT(Expression *e);
    void print();
    datatype evaluate();
};

/* Comparison Operations */

class CompGT : public BinaryOperation
{
    // >
public:
    CompGT(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class CompLT : public BinaryOperation
{
    // <
public:
    CompLT(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class CompGE : public BinaryOperation
{
    // >=
public:
    CompGE(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class CompLE : public BinaryOperation
{
    // <=
public:
    CompLE(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class CompEQ : public BinaryOperation
{
    // =
public:
    CompEQ(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

class CompNEQ : public BinaryOperation
{
    // !=
public:
    CompNEQ(Expression *L, Expression *R);
    void print();
    datatype evaluate();
};

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
class Statement : public ASTNode
{
};
/// @brief Class to represent Expression Statements in the AST. Derives from \ref Statement
class ExpressionStatement : public Statement
{
protected:
    Expression *exp; ///
public:
    ExpressionStatement() = delete;
    /// @brief Constructor for class
    /// @param e input expression
    ExpressionStatement(Expression *e) : exp(e){};
    /// @brief print the content of expression statement
    Expression *getValue();
    void print();
};

/// @brief Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
protected:
    list<Statement *> *stmt_list;
    CompoundStatement() = default;

public:
    /// @brief Constructor for Comppund Statement Class
    /// @param l list of statements
    CompoundStatement(list<Statement *> *l = new list<Statement *>()) : stmt_list(l) {}
    /// @brief print the content of compound statement
    void print();
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
    FamilyMembers(ACCESS_SPEC acc_spec, Statement *member_) : access_specifier(acc_spec), member(member_) {}
    void print();
};
class FamilyDecl : public Statement
{
protected:
    Identifier fam_name;                                            /// Identifier of the familie
    list<FamilyMembers *> members = list<FamilyMembers *>();        /// saves the pouinter to the member vars/ function as a List
    std::optional<pair<Identifier, ACCESS_SPEC>> parent_class = {}; /// saves the Identifier and Access specification of the parent class. if there is no parent class, std::optional is not initialised
public:
    FamilyDecl(Identifier fam_name_):fam_name(fam_name_){}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param members_ List of pointers to the memeber funcs/vars
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, list<FamilyMembers *> members_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_ = {})
        : fam_name(fam_name_), members(members_), parent_class(parent_class_) {}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_) : fam_name(fam_name_), parent_class(parent_class_) {}
    void print();
};
class ConstructorDeclaration : public Statement
{
protected:
    Identifier class_name;
    CompoundStatement *body;
    list<Identifier *> arg_list;

public:
    ConstructorDeclaration(Identifier class_name_, CompoundStatement *body_, list<Identifier *> arg_list_) : class_name(class_name_), body(body_), arg_list(arg_list_){};
    void print();
};

/* Declaration Statements */

/// @brief Class to represent Function Definition in the AST. Derives from Statement
class FunctionDeclaration : public Statement
{
protected:
    Identifier *func_name;
    Identifier return_type;
    CompoundStatement *func_body;
    list<Argument *> arg_list;

public:
    FunctionDeclaration() = delete;
    /// @brief Constructor for Function Definition Class
    /// @param _name function name
    /// @param _t return type
    /// @param _arg_list list of arguments
    /// @param _stmt list of arguments
    FunctionDeclaration(Identifier *_name, Identifier _t, Statement *_stmt, list<Argument *> _arg_list = list<Argument *>())
        :func_name(_name), return_type(_t), func_body((CompoundStatement*)_stmt), arg_list(_arg_list) {}
    /// @brief print the content of function definition
    void print();
};
/// @brief Class to represent Variable Declaration in the AST. Derives from Statement
class VariableDeclaration : public Statement
{
protected:
    Identifier variable_type;
    list<Expression *> variable_list;

public:
    /// @brief Constructor for function declaration
    /// @param t type of variable
    /// @param l list of identifires
    VariableDeclaration(Identifier t, list<Expression *> l = list<Expression*>())
        :variable_type(t), variable_list(l){}
    void print();
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
    DriverDefinition(Statement *body) : func_body((CompoundStatement *)body) {}
    void print();
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
    VariableInitialization(Identifier t, AssignmentExp *e);
    void print();
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
    LabeledStatement(Expression *lb, Statement *st);
    void print();
};
/// @brief Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public LabeledStatement
{
public:
    /// @brief Constructor for CaseLabel
    /// @param lb expression to check for in case
    /// @param st_list statement to execute in said case
    CaseLabel(Expression *lb, Statement *st);
    void print();
};
/// @brief Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public LabeledStatement
{
public:
    /// @brief Constructor for DefaultLabel
    /// @param st_list statement in default case
    DefaultLabel(Statement *st);
    void print();
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
    IterationStatement(CompoundStatement *b, Expression *cond);
    void print();
};
/// @brief Class to represent while loop in the AST. Derives from Statement
class WhileLoop : public IterationStatement
{
public:
    /// @brief Constructor for WhileLoop
    /// @param b list of statements to execute
    WhileLoop(CompoundStatement *b); // this constructor implies use of while loop without statement??
    /// @brief Constructor for WhileLoop
    /// @param b body of while loop
    /// @param cond entry condition for while loop
    WhileLoop(CompoundStatement *b, Expression *cond);
    void print();
};

/// @brief Class to represent for loop in the AST. Derives from Statement
class ForLoop : public IterationStatement
{
protected:
    ExpressionStatement *initialization;
    ExpressionStatement *condition;
    Expression *counter_updation;

public:
    ForLoop(CompoundStatement *b, ExpressionStatement *init, ExpressionStatement *cond, Expression *update);
    void print();
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
    IfStatement(Expression *e, CompoundStatement *block);
    void print();
};
class IfElseStatement : public Statement
{
protected:
    Expression *if_condition;
    CompoundStatement *if_block, else_block;

public:
    IfElseStatement(Expression *cond, CompoundStatement *block1, CompoundStatement *block2);
    void print();
};
/// @brief Class to represent switch case statement in the AST. Derives from Statement
class SwitchStatement : public Statement
{
protected:
    Expression *exp;
    CompoundStatement *block;

public:
    SwitchStatement(Expression *e, CompoundStatement *b);
    void print();
};

/// @brief Provides base class for all jump statements
class JumpStatement : public Statement
{
};
/// @brief Class to represent 'return' in the AST. Derives from Statement.
class ReturnStatement : public JumpStatement
{
protected:
    Expression *return_val;

public:
    ReturnStatement(Expression *val);
    void print();
};
/// @brief Class to represent 'break' in the AST. Derives from Statement
class BreakStatement : public JumpStatement
{
public:
    void print();
};
/// @brief Class to represent 'continue' in the AST. Derives from Statement
class ContinueStatement : public JumpStatement
{
public:
    void print();
};

/*------------------------------------------------------------------------
 * Class to create the AST Root Node
 *------------------------------------------------------------------------*/
/// @brief Class to represent the actual program as the AST. Derives from Statement
class Program : public ASTNode
{
protected:
    list<Statement *> *stmt_list;

public:
    Program(list<Statement *> *stmts = new list<Statement *>());
    void print();
};

// objects at the base of the tree
extern map<string, datatype> symTable;
extern Program *root;

#endif
