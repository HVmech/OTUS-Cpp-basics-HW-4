#pragma once

#include <iostream>
#include <system_error>

class calcexception : public std::exception
{
public:
    enum class CalcErrorCode
    {
        NoError = 0,
        WrongSyntaxNN,
        WrongSyntaxNLb,
        WrongSyntaxOO,
        WrongSyntaxOE,
        WrongSyntaxORb,
        WrongSyntaxLbE,
        WrongSyntaxLbO,
        WrongSyntaxLbRb,
        WrongSyntaxRbN,
        WrongSyntaxRbLb,
        WrongSyntaxBraces,
        WrongSyntaxSpec,
        DivisionByZero,
    };

    explicit calcexception(const CalcErrorCode &errcode)
        : m_errcode(errcode) 
    {};

    [[nodiscard]] const char* what() const noexcept override;

private:
    const CalcErrorCode m_errcode;
};
