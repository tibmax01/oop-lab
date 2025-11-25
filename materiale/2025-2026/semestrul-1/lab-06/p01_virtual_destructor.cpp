#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    virtual ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

int main() {
    A* a = new B();
    B b;
    delete a;
    std::cout << "---------------------\n";
    return 0;
}