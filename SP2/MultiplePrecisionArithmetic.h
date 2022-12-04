#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

/**
 * Base 1 000 000 000 was chosen because it is the largest base that can be stored in 32 bits
 * Conveniently, it is also the largest base that can be multiplied by itself without overflowing
 * and can be stored in 64 bits
 * This is similar to string approach, but with base 1 000 000 000, we do operations with 9 digits at a time
 */
constexpr uint32_t BASE = 1000000000;
/**
 * Number of digits in base 1 000 000 000 (max number is 999 999 999)
 */
constexpr uint8_t MAX_DIGITS = 9;
/**
 * Constant used for the UNLIMITED template parameter
 */
constexpr int8_t UNLIMITED = -1;

/**
 * Concept for checking if a type is integral and if the variable is either UNLIMITED or >= 4 bytes (~9 digits)
 * @tparam T Type to check
 */
template<typename T>
concept ValidDigit = requires(T t) {
    std::is_integral_v<T>;
    t >= MAX_DIGITS || t == UNLIMITED; // 4 byte number ~ 9 digit number (thus MAX_DIGITS)
};

/**
 * Struct for storing the result of a maximum of two ValidDigit variables
 * The biggest possible is UNLIMITED (if at least one is UNLIMITED)
 * Otherwise the bigger of the two is stored
 * @tparam x ValidDigit variable to be chosen from
 * @tparam y ValidDigit variable to be chosen from
 */
template<int32_t x, int32_t y> requires ValidDigit<int32_t>
struct MaxDigits {
    /**
     * The biggest possible is UNLIMITED (if at least one is UNLIMITED)
     * Otherwise the bigger of the two is stored
     */
    static const int32_t value = (x == UNLIMITED || y == UNLIMITED) ? UNLIMITED : (x > y) ? x : y;
};

/**
 * Addition of two arbitrary precision integers is fairly simple
 * We just add the digits from the least significant digit to the most significant digit
 * If the sum of two digits is greater than the base, we carry the 1 to the next digit
 * @param num1 Number to be added
 * @param num2 Number to be added
 * @return Vector of digits representing the sum of num1 and num2
 */
std::vector<uint32_t> add(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (size_t i = 0; i < num1.size() || i < num2.size() || carry; i++) {
        // If there is no digit in either of the numbers, add 0 instead
        uint32_t sum = (num1.size() > i ? num1[i] : 0) +
                       (num2.size() > i ? num2[i] : 0) + carry;
        // Carry is the integer part of the sum divided by the base (either 0 or 1)
        carry = sum / BASE;
        // Sum is the remainder of the sum divided by the base
        sum %= BASE;
        result_number.push_back(sum);
    }

    return result_number;
}

/**
 * Subtraction of two arbitrary precision integers is fairly simple as well
 * We just subtract the digits from the least significant digit to the most significant digit
 * If the difference of two digits is negative, we borrow 1 from the next digit
 * It is expected that num1 is greater than num2
 * @param num1 Number to be subtracted from
 * @param num2 Number to be subtracted
 * @return Vector of digits representing the difference of num1 and num2
 */
std::vector<uint32_t> sub(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (size_t i = 0; i < num1.size() || carry; i++) {
        // Since the num1 is always greater than num2, we can assume that num1 has a digit at index i (always)
        // If there is no digit in num2, subtract 0 instead
        auto sum = static_cast<int32_t>(num1[i] - (num2.size() > i ? num2[i] : 0) - carry);
        // Carry 1 to the next iteration if the difference is negative
        carry = sum < 0;
        // If the difference is negative, add the base to it
        sum += static_cast<int32_t>(carry * BASE);
        result_number.push_back(sum);
    }

    // Remove the leading zeros from the result
    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

/**
 * Multiplication of two arbitrary precision integers is a bit more complicated, but still fairly simple operation
 * We multiply the digits from the least significant digit to the most significant digit
 * If the product of two digits is greater than the base, we carry the integer part to the next digit
 * Be careful of the base shift when carrying and when adding to the result
 * @param num1 Number to be multiplied
 * @param num2 Number to be multiplied
 * @return Vector of digits representing the product of num1 and num2
 */
std::vector<uint32_t> mul(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number(num1.size() + num2.size(), 0);

    for (size_t i = 0; i < num1.size(); i++) {
        uint64_t carry = 0; // 64 bit carry is needed to prevent overflow
        for (size_t j = 0; j < num2.size() || carry; j++) {
            // We always have a number at index i in num1, but we might not have a number at index j in num2
            // If there is no digit in num2, add 0 instead
            uint64_t sum = result_number[i + j] +
                           static_cast<uint64_t>(num1[i]) * (j < num2.size() ? num2[j] : 0) + carry;
            // Carry is the integer part of the sum divided by the base
            carry = sum / BASE;
            // Sum is the remainder of the sum divided by the base
            sum %= BASE;

            result_number[i + j] = sum;
        }
    }

    // Remove the leading zeros from the result
    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

/**
 * Division of an arbitrary precision integer by an integer is a bit more complicated than the other operations
 * We divide the digits from the most significant digit to the least significant digit
 * If the division of two digits is less than the divisor, we borrow 1 from the next digit
 * It is expected that the divisor is greater than 0
 * @param num1 Number to be divided
 * @param num2 Number to divide by
 * @return Vector of digits representing the quotient of num1 and num2
 */
std::vector<uint32_t> div(const std::vector<uint32_t> &num1, uint32_t num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (int32_t i = static_cast<int32_t>(num1.size()) - 1; i >= 0; i--) {
        // Since the num1 is always greater than num2, we can assume that num1 has a digit at index i (always)
        uint64_t sum = static_cast<uint64_t>(num1[i]) + carry * BASE;
        // Result is the integer part of the sum divided by the divisor
        result_number.push_back(sum / num2);
        // Carry is the remainder of the sum divided by the divisor
        carry = sum % num2;
    }

    // Remove the leading zeros from the result
    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

/**
 * Division of two arbitrary precision integers is the most complex operation of them all
 * TODO: Implement this
 * @param num1 Number to be divided
 * @param num2 Number to divide by
 * @return Vector of digits representing the quotient of num1 and num2
 */
std::vector<uint32_t> div(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;

}

/**
 * Class representing an overflow exception
 * This exception is thrown when an operation results in an overflow
 * The operation is not performed and the result is not stored
 */
class MyOverflowException : public std::exception {
private:
    /** Message to be displayed when the exception is thrown */
    char *message;

public:
    /**
     * Constructor for the MyOverflowException class
     * @param msg Message to be displayed when the exception is thrown
     */
    explicit MyOverflowException(const std::string &msg) {
        const char *c_msg = msg.c_str();
        message = new char[strlen(c_msg) + 1];
        strcpy(message, c_msg);
    }

    /**
     * Destructor for the MyOverflowException class
     * Deletes the message
     */
    ~MyOverflowException() override {
        delete[] message;
    }

    /**
     * Returns the message of the exception
     * @return Message of the exception
     */
    char *what() {
        return message;
    }
};

/**
 * Class representing Arbitrary Precision Integers
 * This class is used to store arbitrarily large integers
 * The integers are stored as a vector of digits in base 1 000 000 000
 * The base is chosen to be 1 000 000 000 because it is the largest power of 10 that fits in 32 bits
 * The base is chosen to be 1 000 000 000 because it is the largest power of 10 which can be multiplied by itself
 * without overflowing a 64 bit integer
 * @tparam max_digits Maximum number of digits in the integer (excluding the sign) (UNLIMITED is possible)
 */
template<int32_t max_digits>
class MPInt {
private:
    /** Vector of digits representing the integer */
    std::vector<uint32_t> mNumber;
    /** Sign of the integer (either +1 or -1) */
    int32_t mSign;

    /**
     * Function to check if the number isn't too large for the given number of digits
     * If the number is too large, an overflow exception is thrown
     */
    void checkLengthOfDigits() const {
        // If the maximum number of digits is unlimited, we don't need to check the length of the number
        if (max_digits == UNLIMITED)
            return;

        // If the number of digits seems to be greater than the maximum number of digits, check more precisely
        if (mNumber.size() * MAX_DIGITS > max_digits) {
            std::string str_num = std::to_string(mNumber[mNumber.size() - 1]);
            // If the number of digits is greater than the maximum number of digits, throw an overflow exception
            if (str_num.length() > max_digits % MAX_DIGITS)
                throw MyOverflowException(
                        "Number " + toString() + " is too big for " + std::to_string(max_digits) + " digits"
                );
        }
    }

    /**
     * Function to create a factorial of a number
     * Factorial is simply created by multiplying the number by all the numbers below it
     * @return Factorial of the number
     */
    MPInt factorial() const {
        MPInt result("1");
        uint32_t i = 2;
        while (true) {
            MPInt temp(std::to_string(i));
            if (temp > *this)
                break;
            result *= temp;
            i++;
        }
        return result;
    }

public:
    MPInt() : mNumber(1, 0), mSign(1) {
        // Nothing to do here :)
    }

    /**
     * Constructor for the MPInt class based on a given string
     * @param num Number as a string (can be negative)
     */
    explicit MPInt(const std::string &num) : mNumber(), mSign(1) {
        std::string num_copy = num;

        // If the number is negative, set the sign to -1 and remove the negative sign from the number
        if (num[0] == '-') {
            mSign = -1;
            num_copy = num.substr(1);
        }

        // Go through the number from the least significant digit to the most significant digit
        for (auto i = static_cast<int32_t>(num_copy.length()); i > 0; i -= MAX_DIGITS) {
            if (i < MAX_DIGITS)
                mNumber.push_back(std::stoi(num_copy.substr(0, i)));
            else
                mNumber.push_back(std::stoi(num_copy.substr(i - MAX_DIGITS, MAX_DIGITS)));
        }

        // Check if the number is too large for the given number of digits
        checkLengthOfDigits();
    }

    /**
     * Constructor for the MPInt class based on a given vector of digits and a sign
     * @param num Number as a vector of digits
     * @param sign Sign of the number (either +1 or -1)
     */
    MPInt(std::vector<uint32_t> num, int32_t sign) : mNumber(std::move(num)), mSign(sign) {
        // Check if the number is too large for the given number of digits
        checkLengthOfDigits();
    }

    /**
     * Copy constructor for the MPInt class based on another MPInt instance of the same type
     * @param other MPInt instance to copy
     */
    MPInt(const MPInt &other) noexcept: mNumber(other.mNumber), mSign(other.mSign) {
        // Nothing to do here :)
    }

    /**
     * Move constructor for the MPInt class based on another MPInt instance of the same type
     * @param other MPInt instance to move
     */
    MPInt(MPInt &&other) noexcept: mNumber(std::move(other.mNumber)), mSign(other.mSign) {
        // Take away everything from the other instance
        other.mNumber = {};
        other.mSign = 0;
    }

    /**
     * Default destructor for the MPInt class
     */
    ~MPInt() = default;

    /**
     * Copy assignment operator for the MPInt class based on another MPInt instance of the same type
     * @param other MPInt instance to copy
     * @return MPInt instance with the same value as the other instance
     */
    MPInt &operator=(const MPInt &other) noexcept {
        mNumber = other.mNumber;
        mSign = other.mSign;
        return *this;
    }

    /**
     * Move assignment operator for the MPInt class based on another MPInt instance of the same type
     * @param other MPInt instance to move
     * @return MPInt instance with the same value as the other instance
     */
    MPInt &operator=(MPInt &&other) noexcept {
        mNumber = std::move(other.mNumber);
        mSign = other.mSign;
        // Take away everything from the other instance
        other.mNumber = {};
        other.mSign = 0;
        return *this;
    }

    /**
     * Overloaded operator + for addition of two MPInt instances
     * Addition of two MPInts with the same sign is done by adding the digits of the numbers and carrying over the sign
     * Addition of two MPInts with different signs is done by subtracting the other number from this number, but
     * the sign of the other number needs to be swapped
     * +x + +y is x + y
     * -x + -y is -(x + y)
     * +x + -y is x - y
     * -x + +y is -(x - y)
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Sum of the two MPInt instances with the same number of digits as the maximum number of digits of the two
     */
    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator+(const MPInt<max_digits_other> &other) {
        // +x + +y OR -x + -y -> Addition (with the same sign)
        if (mSign == other.getSign())
            return {add(mNumber, other.getNumber()), mSign};
            // +x + -y OR -x + +y -> Subtraction (but swap sign of the second operand)
        else {
            MPInt<max_digits_other> tmp{other.getNumber(), -other.getSign()};
            return *this - tmp;
        }
    }

    /**
     * Overloaded operator += for addition of two MPInt instances
     * Uses the overloaded operator + for addition
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Sum of the two MPInt instances with the same number of digits as this MPInt instance
     */
    template<int32_t max_digits_other>
    MPInt operator+=(const MPInt<max_digits_other> &other) {
        auto result = *this + other;
        // Check if the number is too large for the given number of digits
        if (MaxDigits<max_digits, max_digits_other>::value != max_digits)
            throw MyOverflowException(
                    "Number " + result.toString() + " is too big for " + std::to_string(max_digits) + " digits");
        // Copy the result to this instance
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    /**
     * Overloaded operator - for subtraction of two MPInt instances,
     * Subtraction of two MPInts is done by subtracting the bigger number from the smaller number and carrying over the
     * right sign (this > other -> this.sign || this < other -> -this.sign)
     * This works only if the two MPInts had the same sign to begin with
     * Subtraction of two MPInts with different signs is done by adding the numbers, but the sign of the other number
     * needs to be swapped
     * +x - +y is x - y
     * -x - -y is -(x - y)
     * +x - -y is x + y
     * -x - +y is -(x + y)
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Difference of the two MPInt instances with the same number of digits as the maximum number of digits of
     *         the two
     */
    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator-(const MPInt<max_digits_other> &other) {
        // +x + +y OR -x + -y -> Subtraction (with the same sign)
        if (mSign == other.getSign()) {
            if (*this >= other)
                return {sub(mNumber, other.getNumber()), mSign};
            else
                return {sub(other.getNumber(), mNumber), -mSign};
        }
            // +x + -y OR -x + +y -> Addition (but swap sign of the second operand)
        else {
            MPInt<max_digits_other> tmp{other.getNumber(), -other.getSign()};
            return *this + tmp;
        }
    }

    /**
     * Overloaded operator -= for subtraction of two MPInt instances
     * Uses the overloaded operator - for subtraction
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Difference of the two MPInt instances with the same number of digits as this MPInt instance
     */
    template<int32_t max_digits_other>
    MPInt operator-=(const MPInt<max_digits_other> &other) {
        auto result = *this - other;
        // Check if the number is too large for the given number of digits
        if (MaxDigits<max_digits, max_digits_other>::value != max_digits)
            throw MyOverflowException(
                    "Number " + result.toString() + " is too big for " + std::to_string(max_digits) + " digits");
        // Copy the result to this instance
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    /**
     * Overloaded operator * for multiplication of two MPInt instances
     * Multiplication of two MPInts is done by multiplying the digits of the numbers and carrying over the sign
     * The sign of the result is the product of the signs of the two operands
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Product of the two MPInt instances with the same number of digits as the maximum number of digits of
     *         the two
     */
    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator*(const MPInt<max_digits_other> &other) {
        return {mul(mNumber, other.getNumber()), mSign * other.getSign()};
    }

    /**
     * Overloaded operator *= for multiplication of two MPInt instances
     * Uses the overloaded operator * for multiplication
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Product of the two MPInt instances with the same number of digits as this MPInt instance
     */
    template<int32_t max_digits_other>
    MPInt operator*=(const MPInt<max_digits_other> &other) {
        auto result = *this * other;
        // Check if the number is too large for the given number of digits
        if (MaxDigits<max_digits, max_digits_other>::value != max_digits)
            throw MyOverflowException(
                    "Number " + result.toString() + " is too big for " + std::to_string(max_digits) + " digits");
        // Copy the result to this instance
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    /**
     * Overloaded operator / for division of two MPInt instances
     * Division of two MPInts is done by dividing this number by the other number and carrying over the sign
     * The sign of the result is the product of the signs of the two operands
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Quotient of the two MPInt instances with the same number of digits as the maximum number of digits of
     *         the two
     */
    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator/(const MPInt<max_digits_other> &other) {
        throw MyOverflowException("Division is not implemented");
        return {div(mNumber, other.getNumber()), mSign * other.getSign()};
    }

    /**
     * Overloaded operator /= for division of two MPInt instances
     * Uses the overloaded operator / for division
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Quotient of the two MPInt instances with the same number of digits as this MPInt instance
     */
    template<int32_t max_digits_other>
    MPInt operator/=(const MPInt<max_digits_other> &other) {
        auto result = *this / other;
        // No need to check if the number is too large for the given number of digits because it's division
        // Copy the result to this instance
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    /**
     * Overloaded operator ! for factorial of an MPInt instance
     * Factorial of an MPInt is done by multiplying all numbers from 1 to the number
     * @return Factorial of the MPInt instance with the same number of digits as this MPInt instance
     */
    MPInt operator!() {
        return factorial();
    }

    /**
     * Overloaded spaceship operator <=> for comparison of two MPInt instances
     * First the signs are compared, if they are equal, then
     * The sizes of the number vectors are compared, if they are equal, then
     * The digits of the numbers are compared from the most significant digit to the least significant digit
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Result of the comparison
     */
    template<int32_t max_digits_other>
    std::strong_ordering operator<=>(const MPInt<max_digits_other> &other) const {
        // Compare the signs
        if (mSign != other.getSign())
            return mSign <=> other.getSign();

        // Compare the sizes of the number vectors
        if (mNumber.size() != other.getNumber().size())
            return mNumber.size() <=> other.getNumber().size();

        // Compare the digits of the numbers
        for (int32_t i = mNumber.size() - 1; i >= 0; i--) {
            if (mNumber[i] != other.getNumber()[i])
                return mNumber[i] <=> other.getNumber()[i];
        }

        // The numbers are equal
        return std::strong_ordering::equal;
    }

    /**
     * Overloaded operator == for equality of two MPInt instances
     * Uses the overloaded spaceship operator <=> for comparison
     * @tparam max_digits_other Maximum number of digits in the other MPInt instance
     * @param other Other MPInt instance
     * @return Result of the comparison
     */
    template<int32_t max_digits_other>
    bool operator==(const MPInt<max_digits_other> &other) const {
        return ((*this <=> other) == std::strong_ordering::equal);
    }

    /**
     * Overloaded operator << for printing an MPInt instance
     * Uses the toString() method to print the number
     * @param os Output stream
     * @param num MPInt instance
     * @return Output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const MPInt &num) {
        os << num.toString();
        return os;
    }

    /**
     * This method returns the string representation of the number
     * @return String representation of the number
     */
    [[nodiscard]] std::string toString() const {
        std::stringstream result;
        // If the number is negative, add a minus sign
        if (mSign == -1)
            result << "-";
        // Add the digits of the number from the most significant digit to the least significant digit
        result << mNumber[mNumber.size() - 1];
        for (int32_t i = static_cast<int32_t>(mNumber.size()) - 2; i >= 0; i--) {
            std::string str_num = std::to_string(mNumber[i]);
            for (int32_t j = 0; j < MAX_DIGITS - str_num.length(); j++) // Add leading zeros
                result << "0";
            result << str_num;
        }
        return result.str();
    }

    /**
     * Getter for the number
     * @return Number
     */
    [[nodiscard]] std::vector<uint32_t> getNumber() const {
        return mNumber;
    }

    /**
     * Getter for the sign
     * @return Sign
     */
    [[nodiscard]] int32_t getSign() const {
        return mSign;
    }

};
