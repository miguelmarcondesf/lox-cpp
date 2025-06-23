#ifndef EXPR_H
#define EXPR_H

#include <memory>
#include "Token.h"

class ExprVisitor {
  public:
    virtual ~ExprVisitor() = default;

    virtual void visitBinaryExpr(class Binary* expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;

    class Binary;

    virtual void accept(ExprVisitor* visitor) = 0;
};

// Expr::Binary
class Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, const Token& op, std::shared_ptr<Expr> right)
        : left(left), op(op), right(right) {}

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    void accept(ExprVisitor* visitor) override {
      visitor->visitBinaryExpr(this);
    }
};

#endif // EXPR_H
