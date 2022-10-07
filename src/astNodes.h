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
        UnaryOperation(Expression* R);
};

class BinaryOperation : public Expression
{
    protected:
        Expression* LHS;
        Expression* RHS;
    public:
        BinaryOperation(Expression* L, Expression* R);
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

class ExpressionStatement : public Statement
{
    protected:
        Expression* exp;
    public:
        ExpressionStatement(Expression* e);
        void print();
};

class CompoundStatement : public Statement
{
    protected:
        list <Statement*> stmt_list;
    public:
        CompoundStatement(list <Statement*> l);
        void print();
};

/* Declaration Statements */

class FunctionDefinition : public Statement
{
    protected:
        Identifier* func_name;
        type return_type;
        CompoundStatement* func_body;
    public:
        FunctionDefinition(Identifier* name, type t, CompoundStatement* stmt);
        void print();
};

class VariableDeclaration : public Statement
{
    protected:
        type variable_type;
        list <Identifier*> variable_list;
    public:
        VariableDeclaration(type t, list <Identifier*> l);
        void print();
};

class DriverDefinition : public CompoundStatement
{
    protected:
        CompoundStatement* func_body;
    public:
        DriverDefinition(CompoundStatement* body);
        void print();
};

class VariableInitialization : public Statement
{
    protected:
        type variable_type;
        AssignmentExp* exp;
    public:
        VariableInitialization(type t, AssignmentExp* e);
        void print();
};

/* Labeled Statements */

class LabeledStatement : public Statement
{
    protected:
        Identifier* label;
        Statement* stmt;
    public:
        LabeledStatement(Identifier* l, Statement* st);
        void print();
};

class CaseLabel : public Statement
{
    protected:
        Expression* label;
        list <Statement*> stmt_list;
    public:
        CaseLabel(Expression* lb, list <Statement*> st_list);
        void print();

};

class DefaultLabel : public Statement
{
    protected:
        list <Statement*> stmt_list;
    public:
        DefaultLabel(list <Statement*> st_list);
        void print();

};

/* Iteration Statements */
class IterationStatement : public Statement
{
    protected:
        CompoundStatement* body;
        ExpressionStatement* condition;
    public:
        IterationStatement(CompoundStatement* b, ExpressionStatement* cond);
};

class WhileLoop : public IterationStatement
{
    public:
        WhileLoop(CompoundStatement* b);
        WhileLoop(CompoundStatement* b, Expression* cond);
        void print();
};


class ForLoop : public IterationStatement
{
    protected:
        Expression* initialization;
        Expression* counter_updation;
    public:
        ForLoop(CompoundStatement* b);
        ForLoop(CompoundStatement* b, Expression* cond);
        ForLoop(CompoundStatement* b, Expression* init);
        ForLoop(CompoundStatement* b, Expression* update);
        ForLoop(CompoundStatement* b, Expression* cond, Expression* init);
        ForLoop(CompoundStatement* b, Expression* cond, Expression* update);
        ForLoop(CompoundStatement* b, Expression* init, Expression* update);
        ForLoop(CompoundStatement* b, Expression* cond, Expression* init, Expression* update);
        void print();
};

/* Selection Statements */
class IfElse : public Statement
{
    protected:
        list <Expression*> condition_list;
        list <CompoundStatement*> if_blocks;
        CompoundStatement* else_block;
    public:
        IfElse(list <Expression*> l, list <CompoundStatement*> ifs);
        IfElse(list <Expression*> l, list <CompoundStatement*> ifs, CompoundStatement* elseb);
        void print();
};

class Switch : public Statement
{
    protected:
        Expression* exp;
        list <CaseLabel*> cases;
    public:
        Switch(Expression* e, list <CaseLabel*> c);
        void print();
};

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

class ReturnStatement: public JumpStatement
{
    protected:
        value_pair return_value;
    public:
        ReturnStatement(value_pair val);
        void print();
};

class BreakStatement: public JumpStatement
{
    public:
        void print();
};

class ContinueStatement: public JumpStatement
{
    public:
        void print();
};

/*------------------------------------------------------------------------
 * Class to create the AST Root Node 
 *------------------------------------------------------------------------*/
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