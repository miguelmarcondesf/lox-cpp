#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>
#include <variant>

class Token
{
public:
  Token(TokenType type, const std::string &lexeme, const std::variant<std::monostate, double, std::string, bool> &literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

  // TODO make type private again after improve interpreter reading
  const TokenType type;

  auto toString() const
  {
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " + std::to_string(literal.index());
  }

  const std::string& getLexeme() const {
    return lexeme;
  }
  private:
    const std::string lexeme;
    std::variant<std::monostate, double, std::string, bool> literal;
    const int line;
};

#endif // TOKEN_H
