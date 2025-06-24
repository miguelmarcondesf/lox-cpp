#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <string>
#include <memory>
#include <sstream>
#include <initializer_list>
#include "Expr.h"

class AstPrinter : public ExprVisitor {
public:
    std::string print(std::shared_ptr<Expr> expr);

    std::string visitBinaryExpr(Binary* expr) override;
    std::string visitGroupingExpr(Grouping* expr) override;
    std::string visitLiteralExpr(Literal* expr) override;
    std::string visitUnaryExpr(Unary* expr) override;

private:
    std::string parenthesize(const std::string& name, std::initializer_list<std::shared_ptr<Expr>> exprs);
    std::string stringify(const std::variant<std::monostate, double, std::string, bool>& value);
};

#endif // AST_PRINTER_H
