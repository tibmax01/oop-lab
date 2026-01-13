#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

enum TipProdus {BAUTURA, DESERT, BURGER};
enum TipDesert {FELIE, CUPA, PORTIE};
enum TipAngajat {CASIER, BUCATAR, LIVRATOR};
enum Strategie {FIFO, GREU, USOR};
enum ProdusMeniu {
    COLA, FANTA, LIMONADA,
    INGHETATA, TORT, STRUDEL,
    BURGER_LIGHT, BURGER_FULL
};

class Produs {
protected:
    std::string nume;
    double gramaj;
    TipProdus tipProdus;

public:
    Produs() = default;
    Produs(const std::string& nume, double gramaj, const TipProdus& tipProdus) : nume(nume), gramaj(gramaj), tipProdus(tipProdus) {}
    virtual ~Produs() = default;

    [[nodiscard]] virtual double energie() const = 0;
};

class Bautura : public Produs {
private:
    bool laSticla;

public:
    Bautura() = default;
    Bautura(const std::string& nume, double gramaj, bool laSticla)
        : Produs(nume, gramaj, BAUTURA), laSticla(laSticla) {}

    [[nodiscard]] double energie() const override {
        return laSticla ? 25 : 0.25 * gramaj;
    }
};

class Desert : public Produs {
private:
    TipDesert tipDesert;

public:
    Desert() = default;
    Desert(const std::string& nume, double gramaj, TipDesert tipDesert)
        : Produs(nume, gramaj, DESERT), tipDesert(tipDesert) {}

    [[nodiscard]] double energie() const override {
        switch (tipDesert) {
            case FELIE:     return 25;
            case PORTIE:    return 0.5 * gramaj;
            case CUPA:      return 2 * gramaj;
            default:        return 0;
        }
    }
};

class Burger : public Produs {
private:
    std::vector<std::string> ingrediente;

public:
    Burger() = default;
    Burger(const std::string& nume, double gramaj, const std::vector<std::string>& ingrediente)
        : Produs(nume, gramaj, BURGER), ingrediente(ingrediente) {}

    [[nodiscard]] double energie() const override {
        return gramaj * 0.25 * ingrediente.size();
    }
};

class Comanda {
private:
    static int nextId;
    const int id;

    std::vector<std::shared_ptr<Produs>> produse;
    bool comandaPrioritara;
    double energieTotala;
public:
    Comanda() : id(++nextId) {}

    void adaugaProdus(const std::shared_ptr<Produs>& produs) {
        produse.push_back(produs);
        energieTotala += produs->energie();
    }

    [[nodiscard]] double getEnergieTotala() const {
        return energieTotala;
    }

    void setEnergieTotala(const double energie_totala) {
        energieTotala = energie_totala;
    }

    [[nodiscard]] std::vector<std::shared_ptr<Produs>> getProduse() const {
        return produse;
    }

    [[nodiscard]] bool esteComandaPrioritara() const {
        return comandaPrioritara;
    }
};

int Comanda::nextId = 0;

class Angajat {
protected:
    TipAngajat tipAngajat;
    double energie;

public:
    Angajat() = default;
    Angajat(const TipAngajat& tipAngajat, double energie) : tipAngajat(tipAngajat), energie(energie) {}
    virtual ~Angajat() = default;

    [[nodiscard]] virtual double costPreluare() const { return 100; }
    [[nodiscard]] virtual double costLivrare() const { return 100; }
    [[nodiscard]] virtual double eficientaPreparare() const { return 1; }
    virtual void finalCiclu() { energie = 100; }

    [[nodiscard]] double getEnergie() const {
        return energie;
    }

    void setEnergie(const double energie) {
        this->energie = energie;
    }
};

class Casier : public Angajat {
public:
    Casier(double energie = 100) : Angajat(CASIER, energie) {}
    [[nodiscard]] double costPreluare() const override { return 25; }
};

class Livrator : public Angajat {
public:
    Livrator(double energie = 100) : Angajat(LIVRATOR, energie) {}
    [[nodiscard]] double costLivrare() const override { return 25; }
};

class Bucatar : public Angajat {
public:
    Bucatar(double energie = 100) : Angajat(BUCATAR, energie) {}
    [[nodiscard]] double eficientaPreparare() const override { return 2; }
    void finalCiclu() override { energie += 100; }
};

class Simulator {
private:
    std::vector<std::shared_ptr<Comanda>> comenzi;
    std::vector<std::shared_ptr<Angajat>> angajati;
    std::vector<std::shared_ptr<Produs>> meniuProduse;
    Strategie strategie;

    static Simulator* instance;

    Simulator(const Strategie& strategie) : strategie(strategie) {}

public:
    Simulator(const Simulator&) = delete;
    Simulator& operator=(const Simulator&) = delete;

    static Simulator* getInstance(const Strategie& strategie) {
        if (instance == nullptr) {
            instance = new Simulator(strategie);
        }
        return instance;
    }

    void initializeazaMeniu() {
        meniuProduse.push_back(std::make_shared<Bautura>("COLA", 500, true));
        meniuProduse.push_back(std::make_shared<Bautura>("FANTA", 250, true));
        meniuProduse.push_back(std::make_shared<Bautura>("LIMONADA", 500, false));

        meniuProduse.push_back(std::make_shared<Desert>("INGHETATA", 200, CUPA));
        meniuProduse.push_back(std::make_shared<Desert>("TORT", 250, FELIE));
        meniuProduse.push_back(std::make_shared<Desert>("STRUDEL", 100, PORTIE));

        std::vector<std::string> burger1 = {"paine", "carne", "cascaval"};
        std::vector<std::string> burger2 = {"paine", "carne", "cascaval", "rosie"};
        meniuProduse.push_back(std::make_shared<Burger>("BURGER LIGHT", 200, burger1));
        meniuProduse.push_back(std::make_shared<Burger>("BURGER FULL", 250, burger2));
    }

    void adaugaAngajat(const TipAngajat& tipAngajat) {
        if (tipAngajat == CASIER) { angajati.push_back(std::make_shared<Casier>()); }
        else if (tipAngajat == LIVRATOR) { angajati.push_back(std::make_shared<Livrator>()); }
        else if (tipAngajat == BUCATAR) { angajati.push_back(std::make_shared<Bucatar>()); }
        else std::cout << "Tip Angajat INVALID!\n";
    }

    std::shared_ptr<Produs> adaugaProdusInComanda(const ProdusMeniu& produsMeniu) {
        if (produsMeniu == COLA)            return meniuProduse[0];
        if (produsMeniu == FANTA)           return meniuProduse[1];
        if (produsMeniu == LIMONADA)        return meniuProduse[2];
        if (produsMeniu == INGHETATA)       return meniuProduse[3];
        if (produsMeniu == TORT)            return meniuProduse[4];
        if (produsMeniu == STRUDEL)         return meniuProduse[5];
        if (produsMeniu == BURGER_LIGHT)    return meniuProduse[6];
        if (produsMeniu == BURGER_FULL)     return meniuProduse[7];
        return nullptr;
    }

    void afiseazaNumarAnagajtiPeTip() {
        int casieri = 0, livratori = 0, bucatari = 0;

        for (const auto& angajat : angajati) {
            if (dynamic_cast<Casier*>(angajat.get())) casieri++;
            else if (dynamic_cast<Livrator*>(angajat.get())) livratori++;
            else if (dynamic_cast<Bucatar*>(angajat.get())) bucatari++;
        }

        std::cout << "Casier : " << casieri << std::endl;
        std::cout << "Livrator : " << livratori << std::endl;
        std::cout << "Bucatar : " << bucatari << std::endl;
    }

    void demoAdaugaAngajati() {
        adaugaAngajat(CASIER);
        adaugaAngajat(LIVRATOR);
        adaugaAngajat(BUCATAR);
        adaugaAngajat(CASIER);
        adaugaAngajat(LIVRATOR);
        adaugaAngajat(BUCATAR);
    }

    void demoAdaugareComanda() {
        auto tempComanda = std::make_shared<Comanda>();
        tempComanda->adaugaProdus(adaugaProdusInComanda(COLA));
        tempComanda->adaugaProdus(adaugaProdusInComanda(TORT));
        tempComanda->adaugaProdus(adaugaProdusInComanda(BURGER_LIGHT));
        comenzi.push_back(tempComanda);
    }

    void sorteazaComenzi() {
        sort(comenzi.begin(), comenzi.end(),
            [this](const std::shared_ptr<Comanda>& a, const std::shared_ptr<Comanda>& b) {
                if (a->esteComandaPrioritara() != b->esteComandaPrioritara()) return a->esteComandaPrioritara() > b->esteComandaPrioritara();
                if (strategie == GREU) return a->getEnergieTotala() > b->getEnergieTotala();
                if (strategie == USOR) return a->getEnergieTotala() < b->getEnergieTotala();
                return false; // FIFO
            });
    }

    void preluareComanda() {
        std::vector<std::shared_ptr<Angajat>> casieri;
        for (const auto& angajat : angajati) {
            if (dynamic_cast<Casier*>(angajat.get()) && angajat->getEnergie() >= angajat->costPreluare()) {
                casieri.push_back(angajat);
            }
        }

        int numarComanda = 0;
        for (const auto& casier : casieri ) {
            if (numarComanda < comenzi.size()) {
                casier->setEnergie(casier->getEnergie() - casier.get()->costPreluare());
                numarComanda++;
            }
        }

        for (const auto& angajat : angajati) {
            if (dynamic_cast<Casier*>(angajat.get()) == nullptr && numarComanda < comenzi.size() && angajat->getEnergie() >= angajat->costPreluare()) {
                angajat->setEnergie(angajat->getEnergie() - angajat.get()->costPreluare());
                numarComanda++;
            }
        }
    }

    void preparaComanda() {
        std::vector<std::shared_ptr<Angajat>> bucatari;
        for (const auto& angajat : angajati) {
            if (dynamic_cast<Bucatar*>(angajat.get())) {
                bucatari.push_back(angajat);
            }
        }

        int numarComanda = 0;
        for (const auto& bucatar : bucatari ) {
            if (numarComanda < comenzi.size()) {
                double energieConsumata = std::min(bucatar->getEnergie() * bucatar->eficientaPreparare(), comenzi[numarComanda]->getEnergieTotala());
                bucatar->setEnergie(bucatar->getEnergie() - energieConsumata);
                comenzi[numarComanda]->setEnergieTotala(comenzi[numarComanda]->getEnergieTotala() - energieConsumata);
                if (comenzi[numarComanda]->getEnergieTotala() <= 0) numarComanda++;
            }
        }

        for (const auto& angajat : angajati ) {
            if (dynamic_cast<Bucatar*>(angajat.get()) == nullptr && numarComanda < comenzi.size()) {
                double energieConsumata = std::min(angajat->getEnergie() * angajat->eficientaPreparare(), comenzi[numarComanda]->getEnergieTotala());
                angajat->setEnergie(angajat->getEnergie() - energieConsumata);
                comenzi[numarComanda]->setEnergieTotala(comenzi[numarComanda]->getEnergieTotala() - energieConsumata);
                if (comenzi[numarComanda]->getEnergieTotala() <= 0) numarComanda++;
            }
        }
    }

    void livrareComanda() {
        std::vector<std::shared_ptr<Angajat>> livratori;
        for (const auto& angajat : angajati) {
            if (dynamic_cast<Livrator*>(angajat.get()) && angajat->getEnergie() >= angajat->costLivrare()) {
                livratori.push_back(angajat);
            }
        }

        for (const auto& livrator : livratori ) {
            if (!comenzi.empty()) {
                livrator->setEnergie(livrator->getEnergie() - livrator.get()->costLivrare());
                comenzi.erase(comenzi.begin());
            }
        }

        for (const auto& angajat : angajati) {
            if (dynamic_cast<Livrator*>(angajat.get()) == nullptr && !comenzi.empty() && angajat->getEnergie() >= angajat->costLivrare()) {
                angajat->setEnergie(angajat->getEnergie() - angajat.get()->costLivrare());
                comenzi.erase(comenzi.begin());
            }
        }
    }

    void finalizareCiclu() {
        for (const auto& angajat : angajati) {
            angajat->finalCiclu();
        }
    }

    void ruleazaCiclu() {
        initializeazaMeniu();
        demoAdaugaAngajati();
        demoAdaugareComanda();
        sorteazaComenzi();
        preluareComanda();
        preparaComanda();
        livrareComanda();
        finalizareCiclu();
    }
};

Simulator* Simulator::instance = nullptr;

int main() {
    Simulator* simulator = Simulator::getInstance(FIFO);
    simulator->ruleazaCiclu();
    return 0;
}