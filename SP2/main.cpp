#include <iostream>
#include "MultiplePrecisionArithmetic.h"

int main() {
    MPInt<10> cislo1("35029");
    MPInt<UNLIMITED> cislo2("-1234567899876543211234567");

    std::cout << cislo1.toString() << std::endl;
    std::cout << cislo2.toString() << std::endl;

    return 0;
}
