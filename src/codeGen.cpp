#include "astNodes.h"

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Utils/IntegerDivision.h>

using namespace std;
using namespace llvm;

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;


Value *IntegerLiteral::codegen()
{
    return ConstantInt::get(*TheContext, APSInt(get<int>(value)));
}

Value *::StringLiteral::codegen()
{
    return ConstantDataArray::getString(*TheContext, get<string>(value), true);
}

Value *BooleanLiteral::codegen()
{
    return ConstantInt::get(*TheContext, APSInt(get<bool>(value)));
}

// Value *Identifier::codegen()
// {
//     return Builder->CreateLoad();
// }

Value *Addition::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (LHS->get_type() == RHS->get_type())
    {
        if (LHS->get_type() == TYPE::INT)
        {
            return Builder->CreateAdd(L, R, "addtmp");
        }
        else if (LHS->get_type() == TYPE::FLOAT)
        {
            return Builder->CreateFAdd(L, R, "addtmp");
        }
        else if (LHS->get_type() == TYPE::BOOL)
        {
            return Builder->CreateAdd(L, R, "addtmp");
        }
    }

}

Value *Subtraction::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            return Builder->CreateSub(L, R, "subtmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFAdd(L, R, "subtmp");
        }
        else if (left_eval.first == BOOL_TYPE)
        {
            return Builder->CreateAdd(L, R, "subtmp");
        }
    }

}

Value *Multiplication::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            return Builder->CreateMul(L, R, "multmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFMul(L, R, "multmp");
        }
        else if (left_eval.first == BOOL_TYPE)
        {
            return Builder->CreateMul(L, R, "multmp");
        }
    }

}

Value *Division::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            return Builder->CreateSDiv(L, R, "divtmp");
        }
        else if (left_eval.first == FLOAT_TYPE && right_eval.second.fvalue != 0)
        {
            return Builder->CreateFDiv(L, R, "divtmp");
        }
        else if (left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            return Builder->CreateUDiv(L, R, "divtmp");
        }
    }
}

Value *ModularDiv::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE && right_eval.second.ivalue != 0)
        {
            Value *Quotient = Builder->CreateUDiv(L, R, "divtmp");
            Value *Product = Builder->CreateMul(R, Quotient, "multmp");
            return Builder->CreateSub(L, Product, "subtmp");
        }
        else if (left_eval.first == BOOL_TYPE && right_eval.second.bvalue != 0)
        {
            Value *Quotient = Builder->CreateUDiv(L, R, "divtmp");
            Value *Product = Builder->CreateMul(R, Quotient, "multmp");
            return Builder->CreateSub(L, Product, "subtmp");
        }
    }
}

Value* CompGT::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            return Builder->CreateICmpSGT(L, R, "cmptmp");
        }
        else if (left_eval.first == BOOL_TYPE || left_eval.first == CHAR_TYPE)
        {
            return Builder->CreateICmpUGT(L, R, "cmptmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFCmpUGT(L, R, "cmptmp");
        }
    }
}

Value* CompLT::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            return Builder->CreateICmpSLT(L, R, "cmptmp");
        }
        else if (left_eval.first == BOOL_TYPE || left_eval.first == CHAR_TYPE)
        {
            return Builder->CreateICmpULT(L, R, "cmptmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFCmpULT(L, R, "cmptmp");
        }
    }
}

Value* CompGE::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE)
        {
            return Builder->CreateICmpSGE(L, R, "cmptmp");
        }
        else if (left_eval.first == BOOL_TYPE || left_eval.first == CHAR_TYPE)
        {
            return Builder->CreateICmpUGE(L, R, "cmptmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFCmpUGE(L, R, "cmptmp");
        }
    }
}

Value* CompLE::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (LHS->get_type() == RHS->get_type())
    {
        if (LHS->get_type() == TYPE::INT)
        {
            return Builder->CreateICmpSLE(L, R, "cmptmp");
        }
        else if (LHS->get_type() == TYPE::BOOL || LHS->get_type() == TYPE::STRING)
        {
            return Builder->CreateICmpULE(L, R, "cmptmp");
        }
        else if (LHS->get_type() == TYPE::FLOAT)
        {
            return Builder->CreateFCmpULE(L, R, "cmptmp");
        }
    }
}

Value* CompEQ::codegen()
{
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    datatype left_eval = LHS->evaluate();
    datatype right_eval = RHS->evaluate();
    if(!L || !R)
    {
        return nullptr;
    }
    if (left_eval.first == right_eval.first)
    {
        if (left_eval.first == INT_TYPE || left_eval.first == BOOL_TYPE || left_eval.first == CHAR_TYPE)
        {
            return Builder->CreateICmpEQ(L, R, "cmptmp");
        }
        else if (left_eval.first == FLOAT_TYPE)
        {
            return Builder->CreateFCmpUEQ(L, R, "cmptmp");
        }
    }
}


Value *IfStatement::codegen()
{
    Value *cond = condition->codegen();
    if(!cond)
    {
        return nullptr;
    }
    cond = Builder->CreateICmpNE(cond, ConstantInt::get(*TheContext, APSInt(0)), "ifcond");

    Function *TheFunction = Builder->GetInsertBlock()->getParent();
    BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "then", TheFunction);
    BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "ifcont");

    Builder->CreateBr(ThenBB);
    Builder->SetInsertPoint(ThenBB);

    Value *ThenV = if_block->codegen();
    if (!ThenV)
    {
        return nullptr;
    }
    
    Builder->CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder->GetInsertBlock();
    TheFunction->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);

    PHINode *PN = Builder->CreatePHI(Type::getDoubleTy(*TheContext), 2, "iftmp");

    PN->addIncoming(ThenV, ThenBB);
    return PN;
}

Value *IfElseStatement::codegen()
{
    Value *cond = if_condition->codegen();
    if(!cond)
    {
        return nullptr;
    }
    cond = Builder->CreateICmpNE(cond, ConstantInt::get(*TheContext, APSInt(0)), "ifcond");

    Function *TheFunction = Builder->GetInsertBlock()->getParent();
    BasicBlock *ThenBB = BasicBlock::Create(*TheContext, "then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(*TheContext, "else");
    BasicBlock *MergeBB = BasicBlock::Create(*TheContext, "ifcont");

    Builder->CreateCondBr(cond, ThenBB, ElseBB);
    Builder->SetInsertPoint(ThenBB);

    Value *ThenV = if_block->codegen();
    if (!ThenV)
    {
        return nullptr;
    }

    Builder->CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder->GetInsertBlock();
    TheFunction->getBasicBlockList().push_back(ElseBB);
    Builder->SetInsertPoint(ElseBB);

    Value *ElseV = else_block->codegen();
    if (!ElseV)
    {
        return nullptr;
    }

    Builder->CreateBr(MergeBB);
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    ElseBB = Builder->GetInsertBlock();

    // Emit merge block.
    TheFunction->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);
    PHINode *PN = Builder->CreatePHI(Type::getDoubleTy(*TheContext), 2, "iftmp");

    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    return PN;
}