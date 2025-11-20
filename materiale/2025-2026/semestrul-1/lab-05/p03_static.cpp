#include <iostream>

class A {
private:
    static int s;
    int x;

public:
    A (int x) : x(x) {s++;}
    int getX() const { return x; }
    int getS() const { return s; }

    static void displayText() {
        std::cout << "Acesta este un text!\n";
        std::cout << s;
    }
};

class Student {
private:
    static int static_id_student;
    int id_student;

public:
    Student () : id_student(static_id_student++) {}
};

int A::s = 0;

int main() {
    A a(1);
    // std::cout << "A.X: " << a.getX() << std::endl;
    // std::cout << "A.S: " << a.getS() << std::endl;

    A b(2);
    // std::cout << "B.X: " << b.getX() << std::endl;
    // std::cout << "B.S: " << b.getS() << std::endl;
    //
    // std::cout << "A.S: " << a.getS() << std::endl;

    a.displayText();
    b.displayText();
    A::displayText();
}