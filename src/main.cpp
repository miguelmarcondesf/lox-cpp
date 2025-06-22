#include <iostream>
#include "Lox.h"

int main(int argc, char const *argv[]) {
    std::cout << "Hello from Miguel's Lox interpreter!" << std::endl;

    Lox::runScript(argc, argv);
    return 0;
}
