#include "AstPrinter.h"
#include <sstream>

std::string AstPrinter::print(std::shared_ptr<Expr<std::string>> expr)
{
  return expr->accept(this);
}

std::string AstPrinter::visitBinaryExpr(Binary<std::string> *expr)
{
  return parenthesize(expr->op.getLexeme(), {expr->left, expr->right});
}

std::string AstPrinter::visitGroupingExpr(Grouping<std::string> *expr)
{
  return parenthesize("group", {expr->expression});
}

std::string AstPrinter::visitLiteralExpr(Literal<std::string> *expr)
{
  return stringify(expr->value);
}

std::string AstPrinter::visitUnaryExpr(Unary<std::string> *expr)
{
  return parenthesize(expr->op.getLexeme(), {expr->right});
}

std::string AstPrinter::parenthesize(
    const std::string &name,
    std::initializer_list<std::shared_ptr<Expr<std::string>>> exprs)
{
  std::ostringstream oss;
  oss << "(" << name;

  for (const auto &expr : exprs)
  {
    oss << " " << expr->accept(this);
  }

  oss << ")";
  return oss.str();
}

std::string AstPrinter::stringify(const std::variant<std::monostate, double, std::string, bool> &value)
{
  return std::visit([](const auto &v) -> std::string
                    {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return "nil";
        } else if constexpr (std::is_same_v<T, double>) {
            return std::to_string(v);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return v;
        } else if constexpr (std::is_same_v<T, bool>) {
            return v ? "true" : "false";
        } else {
            return "unknown";
        } }, value);
}
