#include "parser.hpp"
#include "tokens.hpp"
#include "calcexception.hpp"

using Token = Lexer::Token;
using CalcErrorCode = calcexception::CalcErrorCode;

ASTNode *Parser::parse() { return expr(); }

bool Parser::calcmode() const {return mode_; }

void Parser::checkbraces() {
    if(braces_) {
        // wrong syntax: count of '(' != count of ')'
        throw calcexception{CalcErrorCode::WrongSyntaxBraces};
    } else {
        return;
    }
}

void Parser::next_token() {
    switch (tok_) {
        case Token::Number:
        case Token::Name:
            tok_ = lexer_.next_token();
            switch (tok_) {
                case Token::Number:
                case Token::Name:
                    // wrong syntax: a b
                    throw calcexception{CalcErrorCode::WrongSyntaxNN};
                case Token::Lbrace:
                    // wrong syntax: a (
                    throw calcexception{CalcErrorCode::WrongSyntaxNLb};
                default:
                    return;
            }
        case Token::Operator:
            tok_ = lexer_.next_token();
            switch (tok_) {
                case Token::Operator:
                    // wrong syntax: + *
                    throw calcexception{CalcErrorCode::WrongSyntaxOO};
                case Token::Rbrace:
                    // wrong syntax: + (
                    throw calcexception{CalcErrorCode::WrongSyntaxORb};
                case Token::End:
                    // wrong syntax: + _
                    throw calcexception{CalcErrorCode::WrongSyntaxOE};
                default:
                    return;
            }
        case Token::Rbrace:
            --braces_;
            tok_ = lexer_.next_token();
            switch (tok_) {
                case Token::Number:
                case Token::Name:
                    // wrong syntax: ) a
                    throw calcexception{CalcErrorCode::WrongSyntaxRbN};
                case Token::Lbrace:
                    // wrong syntax: ) (
                    throw calcexception{CalcErrorCode::WrongSyntaxRbLb};
                default:
                    return;
            }
        case Token::Lbrace:
            ++braces_;
            tok_ = lexer_.next_token();
            switch (tok_){
                case Token::Rbrace:
                    // wrong syntax: ( )
                    throw calcexception{CalcErrorCode::WrongSyntaxLbRb};
                case Token::End:
                    // wrong syntax: ( _
                    throw calcexception{CalcErrorCode::WrongSyntaxLbE};
                case Token::Operator:
                    switch(lexer_.get_operator().front()){
                        case '-':
                            return;
                        default:
                            // wrong syntax: ( +
                            throw calcexception{CalcErrorCode::WrongSyntaxLbO}; 
                    }
                default:
                    return;                    
            }
        default:
            tok_ = lexer_.next_token();
            return;
    }
}

ASTNode *Parser::expr() {
    // parse addition and subsctruction
    ASTNode *root = term();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            switch (lexer_.get_operator().front()) {
            case '+':
                // new addition
                root = new Add(root, expr());
                return root;
            case '-':
                // new subsctruction
                root = new Sub(root, expr());
                return root;
            default:
                return root;
            }
            break;
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            // operator
            switch (lexer_.get_operator().front()) {
            case '*':
                // new multiplication
                root = new Mul(root, term());
                return root;
            case '/':
                // new division
                root = new Div(root, term());
                return root;
            default:
                return root;
            }
            break;
        }
        case Token::Lbrace:
            // left brace
            root = expr();
            next_token();
            continue;
            break;
        case Token::Rbrace:
            // right brace
            return root;
        default:
            return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers, variables and special conditions
    ASTNode *node = nullptr;

    // special conditions detection samples:
    // A: -1*... -> "-" isn't a new sub, it's just a number (Token::Spec)
    // B: -(...) -> "-" isn't a new sub, it's brace expression inversion (Token::Lbrace)
    if (tok_ == Token::Spec || tok_ == Token::Lbrace) {
        node = spec();
        if (node) return node;
    } else {
        next_token();
    }

    switch (tok_) {
    case Token::Number:
        // new number
        node = new Number(lexer_.get_number());
        break;
    case Token::Name:
        // new variable or function (further improvements)
        mode_ = false;
        node = new Variable(lexer_.get_name());
        break;
    case Token::Lbrace:
        return node;
    default:
        break;
    }
    next_token();
    return node;
}

ASTNode *Parser::spec() {
    // parse special conditions
    ASTNode *spec = nullptr;
    next_token();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            // operator
            switch (lexer_.get_operator().front()) {
            case '-':
                // special conditions
                spec = new Number(-1);
                spec = new Mul(term(), spec);
                return spec;
            default:
                // wrong operator after spec token
                throw calcexception{CalcErrorCode::WrongSyntaxSpec};
            }
            break;
        }
        default:
            // skip special conditions: no reason for spec
            return spec;
        }
    }
}