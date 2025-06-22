#ifndef KEYWORD_H
#define KEYWORD_H

#include <unordered_map>
#include <string>
#include "TokenType.h"

const std::unordered_map<std::string, TokenType> &getKeywordMap()
{
  static const std::unordered_map<std::string, TokenType> keywords = {
      {"and", TokenType::AND},
      {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},
      {"false", TokenType::FALSE},
      {"for", TokenType::FOR},
      {"fun", TokenType::FUN},
      {"if", TokenType::IF},
      {"nil", TokenType::NIL},
      {"or", TokenType::OR},
      {"print", TokenType::PRINT},
      {"return", TokenType::RETURN},
      {"super", TokenType::SUPER},
      {"this", TokenType::THIS},
      {"true", TokenType::TRUE},
      {"var", TokenType::VAR},
      {"while", TokenType::WHILE}};
  return keywords;
}

#endif
