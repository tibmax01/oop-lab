#include <iostream>

class Fruct {
private:
    std::string numeFruct;
    float greutateFruct;

public:

    Fruct() = default;
    Fruct(const std::string& numeFruct, float greutateFruct) {
        std::cout << "Fruct constructor parametrizabil" << std::endl;
        this->numeFruct = numeFruct;
        this->greutateFruct = greutateFruct;
    }

    Fruct(const Fruct& fruct) {
        std::cout << "Fruct copy constructor" << std::endl;
        this->numeFruct = fruct.numeFruct;
        this->greutateFruct = fruct.greutateFruct;
    }

    // h = g;
    Fruct& operator=(const Fruct& fruct) {
        std::cout << "Fruct assignment operator" << std::endl;
        this->numeFruct = fruct.numeFruct;
        this->greutateFruct = fruct.greutateFruct;
        return *this;
    }

    // std::cout << g;
    friend std::ostream& operator<<(std::ostream& os, const Fruct& fruct) {
        os << fruct.numeFruct << std::endl;
        os << fruct.greutateFruct << std::endl;
        return os;
    }

    ~Fruct() = default;

    void setNumeFruct(const std::string& numeFruct) {
        this->numeFruct = numeFruct;
    }

    void setGreutateFruct(float greutateFruct) {
        this->greutateFruct = greutateFruct;
    }

    std::string getNumeFruct() {
        return this->numeFruct;
    }

    float getGreutateFruct() {
        return this->greutateFruct;
    }

    void print() {
        std::cout << this->numeFruct << " are greutatea de " << this->greutateFruct << " grame." << std::endl;
    }
};

int main() {
    Fruct f("para", 250);
    f.print();
    Fruct g;
    g.setNumeFruct("mar");
    g.setGreutateFruct(200);

    // std::cout << f << g;
    operator<<(operator<<(std::cout, f), g);

    Fruct h, j;
    // h = g;
    // h = g;
    // j = h;
    j.operator=(h.operator=(g));

    h.print();
    return 0;
}