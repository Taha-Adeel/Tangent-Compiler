#include <stdlib.h>
#include <iostream>
#include <list>

#define value_pair pair <exp_type, data>
using namespace std;

/* Definitions to store the value of an Expression */
enum exp_type {INT_TYPE, FLOAT_TYPE, STRING_TYPE, BOOL_TYPE, VOID_TYPE};
union data 
{
    int ivalue;
    float fvalue;
    string svalue;
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
        value_pair evaluate;
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
        value_pair evaluate;
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

/* Arithmetic Operations */

class BinaryArithmetic : public Expression
{
    protected:
        Expression* LHS;
        Expression* RHS;
    public:
        BinaryArithmetic(Expression* L, Expression* R);
};

class Addition : public BinaryArithmetic
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

class Subtraction: public BinaryArithmetic
{
    public:
        Subtraction(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class Multiplication : public BinaryArithmetic
{
    public:
        Multiplication(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class Division : public BinaryArithmetic
{
    public:
        Division(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class ModularDiv : public BinaryArithmetic
{
    public:
        ModularDiv(Expression* L, Expression* R);
        void print();
        value_pair evaluate(); 

};

class UnaryArithmetic : public Expression
{
    protected:
        Expression* RHS;
    public:
        UnaryArithmetic(Expression* R);
};

class UnaryPlus : public UnaryArithmetic
{
    public:
        UnaryPlus(Expression* R);
        void print();
        value_pair evaluate();
};

class UnaryMinus : public UnaryArithmetic
{
    public:
        UnaryMinus(Expression* R);
        void print();
        value_pair evaluate();
};

/* Logical Operations */


/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
class Statement : public ASTNode
{
    
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