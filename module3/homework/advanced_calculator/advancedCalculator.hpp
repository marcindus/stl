#pragma once

#include <stdexcept>
#include <string>
#include <vector>

enum class ErrorCode
{
    BadCharacter,
    BadFormat,
    DivideBy0,
    ModuleOfNonIntegerValue,
    OK,
    SqrtOfNegativeNumber
};

ErrorCode process(std::string input, double* out);

ErrorCode parse(const std::string& input, std::vector<std::string>& result);

class CalculationException : public std::logic_error
{
public:
    CalculationException(std::string p_msg, ErrorCode errorCode_);
    const char* what() const throw() override;
    ErrorCode errorCode;
};
