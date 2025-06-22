#include "Scanner.h"
#include "Token.h"
#include "Lox.h"
#include "Keyword.h"

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
  case '/':
    if (match('/'))
    {
      // A comment goes until the end of the line.
      while (peek() != '\n' && !isAtEnd())
        advance();
    }
    else
    {
      addToken(TokenType::SLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    // Ignore whitespace.
    break;
  case '\n':
    line++;
    break;
  case '"':
    string();
    break;
  case 'o':
    if (match('r'))
    {
      addToken(TokenType::OR);
    }
    break;

  default:
    if (isDigit(c))
    {
      number();
    }
    else if (isAlpha(c))
    {
      identifier();
    }
    else
    {
      Lox::error(line, "Unexpected character.");
    }
  }
}

bool Scanner::match(char expected)
{
  if (isAtEnd())
    return false;
  if (source.at(current) != expected)
    return false;

  current++;
  return true;
}

void Scanner::string()
{
  while (peek() != '"' && !isAtEnd())
  {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (isAtEnd())
  {
    Lox::error(line, "Unterminated string.");
    return;
  }

  // The closing ".
  advance();

  // Trim the surrounding quotes.
  std::string value = source.substr(start + 1, current - 1);
  addToken(TokenType::STRING, value);
}

void Scanner::number()
{
  while (isDigit(peek()))
    advance();

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext()))
  {
    // Consume the "."
    advance();

    while (isDigit(peek()))
      advance();
  }

  addToken(TokenType::NUMBER, std::stod(source.substr(start, current)));
}

void Scanner::identifier()
{
  while (isAlphaNumeric(peek()))
    advance();

  std::string text = source.substr(start, current);
  auto keywordIt = getKeywordMap().find(text);
  TokenType type = (keywordIt != getKeywordMap().end()) ? keywordIt->second : TokenType::IDENTIFIER;

  addToken(type);
}
