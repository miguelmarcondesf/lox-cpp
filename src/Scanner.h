#include <string>
#include <list>

#include "Token.h"
#include "Lox.h"

class Scanner
{
public:
  Scanner(const std::string& source);

  std::list<Token> scanTokens();

private:
  // loxcpp::Lox& lox;

  std::string source;
  std::list<Token> tokens;

  int start{0};
  int current{0};
  int line{1};

  bool isAtEnd() const {
    return current >= source.length();
  }
  char advance() {
    return source.at(current++);
  }
  void addToken(TokenType type) {
    addToken(type, std::monostate{});
  }
  void addToken(TokenType type, const std::variant<std::monostate, double, std::string, bool>& literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
  }
  void scanToken();
};
