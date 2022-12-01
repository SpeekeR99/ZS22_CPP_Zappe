#pragma once

#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr uint32_t BASE = 1000000000;
constexpr uint8_t MAX_DIGITS = 9;
constexpr int8_t UNLIMITED = -1;

template <typename T>
concept LimitedDigit = requires(T t) {
    t >= 4;
};

template <typename T>
concept UnlimitedDigit = requires(T t) {
    t == UNLIMITED;
};

template <typename T>
concept ValidDigit = requires (T t) {
    std::is_integral_v<T>;
    LimitedDigit<T> || UnlimitedDigit<T>;
};

template <typename T, T x, T y>
requires ValidDigit<T>
struct MaxDigits {
    static const int32_t value = (x == UNLIMITED || y == UNLIMITED) ? UNLIMITED : (x > y) ? x : y;
};

template <int32_t max_digits>
class MPInt {
private:
    std::vector<uint32_t> number;
    int8_t sign;

    void checkLengthOfDigits() const {
        if (max_digits == UNLIMITED)
            return;

        if (number.size() * MAX_DIGITS > max_digits) {
            std::string str_num = std::to_string(number[number.size() - 1]);
            if (str_num.length() > max_digits % MAX_DIGITS)
                throw std::overflow_error("Number " + toString() + " is too big for " + std::to_string(max_digits) + " digits");
        }
    }

public:
    explicit MPInt(const std::string &num) : number(), sign(1) {
        std::string num_copy = num;

        if (num[0] == '-') {
            sign = -1;
            num_copy = num.substr(1);
        }

        for (auto i = static_cast<int32_t>(num_copy.length()); i > 0; i -= MAX_DIGITS) {
            if (i < MAX_DIGITS)
                number.push_back(std::stoi(num_copy.substr(0, i)));
            else
                number.push_back(std::stoi(num_copy.substr(i - MAX_DIGITS, MAX_DIGITS)));
        }

        checkLengthOfDigits();
    }

    MPInt(std::vector<uint32_t> num, int8_t sign) : number(std::move(num)), sign(sign) {
        checkLengthOfDigits();
    }

    ~MPInt() = default;

    template<int32_t max_digits_other>
    MPInt<MaxDigits<decltype(max_digits), max_digits, max_digits_other>::value> operator+(const MPInt<max_digits_other> &other) {
        // Adding two positive or two negative numbers
        if (sign == other.getSign()) {
            if (sign == 1)
                return {add(*this, other), 1};
            else
                return {add(*this, other), -1};
        }
        // Addition -> Subtraction
        else {
            // TODO
        }
        return {std::vector<uint32_t>{}, 1};
    }

    std::string toString() const {
        std::stringstream result;
        if (sign == -1)
            result << "-";
        for (int32_t i = number.size() - 1; i >= 0; i--)
            result << number[i];
        return result.str();
    }

    std::vector<uint32_t> getNumber() const {
        return number;
    }

    int8_t getSign() const {
        return sign;
    }

};

template<int32_t max_digits1, int32_t max_digits2>
std::vector<uint32_t> add(const MPInt<max_digits1> &num1, const MPInt<max_digits2> &num2) {
    std::vector<uint32_t> result_number;

    uint8_t carry = 0;
    for (size_t i = 0; i < num1.getNumber().size() || i < num2.getNumber().size() || carry; i++) {
        int32_t sum = (num1.getNumber().size() > i ? num1.getNumber()[i] : 0) +
                      (num2.getNumber().size() > i ? num2.getNumber()[i] : 0) + carry;
        carry = sum / BASE;
        sum %= BASE;
        result_number.push_back(sum);
    }

    return result_number;
}
