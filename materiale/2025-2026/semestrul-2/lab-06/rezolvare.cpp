#include <iostream>
#include <utility>
#include <vector>

enum AgentFrigorific {
    R404a,
    R134a
};

enum Zi {
    LUNI = 1,
    MARTI,
    MIERCURI,
    JOI,
    VINERI,
    SAMBATA,
    DUMINICA
};

enum TipVehicul {
    AUTOUTILITARA,
    CAMION_FRIGORIFIC,
    DRONA
};

std::string tipToString(TipVehicul v) {
    switch (v) {
        case AUTOUTILITARA: return "Autoutilitara";
        case CAMION_FRIGORIFIC: return "Camion Frigorific";
        case DRONA: return "Drona";
        default: return "Necunoscut";
    }
}

std::string ziToString(Zi v) {
    switch (v) {
        case LUNI: return "LUNI";
        case MARTI: return "MARTI";
        case MIERCURI: return "MIERCURI";
        case JOI: return "JOI";
        case VINERI: return "VINERI";
        case SAMBATA: return "SAMBATA";
        case DUMINICA: return "DUMINICA";
        default: return "Necunoscut";
    }
}

std::string agentToString(AgentFrigorific v) {
    switch (v) {
        case R404a: return "R404a";
        case R134a: return "R134a";
        default: return "Necunoscut";
    }
}

class Vehicul {
protected:
    std::string nume;
    double pretAchizitie{};
    double vitezaMedie{};
    double parcursTotal{};
    std::vector<std::string> dotari;

public:
    Vehicul() = default;
    Vehicul(std::string  nume, double pretAchizitie, double vitezaMedie, const std::vector<std::string>& dotari)
        : nume(std::move(nume)), pretAchizitie(pretAchizitie), vitezaMedie(vitezaMedie), parcursTotal(0), dotari(dotari) {
    }

    virtual ~Vehicul() = default;

    [[nodiscard]] std::string get_nume() const {
        return nume;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vehicul& vehicul) {
        vehicul.afisare(os);
        return os;
    }

    [[nodiscard]] virtual TipVehicul getTip() const = 0;
    [[nodiscard]] virtual double calculeazaCost(double distantaTransport) const = 0;
    void adaugaParcurs(double distantaTransport) {
        parcursTotal += distantaTransport;
    }

    [[nodiscard]] virtual double consumMentenanta() const = 0;
    [[nodiscard]] virtual double limitaMentenanta() const = 0;

    [[nodiscard]] bool necesitaMentenanta() const {
        return consumMentenanta() > limitaMentenanta();
    }

    virtual void afisare(std::ostream& os) const {
        os << "Nume: " << nume << std::endl;
        os << "Tip: " << tipToString(getTip()) << std::endl;
        os << "Pret: " << pretAchizitie << std::endl;
        os << "Viteza: " << vitezaMedie << std::endl;
        for (const auto & i : dotari) {
            os << i << std::endl;
        }
    }
};

class Autoutilitara : public Vehicul {
protected:
    double volumMarfa{};
    double consum{};
    bool accesRezidential{};

public:
    Autoutilitara() = default;
    Autoutilitara(const std::string& nume, double pretAchizitie, double vitezaMedie, const std::vector<std::string>& dotari, double volumMarfa, double consum, bool accesRezidential)
        : Vehicul(nume, pretAchizitie, vitezaMedie, dotari), volumMarfa(volumMarfa), consum(consum), accesRezidential(accesRezidential) {}
    ~Autoutilitara() override = default;

    [[nodiscard]] TipVehicul getTip() const override {
        return AUTOUTILITARA;
    }

    [[nodiscard]] double calculeazaCost(double distantaTransport) const override {
        return distantaTransport * consum * 7.5;
    }

    [[nodiscard]] double limitaMentenanta() const override {
        return 15000;
    }

    [[nodiscard]] double consumMentenanta() const override {
        return parcursTotal;
    }

    void afisare(std::ostream& os) const override {
        Vehicul::afisare(os);
        os << "Volum: " << volumMarfa << std::endl;
        os << "Consum: " << consum << std::endl;
        os << "AccesRezidential: " << accesRezidential << std::endl;
    }
};

class CamionFrigorific : public Autoutilitara {
private:
    double temperaturaMinima{};
    AgentFrigorific agentFrigorific{};

public:
    CamionFrigorific() = default;
    CamionFrigorific(const std::string& nume, double pretAchizitie, double vitezaMedie, const std::vector<std::string>& dotari, double volumMarfa, double consum, bool accesRezidential,
        double temperaturaMinima, AgentFrigorific agentFrigorific) : Autoutilitara(nume, pretAchizitie, vitezaMedie, dotari, volumMarfa, consum, accesRezidential),
        temperaturaMinima(temperaturaMinima), agentFrigorific(agentFrigorific) {}
    ~CamionFrigorific() override = default;

    [[nodiscard]] TipVehicul getTip() const override {
        return CAMION_FRIGORIFIC;
    }

    [[nodiscard]] double calculeazaCost(double distantaTransport) const override {
        return distantaTransport * consum * 1.2 * 7.5;
    }

    [[nodiscard]] double limitaMentenanta() const override {
        return 10000;
    }

    void afisare(std::ostream& os) const override {
        Autoutilitara::afisare(os);
        os << "Temperatura: " << temperaturaMinima << std::endl;
        os << "AgentFrigorific: " << agentToString(agentFrigorific) << std::endl;
    }
};

class Drona : public Vehicul {
private:
    double autonomieBaterie{};
    int numarElice{};
    double greutateMaxima{};

public:
    Drona() = default;
    Drona(const std::string& nume, double pretAchizitie, double vitezaMedie, const std::vector<std::string>& dotari, double autonomieBaterie, int numarElice, double greutateMaxima)
        : Vehicul(nume, pretAchizitie, vitezaMedie, dotari), autonomieBaterie(autonomieBaterie), numarElice(numarElice), greutateMaxima(greutateMaxima) {
        if (greutateMaxima > 5) {
            greutateMaxima = 5;
        }
    }

    [[nodiscard]] double get_greutate_maxima() const {
        return greutateMaxima;
    }

    [[nodiscard]] double calculeazaCost(double distantaTransport) const override {
        return distantaTransport  * 2.0 + 15;
    }

    [[nodiscard]] double limitaMentenanta() const override {
        return 100;
    }

    [[nodiscard]] double consumMentenanta() const override {
        return parcursTotal / vitezaMedie;
    }

    [[nodiscard]] TipVehicul getTip() const override {
        return DRONA;
    }

    void afisare(std::ostream& os) const override {
        Vehicul::afisare(os);
        os << "Autonomie: " << autonomieBaterie << std::endl;
        os << "NumarElice: " << numarElice << std::endl;
        os << "GreutateMaxima: " << greutateMaxima << std::endl;
    }

};

class Comanda {
private:
    static int static_id;
    int id{};
    Zi ziLivrare{};
    std::string numeClient;
    double greutateTransport{};
    Vehicul* vehicul{};
    double distanta{};

public:
    Comanda() = default;
    Comanda(Zi zi, std::string numeClient, double greutateTransport, Vehicul* vehicul, double distanta)
        : id(static_id++), ziLivrare(zi), numeClient(std::move(numeClient)), greutateTransport(greutateTransport), vehicul(vehicul), distanta(distanta) {}

    void afisare() const {
        std::cout << "Comanda: " << id << std::endl;
        std::cout << "Zi Livrare: " << ziToString(ziLivrare) << std::endl;
        std::cout << "Nume Client: " << numeClient << std::endl;
        std::cout << "GreutateTransport: " << greutateTransport << std::endl;
        std::cout << "Distanta: " << distanta << std::endl;
        std::cout << "-----------------------\nVehicul:\n";
        vehicul->afisare(std::cout);
        std::cout << "-----------------------\n";
    }

    [[nodiscard]] Zi get_zi_livrare() const {
        return ziLivrare;
    }

    [[nodiscard]] int get_id() const {
        return id;
    }

    [[nodiscard]] double get_greutate_transport() const {
        return greutateTransport;
    }

    [[nodiscard]] Vehicul * get_vehicul() const {
        return vehicul;
    }

    void set_vehicul(Vehicul* vehicul) {
        this->vehicul = vehicul;
    }

    [[nodiscard]] bool esteComandaValida() const {
        double valoareComanda = getValoare();
        if (ziLivrare >= LUNI && ziLivrare <= VINERI) return valoareComanda >= 200;
        return valoareComanda >= 500;
    }

    [[nodiscard]] double getValoare() const {
        if (vehicul == nullptr) return 0;
        return vehicul->calculeazaCost(distanta);
    }
};

class SistemLogistic {
private:
    std::vector<Vehicul*> vehicule;
    std::vector<Comanda> comenzi;

public:
    SistemLogistic() = default;
    ~SistemLogistic() {
        for (auto & vehicul: vehicule) {
            delete vehicul;
        }
    }

    void adaugaVehicul(Vehicul* vehicul) {
        vehicule.push_back(vehicul);
    }

    static bool esteTransportValid(Vehicul* vehicul, double greutateTransport) {
        if (vehicul == nullptr) return false;
        auto *d = dynamic_cast<Drona*>(vehicul);
        if (d != nullptr) {
            return greutateTransport <= d->get_greutate_maxima();
        }
        return true;
    }

    void adaugaComanda(Zi zi, const std::string& numeClient, double greutateTransport, Vehicul* vehicul, double distanta) {
        if (!esteTransportValid(vehicul, greutateTransport)) {
            std::cout << "Comanda respinsa: greutatea depaseste greutatea maxima admisa.\n";
            return;
        }

        Comanda comanda(zi, numeClient, greutateTransport, vehicul, distanta);
        comenzi.push_back(comanda);

        vehicul->adaugaParcurs(distanta);
    }

    void afisareComenzi() const {
        for (const auto & comanda : comenzi) {
            comanda.afisare();
        }
    }

    void afisareComenziValide() const {
        for (const auto & comanda : comenzi) {
            if (comanda.esteComandaValida()) {
                comanda.afisare();
                std::cout << "**********************************************\n";
            }
        }
    }

    void afiseazaVehicule() const {
        for (auto vehicul : vehicule) {
            vehicul->afisare(std::cout);
            std::cout << "\n-------------------------\n";
        }
    }

    void filtreazaVehiculeDupaTip(TipVehicul tip) const {
        std::cout << "--- Filtrare: " << tipToString(tip) << " ---\n";
        for (auto vehicul : vehicule) {
            bool ok = false;
            if (tip == AUTOUTILITARA) {
                const auto *a = dynamic_cast<Autoutilitara*>(vehicul);
                const auto *c = dynamic_cast<CamionFrigorific*>(vehicul);
                if (a != nullptr && c == nullptr) {
                    ok = true;
                }
            } else if (tip == CAMION_FRIGORIFIC) {
                const auto *c = dynamic_cast<CamionFrigorific*>(vehicul);
                if (c != nullptr) {
                    ok = true;
                }
            } else if (tip == DRONA) {
                const auto *d = dynamic_cast<Drona*>(vehicul);
                if (d != nullptr) {
                    ok = true;
                }
            }
            if (ok) {
                vehicul->afisare(std::cout);
                std::cout << "\n-------------------------\n";
            }
        }
    }

    [[nodiscard]] double totalComenziDupaZi(Zi zi) const {
        std::cout << "Comenzile de " << ziToString(zi) << "\n";
        double total = 0;
        for (const auto & comanda : comenzi) {
            if (comanda.get_zi_livrare() == zi && comanda.esteComandaValida()) {
                total += comanda.getValoare();
            }
        }
        return total;
    }

    Vehicul* cautaAlternativa(const Vehicul* vehiculExclus, double greutate) const {
        for (auto vehicul : vehicule) {
            if (vehicul != vehiculExclus && !vehicul->necesitaMentenanta() && esteTransportValid(vehicul, greutate)) {
                return vehicul;
            }
        }
        return nullptr;
    }

    void statusMentenanta() {
        for (auto & vehicul : vehicule) {
            if (vehicul->necesitaMentenanta()) {
                int totalComenziAfectate = 0;
                std::cout << "LIMITA DEPASITA pentru vehiculul " << vehicul->get_nume() << "\n";

                for (auto & comanda : comenzi) {
                    if (comanda.get_vehicul() == vehicul) {
                        totalComenziAfectate++;

                        Vehicul *alternativa = cautaAlternativa(vehicul, comanda.get_greutate_transport());
                        if (alternativa != nullptr) {
                            std::cout << "Comanda " << comanda.get_id() << " va fi livrata de " << alternativa->get_nume()
                            << " in loc de " << vehicul->get_nume() << "\n";
                            comanda.set_vehicul(alternativa);
                        } else {
                            std::cout << "Comanda " << comanda.get_id() << " nu poate fi livrata de " << vehicul->get_nume() << "\n";
                        }
                    }
                }

                std::cout << "Numar comenzi afectate: " << totalComenziAfectate << "\n";
                std::cout << "----------------------------------\n";
            }
        }
    }
};

int Comanda::static_id = 0;

int main() {
    SistemLogistic sistem;

    Vehicul* v1 = new Autoutilitara("V1", 120000, 70, std::vector<std::string>{"GPS", "clima"}, 12, 9, true);
    Vehicul* v2 = new CamionFrigorific("V2", 200000, 65, std::vector<std::string>{"GPS"}, 10, 11, false, -18, R404a);
    Vehicul* v3 = new Drona("V3", 15000, 50, std::vector<std::string>{"GPS"}, 3, 4, 5);

    sistem.adaugaVehicul(v1);
    sistem.adaugaVehicul(v2);
    sistem.adaugaVehicul(v3);

    std::cout << "=======================\n";
    std::cout << "AFISARE VEHICULE\n";
    std::cout << "=======================\n";
    sistem.afiseazaVehicule();

    std::cout << "=======================\n";
    std::cout << "FILTRARE VEHICULE\n";
    std::cout << "=======================\n";
    sistem.filtreazaVehiculeDupaTip(AUTOUTILITARA);
    sistem.filtreazaVehiculeDupaTip(CAMION_FRIGORIFIC);
    sistem.filtreazaVehiculeDupaTip(DRONA);

    std::cout << "=======================\n";
    std::cout << "ADAUGARE COMENZI\n";
    std::cout << "=======================\n";
    sistem.adaugaComanda(LUNI, "Ionescu Ion", 50, v1, 20000);
    sistem.adaugaComanda(MARTI, "Mihai Mihai", 10, v2, 150);
    sistem.adaugaComanda(SAMBATA, "Bob Bob", 4, v3, 3);

    std::cout << "=======================\n";
    std::cout << "AFISARE COMENZI\n";
    std::cout << "=======================\n";
    sistem.afisareComenzi();

    std::cout << "=======================\n";
    std::cout << "AFISARE COMENZI VALIDE\n";
    std::cout << "=======================\n";
    sistem.afisareComenziValide();

    std::cout << "=======================\n";
    std::cout << "AFISARE TOTAL PE ZI\n";
    std::cout << "=======================\n";
    std::cout << sistem.totalComenziDupaZi(LUNI) << std::endl;
    std::cout << sistem.totalComenziDupaZi(MARTI) << std::endl;
    std::cout << sistem.totalComenziDupaZi(JOI) << std::endl;
    std::cout << sistem.totalComenziDupaZi(SAMBATA) << std::endl;

    std::cout << "=======================\n";
    std::cout << "STATUS MENTENANTA \n";
    std::cout << "=======================\n";
    sistem.statusMentenanta();

    delete v1;
    delete v2;
    delete v3;

    return 0;
}