#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<UNLIMITED> cislo3("2");
    MPInt<UNLIMITED> cislo4("3");
    cislo3 *= cislo4;
//    auto vysledek2 = cislo3 / cislo4;

    std::cout << cislo3 << std::endl;
    std::cout << cislo4 << std::endl;
//    std::cout << vysledek2 << std::endl;

    MPInt<UNLIMITED> cislo1("100");
    auto factorial = (!cislo1);
    std::cout << factorial << std::endl;

    return 0;
}
