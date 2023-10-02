#pragma once

#include <istream>

#include "astnode.hpp"
#include "lexer.hpp"

class Parser
{
public:
    explicit Parser(Lexer &lexer)
        : lexer_(lexer) {}

    Parser(const Parser &other) = delete;

    Parser &operator=(const Parser &other) = delete;

    ~Parser() = default;

    ASTNode *parse();

    bool calcmode() const;

    void checkbraces();

private:
    void next_token();

    ASTNode *expr();

    ASTNode *term();

    ASTNode *prim();

    ASTNode *spec();

    int braces_ = 0;
    bool mode_ = true;
    Lexer &lexer_;
    Lexer::Token tok_ = Lexer::Token::Spec;
};
