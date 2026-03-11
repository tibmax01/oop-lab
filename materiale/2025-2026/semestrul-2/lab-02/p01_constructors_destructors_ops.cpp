#include <iostream>

union DummyUnion {
    int a;  // 32 biti
    char c; //  8 biti
}; // 32 biti

struct DummyStruct {
    int a;  // 32 biti
    char c; //  8 biti
}; // 40 biti

struct FructStruct {
    std::string nume;
    double gramaj;
};

class FructClass {
private:
    std::string nume{"no_name"};
    double gramaj{0};

public:
    FructClass() {
        std::cout << "Constructor Default\n";
    }

    FructClass(const std::string& nume) {
        this->nume = nume;
        this->gramaj = 50;

        std::cout << "Constructor Parametrizabil - 1\n";
    }

    FructClass(const std::string& nume, double gramaj) {
        this->nume = nume;
        this->gramaj = gramaj;

        std::cout << "Constructor Parametrizabil - 2\n";
    }

    FructClass& operator=(const FructClass& other) {
        this->nume = other.nume;
        this->gramaj = other.gramaj;
        return *this;
    }

    FructClass(const FructClass& fruit) {
        this->nume = fruit.nume;
        this->gramaj = fruit.gramaj;

        std::cout << "Constructor Copiere\n";
    }

    friend class DummyClass;
    friend std::ostream& operator<<(std::ostream& os, const FructClass& fruit) {
        os << fruit.nume << " " << fruit.gramaj << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, FructClass& fruit) {
        std::cout << "Nume: ";
        is >> fruit.nume;
        std::cout << "Gramaj: ";
        is >> fruit.gramaj;
        return is;
    }

    // std::ostream& operator<<(std::ostream& os) {
    //     os << this->nume << " " << this->gramaj << "\n";
    //     return os;
    // }

    void printInfo() {
        std::cout << this->nume << " " << this->gramaj << '\n';
    }

    ~FructClass() {
        std::cout << "Fructul " << nume << " a fost mancat!\n";
    }
};

class DummyClass {
private:
    FructClass a;

    void f() {
        std::cout << a.nume;
    }
};

int main() {
    // DummyUnion dummy;
    // dummy.a = 97;
    // std::cout << dummy.c << "\n";
    // dummy.c = 'b';
    // std::cout << dummy.a << "\n";

    FructStruct fructStruct("mar", 105);
    FructClass fructClass1("mar", 105), fructClass2;
    fructClass1.printInfo();
    fructClass2.printInfo();

    FructClass fructClass3(fructClass1);
    fructClass3.printInfo();

    FructClass fructClass4;
    fructClass4.printInfo();
    fructClass4 = fructClass1; // echivalent cu fructClass4.operator=(fructClass1);
    std::cout << fructClass4;

    operator<<(operator<<(std::cout, fructClass4), fructClass1);
    std::cout << fructClass4 << fructClass1;
    std::cout << "CITIRE:\n";
    std::cin >> fructClass1;
    std::cout << fructClass1;
    return 0;
}