#include "../include/lab2.h"
#include <algorithm>

unsigned char Eleven::toDigit(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'a' || c == 'A') return 10;
    throw std::invalid_argument("Invalid character in string representation");
}

char Eleven::toChar(unsigned char d) const {
    if (d <= 9) return '0' + d;
    if (d == 10) return 'A';
    throw std::out_of_range("Invalid digit value for base 11");
}

Eleven::Eleven() : _count(1) {
    _digits = new unsigned char[1];
    _digits[0] = 0;
}

Eleven::~Eleven() noexcept {
    delete[] _digits;
}

Eleven::Eleven(const size_t& n, unsigned char t) {
    if (t > 10) {
        throw std::invalid_argument("Invalid fill digit");
    }
    if (n == 0 || t == 0) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
    } else {
        _count = n;
        _digits = new unsigned char[_count];
        for (size_t i = 0; i < _count; ++i) {
            _digits[i] = t;
        }
    }
}

Eleven::Eleven(const std::string& t) {
    if (t.empty()) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
        return;
    }
    size_t first_digit_pos = 0;
    while (first_digit_pos < t.length() && t[first_digit_pos] == '0') {
        first_digit_pos++;
    }

    if (first_digit_pos == t.length()) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
        return;
    }

    _count = t.length() - first_digit_pos;
    _digits = new unsigned char[_count];
    for (size_t i = 0; i < _count; ++i) {
        _digits[i] = toDigit(t[t.length() - 1 - i]);
    }
}

Eleven::Eleven(const std::initializer_list<unsigned char>& t) {
    if (t.size() == 0) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
        return;
    }

    size_t leading_zeros = 0;
    for (unsigned char val : t) {
        if (val > 10) throw std::invalid_argument("Invalid digit in initializer list");
        if (val == 0) leading_zeros++;
        else break;
    }

    if (leading_zeros == t.size()) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
        return;
    }
    
    _count = t.size() - leading_zeros;
    _digits = new unsigned char[_count];
    size_t current_pos = _count;
    for (auto it = t.begin() + leading_zeros; it != t.end(); ++it) {
        _digits[--current_pos] = *it;
    }
}

Eleven::Eleven(const Eleven& other) : _count(other._count) {
    _digits = new unsigned char[_count];
    for (size_t i = 0; i < _count; ++i) {
        _digits[i] = other._digits[i];
    }
}

Eleven::Eleven(Eleven&& other) noexcept : _digits(other._digits), _count(other._count) {
    other._digits = nullptr;
    other._count = 0;
}

std::string Eleven::toString() const {
    if (_count == 0) return "0";
    std::string s = "";
    for (size_t i = _count; i > 0; --i) {
        s += toChar(_digits[i - 1]);
    }
    return s;
}

bool Eleven::equals(const Eleven& other) const {
    if (_count != other._count) return false;
    for (size_t i = 0; i < _count; ++i) {
        if (_digits[i] != other._digits[i]) return false;
    }
    return true;
}

bool Eleven::less(const Eleven& other) const {
    if (_count < other._count) return true;
    if (_count > other._count) return false;
    for (size_t i = _count; i > 0; --i) {
        if (_digits[i - 1] < other._digits[i - 1]) return true;
        if (_digits[i - 1] > other._digits[i - 1]) return false;
    }
    return false;
}

bool Eleven::greater(const Eleven& other) const {
    if (_count > other._count) return true;
    if (_count < other._count) return false;
    for (size_t i = _count; i > 0; --i) {
        if (_digits[i - 1] > other._digits[i - 1]) return true;
        if (_digits[i - 1] < other._digits[i - 1]) return false;
    }
    return false;
}

Eleven Eleven::add(const Eleven& other) const {
    size_t max_len = std::max(_count, other._count);
    unsigned char* temp_result = new unsigned char[max_len + 1];
    int carry = 0;

    for (size_t i = 0; i < max_len; ++i) {
        int d1 = (i < _count) ? _digits[i] : 0;
        int d2 = (i < other._count) ? other._digits[i] : 0;
        int sum = d1 + d2 + carry;
        temp_result[i] = sum % 11;
        carry = sum / 11;
    }
    
    size_t final_size = max_len;
    if (carry > 0) {
        temp_result[max_len] = carry;
        final_size = max_len + 1;
    }

    Eleven result;
    delete[] result._digits;
    result._count = final_size;
    result._digits = new unsigned char[final_size];
    for (size_t i = 0; i < final_size; ++i) {
        result._digits[i] = temp_result[i];
    }
    
    delete[] temp_result;
    return result;
}

Eleven Eleven::subtract(const Eleven& other) const {
    if (this->less(other)) {
        throw std::logic_error("Subtraction result would be negative");
    }

    unsigned char* temp_result = new unsigned char[_count];
    int borrow = 0;
    for (size_t i = 0; i < _count; ++i) {
        int d1 = _digits[i];
        int d2 = (i < other._count) ? other._digits[i] : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp_result[i] = diff;
    }
    
    size_t final_size = _count;
    while (final_size > 1 && temp_result[final_size - 1] == 0) {
        final_size--;
    }

    Eleven result;
    delete[] result._digits;
    result._count = final_size;
    result._digits = new unsigned char[final_size];
    for (size_t i = 0; i < final_size; ++i) {
        result._digits[i] = temp_result[i];
    }
    
    delete[] temp_result;
    return result;
}