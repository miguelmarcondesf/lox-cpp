#ifndef EXPR_H
#define EXPR_H

#include <memory>
#include <variant>
#include <string>
#include "Token.h"

class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor {
  public:
    virtual ~ExprVisitor() = default;

    virtual std::string visitBinaryExpr(Binary* expr) = 0;
    virtual std::string visitGroupingExpr(Grouping* expr) = 0;
    virtual std::string visitLiteralExpr(Literal* expr) = 0;
    virtual std::string visitUnaryExpr(Unary* expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;

    virtual std::string accept(ExprVisitor* visitor) = 0;
};

// Expr::Binary
class Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, const Token& op, std::shared_ptr<Expr> right)
        : left(left), op(op), right(right) {}

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    std::string accept(ExprVisitor* visitor) override {
        return visitor->visitBinaryExpr(this);
    }
};

class Grouping : public Expr {
public:
    Grouping(std::shared_ptr<Expr> expression)
        : expression(expression) {}

    std::shared_ptr<Expr> expression;

    std::string accept(ExprVisitor* visitor) override {
        return visitor->visitGroupingExpr(this);
    }
};

class Literal : public Expr {
public:
    Literal(const std::variant<std::monostate, double, std::string, bool>& value)
        : value(value) {}

    std::variant<std::monostate, double, std::string, bool> value;

    std::string accept(ExprVisitor* visitor) override {
        return visitor->visitLiteralExpr(this);
    }
};

class Unary : public Expr {
public:
    Unary(const Token& op, std::shared_ptr<Expr> right)
        : op(op), right(right) {}

    Token op;
    std::shared_ptr<Expr> right;

    std::string accept(ExprVisitor* visitor) override {
        return visitor->visitUnaryExpr(this);
    }
};

#endif // EXPR_H
