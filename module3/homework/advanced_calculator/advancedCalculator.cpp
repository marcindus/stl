#include "advancedCalculator.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

std::vector<std::string> parse(const std::string &input) {

  std::regex command("\\s*([-+]?[0-9]*\\.[0-9]+|[+-]?[0-9]+)\\s*"
                     "\\s*([-+*$/^%]{1})\\s*"
                     "\\s*([-+]?[0-9]*\\.[0-9]+|[-]?[0-9]+)\\s*");

  std::regex command_factorial("\\s*([-+]?[0-9]*\\.[0-9]+|[+-]?[0-9]+)\\s*" "\\s*(\\!)\\s*");

  std::smatch match_result;
  std::vector<std::string> result;

  if (std::regex_match(input, match_result, command)) {
    auto match_iter = match_result.begin();

    for (std::advance(match_iter, 1); match_iter != match_result.end();
         advance(match_iter, 1)) {
      result.push_back(*match_iter);
    }

    return result;

  } else if (std::regex_match(input, match_result, command_factorial)) {
    auto match_iter = match_result.begin();
    for (std::advance(match_iter, 1); match_iter != match_result.end();
         advance(match_iter, 1)) {
      result.push_back(*match_iter);
    }
    return result;
  }

  std::cout << "No match!" << std::endl;
  return result;
}

ErrorCode process(std::string input, double *out) {
  std::map<std::string, std::function<double(double, double)>> operations;
  std::vector<std::string> parsed = parse(input);

  double a = atof(parsed[0].c_str());
  std::string oper = parsed[1];
  double b = atof(parsed[2].c_str());

  operations["-"] = [a, b](double a, double b) { return a - b; };
  operations["+"] = [a, b](double a, double b) { return a + b; };
  operations["*"] = [a, b](double a, double b) { return a * b; };
  operations["/"] = [a, b](double a, double b) { return a / b; };
  operations["^"] = [a, b](double a, double b) { return pow(a, b); };
  operations["%"] = [a, b](double a, double b) { return (int)a % (int)b; }; //!!!!!
  operations["$"] = [a, b](double a, double b) { return pow(a, 1 / b); };
  operations["!"] = [a, b](double a, double b) { return a; };



  try {
    *out = operations.at(oper)(a, b);
    //        std::cout << "a " << a << " b " << b <<  " oper" << oper <<
    //        "result " << *out << "\n";
  } catch (const std::out_of_range &ex) {
    return ErrorCode::BadCharacter;
  }

  return ErrorCode::OK;
}
