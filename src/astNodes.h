#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <variant>

using namespace std;

enum type {INT_TYPE=0, FLOAT_TYPE, STRING_TYPE, BOOL_TYPE, VOID_TYPE};
typedef variant<int,float,string, bool> var_data;
typedef pair<type, var_data> value_pair;

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
/// @brief checks if comparasion of two values in value_pair is valid or not
/// @param a first vp
/// @param b second vp
/// @return true if comparasion is possible. else returns false
bool is_valid_comparasion(value_pair a, value_pair b);
bool is_unary_operation_valid(value_pair& a);
bool is_boolean_operation_valid(value_pair& a, value_pair& b);

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

class Literal : public Expression
{

};
class IntegerLiteral : public Literal
{
    public:
        IntegerLiteral(int num);
        void print();
        value_pair evaluate();
};

class FloatingPointLiteral : public Literal
{
    public:
        FloatingPointLiteral(float num);
        void print();
        value_pair evaluate();
};

class StringLiteral : public Literal
{
    public:
        StringLiteral(string s);
        void print();
        value_pair evaluate();
};

class BooleanLiteral : public Literal
{
    public:
        BooleanLiteral(bool b);
        void print();
        value_pair evaluate();
};

/* Identifiers */

class Variable : public Expression
{

};

class Identifier : public Variable
{
    protected:
        string id;
    public:
        Identifier(string name);
        void print();
        string ret_id();
        value_pair evaluate();
};

class MemberAccess : public Variable
{
    protected:
        Variable* accessor_name;
        string id;
    public: 
        MemberAccess(Variable* v, string s);
        void print();
        value_pair evaluate();
};

/* Array Element Access */

class ArrayAccess : public Variable
{
    protected:
        Variable* array_name;
        Expression* index;
    public:
        ArrayAccess(Identifier* name, Expression* ind);
        void print();
        value_pair evaluate();
};

class Argument: public Expression
{
    protected:
        type t;
        Identifier* id;
    public:
        Argument(type t_, Identifier* id_);
        void print();
        value_pair evaluate();
};

/* Function Call */

class FunctionCall : public Expression
{
    protected:
        Variable* func_name;
        list <Expression*> args_list;
    public:
        FunctionCall(Variable* name, list <Expression*> l = list<Expression*>());
        void print();
        value_pair evaluate();
};

/* Assignment */

class AssignmentExp : public Expression
{
    protected:
        Variable* LHS;
        Expression* RHS;
    public:
        AssignmentExp();
        AssignmentExp(Variable* L, Expression* R);
        void print();
        value_pair evaluate();
};

class AddAssign : public AssignmentExp
{
    public:
        AddAssign(Variable* L, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class SubAssign : public AssignmentExp
{
    public:
        SubAssign(Variable* L, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class MulAssign : public AssignmentExp
{
    public:
        MulAssign(Variable* L, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class DivAssign : public AssignmentExp
{
    public:
        DivAssign(Variable* L, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

class ModAssign : public AssignmentExp
{
    public:
        ModAssign(Variable* L, Expression* R); // uses the constructor if AssignmentExp
        void print();
        value_pair evaluate(); // evaluation is different from AssignmentExp

};

/* Base Classes for Unary and Binary Operations */

class UnaryOperation : public Expression
{

};

class UnaryIncrement : public UnaryOperation
{
    protected:
        Variable* var;
};

class PostfixInc : public UnaryIncrement
{
    public:
        PostfixInc(Variable* v);
        void print();
        value_pair evaluate();
};

class PrefixInc : public UnaryIncrement
{
    public:
        PrefixInc(Variable* v);
        void print();
        value_pair evaluate();
};


class UnaryDecrement : public UnaryOperation
{
    protected:
        Variable* var;
    public:
        UnaryDecrement(Variable* v);
        void print();
        value_pair evaluate();
};

class PostfixDec : public UnaryDecrement
{
    public:
        PostfixDec(Variable* v);
        void print();
        value_pair evaluate();
};

class PrefixDec : public UnaryDecrement
{
    public:
        PrefixDec(Variable* v);
        void print();
        value_pair evaluate();
};

class UnaryPlus : public UnaryOperation
{
    protected:
        Expression* exp;
    public:
        UnaryPlus(Expression* e);
        void print();
        value_pair evaluate();
};

class UnaryMinus : public UnaryOperation
{
    protected:
        Expression* exp;
    public:
        UnaryMinus(Expression* e);
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

/// @brief Class to represent the ternary operator in the AST. Derives from Statement
class TernaryOperator : public Expression
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
    protected:
        Expression* exp;
    public:
        LogicalNOT(Expression* e);
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
enum class ACCESS_SPEC{PUBLIC, PRIVATE};
/// @brief Class to represent family declarations 
class FamilyDecl: public Statement
{
    protected:
        Identifier fam_name;                                        /// Identifier of the familie
        list<FamilyMembers*> members = list<FamilyMembers*>();          /// saves the pouinter to the member vars/ function as a List
        optional<pair<Identifier, ACCESS_SPEC>> parent_class ={};   /// saves the Identifier and Access specification of the parent class. if there is no parent class, std::optional is not initialised
    public:
        
        /**
         * @brief Construct a new Family Decl object
         * 
         * @param fam_name_ Identifier of family
         * @param members_ List of pointers to the memeber funcs/vars
         * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional. 
         */
        FamilyDecl(Identifier fam_name_, list<FamilyMembers*> members_ = list<FamilyMembers*>(), optional<pair<Identifier, ACCESS_SPEC>> parent_class_ = {} ):
            fam_name(fam_name_), members(members_), parent_class(parent_class_){}
        /**
         * @brief Construct a new Family Decl object
         *
         * @param fam_name_ Identifier of family
         * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional. 
         */
        FamilyDecl(Identifier fam_name_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_ = {} ):
            fam_name(fam_name_), parent_class(parent_class_){}
        void print();
};
class FamilyMembers: public Statement
{
    protected:
        ACCESS_SPEC access_specifier;
        Statement* member;
    public:
        FamilyMembers(ACCESS_SPEC acc_spec, Statement* member_):access_specifier(acc_spec), member(member_){}
        void print();
};
class ConstructorDeclaration: public Statement
{
    protected:
        Identifier class_name;
        CompoundStatement* body;
        list<Identifier*> arg_list;
    public:
        ConstructorDeclaration(Identifier class_name_, CompoundStatement* body_, list<Identifier*>arg_list_):
                                class_name(class_name_), body(body_), arg_list(arg_list_){};
        void print();

};
/// @brief Class to represent Expression Statements in the AST. Derives from \ref Statement
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

/// @brief Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
    protected:
        list <Statement*> stmt_list;
        CompoundStatement() = default;
    public:
        /// @brief Constructor for Comppund Statement Class
        /// @param l list of statements
        CompoundStatement(list <Statement*> l = new list<Statement*>());
        /// @brief print the content of compound statement
        void print();
};

/* Declaration Statements */

/// @brief Class to represent Function Definition in the AST. Derives from Statement
class FunctionDeclaration : public Statement
{
    protected:
        Identifier* func_name;
        type return_type;
        CompoundStatement* func_body;
        list<Argument*> arg_list;
    public:
        FunctionDeclaration() = delete;
        /// @brief Constructor for Function Definition Class
        /// @param _name function name
        /// @param _t return type
        /// @param _arg_list list of arguments
        /// @param _stmt list of arguments 
        FunctionDeclaration(Identifier* _name, type _t, CompoundStatement* _stmt, list<Argument*> _arg_list = list<Argument*>());
        /// @brief print the content of function definition
        void print();
};
/// @brief Class to represent Variable Declaration in the AST. Derives from Statement
class VariableDeclaration : public Statement
{
    protected:
        type variable_type;
        list <Expression*> variable_list;
    public:
        /// @brief Constructor for function declaration 
        /// @param t type of variable
        /// @param l list of identifires
        VariableDeclaration(type t, list <Expression*> l);
        void print();
};
/// @brief Class to represent definition of driver function in the AST. Derives from CompoundStatement
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
/// @brief Class to represent variable initialization in the AST. Derives from Statement
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

/// @brief Class to represent All Labelled Statements in the AST
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
/// @brief Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public LabeledStatement
{
    public:
        /// @brief Constructor for CaseLabel
        /// @param lb expression to check for in case
        /// @param st_list statement to execute in said case
        CaseLabel(Expression* lb, Statement* st);
        void print();
};
/// @brief Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public LabeledStatement
{
    public:
        /// @brief Constructor for DefaultLabel
        /// @param st_list statement in default case
        DefaultLabel(Statement* st);
        void print();
};

/* Iteration Statements */

/// @brief Class to represent  iterations in the AST. Derives from Statement. Provides base class to classes like WhileLoop
class IterationStatement : public Statement
{
    protected:
        CompoundStatement* body;
        Expression* condition;
    public:
        /// @brief Constructor for IterationStatement
        IterationStatement(CompoundStatement* b, Expression* cond);
        void print();
};
/// @brief Class to represent while loop in the AST. Derives from Statement
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

/// @brief Class to represent for loop in the AST. Derives from Statement
class ForLoop : public IterationStatement
{
    protected:
        ExpressionStatement* initialization;
        ExpressionStatement* condition;
        Expression* counter_updation;
    public:
        ForLoop(CompoundStatement* b, ExpressionStatement* init, ExpressionStatement* cond, Expression* update);
        void print();
};

/*********************************************
 * Selection Statements 
 * *******************************************/
/// @brief Class to represent if - else statements in the AST. Derives from Statement
class IfStatement : public Statement
{
    protected:
        Expression* condition;
        CompoundStatement* if_block;
    public:
        IfStatement(Expression* e, CompoundStatement* block);
        void print();
};
class IfElseStatement : public Statement
{
    protected:
        Expression* if_condition;
        CompoundStatement* if_block, else_block;
    public:
        IfElseStatement(Expression* cond, CompoundStatement* block1, CompoundStatement* block2);
        void print();
};
/// @brief Class to represent switch case statement in the AST. Derives from Statement
class SwitchStatement : public Statement
{
    protected:
        Expression* exp;
        CompoundStatement* block;
    public:
        Switch(Expression* e, CompoundStatement* b);
        void print();
};

/// @brief Provides base class for all jump statements
class JumpStatement : public Statement{};
/// @brief Class to represent 'return' in the AST. Derives from Statement. 
class ReturnStatement: public JumpStatement
{
    protected:
        Expression *return_val;
    public:
        ReturnStatement(Expression* val);
        void print();
};
/// @brief Class to represent 'break' in the AST. Derives from Statement
class BreakStatement: public JumpStatement
{
    public:
        void print();
};
/// @brief Class to represent 'continue' in the AST. Derives from Statement
class ContinueStatement: public JumpStatement
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
        list <Statement*> *stmt_list;
    public:
        Program(list <Statement*> *stmts = new list <Statement*> ());
};

// objects at the base of the tree
extern map <string, value_pair> symTable;
extern Program *root;