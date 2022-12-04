#include "MultiplePrecisionArithmetic.h"
#include "MultiplePrecisionTerminal.h"

void demonstrate() {
    // TODO: Implement this function
}

/**
 * Main function for the Multiple Precision Calculator
 * @param argc Argument count (2 are expected)
 * @param argv Argument vector (argv[1] is the mode: "unlimited", "limited to 32 bytes", "demonstration")
 * @return 0 if the program exits normally, 1 if the program exits with an error
 */
int main(int argc, char **argv) {
    // Check the number of arguments
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <mode>" << std::endl;
        return EXIT_FAILURE;
    }

    // Three modes are possible: 1 for unlimited precision, 2 for limited precision (32 bytes), 3 for demonstration mode
    uint8_t mode = std::stoi(argv[1]);
    if (mode == 1) {
        std::unique_ptr<MPTerm<UNLIMITED>> terminal = std::make_unique<MPTerm<UNLIMITED>>();
        terminal->run();
    } else if (mode == 2) {
        std::unique_ptr<MPTerm<78>> terminal = std::make_unique<MPTerm<78>>(); // 32 bytes = 256 bits ~ 78 digits
        terminal->run();
    } else if (mode == 3) {
        std::cout << "Demonstration mode" << std::endl;
        demonstrate();
    }

    return EXIT_SUCCESS;
}
