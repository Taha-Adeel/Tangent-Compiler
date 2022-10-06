#include <stdlib.h>
#include <iostream>
#include <list>

using namespace std;

class ASTNode
{
    virtual void print() = 0;
};

class Expression : public ASTNode
{

};

class Statement : public ASTNode
{
    
};

class Program : public ASTNode
{
    protected:
        list <Statement*> stmt_list;
    public:
        Program(list <Statement*> stmt_list);
};