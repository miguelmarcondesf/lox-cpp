#ifndef EXPR_H
#define EXPR_H

#include <memory>
#include <variant>
#include <string>
#include "Token.h"

template<typename R> class Binary;
template<typename R> class Grouping;
template<typename R> class Literal;
template<typename R> class Unary;

template<typename R>
class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;

    virtual R visitBinaryExpr(Binary<R>* expr) = 0;
    virtual R visitGroupingExpr(Grouping<R>* expr) = 0;
    virtual R visitLiteralExpr(Literal<R>* expr) = 0;
    virtual R visitUnaryExpr(Unary<R>* expr) = 0;
};

template<typename R>
class Expr {
public:
    virtual ~Expr() = default;
    virtual R accept(ExprVisitor<R>* visitor) = 0;
};

template<typename R>
class Binary : public Expr<R> {
public:
    Binary(std::shared_ptr<Expr<R>> left, const Token& op, std::shared_ptr<Expr<R>> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::shared_ptr<Expr<R>> left;
    Token op;
    std::shared_ptr<Expr<R>> right;

    R accept(ExprVisitor<R>* visitor) override {
        return visitor->visitBinaryExpr(this);
    }
};

template<typename R>
class Grouping : public Expr<R> {
public:
    Grouping(std::shared_ptr<Expr<R>> expression)
        : expression(std::move(expression)) {}

    std::shared_ptr<Expr<R>> expression;

    R accept(ExprVisitor<R>* visitor) override {
        return visitor->visitGroupingExpr(this);
    }
};

template<typename R>
class Literal : public Expr<R> {
public:
    Literal(const std::variant<std::monostate, double, std::string, bool>& value)
        : value(value) {}

    std::variant<std::monostate, double, std::string, bool> value;

    R accept(ExprVisitor<R>* visitor) override {
        return visitor->visitLiteralExpr(this);
    }
};

template<typename R>
class Unary : public Expr<R> {
public:
    Unary(const Token& op, std::shared_ptr<Expr<R>> right)
        : op(op), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Expr<R>> right;

    R accept(ExprVisitor<R>* visitor) override {
        return visitor->visitUnaryExpr(this);
    }
};

#endif // EXPR_H
