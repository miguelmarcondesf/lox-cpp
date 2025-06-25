#include <iostream>
#include <memory>
#include "Lox.h"
#include "Expr.h"
#include "AstPrinter.h"
#include "Token.h"
#include "TokenType.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello from Miguel's Lox interpreter!" << std::endl;

    int lineOfCode = 1;
    using ExprPtr = std::shared_ptr<Expr<std::string>>;

    ExprPtr unary = std::make_shared<Unary<std::string>>(
        Token(TokenType::MINUS, "-", std::monostate{}, lineOfCode),
        std::make_shared<Literal<std::string>>(123.0));

    ExprPtr grouping = std::make_shared<Grouping<std::string>>(
        std::make_shared<Literal<std::string>>(45.67));

    ExprPtr expression = std::make_shared<Binary<std::string>>(
        unary,
        Token(TokenType::STAR, "*", std::monostate{}, lineOfCode),
        grouping);

    AstPrinter printer;
    std::cout << printer.print(expression) << std::endl;

    Lox::runScript(argc, argv);
    return 0;
}
