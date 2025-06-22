#include "Scanner.h"
#include "Token.h"
#include "Lox.h"

Scanner::Scanner(const std::string &source)
    : source(source) {};

std::list<Token> Scanner::scanTokens()
{
  while (!isAtEnd())
  {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  tokens.push_back(Token(TokenType::END_OF_FILE, "", std::monostate{}, line));
  return tokens;
}

void Scanner::scanToken()
{
  char c = advance();
  switch (c)
  {
  case '(':
    addToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '.':
    addToken(TokenType::DOT);
    break;
  case '-':
    addToken(TokenType::MINUS);
    break;
  case '+':
    addToken(TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(TokenType::STAR);
    break;
  case '!':
    addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  default:
    Lox::error(line, "Unexpected character.");
    break;
  }
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}
