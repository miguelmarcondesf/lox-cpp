#include "Lox.h"
#include "Token.h"
#include "Scanner.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool Lox::hadError = false;
Lox::Lox() {};

void Lox::runScript(int argc, const char *argv[])
{
  if (argc > 1)
  {
    std::cout << "Usage: jlox [script]" << std::endl;
    exit(64); // EX_USAGE
  }
  else if (argc == 1)
  {
    runFile(argv[0]);
  }
  else
  {
    runPrompt();
  }
}

void Lox::runFile(const std::string &path)
{
  std::ifstream file(path);
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open file " << path << std::endl;
    exit(74); // EX_IOERR
    return;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();
  file.close();

  run(content);

  if (hadError)
    exit(65); // EX_DATAERR
}

// "REPL" Read a line of input
// Evaluate it, Print the result,
// then Loop and do it all over again
void Lox::runPrompt()
{
  std::string line;

  for (;;)
  {
    std::cout << "> ";
    std::cout.flush();

    if (!std::getline(std::cin, line))
    {
      break;
    }

    run(line);
    hadError = false;
  }
}

void Lox::run(std::string &source)
{
  Scanner scanner(source);
  std::list<Token> tokens = scanner.scanTokens();

  for (const Token &token : tokens)
  {
    std::cout << token.toString() << std::endl;
  }
}

void Lox::error(int line, const std::string &message)
{
  report(line, "", message);
}

void Lox::report(const int line, const std::string &where, const std::string &message)
{
  std::cout << "[line " + std::to_string(line) + "] Error" + where + ": " + message << std::endl;
  hadError = true;
}
