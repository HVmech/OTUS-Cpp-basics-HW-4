#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode
{
public:
    explicit ASTNode(const std::string &repr);

    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    ASTNode(const ASTNode &other) = delete;

    ASTNode &operator=(const ASTNode &other) = delete;

    virtual ~ASTNode();
    
    std::string repr() const
    {
        return repr_;
    }

    void print(std::ostream &out) const;

    int value()
    {
        return val_;
    }

protected:
    void set_val(int val)
    {
        val_ = val;
    }

private:
    void inner_print(std::ostream &out, size_t indent) const;

    int val_;
    std::string repr_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};
