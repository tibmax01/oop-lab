#include <iostream>
#include <vector>
#include <fstream>

class Vaccin {
protected:
    double pret;
    double temperaturaDepozitare;
    std::vector<std::string> substante;
    std::string schemaVaccinare;
    std::string producator;

public:
    Vaccin() = default;
    Vaccin(double pret, double temperaturaDepozitare, const std::vector<std::string>& substante, const std::string producator)
        : pret(pret), temperaturaDepozitare(temperaturaDepozitare), substante(substante), producator(producator) {}
    virtual ~Vaccin() = default;

    virtual void print(std::ostream& os) const {
        os << "Pret: " << pret << std::endl;
        os << "Temperatura Depozitare: " << temperaturaDepozitare << std::endl;
        os << "Substante:\n";
        for (auto &substanta : substante) {
            os << substanta << std::endl;
        }
        os << "Producator: " << producator << std::endl;
        os << "Schema Vaccinare: " << schemaVaccinare << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vaccin& vaccin) {
        vaccin.print(os);
        return os;
    }

    virtual void read(std::istream& is) {
        std::cout << "Pret: ";
        is >> pret;
        std::cout << "Temperatura Depozitare: ";
        is >> temperaturaDepozitare;
        int numarSubstante;
        std::cout << "Numar Substante:\n";
        is >> numarSubstante;
        for (int i = 0; i < numarSubstante; i++) {
            std::string substanta;
            is >> substanta;
            substante.push_back(substanta);
        }
        std::cout << "Producator: ";
        is >> producator;
    }

    friend std::istream& operator>>(std::istream& is, Vaccin& vaccin) {
        vaccin.read(is);
        return is;
    }

    [[nodiscard]] std::string getProducator() const {
        return producator;
    }

    [[nodiscard]] double getPret() const {
        return pret;
    }

    [[nodiscard]] std::string getSchemaVaccinare() const {
        return schemaVaccinare;
    }
};

enum TulpinaVaccinAntiGripal {
    A_H1N1 = 1,
    A_H3N2 = 2,
    A_California = 3
};

enum TipHepatita {
    A = 1,
    B = 2,
    C = 3
};

enum ModAdministareVaccinAntiHepatita {
    INTRAMUSCULAR = 1,
    SUBCUTANAT = 2,
    INTRADERMIC = 3
};

class VaccinAntiGripal : public Vaccin {
private:
    TulpinaVaccinAntiGripal tulpina;
    bool respectaOMS;

public:
    VaccinAntiGripal() {
        schemaVaccinare = "se administrează la adulți o doză de 0.5 ml, iar la copii și adolescenți o doză de 0.3 ml, repetându-se din 2 în 2 ani";
    };
    VaccinAntiGripal(double pret, double temperaturaDepozitare, const std::vector<std::string>& substante, const std::string producator,
        const TulpinaVaccinAntiGripal& tulpina, bool respectaOMS) : Vaccin(pret, temperaturaDepozitare, substante, producator),
        tulpina(tulpina), respectaOMS(respectaOMS) {
        schemaVaccinare = "se administrează la adulți o doză de 0.5 ml, iar la copii și adolescenți o doză de 0.3 ml, repetându-se din 2 în 2 ani";
    }

    void print(std::ostream& os) const override {
        Vaccin::print(os);
        os << "Tulpina Vaccin: " << tulpina << std::endl;
        os << "Respecta OMS: " << respectaOMS << std::endl;
    }

    void read(std::istream& is) override {
        Vaccin::read(is);
        std::cout << "Tulpina Vaccin (1-3): ";
        int tulpinaVaccin;
        is >> tulpinaVaccin;
        tulpina = TulpinaVaccinAntiGripal(tulpinaVaccin);
        std::cout << "Respecta OMS: ";
        is >> respectaOMS;
    }
};

class VaccinAntiHepatita : public Vaccin {
private:
    TipHepatita tipHepatita;
    ModAdministareVaccinAntiHepatita mod;

public:
    VaccinAntiHepatita() {
        schemaVaccinare = "cel Antihepatită A și B, la copii cu vârstă mai mică de 1 an se adminstrează 2 injectări"
                          "la un interval de o lună, a treia injectare după 6 luni de la prima administrare,"
                          "la adulți conform schemei de imunizare recomandată de medic; cel Antihepatită C doar la recomandarea medicului";
    };
    VaccinAntiHepatita(double pret, double temperaturaDepozitare, const std::vector<std::string>& substante, const std::string producator,
        const TipHepatita& tipHepatita, const ModAdministareVaccinAntiHepatita& mod) : Vaccin(pret, temperaturaDepozitare, substante, producator),
        tipHepatita(tipHepatita), mod(mod) {
        if (tipHepatita == TipHepatita::A || tipHepatita == TipHepatita::B) {
            schemaVaccinare = "la copii cu vârstă mai mică de 1 an se adminstrează 2 injectări"
                              "la un interval de o lună, a treia injectare după 6 luni de la prima administrare,"
                              "la adulți conform schemei de imunizare recomandată de medic";
        } else {
            schemaVaccinare = "doar la recomandarea medicului";
        }
    }

    void print(std::ostream& os) const override {
        Vaccin::print(os);
        os << "Tip Hepatita: " << tipHepatita << std::endl;
        os << "Mod Administrare: " << mod << std::endl;
    }

    void read(std::istream& is) override {
        Vaccin::read(is);
        std::cout << "Tip Hepatita (1-3): ";
        int tip;
        is >> tip;
        tipHepatita = TipHepatita(tip);
        std::cout << "Mod Administrare (1-3): ";
        is >> tip;
        mod = ModAdministareVaccinAntiHepatita(tip);
    }
};

class VaccinAntiSarsCov2 : public Vaccin {
private:
    std::vector<std::string> reactiiAdverse;
    double rataEficienta;
    std::vector<std::string> medicamenteContraindicate;

public:
    VaccinAntiSarsCov2() {
        schemaVaccinare = "se administrează persoanelor cu vârstă de peste 16 ani, 2 doze la o perioadă de 21 zile";
    };
    VaccinAntiSarsCov2(double pret, double temperaturaDepozitare, const std::vector<std::string>& substante, const std::string producator,
        const std::vector<std::string>& reactiiAdverse, double rataEficienta, const std::vector<std::string>& medicamenteContraindicate)
        : Vaccin(pret, temperaturaDepozitare, substante, producator), reactiiAdverse(reactiiAdverse), rataEficienta(rataEficienta),
        medicamenteContraindicate(medicamenteContraindicate) {
        schemaVaccinare = "se administrează persoanelor cu vârstă de peste 16 ani, 2 doze la o perioadă de 21 zile";
    }

    void print(std::ostream& os) const override {
        Vaccin::print(os);
        os << "Reactii Adverse:\n";
        for (auto &reactieAdversa : reactiiAdverse) {
            os << reactieAdversa << std::endl;
        }

        os << "Rata Eficienta: " << rataEficienta << std::endl;

        os << "Medicamente Contraindicate:\n";
        for (auto &medicamentContraindicat : medicamenteContraindicate) {
            os << medicamentContraindicat << std::endl;
        }
    }

    void read(std::istream& is) override {
        int nr;
        std::cout << "Numar reactii alergice: ";
        is >> nr;
        for (int i = 0; i < nr; i++) {
            std::string reactie;
            is >> reactie;
            reactiiAdverse.push_back(reactie);
        }

        std::cout << "Rata Eficienta:";
        is >> rataEficienta;

        std::cout << "Numar medicamente Contraindicate: ";
        is >> nr;
        for (int i = 0; i < nr; i++) {
            std::string medicament;
            is >> medicament;
            medicamenteContraindicate.push_back(medicament);
        }
    }
};

struct VaccinCantitate {
    Vaccin* vaccin;
    unsigned int cantitate;
};

class Comanda {
private:
    static int static_id;
    int id;
    std::string data;
    std::string client;
    std::vector<VaccinCantitate> vaccinuri;
    double sumaMinimaComanda;

public:
    Comanda() : id(++static_id) {}
    Comanda(const std::string& data, const std::string& client, const std::vector<VaccinCantitate>& vaccinuri, double sumaMinimaComanda)
        : id(++static_id), data(data), client(client), vaccinuri(vaccinuri), sumaMinimaComanda(sumaMinimaComanda) {}

    virtual void print(std::ostream& os) const {
        os << "ID: " << id << std::endl;
        os << "Data: " << data << std::endl;
        os << "Client: " << client << std::endl;
        os << "Vaccinuri: " << vaccinuri.size() << std::endl;
        for (auto &vaccin : vaccinuri) {
            os << "Cantitate: " << vaccin.cantitate << std::endl;
            os << vaccin.vaccin << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& comanda) {
        comanda.print(os);
        return os;
    }

    virtual void read(std::istream& is) {
        std::cout << "Data: ";
        is >> data;
        std::cout << "Client: ";
        is >> client;
        int nr;
        std::cout << "Tipuri de vaccinuri: ";
        is >> nr;
        for (int i = 0; i < nr; i++) {
            Vaccin* vaccin;
            int tip;
            std::cout << "Tip Vaccin (1-3): ";
            std::cin >> tip;

            if (tip == 1) {
                vaccin = new VaccinAntiGripal();
            }
            else if (tip == 2) {
                vaccin = new VaccinAntiHepatita();
            } else if (tip == 3) {
                vaccin = new VaccinAntiSarsCov2();
            }

            int numarVaccinuri;
            std::cout << "Numar Vaccinuri: ";
            is >> numarVaccinuri;

            VaccinCantitate vaccinCantitate;
            vaccinCantitate.vaccin = vaccin;
            vaccinCantitate.cantitate = numarVaccinuri;
            vaccinuri.push_back(vaccinCantitate);
        }

    }

    friend std::istream& operator>>(std::istream& is, Comanda& comanda) {
        comanda.read(is);
        return is;
    }

    [[nodiscard]] std::string getData() const {
        return data;
    }

    double getPretTotal() {
        double pretTotal = 0;
        for (auto &vaccin : vaccinuri) {
            pretTotal += vaccin.cantitate * vaccin.vaccin->getPret();
        }
        return pretTotal;
    }
};

class Aplicatie {
private:
    std::vector<Vaccin*> vaccinuri;
    std::vector<Comanda*> comenzi;

public:
    Aplicatie() = default;
    Aplicatie(const std::vector<Vaccin*>& vaccinuri, const std::vector<Comanda*>& comenzi) : vaccinuri(vaccinuri), comenzi(comenzi) {}

    void adaugaVaccin() {
        int tip;
        Vaccin* vaccin;
        std::cout << "Tip Vaccin (1-3): ";
        std::cin >> tip;

        if (tip == 1) {
            vaccin = new VaccinAntiGripal();
        }
        else if (tip == 2) {
            vaccin = new VaccinAntiHepatita();
        } else if (tip == 3) {
            vaccin = new VaccinAntiSarsCov2();
        }

        std::cin >> *vaccin;
        vaccinuri.push_back(vaccin);
    }

    void afisareVaccinuri() {
        for (auto &vaccin : vaccinuri) {
            std::cout << vaccin << std::endl;
        }
    }

    void afisareNumeProducatori() {
        for (auto &vaccin : vaccinuri) {
            std::cout << vaccin->getProducator() << std::endl;
        }
    }

    void adaugaComanda() {
        Comanda *comanda = new Comanda();
        std::cin >> *comanda;
        comenzi.push_back(comanda);
    }

    void afisareComenzi() {
        for (auto &comanda : comenzi) {
            std::cout << comanda << std::endl;
        }
    }

    void totalComenziData(std::string data) {
        double sumaTotala = 0;
        for (auto &comanda : comenzi) {
            if (comanda->getData() == data) {
                sumaTotala += comanda->getPretTotal();
            }
        }
        std::cout << sumaTotala << std::endl;
    }

    void afisareSchemaVaccinare() {
        Vaccin* vaccin;
        int tip;
        std::cout << "Tip Vaccin (1-3): ";
        std::cin >> tip;

        if (tip == 1) {
            vaccin = new VaccinAntiGripal();
        }
        else if (tip == 2) {
            vaccin = new VaccinAntiHepatita();
        } else if (tip == 3) {
            vaccin = new VaccinAntiSarsCov2();
        }

        std::cout << vaccin->getSchemaVaccinare() << std::endl;
    }

    void exportComenzi(std::string numeFisier) {
        std::ofstream fout(numeFisier);
        for (auto &comanda : comenzi) {
            fout << comanda << std::endl;
        }
    }
};

int main() {

    return 0;

}