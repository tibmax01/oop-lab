#include <iostream>
#include <memory>

class A {
private:
    int x;

public:
    A(int x) : x(x) {
        std::cout << "Am facut A(" << x << ")" << std::endl;
    }
    ~A() {
        std::cout << "Am sters A(" << x << ")" << std::endl;
    }
};

int main() {
    // std::unique_ptr<A> a2 = std::make_unique<A>(2);
    //
    // {
    //     std::unique_ptr<A> a3 = std::make_unique<A>(3);
    //     // std::unique_ptr<A> a4 = a3; // error
    // }

    std::shared_ptr<A> a4 = std::make_shared<A>(4);
    std::cout << "Contor: " << a4.use_count() << std::endl;

    {
        std::shared_ptr<A> a5 = a4;
        std::cout << "Contor: " << a4.use_count() << std::endl;

        if (1) {
            std::shared_ptr<A> a6 = a5;
            std::cout << "Contor: " << a4.use_count() << std::endl;
        }

        std::cout << "Contor: " << a4.use_count() << std::endl;

        std::weak_ptr<A> a7 = a5;
        std::cout << "Contor: " << a4.use_count() << std::endl;
    }

    std::cout << "Contor: " << a4.use_count() << std::endl;

    return 0;
}