#include "../include/lab2.h" 
#include <vector>
#include <algorithm>



unsigned char Eleven::toDigit(char c) const {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c == 'A' || c == 'a') {
        return 10;
    }
    throw std::invalid_argument("Invalid char in string for Eleven number");
}

char Eleven::toChar(unsigned char d) const {
    if (d < 10) {
        return '0' + d;
    }
    if (d == 10) {
        return 'A';
    }
    
    throw std::out_of_range("Digit is out of range for base 11");
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
        throw std::invalid_argument("Initialization digit is not valid for base 11");
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

    
    std::vector<unsigned char> temp_digits;
    for (int i = t.length() - 1; i >= 0; --i) {
        temp_digits.push_back(toDigit(t[i]));
    }
    
    // Удаляем ведущие нули 
    while (temp_digits.size() > 1 && temp_digits.back() == 0) {
        temp_digits.pop_back();
    }
    
    _count = temp_digits.size();
    _digits = new unsigned char[_count];
    
    for (size_t i = 0; i < _count; ++i) {
        _digits[i] = temp_digits[i];
    }
}

Eleven::Eleven(const std::initializer_list<unsigned char>& t) {
    if (t.size() == 0) {
        _count = 1;
        _digits = new unsigned char[1];
        _digits[0] = 0;
        return;
    }

    std::vector<unsigned char> temp_digits;
    // Копируем в обратном порядке
    for (auto it = t.end(); it != t.begin(); ) {
        --it;
        if (*it > 10) {
            throw std::invalid_argument("Digit in initializer list is not valid");
        }
        temp_digits.push_back(*it);
    }
    
    // Удаляем ведущие нули
    while (temp_digits.size() > 1 && temp_digits.back() == 0) {
        temp_digits.pop_back();
    }

    _count = temp_digits.size();
    _digits = new unsigned char[_count];
    for (size_t i = 0; i < _count; ++i) {
        _digits[i] = temp_digits[i];
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
    std::string s = "";
    for (size_t i = _count; i > 0; --i) {
        s += toChar(_digits[i - 1]);
    }
    return s;
}

bool Eleven::equals(const Eleven& other) const {
    if (_count != other._count) {
        return false;
    }
    for (size_t i = 0; i < _count; ++i) {
        if (_digits[i] != other._digits[i]) {
            return false;
        }
    }
    return true;
}

bool Eleven::less(const Eleven& other) const {
    if (_count < other._count) return true;
    if (_count > other._count) return false;
    
    // Сравниваем цифры со старших разрядов к младшим
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
    std::vector<unsigned char> result_digits;
    int carry = 0;

    for (size_t i = 0; i < max_len; ++i) {
        int d1 = (i < _count) ? _digits[i] : 0;
        int d2 = (i < other._count) ? other._digits[i] : 0;
        int sum = d1 + d2 + carry;
        result_digits.push_back(sum % 11);
        carry = sum / 11;
    }

    if (carry > 0) {
        result_digits.push_back(carry);
    }
    
    
    Eleven result;
    delete[] result._digits; 
    result._count = result_digits.size();
    result._digits = new unsigned char[result._count];
    for(size_t i = 0; i < result._count; ++i) {
        result._digits[i] = result_digits[i];
    }
    
    return result;
}

Eleven Eleven::subtract(const Eleven& other) const {
    if (this->less(other)) {
        throw std::logic_error("Cannot subtract a larger number from a smaller one.");
    }

    std::vector<unsigned char> result_digits;
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
        result_digits.push_back(diff);
    }
    
    // Убираем ведущие нули
    while (result_digits.size() > 1 && result_digits.back() == 0) {
        result_digits.pop_back();
    }
    
    Eleven result;
    delete[] result._digits;
    result._count = result_digits.size();
    result._digits = new unsigned char[result._count];
    for(size_t i = 0; i < result._count; ++i) {
        result._digits[i] = result_digits[i];
    }
    
    return result;
}