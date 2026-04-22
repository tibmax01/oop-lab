#include <iostream>

class FormaGeometrica {
public:
    FormaGeometrica() {
        // std::cout << "Am creat o forma geometrica!\n";
    }

    virtual ~FormaGeometrica() {
        // std::cout << "Am distrus o forma geometrica!\n";
    }

    virtual FormaGeometrica* clone() = 0;

    virtual void printData() {
        std::cout << "Aceasta este o forma geometrica!\n";
    }
};

class Cerc : public FormaGeometrica {
public:
    Cerc() {
        // std::cout << "Am creat un cerc!\n";
    }

    ~Cerc() {
        // std::cout << "Am distrus un cerc!\n";
    }

    FormaGeometrica* clone() override {
        return new Cerc(*this); // FormaGeometrica* cerc = new Cerc();
    }

    void printData() override {
        std::cout << "Acesta este un cerc!\n";
    }
};

int main() {
    // // Destructor Virtual
    // FormaGeometrica* cerc = new Cerc();
    // cerc->printData();
    // delete cerc;

    // Constructor Virtual - clone()
    Cerc* cerc = new Cerc();
    cerc->printData();
    FormaGeometrica* formaGeometrica = cerc->clone();
    formaGeometrica->printData();

    delete formaGeometrica;
    delete cerc;
    return 0;
}