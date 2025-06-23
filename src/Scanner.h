#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <list>

#include "Token.h"
#include "Lox.h"

class Scanner
{
public:
  Scanner(const std::string &source);

  std::list<Token> scanTokens();

private:
  std::string source;
  std::list<Token> tokens;

  int start{0};
  int current{0};
  int line{1};

  void scanToken();
  bool match(char expected);
  void string();
  void number();
  void identifier();

  bool isAtEnd() const
  {
    return current >= source.length();
  }
  char advance()
  {
    return source.at(current++);
  }
  void addToken(TokenType type)
  {
    addToken(type, std::monostate{});
  }

  void addToken(TokenType type, const std::variant<std::monostate, double, std::string, bool> &literal)
  {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
  }
  char peek()
  {
    if (isAtEnd())
      return '\0';
    return source.at(current);
  }
  char peekNext()
  {
    if (current + 1 >= source.length())
      return '\0';
    return source.at(current + 1);
  }

  bool isDigit(char c)
  {
    // return c >= '0' && c <= '9';
    return std::isdigit(static_cast<unsigned char>(c));
  }
  bool isAlpha(char c)
  {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
  }

  bool isAlphaNumeric(char c)
  {
    return isAlpha(c) || isDigit(c);
  }
};

#endif // SCANNER_H
