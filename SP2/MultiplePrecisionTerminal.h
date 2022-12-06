#pragma once

#include <array>
#include <regex>
#include <chrono>
#include "MultiplePrecisionArithmetic.h"

/**
 * Terminal for the Multiple Precision Calculator
 * @tparam max_digits Maximum number of digits for the numbers
 */
template<ValidDigit T, T max_digits>
class MPTerm {
private:
    /**
     * Bank of last five results
     */
    std::array<MPInt<T, max_digits>, 5> bank;

    /**
     * Prints the initial information message
     */
    void printInitialMessage() {
        std::cout << "Multiple Precision Calculator" << std::endl;
        if (max_digits == UNLIMITED)
            std::cout << "Unlimited mode" << std::endl;
        else
            std::cout << "Limited mode (" << max_digits << " digits)" << std::endl;
        std::cout << "Type 'help' for help" << std::endl;
        std::cout << "Enter your expression with upmost one operator" << std::endl;
    }

    /**
     * Prints the help message
     */
    void printHelp() {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "| Available commands:                 |" << std::endl;
        std::cout << "| help | prints this message          |" << std::endl;
        std::cout << "| exit | exits the program            |" << std::endl;
        std::cout << "| bank | shows the last five results  |" << std::endl;
        std::cout << "|- - - - - - - - - - - - - - - - - - -|" << std::endl;
        std::cout << "| Available operators:                |" << std::endl;
        std::cout << "| + | addition       | (binary)       |" << std::endl;
        std::cout << "| - | subtraction    | (binary)       |" << std::endl;
        std::cout << "| * | multiplication | (binary)       |" << std::endl;
        std::cout << "| / | division       | (binary)       |" << std::endl;
        std::cout << "| ! | factorial      | (unary)        |" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
    }

    /**
     * Parses the input and checks for help or bank commands
     * @param input Input string
     * @return True if the input is a command, false otherwise
     */
    bool parseCommand(std::string &input) {
        // If the user wants help, print help message
        if (input == "help" || input == "HELP") {
            printHelp();
            return true;
        }
            // If the user wants to see the bank, print it
        else if (input == "bank" || input == "BANK") {
            std::cout << "Bank: " << std::endl;
            size_t i = 1;
            std::for_each(bank.begin(), bank.end(), [&i](MPInt<T, max_digits> &n) { // Lambda function
                std::cout << "$" << i << " = " << n << std::endl;
                i++;
            });
            return true;
        }
        return false;
    }

    /**
     * Parses the input expression and calls the appropriate function to compute the result
     * @param input Input string
     */
    void parseExpression(std::string &input) {
        // Possible two formats are:
        std::regex regex1(R"(^(\$[1-5]|(\-?\d+))(\s+)*(\+|\-|\*|\/)(\s+)*(\$[1-5]|(\-?\d+))$)");
        std::regex regex2(R"(^(\$[1-5]|(\-?\d+))(\s+)*(\!)$)");

        // If the input matches no format, print error message
        if (!std::regex_match(input, regex1) && !std::regex_match(input, regex2)) {
            std::cout << "Invalid input" << std::endl;
            return;
        }

        MPInt<T, max_digits> result;
        // If the input matches the first format, parse it
        // Get the first number
        std::smatch match;
        std::regex_search(input, match, std::regex(R"(^(\$[1-5]|(\-?\d+)))"));
        std::string number1 = match.str();
        input = match.suffix();

        // Get the operator
        std::regex_search(input, match, std::regex(R"((\+|\-|\*|\/|\!))"));
        std::string op = match.str();
        input = match.suffix();

        std::string number2 = "0";
        if (op != "!") {
            // Get the second number
            std::regex_search(input, match, std::regex(R"((\$[1-5]|(\-?\d+))$)"));
            number2 = match.str();
        }
        // Parse the numbers
        MPInt<T, max_digits> num1, num2;
        if (number1[0] == '$')
            num1 = bank[number1[1] - '1'];
        else
            num1 = MPInt<T, max_digits>(number1);
        if (number2[0] == '$')
            num2 = bank[number2[1] - '1'];
        else
            num2 = MPInt<T, max_digits>(number2);

        // Try to perform the operation
        if (!performOperation(num1, num2, op, result))
            return;

        // Print the result
        std::cout << "$1 = " << result << std::endl;

        // Update the bank
        for (int i = 4; i > 0; i--)
            bank[i] = bank[i - 1];
        bank[0] = result;
    }

    /**
     * Tries to perform the operation
     * @param num1 Operand 1
     * @param num2 Operand 2
     * @param op Operator
     * @param result Result of the operation (if successful)
     * @return True if the operation was successful, false otherwise
     */
    bool performOperation(MPInt<T, max_digits> &num1, MPInt<T, max_digits> &num2, const std::string &op,
                          MPInt<T, max_digits> &result) {
        try {
            if (op == "+")
                result = num1 + num2;
            else if (op == "-")
                result = num1 - num2;
            else if (op == "*")
                result = num1 * num2;
            else if (op == "/")
                result = num1 / num2;
            else if (op == "!")
                result = !num1;
        }
            // Catch overflow exception
        catch (MyOverflowException &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
            // Catch division by zero, negative number factorial
        catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
            // Catch unexpected exception
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
        return true;
    }

public:
    /**
     * Constructor for the terminal
     */
    MPTerm() : bank{} {
        // Nothing to do here :)
    }

    /**
     * Runs the terminal
     * Infinite loop of reading input and parsing it
     * @param in Input stream (default: std::cin) (for demonstration mode purposes)
     * @param demonstration If true, the terminal will output the input differently
     */
    void run(std::istream &in = std::cin, bool demonstration = false) {
        printInitialMessage();

        while (true) {
            // Get user input
            std::string input;
            if (!demonstration)
                std::cout << "> ";
            std::getline(in, input);
            if (demonstration)
                std::cout << "> " << input << std::endl;

            // If the user wants to exit, exit
            if (input == "exit" || input == "EXIT")
                break;

            // Check for help or bank commands
            if (parseCommand(input))
                continue;

            // Parse the input expression
            parseExpression(input);
        }

        std::cout << "Exiting..." << std::endl;
    }
};