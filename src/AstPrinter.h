#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "Expr.h"
#include <memory>
#include <string>
#include <variant>

class AstPrinter : public ExprVisitor<std::string>
{
public:
  std::string print(std::shared_ptr<Expr<std::string>> expr);

  std::string visitBinaryExpr(Binary<std::string> *expr) override;
  std::string visitGroupingExpr(Grouping<std::string> *expr) override;
  std::string visitLiteralExpr(Literal<std::string> *expr) override;
  std::string visitUnaryExpr(Unary<std::string> *expr) override;

private:
  std::string parenthesize(const std::string &name, std::initializer_list<std::shared_ptr<Expr<std::string>>> exprs);
  std::string stringify(const std::variant<std::monostate, double, std::string, bool> &value);
};

#endif // AST_PRINTER_H
