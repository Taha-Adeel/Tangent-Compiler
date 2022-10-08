#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <map>

#define value_pair pair <type, data>
using namespace std;

/* Definitions to store the value of an Expression */
enum type {INT_TYPE, FLOAT_TYPE, STRING_TYPE, BOOL_TYPE, VOID_TYPE};
union data 
{
    int ivalue;
    float fvalue;
    char *svalue;
    bool bvalue;
};
string enumtypeToString(type t)
{
    switch (t)
    {
        case INT_TYPE: return "INT";
        case FLOAT_TYPE: return "FLOAT";
        case STRING_TYPE: return "STRING";
        case BOOL_TYPE: return "BOOL";
        case VOID_TYPE: return "VOID";
    }
    return "UNRECOGNISED TYPE";
}
/*------------------------------------------------------------------------
 * Defining the Class Hierarchy
 *------------------------------------------------------------------------*/
class ASTNode
{
    public:
        virtual void print() = 0;
};

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/
class Expression : public ASTNode
{
    protected:
        value_pair value;
    public:
        Expression();
        ~Expression();
        virtual value_pair evaluate() = 0;

};

/* Literals */
class IntegerLiteral : public Expression
{
    public:
        IntegerLiteral(int num);
        void print();
        value_pair evaluate();
};

class FloatingPointLiteral : public Expression
{
    public:
        FloatingPointLiteral(float num);
        void print();
        value_pair evaluate();
};

class StringLiteral : public Expression
{
    public:
        StringLiteral(string s);
        void print();
        value_pair evaluate();
};

class BooleanLiteral : public Expression
{
    public:
        BooleanLiteral(bool b);
        void print();
        value_pair evaluate();
};

/* Identifiers */

class Identifier : public Expression
{
    protected:
        string id;
    public:
        Identifier(string name);
        void print();
        string ret_id();
        value_pair evaluate();
};

/* Array Element Access */

class ArrayAccess : public Expression
{
    protected:
        Identifier* array_name;
        int index;
    public:
        ArrayAccess(Identifier* name, int i);
        void print();
        value_pair evaluate();
};

/* Function Call */

class FunctionCall : public Expression
{
    protected:
        Identifier* func_name;
        list <Identifier*> args_list;
    public:
        FunctionCall(Identifier* name, list <Identifier*> l);
        void print();
        value_pair evaluate();
};

/* Assignment */

class AssignmentExp : public Expression
{
    protected:
        Identifier* id;
        Expression* RHS;
    public:
        AssignmentExp();
        AssignmentExp(Identifier* name, Expression* R);
        void print();
        value_pair evaluate();
};

class AddAssign : public AssignmentExp
{
    public:
        AddAssign(Identifier* name, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class SubAssign : public AssignmentExp
{
    public:
        SubAssign(Identifier* name, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class MulAssign : public AssignmentExp
{
    public:
        MulAssign(Identifier* name, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class DivAssign : public AssignmentExp
{
    public:
        DivAssign(Identifier* name, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class ModAssign : public AssignmentExp
{
    public:
        ModAssign(Identifier* name, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

/* Base Classes for Unary and Binary Operations */

class UnaryOperation : public Expression
{
    protected:
        Expression* RHS;
    public:
        UnaryOperation();
        UnaryOperation(Expression* R);
        void print();
        value_pair evaluate();
};

class BinaryOperation : public Expression
{
    protected:
        Expression* LHS;
        Expression* RHS;
    public:
        BinaryOperation();
        BinaryOperation(Expression* L, Expression* R);
        void print();
        value_pair evaluate();
};

/* Arithmetic Operations */

class Addition : public BinaryOperation
{
    public:
        Addition(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 
    /*
    Note : in the implmentation of evaluate function, check the type of both expressions 
    and proceed accordingly 
    Concatenation can be implemented here
    */
};

class Subtraction: public BinaryOperation
{
    public:
        Subtraction(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class Multiplication : public BinaryOperation
{
    public:
        Multiplication(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class Division : public BinaryOperation
{
    public:
        Division(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class ModularDiv : public BinaryOperation
{
    public:
        ModularDiv(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class UnaryPlus : public UnaryOperation
{
    public:
        UnaryPlus(Expression* R);
        void print();
        value_pair evaluate();
};

class UnaryMinus : public UnaryOperation
{
    public:
        UnaryMinus(Expression* R);
        void print();
        value_pair evaluate();
};

/* Logical Operations */

class LogicalAND : public BinaryOperation
{
    public:
        LogicalAND(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class LogicalOR : public BinaryOperation
{
    public:
        LogicalOR(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class LogicalNOT : public UnaryOperation
{
    public:
        LogicalNOT(Expression* R);
        void print();
        value_pair evaluate();
};

/* Comparison Operations */

class CompGT: public BinaryOperation
{
    // >
    public:
        CompGT(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 
        va

};

class CompLT: public BinaryOperation
{
    // <
    public:
        CompLT(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class CompGE: public BinaryOperation
{
    // >=
    public:
        CompGE(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class CompLE: public BinaryOperation
{
    // <=
    public:
        CompLE(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class CompEQ: public BinaryOperation
{
    // =
    public:
        CompEQ(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class CompNEQ: public BinaryOperation
{
    // !=
    public:
        CompNEQ(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};


/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
class Statement : public ASTNode
{
    
};

/// @class Class to represent Expression Statements in the AST. Derives from \ref Statement
class ExpressionStatement : public Statement
{
    protected:
        Expression* exp; ///
    public:
        ExpressionStatement() = delete;
        /// @brief Constructor for class
        /// @param e input expression
        ExpressionStatement(Expression* e):exp(e){}
        /// @brief print the content of expression statement
        void print();
};

/// @class Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
    protected:
        list <Statement*> stmt_list;
    public:
        CompoundStatement() = delete;
        /// @brief Constructor for Comppund Statement Class
        /// @param l list of statements
        CompoundStatement(list <Statement*> l):stmt_list(l){} 
        /// @brief print the content of compound statement
        void print();
};

/* Declaration Statements */

/// @class Class to represent Function Definition in the AST. Derives from Statement
class FunctionDefinition : public Statement
{
    protected:
        Identifier* func_name;
        type return_type;
        CompoundStatement* func_body;
        list<Identifier*> arg_list;
    public:
        FunctionDefinition() = delete;
        /// @brief Constructor for Function Definition Class
        /// @param _name function name
        /// @param _t return type
        /// @param _arg_list list of arguments
        /// @param _stmt list of arguments 
        FunctionDefinition(Identifier* _name, type _t, list<Identifier*> _arg_list, CompoundStatement* _stmt): func_name(_name), return_type(_t), arg_list(_arg_list), func_body(_stmt){};
        /// @brief print the content of function definition
        void print();
};
/// @class Class to represent Variable Declaration in the AST. Derives from Statement
class VariableDeclaration : public Statement
{
    protected:
        type variable_type;
        list <Identifier*> variable_list;
    public:
        /// @brief Constructor for function declaration 
        /// @param t type of variable
        /// @param l list of identifires
        VariableDeclaration(type t, list <Identifier*> l): variable_type(t), variable_list(l){};
        void print();
};
/// @class Class to represent definition of driver function in the AST. Derives from CompoundStatement
class DriverDefinition : public CompoundStatement
{
    protected:
        CompoundStatement* func_body;
    public:
        DriverDefinition() = delete;
        /// @brief Constructor for DriverFunction
        /// @param body the Compound Statements that take make up the driver function
        DriverDefinition(CompoundStatement* body);
        void print();
};
/// @class Class to represent variable initialization in the AST. Derives from Statement
class VariableInitialization : public Statement
{
    protected:
        type variable_type;
        AssignmentExp* exp;
    public:
        /// @brief Constructor for VariableInitiailization
        /// @param t type of variable
        /// @param e paired assignment expression
        VariableInitialization(type t, AssignmentExp* e);
        void print();
};

/* Labeled Statements */

/// @class Class to represent All Labelled Statements in the AST
class LabeledStatement : public Statement
{
    protected:
        Identifier* label;
        Statement* stmt;
    public:
        /// @brief Constructor for LabelledStatement
        LabeledStatement(Identifier* l, Statement* st);
        void print();
};
/// @class Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public Statement
{
    protected:
        Expression* label;
        list <Statement*> stmt_list;
    public:
        /// @brief Constructor for CaseLabel
        /// @param lb expression to check for in case
        /// @param st_list list of statements to execute in said case
        CaseLabel(Expression* lb, list <Statement*> st_list);
        void print();

};
/// @class Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public Statement
{
    protected:
        list <Statement*> stmt_list;
    public:
        /// @brief Constructor for DefaultLabel
        /// @param st_list list of statements in default case
        DefaultLabel(list <Statement*> st_list);
        void print();
};

/* Iteration Statements */

/// @class Class to represent  iterations in the AST. Derives from Statement. Provides base class to classes like WhileLoop
class IterationStatement : public Statement
{
    protected:
        CompoundStatement* body;
        ExpressionStatement* condition;
    public:
        /// @brief Constructor for IterationStatement
        IterationStatement(CompoundStatement* b, ExpressionStatement* cond);
};
/// @class Class to represent while loop in the AST. Derives from Statement
class WhileLoop : public IterationStatement
{
    public:
        /// @brief Constructor for WhileLoop
        /// @param b list of statements to execute
        WhileLoop(CompoundStatement* b);
        /// @brief Constructor for WhileLoop
        /// @param b body of while loop 
        /// @param cond entry condition for while loop
        WhileLoop(CompoundStatement* b, Expression* cond);
        void print();
};

/// @class Class to represent for loop in the AST. Derives from Statement
class ForLoop : public IterationStatement
{
    protected:
        Expression* initialization;
        Expression* counter_updation;
    public:
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        ForLoop(CompoundStatement* b);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param cond entry condition for for loop
        ForLoop(CompoundStatement* b, Expression* cond);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param init initialization expression
        ForLoop(CompoundStatement* b, Expression* init);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param update update expression in for loop
        ForLoop(CompoundStatement* b, Expression* update);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param init initialization expression
        /// @param cond entry condition for for loop
        ForLoop(CompoundStatement* b, Expression* cond, Expression* init);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param cond entry condition for for loop
        /// @param update update expression in for loop
        ForLoop(CompoundStatement* b, Expression* cond, Expression* update);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param init initialization expression
        /// @param update update expression in for loop
        ForLoop(CompoundStatement* b, Expression* init, Expression* update);
        /// @brief Constructor for ForLoop
        /// @param b body of for loop
        /// @param init initialization expression
        /// @param cond entry condition for for loop
        /// @param update update expression in for loop
        ForLoop(CompoundStatement* b, Expression* cond, Expression* init, Expression* update);
        void print();
};

/*********************************************
 * Selection Statements 
 * *******************************************/
/// @class Class to represent if - else statements in the AST. Derives from Statement
class IfElse : public Statement
{
    protected:
        list <Expression*> condition_list;
        list <CompoundStatement*> if_blocks;
        CompoundStatement* else_block;
    public:
        /// @brief Constructor for IfElse
        /// @param l 
        /// @param ifs 
        IfElse(list <Expression*> l, list <CompoundStatement*> ifs);
        IfElse(list <Expression*> l, list <CompoundStatement*> ifs, CompoundStatement* elseb);
        void print();
};
/// @class Class to represent switch case statement in the AST. Derives from Statement
class Switch : public Statement
{
    protected:
        Expression* exp;
        list <CaseLabel*> cases;
    public:
        Switch(Expression* e, list <CaseLabel*> c);
        void print();
};
/// @class Class to represent the ternary operator in the AST. Derives from Statement
class TernaryOperator : public Statement
{
    protected:
        Expression* condition;
        Expression* true_eval;
        Expression* false_eval;
    public:
        TernaryOperator(Expression* cond, Expression* t_eval, Expression* f_eval);
        void print();
};

class JumpStatement : public Statement
{

};
/// @class Class to represent 'return' in the AST. Derives from Statement
class ReturnStatement: public JumpStatement
{
    protected:
        value_pair return_value;
    public:
        ReturnStatement(value_pair val);
        void print();
};
/// @class Class to represent 'break' in the AST. Derives from Statement
class BreakStatement: public JumpStatement
{
    public:
        void print();
};
/// @class Class to represent 'continue' in the AST. Derives from Statement
class ContinueStatement: public JumpStatement
{
    public:
        void print();
};

/*------------------------------------------------------------------------
 * Class to create the AST Root Node 
 *------------------------------------------------------------------------*/
/// @class Class to represent the actual program as the AST. Derives from Statement
class Program : public ASTNode
{
    protected:
        list <Statement*> stmt_list;
    public:
        Program(list <Statement*> stmt_list);
};

// objects at the base of the tree
extern map <string, value_pair> symTable;
extern Program *root;