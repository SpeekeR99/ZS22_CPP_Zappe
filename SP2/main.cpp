#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<30> cislo1("11111");
    MPInt<10> cislo2("1111111111");
    auto vysledek = cislo1 + cislo2;
    MPInt<UNLIMITED> cislo3("-123456789987654311111111111111111111111111111111111111111111111111211234567");
    auto vysledek2 = cislo3 + cislo2;

    std::cout << cislo1.toString() << std::endl;
    std::cout << cislo2.toString() << std::endl;
    std::cout << vysledek.toString() << std::endl;
    std::cout << cislo3.toString() << std::endl;
    std::cout << vysledek2.toString() << std::endl;

    return 0;
}
