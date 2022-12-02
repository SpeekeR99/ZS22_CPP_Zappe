#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
//    MPInt<50> cislo1("-48");
//    MPInt<30> cislo2("50");
//    auto vysledek = cislo1 + cislo2;

    MPInt<UNLIMITED> cislo3("1234567897897897864564561233124564564567867977565456456");
    MPInt<UNLIMITED> cislo4("11111111111111111111111111111111111111111111111111111111111111111111111");
    auto vysledek2 = cislo3 - cislo4;
    cislo3 -= cislo4;
//    std::cout << cislo1 << std::endl;
//    std::cout << cislo2 << std::endl;
//    std::cout << vysledek << std::endl;

    std::cout << cislo3 << std::endl;
    std::cout << cislo4 << std::endl;
    std::cout << cislo3 << std::endl;
    std::cout << vysledek2 << std::endl;

    return 0;
}
