#pragma once

#include <string>

#include "calcexception.hpp"
#include "astnode.hpp"

class Number : public ASTNode {
  public:
    Number(int val)
        : ASTNode(std::to_string(val))
        {set_val(val);}
};

class Variable : public ASTNode {
  public:
    Variable(std::string name)
        : ASTNode(name)
        // set value (further improvements)
        {set_val(1);}
};

class Add : public ASTNode {
  public:
    Add(ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(1, '+'), lhs, rhs)
        {set_val(lhs->value()+rhs->value()); }
};

class Sub : public ASTNode {
  public:
    Sub(ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(1, '-'), lhs, rhs)
        {set_val(lhs->value()-rhs->value()); }
};

class Mul : public ASTNode {
  public:
    Mul(ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(1, '*'), lhs, rhs)
        {set_val(lhs->value()*rhs->value()); }
};

class Div : public ASTNode {
  public:
    Div(ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(1, '/'), lhs, rhs)
        {
          if(rhs->value()) {
            set_val(lhs->value()/rhs->value());
          } else{
            throw calcexception{calcexception::CalcErrorCode::DivisionByZero};
          }
        }
};