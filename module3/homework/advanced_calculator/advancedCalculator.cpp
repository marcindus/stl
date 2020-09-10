#include <sstream>
#include <functional>
#include <map>
#include <stdexcept>

#include "advancedCalculator.hpp"




ErrorCode process(std::string input, double* out)
{
    std::map<char, std::function<double(double,double)> > operations;

    double a;
    char oper;
    double b;


    std::function<double(double,double)> minus_ = [a,b](double a,double b){return a-b;}; 
    operations.at('-') = minus_;

    std::function<double(double,double)> plus_ = [a,b](double a,double b){return a+b;}; 
    operations.at('+') = plus_;

    std::function<double(double,double)> multipl_ = [a,b](double a,double b){return a*b;}; 
    operations.at('-') = multipl_;

    std::function<double(double,double)> divide_ = [a,b](double a,double b){return a/b;}; 
    operations.at('/') = divide_;

    std::stringstream ss;
    ss << input;
    ss >> a;
    ss >> oper;
    ss >> b;

    try
    {
        *out =  operations.at(oper)(a,b);
    }
    catch (const std::out_of_range& ex)
    {
        return ErrorCode::BadCharacter;
    }

    return ErrorCode::OK;

}
