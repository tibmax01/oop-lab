#include <iostream>

class MyException : public std::exception {
public:
    MyException() = default;
    ~MyException() = default;

    const char* what() const noexcept override{
        return "Aceasta este prima mea exceptie custom!\n";
    }
};

class MyParamException : public std::exception {
    std::string text;
public:
    MyParamException() = delete;
    MyParamException(const std::string& text) : text(text) {}
    ~MyParamException() = default;

    const char* what() const noexcept override{
        return text.c_str();
    }
};

int main() {
    // try {
    //     int a, b;
    //     std::cin >> a >> b;
    //     if (b == 0) throw b;
    //     std::cout << a / b << std::endl;
    //
    //     char c;
    //     std::cin >> c;
    //     if (c == 'a') throw c;
    //
    //     bool d;
    //     std::cin >> d;
    //     if (d == false) throw d;
    // } catch (int e) {
    //     std::cout << "Valoarea lui b este " << e << ", ceea ce este ilegal!\n";
    // } catch (char e) {
    //     std::cout << "Nu imi place litera " << e << "\n";
    // } catch (...) {
    //     std::cout << "O alta eroare, nu stiu despre ce e vorba!\n";
    // }


    try {
        int a;
        std::cin >> a;

        try {
            int b;
            std::cin >> b;
            throw MyParamException("Aceasta este o exceptie parametrizabila!\n");
        } catch (MyParamException &e) {
            std::cout << "TRY - INTERIOR: " << e.what() << std::endl;
            throw 1;
        }
    } catch (int e) {
        std::cout << "TRY - EXTERIOR: " << e << std::endl;
    }

    return 0;
}