#include <sstream>
#include <functional>
#include <map>
#include <stdexcept>
#include <iostream>
#include <regex>
#include <stdlib.h>
#include <math.h>
#include "advancedCalculator.hpp"

std::vector<std::string>  parse(const std::string& input) {



    std::regex double_reg("\\s*([-+]?[0-9]*\\.[0-9]+|[+-]?[0-9]+)\\s*" "\\s*([-+*$/^%]{1})\\s*" "\\s*([-+]?[0-9]*\\.[0-9]+|[-]?[0-9]+)\\s*");
//    std::regex double_reg("\\s*([-+]?[0-9]+)\\s*" "\\s*([-+*$])\\s*" "\\s*([-+]?[0-9]+)\\s*");

    std::smatch match_result;
    std::vector<std::string > result;


    if (std::regex_match(input, match_result, double_reg))
    {
      auto match_iter = match_result.begin();

      for (std::advance(match_iter, 1); match_iter != match_result.end(); advance(match_iter, 1))
      {
          result.push_back(*match_iter);
      }

      return result;

    }
    std::cout << "No match!" << std::endl;
    return result;
}


ErrorCode process(std::string input, double* out)
{
    std::map<std::string, std::function<double(double,double)> > operations;
    std::vector<std::string> parsed = parse(input);

    double a = atof(parsed[0].c_str());
    std::string oper = parsed[1];
    double b = atof(parsed[2].c_str());


    std::function<double(double,double)> minus_ = [a,b](double a,double b){return a-b;};
    operations["-"] = minus_;

    std::function<double(double,double)> plus_ = [a,b](double a,double b){return a+b;};
    operations["+"] = plus_;

    std::function<double(double,double)> multipl_ = [a,b](double a,double b){return a*b;};
    operations["*"] = multipl_;

    std::function<double(double,double)> divide_ = [a,b](double a,double b){return a/b;};
    operations["/"] = divide_;

    std::function<double(double,double)> power_ = [a,b](double a,double b){return pow(a,b);};
    operations["^"] = power_;

    std::function<double(double,double)> sqrt_ = [a,b](double a,double b){return pow(a,1/b);};
    operations["$"] = sqrt_;



    try
    {
        *out =  operations.at(oper)(a,b);

//        std::cout << "a " << a << " b " << b <<  " oper" << oper << "result " << *out << "\n";
    }
    catch (const std::out_of_range& ex)
    {
        return ErrorCode::BadCharacter;
    }

    return ErrorCode::OK;

}
