#include <iostream>

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

    virtual Instrument* clone() const = 0;
};

class Chitara : public Instrument {
private:
    std::string tipChitara;

public:
    Chitara() = default;
    virtual ~Chitara() = default;
    Chitara(const std::string& tipInstrument, const std::string& tipChitara)
        : Instrument(tipInstrument), tipChitara(tipChitara) {}

    void print(std::ostream& os) const override {
        Instrument::print(os);
        os << "Tip Chitara: " << tipChitara << "\n";
    }

    Instrument* clone() const override {
        return new Chitara(*this);
    }
};

class Pian : public Instrument {
private:
    std::string tipPian;

public:
    Pian() = default;
    virtual ~Pian() = default;
    Pian(const std::string& tipInstrument, const std::string& tipPian)
        : Instrument(tipInstrument), tipPian(tipPian) {}

    void print(std::ostream& os) const override {
        Instrument::print(os);
        os << "Tip Pian: " << tipPian << "\n";
    }

    Instrument* clone() const override {
        return new Pian(*this);
    }
};

int main() {
    Instrument* instrument = new Chitara("coarda", "acustica");
    std::cout << *instrument << "\n";

    Instrument* intrument2 = instrument->clone();
    std::cout << *intrument2 << "\n";
    return 0;
}
