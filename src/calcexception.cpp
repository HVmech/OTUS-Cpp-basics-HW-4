#include "calcexception.hpp"

const char* calcexception::what() const noexcept {
    switch(m_errcode){
        case CalcErrorCode::NoError:
            return "no Error";
        case CalcErrorCode::WrongSyntaxNN:
            return "wrong syntax: num/name num/name";
        case CalcErrorCode::WrongSyntaxNLb:
            return "wrong syntax: num/name lbrace";
        case CalcErrorCode::WrongSyntaxOO:
            return "wrong syntax: operator operator";
        case CalcErrorCode::WrongSyntaxOE:
            return "wrong syntax: operator end";
        case CalcErrorCode::WrongSyntaxORb:
            return "wrong syntax: operator rbrace";
        case CalcErrorCode::WrongSyntaxLbE:
            return "wrong syntax: lbrace end";
        case CalcErrorCode::WrongSyntaxLbO:
            return "wrong syntax: lbrace operator";
        case CalcErrorCode::WrongSyntaxLbRb:
            return "wrong syntax: lbrace rbrace";
        case CalcErrorCode::WrongSyntaxRbN:
            return "wrong syntax: rbrace num/name";
        case CalcErrorCode::WrongSyntaxRbLb:
            return "wrong syntax: rbrace lbrace";
        case CalcErrorCode::WrongSyntaxBraces:
            return "wrong syntax: lbraces nmber isn't equal to rbrace number";
        case CalcErrorCode::WrongSyntaxSpec:
            return "wrong syntax: spec operator";
        case CalcErrorCode::DivisionByZero:
            return "division by zero";
        default:
            return "unknown error";
    }
};