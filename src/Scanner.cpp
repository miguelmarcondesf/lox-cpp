#include "Scanner.h"
#include "Token.h"

#include "TokenType.h"

Scanner::Scanner(const std::string& source)
    : source(source) {};

std::list<Token> Scanner::scanTokens() {
  while(!isAtEnd()) {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  tokens.push_back(Token(TokenType::END_OF_FILE, "", nullptr, line));
  return tokens;
}
