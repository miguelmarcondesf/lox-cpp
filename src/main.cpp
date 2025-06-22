#include <iostream>
#include "Lox.h"

int main(int argc, char const *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    Lox::runScript(argc, argv);
    return 0;
}
