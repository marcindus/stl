#include "advancedCalculator.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

AmountException::AmountException(std::string p_msg, ErrorCode errorCode_) : logic_error(p_msg), errorCode(errorCode_)
{
}

const char* AmountException::what() const throw()
{
    std::ostringstream o;
    o << logic_error::what();
    return o.str().c_str();
}

ErrorCode parse(const std::string& input, std::vector<std::string>& result)
{

    std::regex command("\\s*([-+]?[0-9]*\\.[0-9]+|[+-]?[0-9]+)\\s*"
                       "\\s*([-+*$/^%]{1})\\s*"
                       "\\s*([-+]?[0-9]*\\.[0-9]+|[-]?[0-9]+)\\s*");

    std::regex command_factorial("\\s*([-+]?[0-9]*\\.[0-9]+|[+-]?[0-9]+)\\s*"
                                 "\\s*(\\!)\\s*");

    std::smatch match_result;

    if (std::regex_match(input, match_result, command))
    {
        auto match_iter = match_result.begin();

        for (std::advance(match_iter, 1); match_iter != match_result.end(); advance(match_iter, 1))
        {
            result.push_back(*match_iter);
        }
        return ErrorCode::OK;
    }
    else if (std::regex_match(input, match_result, command_factorial))
    { // fix me - copy pasta, here shoul be done conversion to double
        auto match_iter = match_result.begin();
        for (std::advance(match_iter, 1); match_iter != match_result.end(); advance(match_iter, 1))
        {
            result.push_back(*match_iter);
        }
        return ErrorCode::OK;
    }

    return ErrorCode::BadFormat;
}

ErrorCode process(std::string input, double* out)
{
    std::map<std::string, std::function<double(double, double)>> operations;
    std::vector<std::string> parsed{};
    ErrorCode status_ = parse(input, parsed);

    if(status_ != ErrorCode::OK) return status_;

    double a = 0;
    double b = 0;
    std::string oper;

    if(parsed.size() == 2)
    {
        a = atof(parsed[0].c_str());
        oper = parsed[1];
    }

    else if (parsed.size() == 3)
    {
        a = atof(parsed[0].c_str());
        oper = parsed[1];
        b = atof(parsed[2].c_str());
    }
    else 
    {
       return  ErrorCode::BadFormat;
    }

    operations["-"] = [a, b](double a, double b) {
        return a - b; };
    operations["+"] = [a, b](double a, double b) {
        return a + b; };
    operations["*"] = [a, b](double a, double b) {
        return a * b; };
    operations["/"] = [a, b](double a, double b) {
        if (b == 0)
        {
            throw AmountException("blah blah", ErrorCode::DivideBy0);
            return 0.0; // Why!
        }
        return a / b;
    };

    operations["^"] = [a, b](double a, double b) {
        return pow(a, b); };

    operations["%"] = [a, b](double a, double b) {
        if (((int)a - a) != 0 or (int) b - b != 0)
        {
            throw AmountException("blah blah", ErrorCode::ModuleOfNonIntegerValue);
        }

        return (int)a % (int)b;
    };

    operations["$"] = [a, b](double a, double b) {
        if (a < 0)
        {
            throw AmountException("blah blah", ErrorCode::SqrtOfNegativeNumber);
            return 0.0;
        }

        return pow(a, 1 / b);
    };

    operations["!"] = [a, b](double a, double b) {
        return a; };

    try
    {
        *out = operations.at(oper)(a, b);
        std::cout << "a " << a << " b " << b << " oper" << oper << "result " << *out << "\n";
    }
    catch (const std::out_of_range& ex)
    {
        return ErrorCode::BadCharacter;
    }
    catch (const AmountException& ex)
    {
        return ex.errorCode;
    }
    return ErrorCode::OK;
}
