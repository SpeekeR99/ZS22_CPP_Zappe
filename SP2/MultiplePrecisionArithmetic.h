#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

constexpr uint32_t BASE = 1000000000;
constexpr uint8_t MAX_DIGITS = 9;
constexpr int8_t UNLIMITED = -1;

template <typename T>
concept ValidDigit = requires (T t) {
    std::is_integral_v<T>;
    t >= MAX_DIGITS || t == UNLIMITED; // 4 byte number ~ 9 digit number (thus MAX_DIGITS)
};

template <int32_t x, int32_t y>
requires ValidDigit<int32_t>
struct MaxDigits {
    static const int32_t value = (x == UNLIMITED || y == UNLIMITED) ? UNLIMITED : (x > y) ? x : y;
};

std::vector<uint32_t> add(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (size_t i = 0; i < num1.size() || i < num2.size() || carry; i++) {
        uint32_t sum = (num1.size() > i ? num1[i] : 0) +
                       (num2.size() > i ? num2[i] : 0) + carry;
        carry = sum / BASE;
        sum %= BASE;
        result_number.push_back(sum);
    }

    return result_number;
}

std::vector<uint32_t> sub(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (size_t i = 0; i < num1.size() || carry; i++) {
        auto sum = static_cast<int32_t>(num1[i] - (num2.size() > i ? num2[i] : 0) - carry);
        carry = sum < 0;
        sum += static_cast<int32_t>(carry * BASE);
        result_number.push_back(sum);
    }

    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

std::vector<uint32_t> mul(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number(num1.size() + num2.size(), 0);

    for (size_t i = 0; i < num1.size(); i++) {
        uint64_t carry = 0;
        for (size_t j = 0; j < num2.size() || carry; j++) {
            uint64_t sum = result_number[i + j] + static_cast<uint64_t>(num1[i]) * (j < num2.size() ? num2[j] : 0) + carry;
            carry = sum / BASE;
            sum %= BASE;
            if (result_number.size() > i + j)
                result_number[i + j] = sum;
            else
                result_number.push_back(sum);
        }
    }

    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

std::vector<uint32_t> div(const std::vector<uint32_t> &num1, uint32_t num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (int32_t i = num1.size() - 1; i >= 0; i--) {
        uint64_t sum = static_cast<uint64_t>(num1[i]) + carry * BASE;
        result_number.push_back(sum / num2);
        carry = sum % num2;
    }

    while (result_number.size() > 1 && result_number.back() == 0)
        result_number.pop_back();

    return result_number;
}

std::vector<uint32_t> div(const std::vector<uint32_t> &num1, const std::vector<uint32_t> &num2) {
    std::vector<uint32_t> result_number;


}

class MyOverflowException : public std::exception {
private:
    char *message;

public:
    explicit MyOverflowException(const std::string &msg) {
        const char *c_msg = msg.c_str();
        message = new char[strlen(c_msg) + 1];
        strcpy(message, c_msg);
    }

    ~MyOverflowException() override {
        delete[] message;
    }

    char *what() {
        return message;
    }
};

template <int32_t max_digits>
class MPInt {
private:
    std::vector<uint32_t> mNumber;
    int32_t mSign;

    void checkLengthOfDigits() const {
        if (max_digits == UNLIMITED)
            return;

        if (mNumber.size() * MAX_DIGITS > max_digits) {
            std::string str_num = std::to_string(mNumber[mNumber.size() - 1]);
            if (str_num.length() > max_digits % MAX_DIGITS)
                throw MyOverflowException("Number " + toString() + " is too big for " + std::to_string(max_digits) + " digits");
        }
    }

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
    explicit MPInt(const std::string &num) : mNumber(), mSign(1) {
        std::string num_copy = num;

        if (num[0] == '-') {
            mSign = -1;
            num_copy = num.substr(1);
        }

        for (auto i = static_cast<int32_t>(num_copy.length()); i > 0; i -= MAX_DIGITS) {
            if (i < MAX_DIGITS)
                mNumber.push_back(std::stoi(num_copy.substr(0, i)));
            else
                mNumber.push_back(std::stoi(num_copy.substr(i - MAX_DIGITS, MAX_DIGITS)));
        }

        checkLengthOfDigits();
    }

    MPInt(std::vector<uint32_t> num, int32_t sign) : mNumber(std::move(num)), mSign(sign) {
        checkLengthOfDigits();
    }

    MPInt(const MPInt &other) noexcept : mNumber(other.mNumber), mSign(other.mSign) {
        //
    }

    MPInt(MPInt &&other) noexcept : mNumber(std::move(other.mNumber)), mSign(other.mSign) {
        other.mNumber = {};
        other.mSign = 0;
    }

    ~MPInt() = default;

    MPInt &operator=(const MPInt &other) noexcept {
        mNumber = other.mNumber;
        mSign = other.mSign;
        return *this;
    }

    MPInt &operator=(MPInt &&other) noexcept {
        mNumber = std::move(other.mNumber);
        mSign = other.mSign;
        other.mNumber = {};
        other.mSign = 0;
        return *this;
    }

    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator+(const MPInt<max_digits_other> &other) {
        // + + + OR - + - -> Addition
        if (mSign == other.getSign())
            return {add(mNumber, other.getNumber()), mSign};
        // + + - OR - + + -> Subtraction (but swap sign of the second operand)
        else {
            MPInt<max_digits_other> tmp {other.getNumber(), -other.getSign()};
            return *this - tmp;
        }
    }

    template<int32_t max_digits_other>
    MPInt operator+=(const MPInt<max_digits_other> &other) {
        auto result = *this + other;
        if (MaxDigits<max_digits, max_digits_other>::value != max_digits)
            throw MyOverflowException("Number " + result.toString() + " is too big for " + std::to_string(max_digits) + " digits");
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator-(const MPInt<max_digits_other> &other) {
        // + - + OR - - - -> Subtraction
        if (mSign == other.getSign()) {
            if (*this >= other)
                return {sub(mNumber, other.getNumber()), mSign};
            else
                return {sub(other.getNumber(), mNumber), -mSign};
        }
        // + - - OR - - + -> Addition (but swap sign of the second operand)
        else {
            MPInt<max_digits_other> tmp {other.getNumber(), -other.getSign()};
            return *this + tmp;
        }
    }

    template<int32_t max_digits_other>
    MPInt operator-=(const MPInt<max_digits_other> &other) {
        auto result = *this - other;
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator*(const MPInt<max_digits_other> &other) {
        return {mul(mNumber, other.getNumber()), mSign * other.getSign()};
    }

    template<int32_t max_digits_other>
    MPInt operator*=(const MPInt<max_digits_other> &other) {
        auto result = *this * other;
        if (MaxDigits<max_digits, max_digits_other>::value != max_digits)
            throw MyOverflowException("Number " + result.toString() + " is too big for " + std::to_string(max_digits) + " digits");
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    template<int32_t max_digits_other>
    MPInt<MaxDigits<max_digits, max_digits_other>::value> operator/(const MPInt<max_digits_other> &other) {
        return {div(mNumber, other.getNumber()), mSign * other.getSign()};
    }

    template<int32_t max_digits_other>
    MPInt operator/=(const MPInt<max_digits_other> &other) {
        auto result = *this / other;
        mNumber = result.getNumber();
        mSign = result.getSign();
        return *this;
    }

    MPInt operator!() {
        return factorial();
    }

    template<int32_t max_digits_other>
    std::strong_ordering operator<=>(const MPInt<max_digits_other> &other) const {
        if (mSign != other.getSign())
            return mSign <=> other.getSign();

        if (mNumber.size() != other.getNumber().size())
            return mNumber.size() <=> other.getNumber().size();

        for (int32_t i = mNumber.size() - 1; i >= 0; i--) {
            if (mNumber[i] != other.getNumber()[i])
                return mNumber[i] <=> other.getNumber()[i];
        }

        return std::strong_ordering::equal;
    }

    template<int32_t max_digits_other>
    bool operator==(const MPInt<max_digits_other> &other) const {
        return ((*this <=> other) == std::strong_ordering::equal);
    }

    friend std::ostream& operator<<(std::ostream& os, const MPInt& num) {
        os << num.toString();
        return os;
    }

    std::string toString() const {
        std::stringstream result;
        if (mSign == -1)
            result << "-";
        result << mNumber[mNumber.size() - 1];
        for (int32_t i = static_cast<int32_t>(mNumber.size()) - 2; i >= 0; i--) {
            std::string str_num = std::to_string(mNumber[i]);
            for (int32_t j = 0; j < MAX_DIGITS - str_num.length(); j++) // "non leading" zeros
                result << "0";
            result << str_num;
        }
        return result.str();
    }

    std::vector<uint32_t> getNumber() const {
        return mNumber;
    }

    int32_t getSign() const {
        return mSign;
    }

};
