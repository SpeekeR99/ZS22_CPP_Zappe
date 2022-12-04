#include "MultiplePrecisionArithmetic.h"
#include "MultiplePrecisionTerminal.h"

int main(int argc, char** argv) {
    // Check the number of arguments
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <mode>" << std::endl;
        return EXIT_FAILURE;
    }

    // Three modes are possible: 1 for unlimited precision, 2 for limited precision (32 bytes), 3 for demonstration mode
    uint8_t mode = std::stoi(argv[1]);
    if (mode == 1) {
        MPTerm<UNLIMITED> terminal;
        terminal.run();
    }
    else if (mode == 2) {
        MPTerm<78> terminal; // 32 bytes = 256 bits ~ 78 digits
        terminal.run();
    }
    else if (mode == 3) {
        std::cout << "Demonstration mode" << std::endl;
    }

    return EXIT_SUCCESS;
}
