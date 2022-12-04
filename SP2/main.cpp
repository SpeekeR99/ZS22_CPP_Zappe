#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<20> cislo3("11");
    MPInt<50> cislo4("300520210");

    auto vysledek2 = cislo3 - cislo4;
    try {
        cislo3 -= cislo4;
    }
    catch (MyOverflowException &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << cislo3 << std::endl;
    std::cout << cislo4 << std::endl;
    std::cout << vysledek2 << std::endl;

    MPInt<50> cislo1("100");
    try {
        auto factorial = (!cislo1);
        std::cout << factorial << std::endl;
    } catch (MyOverflowException &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
