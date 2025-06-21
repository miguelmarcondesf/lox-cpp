#include <string>
#include <list>

#include "Token.h"

class Scanner
{
public:
  Scanner(const std::string& source);

  std::list<Token> scanTokens();

private:
  std::string source;
  std::list<Token> tokens;

  int start{0};
  int current{0};
  int line{1};

  bool isAtEnd() {
    return current >= source.length();
  }
};
