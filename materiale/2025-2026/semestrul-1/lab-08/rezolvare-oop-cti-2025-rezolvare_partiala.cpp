#include <iostream>
#include <memory>
#include <vector>

enum TipArtefactArtistic {
    PICTURA = 0,
    SCULPTURA = 1
};

enum MaterialArtefactArtistic {
    ACRILIC = 0,
    ULEI = 1,
    LEMN = 2,
    PIATRA = 3,
    MARMURA = 4
};

enum GradColectibilitate {
    SCAZUT = 0,
    RIDICAT = 1
};

enum TipArtefact {
    ISTORIC,
    ARTISTIC,
    PRETIOS
};

class Artefact {
protected:
    static int static_id;
    const int id = static_id++;
    std::string nume;
    std::string dataSauEra;
    double pretInitial;
    TipArtefact tipArtefact;
    double pretCurent;

public:
    Artefact() = default;
    Artefact(const std::string& nume, const std::string& dataSauEra, double pretInitial)
        : nume(nume), dataSauEra(dataSauEra), pretInitial(pretInitial) {};
    virtual ~Artefact() = default;

    virtual void read(std::istream& is) {
        std::cout << "Nume: ";
        is >> nume;
        std::cout << "Data sau Era: ";
        is >> dataSauEra;
        std::cout << "Pret Initial: ";
        is >> pretInitial;
    }

    virtual void print(std::ostream& os) const {
        os << "ID: " << id << "\n";
        os << "Nume: " << nume << "\n";
        os << "Data sau Era: " << dataSauEra << "\n";
        os << "Pret Initial: " << pretInitial << "\n";
    }

    friend std::istream& operator>>(std::istream& is, Artefact& artefact) {
        artefact.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Artefact& artefact) {
        artefact.print(os);
        return os;
    }

    virtual GradColectibilitate calculeazaGradColectibilitate() = 0;

    [[nodiscard]] int get_id() const {
        return id;
    }

    [[nodiscard]] std::string get_nume() const {
        return nume;
    }

    [[nodiscard]] std::string get_data_sau_era() const {
        return dataSauEra;
    }

    [[nodiscard]] double get_pret_initial() const {
        return pretInitial;
    }

    [[nodiscard]] TipArtefact get_tip_artefact() const {
        return tipArtefact;
    }

    [[nodiscard]] double get_pret_curent() const {
        return pretCurent;
    }
};

int Artefact::static_id = 0;

class ArtefactIstoric : public Artefact {
private:
    std::vector<std::string> numePersoaneRenumite;

public:
    ArtefactIstoric() {
        tipArtefact = TipArtefact::ISTORIC;
    };
    ArtefactIstoric(const std::string& nume, const std::string& dataSauEra,
        double pretInitial, const std::vector<std::string>& numePersoaneRenumite) :
        Artefact(nume, dataSauEra, pretInitial), numePersoaneRenumite(numePersoaneRenumite) {
        tipArtefact = TipArtefact::ISTORIC;
    }

    void read(std::istream& is) override {
        Artefact::read(is);
        int numarPersoane;
        std::cout << "Numar Persoane: ";
        is >> numarPersoane;
        for (int i = 0; i < numarPersoane; i++) {
            std::string persoana;
            std::cout << "Persoana (" << i + 1 << "): ";
            is >> persoana;
            numePersoaneRenumite.push_back(persoana);
        }
    }

    void print(std::ostream& os) const override {
        Artefact::print(os);
        os << "Persoane renumite:\n";
        for (int i = 0; i < numePersoaneRenumite.size(); i++) {
            os << "Persoana " << i + 1 << ": " << numePersoaneRenumite[i] << "\n";
        }
    }

    GradColectibilitate calculeazaGradColectibilitate() override {
        return GradColectibilitate(numePersoaneRenumite.size() >= 3);
    }
};

class ArtefactArtistic : public Artefact {
private:
    TipArtefactArtistic tip;
    MaterialArtefactArtistic material;

public:
    ArtefactArtistic() {
        tipArtefact = TipArtefact::ARTISTIC;
    };
    ArtefactArtistic(const std::string& nume, const std::string& dataSauEra, double pretInitial,
        const TipArtefactArtistic& tip, const MaterialArtefactArtistic& material) :
        Artefact(nume, dataSauEra, pretInitial), tip(tip), material(material) {
        tipArtefact = TipArtefact::ARTISTIC;
    }

    void read(std::istream& is) override {
        Artefact::read(is);
        int optiune;
        std::cout << "Tip (0-1):";
        is >> optiune;
        this->tip = TipArtefactArtistic(optiune);

        std::cout << "Material (0-4):";
        this->material = MaterialArtefactArtistic(optiune);
    }

    void print(std::ostream& os) const override {
        Artefact::print(os);
        os << "Tip: " << tip << "\n";
        os << "Material: " << material << "\n";
    }

    GradColectibilitate calculeazaGradColectibilitate() override {
        return GradColectibilitate(
            material == MaterialArtefactArtistic::ULEI ||
            material == MaterialArtefactArtistic::MARMURA);
    }
};

class ArtefactPretios : public Artefact {
private:
    std::string numeDesigner;
    double greutate;

public:
    ArtefactPretios() {
        tipArtefact = TipArtefact::PRETIOS;
    };
    ArtefactPretios(const std::string& nume, const std::string& dataSauEra, double pretInitial,
        const std::string& numeDesigner, double greutate)
        : Artefact(nume, dataSauEra, pretInitial), numeDesigner(numeDesigner), greutate(greutate) {
        tipArtefact = TipArtefact::PRETIOS;
    }

    void read(std::istream& is) override {
        Artefact::read(is);
        std::cout << "Nume designer:";
        is >> numeDesigner;
        std::cout << "Greutate: ";
        is >> greutate;
    }

    void print(std::ostream& os) const override {
        Artefact::print(os);
        os << "Nume designer: " << numeDesigner << "\n";
        os << "Greutate: " << greutate << "\n";
    }

    GradColectibilitate calculeazaGradColectibilitate() override {
        return GradColectibilitate(
            numeDesigner != "Necunoscut" &&
            greutate >= 250);
    }
};

class Entitate {
protected:
    static int static_id;
    const int id = static_id++;
    double buget;
    double pasLicitare;
    double valoareConfort;
    TipArtefact tipPreferat;
    TipArtefact tipIgnorat;

    bool participaLaLicitatiaCurenta = true;
    unsigned int numarArtefacteCumparate = 0;


public:
    Entitate() = default;
    Entitate(double buget, double pasLicitare, double valoareConfort,
        const TipArtefact& tipPreferat, const TipArtefact& tipIgnorat)
        : buget(buget), pasLicitare(pasLicitare), valoareConfort(valoareConfort),
        tipPreferat(tipPreferat), tipIgnorat(tipIgnorat) {}
    virtual ~Entitate() = default;

    virtual void read(std::istream& is) {
        std::cout << "Buget: ";
        is >> buget;
        std::cout << "Pas Lictare: ";
        is >> pasLicitare;
        std::cout << "Valoare Confort: ";
        is >> valoareConfort;
        int optiune;
        std::cout << "Tip Preferat (0-2):";
        is >> optiune;
        this->tipPreferat = TipArtefact(optiune);
        std::cout << "Tip Ignorat (0-2):";
        is >> optiune;
        this->tipIgnorat = TipArtefact(optiune);
    }

    virtual void print(std::ostream& os) const {
        os << "ID: " << id << "\n";
        os << "Buget: " << buget << "\n";
        os << "Pas Lictare: " << pasLicitare << "\n";
        os << "Valoare Confort: " << valoareConfort << "\n";
        os << "Tip Preferat: " << tipPreferat << "\n";
        os << "Tip Ignorat: " << tipIgnorat << "\n";
    }

    friend std::istream& operator>>(std::istream& is, Entitate& entitate) {
        entitate.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Entitate& entitate) {
        entitate.print(os);
        return os;
    }

    virtual bool continuaLicitatie(std::shared_ptr<Artefact> artefact) = 0;
};

int Entitate::static_id = 0;

class PersoanaFizica : public Entitate {
private:
    std::string numeSauAlias;

public:
    PersoanaFizica() = default;
    PersoanaFizica(double buget, double pasLicitare, double valoareConfort,
        const TipArtefact& tipPreferat, const TipArtefact& tipIgnorat, const std::string& numeSauAlias) :
        Entitate(buget, pasLicitare, valoareConfort, tipPreferat, tipIgnorat),
        numeSauAlias(numeSauAlias) {}

    void read(std::istream& is) override {
        Entitate::read(is);
        std::cout << "Nume Sau Alias: ";
        is >> numeSauAlias;
    }

    void print(std::ostream& os) const override {
        Entitate::print(os);
        os << "Nume Sau Alias: " << numeSauAlias << "\n";
    }

    bool continuaLicitatie(std::shared_ptr<Artefact> artefact) override {
        if (artefact->get_tip_artefact() == tipIgnorat) return false;
        if (artefact->get_pret_curent() > buget) return false;
        if (artefact->get_tip_artefact() != tipPreferat
            && artefact->get_pret_curent() > valoareConfort) return false;
        return true;
    }
};

class PersoanaJuridica : public Entitate {
private:
    std::string numeOrganizatie;
    std::vector<std::shared_ptr<PersoanaFizica>> persoaneFizice;

public:
    PersoanaJuridica() = default;
    PersoanaJuridica(double buget, double pasLicitare, double valoareConfort,
        const TipArtefact& tipPreferat, const TipArtefact& tipIgnorat,
        const std::string& numeOrganizatie, const std::vector<std::shared_ptr<PersoanaFizica>>& persoaneFizice) :
        Entitate(buget, pasLicitare, valoareConfort, tipPreferat, tipIgnorat),
        numeOrganizatie(numeOrganizatie), persoaneFizice(persoaneFizice) {}

    void read(std::istream& is) override {
        Entitate::read(is);
        std::cout << "Nume Organizatie: ";
        is >> numeOrganizatie;
        int numarPersoane;
        std::cout << "Numar persoane:";
        is >> numarPersoane;
        for (int i = 0; i < numarPersoane; i++) {
            std::cout << "Persoana " << i + 1 << ": ";
            std::shared_ptr<PersoanaFizica> tempFizica = std::make_shared<PersoanaFizica>();
            is >> *tempFizica;
            persoaneFizice.push_back(tempFizica);
        }
    }

    void print(std::ostream& os) const override {
        Entitate::print(os);
        os << "Nume Organizatie: " << numeOrganizatie << "\n";
        std::cout << "Persoane fizice:\n";
        for (int i = 0; i < persoaneFizice.size(); i++) {
            os << "Persoana " << i + 1 << ": ";
            os << *(persoaneFizice[i]);
        }
    }

    bool continuaLicitatie(std::shared_ptr<Artefact> artefact) override {
        if (artefact->get_tip_artefact() == tipIgnorat) return false;
        if (artefact->get_pret_curent() > buget) return false;

        int voturi;
        for (auto & persoana : persoaneFizice) {
            voturi += persoana->continuaLicitatie(artefact);
        }

        if (artefact->get_tip_artefact() != tipPreferat) {
            if (artefact->get_pret_curent() > valoareConfort) return false;
            if (voturi < persoaneFizice.size() / 2) return false;
        }
        return true;
    }
};

class Licitatie {
private:
    std::vector<std::shared_ptr<Entitate>> entitati;
    std::vector<std::shared_ptr<Artefact>> artefacte;
    std::vector<std::shared_ptr<Artefact>> istoricLicitatii;

};

int main() {
    std::shared_ptr<Artefact> artefact = std::make_shared<ArtefactPretios>();
    std::shared_ptr<Entitate> entitate = std::make_shared<PersoanaJuridica>();

    std::cin >> *artefact;
    std::cout << *artefact << "\n--------\n";
    std::cout << artefact->calculeazaGradColectibilitate() << "\n-------\n";

    std::cin >> *entitate;
    std::cout << *entitate;
    return 0;
}