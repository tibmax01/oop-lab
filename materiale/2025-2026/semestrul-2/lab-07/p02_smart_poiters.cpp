#include <iostream>
#include <memory>

class DummyClass {
    int n;

public:
    DummyClass(int n) : n(n) {
        std::cout << "[CONSTRUCTOR] - n: " << n << std::endl;
    }

    ~DummyClass() {
        std::cout << "[DESTRUCTOR] - n: " << n << std::endl;
    }
};

int main() {
    // // unique_ptr
    // std::unique_ptr<DummyClass> unique = std::make_unique<DummyClass>(3);
    // std::cout << "BEFORE\n";
    // {
    //     std::unique_ptr<DummyClass> unique2 = std::make_unique<DummyClass>(10);
    // }
    // std::cout << "AFTER\n";

    // shared_ptr
    std::shared_ptr<DummyClass> ptr = std::make_shared<DummyClass>(3);
    std::cout << "[CNT]: " << ptr.use_count() << std::endl;
    std::cout << "BEFORE\n";
    {
        std::cout << "[CNT]: " << ptr.use_count() << std::endl;
        std::shared_ptr<DummyClass> ptr1 = ptr;
        std::cout << "[CNT]: " << ptr.use_count() << std::endl;
        std::cout << "BEFORE 2\n";
        {
            std::cout << "[CNT]: " << ptr.use_count() << std::endl;
            std::shared_ptr<DummyClass> ptr2 = ptr1;
            std::cout << "[CNT]: " << ptr.use_count() << std::endl;
        }
        std::cout << "AFTER 2\n";
        std::cout << "[CNT]: " << ptr.use_count() << std::endl;
    }
    std::cout << "AFTER\n";
    std::cout << "[CNT]: " << ptr.use_count() << std::endl;
    return 0;
}