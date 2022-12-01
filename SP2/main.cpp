#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<30> cislo1("1111100900");
    MPInt<10> cislo2("1111111111");
    auto vysledek = cislo1 + cislo2;

    MPInt<UNLIMITED> cislo3("-1234567890123456789012345678901234567890123456789023");
    MPInt<UNLIMITED> cislo4("-55555555555555555555555555555555555555555555555555555555555555555555555");
    auto vysledek2 = cislo3 + cislo4;

    std::cout << cislo1.toString() << std::endl;
    std::cout << cislo2.toString() << std::endl;
    std::cout << vysledek.toString() << std::endl;

    std::cout << cislo3.toString() << std::endl;
    std::cout << cislo4.toString() << std::endl;
    std::cout << vysledek2.toString() << std::endl;

    return 0;
}
