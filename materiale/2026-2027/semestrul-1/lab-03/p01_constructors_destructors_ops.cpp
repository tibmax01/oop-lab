#include <iostream>

class Fruct {
private:
    std::string nume;
    float greutate;

public:
    Fruct() {
        std::cout << "Fruct - Constructor Default\n";
    };
    Fruct(const std::string& nume, float greutate) {
        std::cout << "Fruct - Constructor Parametrizabil\n";
        this->nume = nume;
        this->greutate = greutate;
    }
    Fruct(const Fruct& fruct) {
        std::cout << "Fruct - Constructor de Copiere\n";
        this->nume = fruct.nume;
        this->greutate = fruct.greutate;
    }
    ~Fruct() {
        std::cout << "Fruct - Destructor\n";
    }

    Fruct& operator=(const Fruct& fruct) {
        std::cout << "Fruct - Operator Egal\n";
        this->nume = fruct.nume;
        this->greutate = fruct.greutate;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fruct& fruct) {
        os << "Fruct Nume: " << fruct.nume << std::endl;
        os << "Greutate: " << fruct.greutate << std::endl;
        return os;
    }

    void printInfo() const {
        std::cout << "Nume: " << this->nume << std::endl;
        std::cout << "Greutate: " << this->greutate << std::endl;
    }

    [[nodiscard]] const std::string & getNume() const {
        return nume;
    }

    void setNume(const std::string &nume) {
        this->nume = nume;
    }

    [[nodiscard]] float getGreutate() const {
        return greutate;
    }

    void setGreutate(const float greutate) {
        this->greutate = greutate;
    }
};

int main() {
    Fruct mar1("mar", 135);
    Fruct mar2(mar1);
    Fruct mar3;
    mar3 = mar2 = mar1;
    mar3.operator=(mar2.operator=(mar1));
    // mar3.printInfo();

    std::cout << mar3 << mar2 << mar1;;
    operator<<(operator<<(operator<<(std::cout, mar3), mar2), mar1);

    mar1.setNume("mar golden");
    mar1.setGreutate(105);
    std::cout << mar1.getNume() << " " << mar1.getGreutate() << std::endl;

    return 0;
}