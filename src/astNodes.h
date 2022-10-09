#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <map>

#define value_pair pair <type, union data>
using namespace std;

/* Definitions to store the value of an Expression */
enum type {INT_TYPE, FLOAT_TYPE, STRING_TYPE, BOOL_TYPE, VOID_TYPE};
union data 
{
    int ivalue;
    float fvalue;
    string svalue;
    bool bvalue;
};
#define value_pair pair <type, union data>

/// @brief returns type of variable as string
/// @param t input type
/// @return type of variable 
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
/// @brief returns the value stored in valuepair as a string
/// @param d input valuepair
/// @return content of the value pair
string get_valuepair_content(value_pair d)
{
    switch(d.first)
    {
        case INT_TYPE: return(to_string(d.second.ivalue));
        case FLOAT_TYPE: return(to_string(d.second.fvalue));
        case STRING_TYPE: return(d.second.svalue);
        case BOOL_TYPE: return(to_string(d.second.bvalue));
        case VOID_TYPE: return("VOID");
    }
    return "";
}
/// @brief copies value of d to inp
/// @param inp value to set
/// @param d value to copy
void copy_valuepair(value_pair& inp, value_pair d)
{
    switch(d.first)
    {
        case INT_TYPE: inp.second.ivalue = d.second.ivalue;break;
        case FLOAT_TYPE: inp.second.fvalue = d.second.fvalue;break;
        case STRING_TYPE: inp.second.svalue = d.second.svalue;break;
        case BOOL_TYPE: inp.second.bvalue = d.second.bvalue;break;
    }
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
        ExpressionStatement(Expression* e):exp(e){};
        /// @brief print the content of expression statement
        Expression* getValue();
        void print();
};

/// @class Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
    protected:
        list <Statement*> stmt_list;
        CompoundStatement() = default;
    public:
        /// @brief Constructor for Comppund Statement Class
        /// @param l list of statements
        CompoundStatement(list <Statement*> l);
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
        FunctionDefinition(Identifier* _name, type _t, list<Identifier*> _arg_list, CompoundStatement* _stmt);
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
        VariableDeclaration(type t, list <Identifier*> l);
        void print();
};
/// @class Class to represent definition of driver function in the AST. Derives from CompoundStatement
class DriverDefinition : public Statement
{
    protected:
        CompoundStatement* func_body;
    public:
        DriverDefinition() = delete;
        /// @brief Constructor for DriverFunction
        /// @param body the Compound Statements that take make up the driver function
        DriverDefinition(CompoundStatement* body) : func_body(body) {};
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
        Expression* label;
        Statement* stmt;
        
    public:
        /// @brief Constructor for LabelledStatement
        LabeledStatement() = default;
        LabeledStatement(Expression* lb, Statement* st);
        void print();
};
/// @class Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public LabeledStatement
{
    public:
        /// @brief Constructor for CaseLabel
        /// @param lb expression to check for in case
        /// @param st_list statement to execute in said case
        CaseLabel(Expression* lb, Statement* st) : LabeledStatement(lb, st){};
        void print();
};
/// @class Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public LabeledStatement
{
    public:
        /// @brief Constructor for DefaultLabel
        /// @param st_list statement in default case
        DefaultLabel(Statement* st) : LabeledStatement(NULL, st){};
        void print();
};

/* Iteration Statements */

/// @class Class to represent  iterations in the AST. Derives from Statement. Provides base class to classes like WhileLoop
class IterationStatement : public Statement
{
    protected:
        CompoundStatement* body;
        Expression* condition;
    public:
        /// @brief Constructor for IterationStatement
        IterationStatement(CompoundStatement* b, Expression* cond);
};
/// @class Class to represent while loop in the AST. Derives from Statement
class WhileLoop : public IterationStatement
{
    public:
        /// @brief Constructor for WhileLoop
        /// @param b list of statements to execute
        WhileLoop(CompoundStatement* b);                                   //this constructor implies use of while loop without statement??
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

        //removed most constructor beacuse there is no way to distinguish between them on basis of arguments passed

        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // ForLoop(CompoundStatement* b);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param cond entry condition for for loop
        // ForLoop(CompoundStatement* b, Expression* cond);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param init initialization expression
        // ForLoop(CompoundStatement* b, Expression* init);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param update update expression in for loop
        // ForLoop(CompoundStatement* b, Expression* update);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param init initialization expression
        // /// @param cond entry condition for for loop
        // ForLoop(CompoundStatement* b, Expression* cond, Expression* init);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param cond entry condition for for loop
        // /// @param update update expression in for loop
        // ForLoop(CompoundStatement* b, Expression* cond, Expression* update);
        // /// @brief Constructor for ForLoop
        // /// @param b body of for loop
        // /// @param init initialization expression
        // /// @param update update expression in for loop
        // ForLoop(CompoundStatement* b, Expression* init, Expression* update);
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
        // /// @brief Constructor for IfElse
        // /// @param l list of if statements
        // /// @param ifs block of code for corresponding statement
        // IfElse(list <Expression*> l, list <CompoundStatement*> ifs);
        /// @brief Constructor for IfElse
        /// @param l list of if statements
        /// @param ifs block of code for corresponding statement
        /// @param elseb block of code for else block
        IfElse(list <Expression*> l, list <CompoundStatement*> ifs, CompoundStatement* elseb = nullptr);
        void print();
};
/// @class Class to represent switch case statement in the AST. Derives from Statement
class Switch : public Statement
{
    protected:
        Expression* exp;
        list <CaseLabel*> cases;
        DefaultLabel* def;
    public:
        /// @brief Constructor for Switch statement
        /// @param e switch expression
        /// @param c cases for switch
        Switch(Expression* e, list <CaseLabel*> c);
        /// @brief Constructor for Switch statement
        /// @param e switch expression
        /// @param c cases for switch
        /// @param _def default case for switch
        Switch(Expression* e, list <CaseLabel*> c, DefaultLabel* _def);
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
        /// @brief Constructor for TernaryOperator
        /// @param cond conditon
        /// @param t_eval expression to eval on cond == true
        /// @param f_eval expression to eval on cond == false
        TernaryOperator(Expression* cond, Expression* t_eval, Expression* f_eval);
        void print();
};
/// @class Provides base class for all jump statements
class JumpStatement : public Statement{};
/// @class Class to represent 'return' in the AST. Derives from Statement. 
class ReturnStatement: public JumpStatement
{
    protected:
        Expression *return_val;
    public:
        ReturnStatement(Expression* val) : return_val(val) {};
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
        list <Statement*> *stmt_list;
    public:
        Program(list <Statement*> *stmts = new list <Statement*> ());
};

// objects at the base of the tree
extern map <string, value_pair> symTable;
extern Program *root;