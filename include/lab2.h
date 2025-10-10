#ifndef LAB2_REFACTORED_H
#define LAB2_REFACTORED_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Eleven {
public:
    
    Eleven();
    Eleven(const size_t& n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char>& t);
    Eleven(const std::string& t);

    
    virtual ~Eleven() noexcept;
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    

  
    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;

    bool equals(const Eleven& other) const;
    bool less(const Eleven& other) const;
    bool greater(const Eleven& other) const;

    std::string toString() const;

private:
    
    unsigned char* _digits = nullptr; // Массив для хранения цифр
    size_t _count = 0;              // Количество цифр

    
    unsigned char toDigit(char c) const;
    char toChar(unsigned char d) const;
};

#endif 