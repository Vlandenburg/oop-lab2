#include "./include/lab2.h"
#include <iostream>
#include <string>
#include <exception>

void print_line() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    std::cout << "Демонстрация работы с 11-ричными числами" << std::endl;
    print_line();

    std::string input1, input2;
    std::cout << "Введите первое 11-ричное число (цифры 0-9, A): ";
    std::cin >> input1;
    std::cout << "Введите второе 11-ричное число (цифры 0-9, A): ";
    std::cin >> input2;
    print_line();

    try {
        Eleven num1(input1);
        Eleven num2(input2);

        std::cout << "Число 1: " << num1.toString() << std::endl;
        std::cout << "Число 2: " << num2.toString() << std::endl;
        print_line();
        
        std::cout << "Результаты сравнения:" << std::endl;
        std::cout << "  Число 1 == Число 2: " << (num1.equals(num2) ? "Да" : "Нет") << std::endl;
        std::cout << "  Число 1 > Число 2: " << (num1.greater(num2) ? "Да" : "Нет") << std::endl;
        std::cout << "  Число 1 < Число 2: " << (num1.less(num2) ? "Да" : "Нет") << std::endl;
        print_line();

        std::cout << "Арифметические операции:" << std::endl;
        Eleven sum = num1.add(num2);
        std::cout << "  Сложение: " << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << std::endl;
        
        try {
            Eleven diff = num1.subtract(num2);
            std::cout << "  Вычитание: " << num1.toString() << " - " << num2.toString() << " = " << diff.toString() << std::endl;
        } catch (const std::logic_error& e) {
            std::cerr << "  Ошибка вычитания: " << e.what() << std::endl;
        }
        print_line();

    } catch (const std::exception& e) {
        std::cerr << "Произошла критическая ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}