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

public:

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

    friend std::istream& operator>>(std::istream& is, Fruct& fruct) {
        is >> fruct.numeFruct;
        is >> fruct.greutateFruct;
        return is;
    }

    ~Fruct() = default;

    void setNumeFruct(const std::string& numeFruct) {
        this->numeFruct = numeFruct;
    }

    void setGreutateFruct(float greutateFruct) {
        this->greutateFruct = greutateFruct;
    }

    [[nodiscard]] const std::string & get_nume_fruct() const {
        return numeFruct;
    }

    [[nodiscard]] float get_greutate_fruct() const {
        // greutateFruct = 100; EROARE - functia este read-only
        return greutateFruct;
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

    Fruct i;
    float greutate;
    std::string nume;
    std::cin >> nume >> greutate;
    i.setGreutateFruct(greutate);
    i.setNumeFruct(nume);
    std::cout << i << std::endl;

    Fruct k;
    std::cin >> k;
    std::cout << k << "\n";
    return 0;
}