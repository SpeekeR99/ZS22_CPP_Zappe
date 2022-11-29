#pragma once

#include <sstream>
#include <string>
#include <vector>

constexpr uint32_t BASE = 1000000000;
constexpr uint32_t MAX_NUMBER = BASE - 1;
constexpr uint8_t MAX_DIGITS = 9;
constexpr int8_t UNLIMITED = -1;

template <int max_bytes>
class MPInt {
private:
    std::vector<int> number;
    int8_t sign;

public:
    explicit MPInt(const std::string &num) : number(), sign(1) {
        std::string num_copy = num;

        if (num[0] == '-') {
            sign = -1;
            num_copy = num.substr(1);
        }

        for (size_t i = 0; i < num_copy.length(); i += MAX_DIGITS) {
            if (i + MAX_DIGITS < num_copy.length()) {
                number.push_back(std::stoi(num_copy.substr(i, MAX_DIGITS)));
            } else {
                number.push_back(std::stoi(num_copy.substr(i)));
            }
        }
    }

    std::string toString() const {
        std::stringstream result;
        if (sign == -1)
            result << "-";
        for (int i : number)
            result << std::to_string(i);
        return result.str();
    }

};
