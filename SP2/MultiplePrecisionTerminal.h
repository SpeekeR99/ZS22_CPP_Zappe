#pragma once

#include <array>
#include <regex>
#include <chrono>
#include "MultiplePrecisionArithmetic.h"

/**
 * Terminal for the Multiple Precision Calculator
 * @tparam max_digits Maximum number of digits for the numbers
 */
template<int32_t max_digits>
class MPTerm {
private:
    /**
     * Bank of last five results
     */
    std::array<MPInt<max_digits>, 5> bank;

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
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "| Available commands:                 |" << std::endl;
        std::cout << "| help | prints this message          |" << std::endl;
        std::cout << "| exit | exits the program            |" << std::endl;
        std::cout << "| bank | shows the last five results  |" << std::endl;
        std::cout << "|- - - - - - - - - - - - - - - - - - -|" << std::endl;
        std::cout << "| Available operators:                |" << std::endl;
        std::cout << "| + | addition                        |" << std::endl;
        std::cout << "| - | subtraction                     |" << std::endl;
        std::cout << "| * | multiplication                  |" << std::endl;
        std::cout << "| / | division                        |" << std::endl;
        std::cout << "| ! | factorial                       |" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
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
            std::for_each(bank.begin(), bank.end(), [&i](MPInt<max_digits> &n) { // Lambda function
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
            std::cerr << "Invalid input" << std::endl;
            return;
        }

        MPInt<max_digits> result;
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
        MPInt<max_digits> num1, num2;
        if (number1[0] == '$')
            num1 = bank[number1[1] - '1'];
        else
            num1 = MPInt<max_digits>(number1);
        if (number2[0] == '$')
            num2 = bank[number2[1] - '1'];
        else
            num2 = MPInt<max_digits>(number2);

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
    bool performOperation(MPInt<max_digits> &num1, MPInt<max_digits> &num2, const std::string &op,
                          MPInt<max_digits> &result) {
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
            std::cerr << e.what() << std::endl;
            return false;
        }
            // Catch general exception (division by zero and unexpected errors)
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
        return true;
    }

public:
    /**
     * Constructor for the terminal
     */
    MPTerm() : bank{} {
        printInitialMessage();
    }

    /**
     * Runs the terminal
     */
    void run() {
        while (true) {
            // Get user input
            std::string input;
            std::cout << "> ";
            std::getline(std::cin, input);

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