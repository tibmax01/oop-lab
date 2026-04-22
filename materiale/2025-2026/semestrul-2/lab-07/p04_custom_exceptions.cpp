#include <iostream>

class MyException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Aceasta este o exceptie custom!";
    }
};

class MyCustomException : public std::exception {
private:
    std::string message;
public:
    MyCustomException(const std::string &message) : message(message) {}
    const char *what() const noexcept override {
        return message.c_str();
    }
};

class Impartire {
    int a, b;

public:
    Impartire(int a, int b) : a(a), b(b) {
        if (b == 0) {
            // throw std::invalid_argument("Impartirea la zero este ilegala!");
            // throw MyException();
            throw MyCustomException("Custom Exception!");
        }
    }

    int rezultat() {
        return a / b;
    }
};

int main() {
    // try {
    //     Impartire impartire(1, 0);
    //     std::cout << impartire.rezultat() << std::endl;
    // } catch (std::invalid_argument &e) {
    //     std::cout << e.what() << std::endl;
    // } catch (MyException &e) {
    //     std::cout << e.what() << std::endl;
    // } catch (...) {
    //     std::cout << "Exceptie nedefinita!\n";
    // }

    try {
        try {
            int a = 3;
            throw a;
        } catch (int a) {
            std :: cout << a << std :: endl;
            throw 'c';
        }
    } catch (char c) {
        std::cout << c << std::endl;
    }
    return 0;
}