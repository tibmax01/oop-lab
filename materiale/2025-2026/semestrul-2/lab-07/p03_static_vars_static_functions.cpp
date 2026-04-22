#include <iostream>

class DummyClass {
    static int id;
    int i;

public:
    DummyClass(int i, int n) {
        this->i = i;
        id = n;
    }

    ~DummyClass() = default;

    void printInfo() {
        std::cout << "ID[" << i << "] = " << id << std::endl;
    }

    static void sPrintInfo() {
        std::cout << "ID = " << id << std::endl;
    }
};

int DummyClass::id = 0;

int main() {
    DummyClass dummyObj1(1, 5);
    dummyObj1.printInfo();

    DummyClass dummyObj2(2, 10);
    dummyObj2.printInfo();
    dummyObj1.printInfo();

    dummyObj2.sPrintInfo();
    DummyClass::sPrintInfo();
    return 0;
}