#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<10> cislo1("35029111111111111");
    MPInt<UNLIMITED> cislo2("-1234567899876543211234567");
    MPInt<10> cislo3("76532111111111111");

    MPInt<10> vysledek = cislo1 + cislo3;

    std::cout << cislo1.toString() << std::endl;
    std::cout << cislo2.toString() << std::endl;
    std::cout << cislo3.toString() << std::endl;

    std::cout << vysledek.toString() << std::endl;

    return 0;
}
