# Multiple Precision Integer Arithmetics

## Description

This is a library for multiple precision integer arithmetics.

Application takes one command line argument:

    mode  - 1 for unlimited precision
          - 2 for 32 byte precision (~78 decimal digits)
          - 3 for demonstration of the library

Application prints the result of the arithmetics to the standard output.

Application takes the input from the standard input.

Possible commands are:

    help - prints the help message
    exit - exits the application
    bank - prints the bank of numbers (last five results)

Possible operators are:

    +  addition (binary)
    -  subtraction (binary)
    *  multiplication (binary)
    /  division (binary)
    !  factorial (unary)

Expected input format is:

    <operand1> <operator> <operand2>   // (binary)
    OR
    <operand1> <operator>              // (unary) (only for factorial)

## Usage

    ./mpcalc.exe <mode>

### Build

Project is built using CMake. To build the project, run the following commands:

#### Windows

    mkdir build
    cd build
    cmake ..
    cmake --build .

#### Linux

    mkdir build
    cd build
    cmake ..
    make
