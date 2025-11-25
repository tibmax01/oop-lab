#include <iostream>
#include <vector>

int numarChitare = 0;
int numarPiane = 0;

class Instrument {
protected:
    std::string tipInstrument;

public:
    Instrument() = default;
    virtual ~Instrument() = default;
    Instrument(const std::string& tipInstrument) : tipInstrument(tipInstrument) {}

    virtual void print(std::ostream& os) const {
        os << "Tip Instrument: " << tipInstrument << "\n";
    }

    friend std::ostream& operator<< (std::ostream& os, const Instrument& instrument) {
        instrument.print(os);
        return os;
    }

    virtual void sunet() {
        std::cout << "Suna bine!\n";
    }

    virtual Instrument* clone() const = 0;
};

class Chitara : public Instrument {
private:
    std::string tipChitara;
    int numarCorzi = 6;

public:
    Chitara() = default;
    virtual ~Chitara() = default;
    Chitara(const std::string& tipInstrument, const std::string& tipChitara)
        : Instrument(tipInstrument), tipChitara(tipChitara) {}

    void print(std::ostream& os) const override {
        Instrument::print(os);
        os << "Tip Chitara: " << tipChitara << "\n";
    }

    void sunet() override {
        std::cout << "Suna a chitara!\n";
    }

    void cateCorzi() {
        std::cout << "Sunt " << numarCorzi << " corzi!\n";
    }

    Instrument* clone() const override {
        return new Chitara(*this);
    }
};

class Pian : public Instrument {
private:
    std::string tipPian;
    int numarOctave = 8;

public:
    Pian() = default;
    virtual ~Pian() = default;
    Pian(const std::string& tipInstrument, const std::string& tipPian)
        : Instrument(tipInstrument), tipPian(tipPian) {}

    void print(std::ostream& os) const override {
        Instrument::print(os);
        os << "Tip Pian: " << tipPian << "\n";
    }

    void sunet() override {
        std::cout << "Suna a pian!\n";
    }

    void cateOctave() {
        std::cout << "Sunt " << numarOctave << " octave!\n";
    }

    Instrument* clone() const override {
        return new Pian(*this);
    }
};

int main() {
    // Instrument* instrument = new Chitara("coarda", "acustica");
    // std::cout << *instrument << "\n";
    //
    // Instrument* intrument2 = instrument->clone();
    // std::cout << *intrument2 << "\n";

    std::vector<Instrument*> instrumente;
    instrumente.push_back(new Chitara("coarda", "acustica"));
    instrumente.push_back(new Pian("coarda", "concert"));
    instrumente.push_back(new Chitara("coarda", "clasica"));
    instrumente.push_back(new Chitara("coarda", "bass"));
    instrumente.push_back(new Pian("coarda", "electric"));

    for (int i = 0; i < instrumente.size(); i++) {
        Pian* pian = dynamic_cast<Pian*>(instrumente[i]);
        Chitara* chitara = dynamic_cast<Chitara*>(instrumente[i]);

        instrumente[i]->print(std::cout);

        if (dynamic_cast<Pian*>(instrumente[i]) != nullptr) {
            std::cout << "Acesta este un pian!\n";
            numarPiane++;
        }

        if (dynamic_cast<Chitara*>(instrumente[i]) != nullptr) {
            std::cout << "Acesta este o chitara!\n";
            numarChitare++;
        }

        if (pian != nullptr) {
            pian->cateOctave();
        } else if (chitara != nullptr) {
            chitara->cateCorzi();
        } else {
            std::cout << "Alt tip de instrument\n";
        }

        std::cout << std::endl;
    }

    // Chitara chitara("coarda", "clasica");
    // chitara.sunet();
    //
    // std::cout << "------------------------\n";
    //
    // Instrument &instrument = chitara;
    // instrument.sunet();

    std::cout << numarPiane << std::endl;
    std::cout << numarChitare << std::endl;

    return 0;
}
