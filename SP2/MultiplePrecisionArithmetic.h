#pragma once

#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr uint32_t BASE = 1000000000;
constexpr uint32_t MAX_NUMBER = BASE - 1;
constexpr uint8_t MAX_DIGITS = 9;
constexpr int8_t UNLIMITED = -1;

template <int32_t max_bytes>
class MPInt {
private:
    std::vector<uint32_t> number;
    int8_t sign;

    template<int32_t max_bytes1, int32_t max_bytes2>
    std::vector<uint32_t> add(const MPInt<max_bytes1> &num1, const MPInt<max_bytes2> &num2) {
        MPInt result{};
        std::vector<uint32_t> result_number;

        int32_t carry = 0;
        for (size_t i = 0; i < num1.number.size() || carry; i++) {
            int32_t sum = (num1.number.size() >= i ? num1.number[i] : 0) +
                          (num2.number.size() >= i ? num2.number[i] : 0) + carry;
            carry = sum >= BASE;
            if (carry) sum -= BASE;
            result_number.push_back(sum);
        }

        return result_number;
    }

public:
    MPInt() = default;

    explicit MPInt(const std::string &num) : number(), sign(1) {
        std::string num_copy = num;

        if (num[0] == '-') {
            sign = -1;
            num_copy = num.substr(1);
        }

        for (auto i = static_cast<int32_t>(num_copy.length()); i >= 0; i -= MAX_DIGITS) {
            if (i < MAX_DIGITS)
                number.push_back(std::stoi(num_copy.substr(0, i)));
            else
                number.push_back(std::stoi(num_copy.substr(i - MAX_DIGITS, MAX_DIGITS)));
        }
    }

    MPInt(std::vector<uint32_t> num, int8_t sign) : number(std::move(num)), sign(sign) { }

    ~MPInt() = default;

    std::string toString() const {
        std::stringstream result;
        if (sign == -1)
            result << "-";
        for (int32_t i = number.size() - 1; i >= 0; i--)
            result << number[i];
        return result.str();
    }

    template<int32_t other_max_bytes>
    MPInt operator+(const MPInt<other_max_bytes> &other) {
        return MPInt<max_bytes>(add(*this, other), 1);
    }

};
