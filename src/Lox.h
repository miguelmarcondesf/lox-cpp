#ifndef LOX_H
#define LOX_H

#pragma once
#include <string>
#include <vector>

class Lox
{
public:
  Lox();
  static void runScript(int argc, const char* argv[]);
  static void error(int line,const std::string& message);

private:
  static bool hadError;

  static void runFile(const std::string &path);
  static void runPrompt();
  static void run(std::string &source);
  static void report(const int line, const std::string &where, const std::string &message);
};

#endif // LOX_H
