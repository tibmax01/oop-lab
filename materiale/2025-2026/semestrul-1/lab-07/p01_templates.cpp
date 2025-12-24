#include <iostream>

// int getMin(int a, int b) {
//     if (a < b) {
//         std::cout << "a";
//         return a;
//     }
//     std::cout << "b";
//     return b;
// }
//
// float getMin(float a, float b) {
//     if (a < b) {
//         std::cout << "a";
//         return a;
//     }
//     std::cout << "b";
//     return b;
// }

template<typename T>
T getMin(T a, T b) {
    if (a < b) {
        std::cout << "a ";
        return a;
    }
    std::cout << "b ";
    return b;
}

template<typename T, typename U, int N>
class Sum {
private:
    T val1, val2;
    T val3[N];
    U val4;

public:
    Sum(T val1, T val2, U val4) : val1(val1), val2(val2), val4(val4) {}

    [[nodiscard]] T getVal1() const {
        return val1;
    }

    [[nodiscard]] T getVal2() const {
        return val2;
    }

    T getResult() {
        std::cout << val4 << std::endl;
        return val1 + val2;
    }
};

int main()
{
    std::cout << getMin<int>(4, 5) << "\n";
    std::cout << getMin<float>(3.7, 2.2) << "\n";

    std::cout << "-------------------------\n";

    Sum<float, std::string, 5> *sum = new Sum<float, std::string, 5>(3.5, 5.23, "Result:");
    std::cout << sum->getResult() << "\n";
    return 0;
}
