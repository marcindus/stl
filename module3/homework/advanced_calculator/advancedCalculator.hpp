#include <string>

enum class ErrorCode {
  BadCharacter,
  BadFormat,
  DivideBy0,
  ModuleOfNonIntegerValue,
  OK,
  SqrtOfNegativeNumber
};

ErrorCode process(std::string input, double *out);
