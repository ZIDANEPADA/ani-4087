#include <iostream>
#include "test.hpp"


int main() {
    calculatrice calc;
    std::cout << "Addition: " << calc.add(5, 3) << std::endl;
    std::cout << "Subtraction: " << calc.sub(5, 3) << std::endl;
    std::cout << "Multiplication: " << calc.mul(5, 3) << std::endl;
    return 0;
}
