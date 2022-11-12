#include <iostream>
#include <vector>
#include <string>

// 2 147 483 648
// soucet 1 000 000 000 + 1 000 000 000 = 2 000 000 000 funguje
// rozdil 1 000 000 000 - 1 000 000 000 = 0 funguje
// soucin 10 000 * 10 000 = 100 000 000 funguje (víc ale nejde!)
// podil 1 000 000 000 / 1 000 000 000 = 1 funguje
// => musi byt pouzity max 10 000
// => proc ne 1 000 ? Bylo by to asi lepsi

// 18 446 744 073 709 551 616
// soucet: 1 000 000 000 000 000 000
// rozdil: 1 000 000 000 000 000 000
// soucin: 1 000 000 000 * 1 000 000 000 = 1 000 000 000 000 000 000 < 18 446 744 073 709 551 616 funguje
// podil: 1 000 000 000 000 000 000 / 1 000 000 000 000 000 000 = 1 funguje
// => musi byt pouzity max 1 000 000 000
// coz je 10^9 aka miliarda (pri uziti long)

// ze zadani >= 4 byte => 32 bit => long nejde pouzit, pac by byl 64 bit
// asi bude fajn pouzivat 1 000 nebo max 10 000.. ale 10^3 zni lip

int main() {
    // Kdyby PC rozsah byl jen do 128
    // 35 029 = 29 + 50 * (100) + 3 * (100 * 100)
    // Takže max val by byl 99 (tudíž násobit 100)
    std::string cislo = "35029";
    std::vector<int> cislo_vector {};

    while (cislo.length() > 2) {
        std::string cislo_tmp = cislo.substr(cislo.size() - 2, cislo.size());
        cislo_vector.push_back(std::stoi(cislo_tmp));
        cislo = cislo.substr(0, cislo.size() - 2);
    }
    cislo_vector.push_back(std::stoi(cislo));

    for (auto i = cislo_vector.rbegin(); i != cislo_vector.rend(); ++i) {
        std::cout << *i << std::endl;
    }

    return 0;
}
