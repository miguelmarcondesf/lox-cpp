#pragma once
#include <string>
#include <vector>

namespace loxcpp
{
  class Lox
  {
  public:
    Lox();
    void main(std::vector<std::string> &args);
    void error(const int line, const std::string &message);

  private:
    bool hadError;

    void runFile(const std::string &path);
    void runPrompt();
    void run(std::string &source);
    void report(const int line, const std::string &where, const std::string &message);
  };
} // namespace lox
