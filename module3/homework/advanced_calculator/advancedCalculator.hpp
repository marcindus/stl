#include <string>
#include <vector>

enum class ErrorCode {
  BadCharacter,
  BadFormat,
  DivideBy0,
  ModuleOfNonIntegerValue,
  OK,
  SqrtOfNegativeNumber
};

ErrorCode process(std::string input, double *out);


std::vector<std::string>  parse(const std::string& input);
