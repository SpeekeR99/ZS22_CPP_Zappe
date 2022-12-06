#include "MultiplePrecisionArithmetic.h"
#include "MultiplePrecisionTerminal.h"

/**
 * Function demonstrates the functions of the Multiple Precision Calculator
 * First demonstration is basic calculations on maximum of 10 digits
 * Second demonstration is non-leading zero (and white space) parsing and calculations on maximum of 10 digits
 * Third demonstration is about negative numbers, parsing them and calculations on maximum of 10 digits
 * Fourth demonstration is about invalid inputs on maximum of 10 digits
 * Fifth demonstration is about overflow on maximum of 3 digits (-999 to 999)
 * Sixth demonstration is about division in unlimited mode
 * Seventh demonstration is about factorials in unlimited mode
 * Eighth demonstration is about large random numbers in unlimited mode
 */
void demonstrate() {
    // Demonstration of basic calculations on maximum of 10 digits
    std::string basic = "help\n1+1\n2-2\n4*4\n10/3\n3/10\n100!\nbank\n5!\nbank\nexit\n";
    std::stringstream basic_ss(basic);
    // Demonstration of non-leading zero (and white space) parsing and calculations on maximum of 10 digits
    std::string nlz_ws = "001\t\t+  00000001\n00000000000000    !\n00000005\t*005\n00000000000000010 - 09\nbank\nexit\n";
    std::stringstream nlz_ws_ss(nlz_ws);
    // Demonstration of negative numbers, parsing them and calculations on maximum of 10 digits
    std::string negative = "-1--1\n1+-1\n-5*5\n-5*-5\n$1/-5\nbank\nexit\n";
    std::stringstream negative_ss(negative);
    // Demonstration of invalid inputs on maximum of 10 digits
    std::string invalid = "1+1+1\n-1-*1\n-1---1\n1+\n1!1\n1/0\n-1!\n:)\nbank\nexit\n";
    std::stringstream invalid_ss(invalid);
    // Demonstration of overflow on maximum of 3 digits (-999 to 999)
    std::string overflow = "-998-1\n$1-1\n998+1\n$1+1\nbank\nexit\n";
    std::stringstream overflow_ss(overflow);
    // Demonstration of division in unlimited mode
    std::string division = "0/9999999999999999999\n123456789/123456789\n123456789/-123456789\n-123456789/-1\n"
                           "1000000000000000000000000000000/555555555555555555555555\n555555555555555555555555555/1111111111111111111\n"
                           "987654321123456789/12345678987654321\n9876543210123456789/12345678987654321\n";
    std::stringstream division_ss;
    division_ss << division;
    // Showcase of big number divided by the same number, but always a digit smaller
    std::string numerator = "55555555555555555555555555555555555555555555555/";
    std::string denominator = "11111111111111111111111111111111111111111111111";
    for (int32_t i = 0; i < denominator.length(); i++) {
        auto denominator_view = std::string_view(denominator); // Create a view of the denominator
        denominator_view.remove_suffix(i); // Remove the last i digits
        division_ss << numerator << denominator_view << "\n";
    }
    division_ss << "exit\n";
    // Demonstration of factorials in unlimited mode
    std::string factorial = "-1!\n0!\n1!\n5!\n$1!\n1000!\nexit\n";
    std::stringstream factorial_ss(factorial);
    // Demonstration of large random numbers in unlimited mode
    std::string large = "1234567890123456789*98765432109876543210\n$1*-420\n$2-$1\n$2/$3\n$4+$1\n120!\n100!\n$2/$1\nbank\nexit\n";
    std::stringstream large_ss(large);

    // Prepare terminals
    MPTerm<3> term_3;
    MPTerm<10> term_10_1;
    MPTerm<10> term_10_2;
    MPTerm<10> term_10_3;
    MPTerm<10> term_10_4;
    MPTerm<UNLIMITED> term_unlimited_1;
    MPTerm<UNLIMITED> term_unlimited_2;
    MPTerm<UNLIMITED> term_unlimited_3;

    std::cout << "Demonstration of the Multiple Precision Calculator" << std::endl;

    std::cout << std::endl << "---------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate basic arithmetics on 10 maximum digits:" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl << std::endl;
    term_10_1.run(basic_ss, true);

    std::cout << std::endl << "--------------------------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate non-leading zero (and white space) on 10 maximum digits:" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl << std::endl;
    term_10_2.run(nlz_ws_ss, true);

    std::cout << std::endl << "--------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate negative numbers on 10 maximum digits:" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl << std::endl;
    term_10_3.run(negative_ss, true);

    std::cout << std::endl << "-----------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate invalid expressions on 10 maximum digits:" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl << std::endl;
    term_10_4.run(invalid_ss, true);

    std::cout << std::endl << "-----------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate overflow on 3 maximum digits:" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl << std::endl;
    term_3.run(overflow_ss, true);

    std::cout << std::endl << "---------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate division in unlimited mode:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl << std::endl;
    term_unlimited_1.run(division_ss, true);

    std::cout << std::endl << "--------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate factorial on unlimited maximum digits:" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl << std::endl;
    term_unlimited_2.run(factorial_ss, true);

    std::cout << std::endl << "------------------------------------------------------------" << std::endl;
    std::cout << "Let's demonstrate large numbers on unlimited maximum digits:" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl << std::endl;
    term_unlimited_3.run(large_ss, true);
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
        std::cout << "Modes: 1 (unlimited), 2 (limited to 32 bytes ~ 78 digits), 3 (demonstration)" << std::endl;
        return EXIT_FAILURE;
    }

    // Three modes are possible: 1 for unlimited precision, 2 for limited precision (32 bytes), 3 for demonstration mode
    uint8_t mode;
    // Try to parse the mode
    try {
        mode = std::stoi(argv[1]);
    }
    catch (std::exception &e) {
        std::cout << "Invalid mode: " << argv[1] << std::endl;
        std::cout << "Modes: 1 (unlimited), 2 (limited to 32 bytes ~ 78 digits), 3 (demonstration)" << std::endl;
        return EXIT_FAILURE;
    }
    if (mode < 1 || mode > 3) {
        std::cout << "Invalid mode: " << argv[1] << std::endl;
        std::cout << "Modes: 1 (unlimited), 2 (limited to 32 bytes ~ 78 digits), 3 (demonstration)" << std::endl;
        return EXIT_FAILURE;
    }

    // Run the program in the selected mode
    if (mode == 1) {
        std::unique_ptr<MPTerm<UNLIMITED>> terminal = std::make_unique<MPTerm<UNLIMITED>>();
        terminal->run();
    } else if (mode == 2) {
        std::unique_ptr<MPTerm<78>> terminal = std::make_unique<MPTerm<78>>(); // 32 bytes = 256 bits ~ 78 digits
        terminal->run();
    } else if (mode == 3)
        demonstrate();

    return EXIT_SUCCESS;
}
