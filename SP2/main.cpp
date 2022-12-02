#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<50> cislo1("48");
    MPInt<30> cislo2("48");
    auto vysledek = cislo1 - cislo2;

    MPInt<UNLIMITED> cislo3("9999999999999999999999999999999999999999999999999999999999999999999999999999");
    MPInt<UNLIMITED> cislo4("55555555555555555555555555555555555555555555555555555555555555555555555");
    auto vysledek2 = cislo3 - cislo4;

    std::cout << cislo1 << std::endl;
    std::cout << cislo2 << std::endl;
    std::cout << vysledek << std::endl;

    std::cout << cislo3 << std::endl;
    std::cout << cislo4 << std::endl;
    std::cout << vysledek2 << std::endl;

    if (cislo1 < cislo2) {
        std::cout << "Cislo1 je mensi nez cislo2" << std::endl;
    }
    if (cislo1 > cislo2) {
        std::cout << "Cislo1 je vetsi nez cislo2" << std::endl;
    }
    if (cislo1 == cislo2) {
        std::cout << "Cislo1 je rovno cislo2" << std::endl;
    }
    if (cislo1 != cislo2) {
        std::cout << "Cislo1 neni rovno cislo2" << std::endl;
    }
    if (cislo1 <= cislo2) {
        std::cout << "Cislo1 je mensi nebo rovno cislo2" << std::endl;
    }
    if (cislo1 >= cislo2) {
        std::cout << "Cislo1 je vetsi nebo rovno cislo2" << std::endl;
    }

    return 0;
}
