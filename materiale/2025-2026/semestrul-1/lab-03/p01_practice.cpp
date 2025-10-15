/**
    Sa se implementeze un catalog universal pentru clasele de elevi dintr-o scoala.
    Catalogul va stoca 3 medii finale, de la materiile pe care elevii le studiaza.
    Elevii sunt identificati dupa numar matricol. Acestia au nume, prenume, clasa,
    dar si un field setat automat prin care se identifica ciclul de studii curent:
        - PRIMAR
        - GIMNAZIAL
        - LICEAL
    Sa se:
        - stocheze elevi in catalog
        - calculeze media finala a elevilor
        - filtreze elevii care apartin unui ciclu de studii dat
            - daca nu exista elevi la acel ciclu de studii, se va afisa un mesaj corespunzator
        - afiseze datele unui elev identificat prin numarul matricol
            - daca elevul nu exista, se va afisa un mesaj corespunzator
            - se va afisa si media finala
                - de asemenea, daca media este sub 5, se afiseaza mesajul CORIJENT
                - daca media este >= 5, se afiseaza mesajul PROMOVAT
*/

#include <iostream>
#include <map>
#include <vector>

enum CicluStudii {
    PRIMAR,
    GIMNAZIAL,
    LICEAL
};

const std::map<CicluStudii, std::string> CicluStudii_toString = {
    {PRIMAR, "Ciclu Primar"},
    {GIMNAZIAL, "Ciclu Gimnazial"},
    {LICEAL, "Ciclu Liceal"}
};

class Elev {
private:
    unsigned int numar_matricol{};
    std::string nume{};
    std::string prenume{};
    unsigned short clasa{};
    float medii[3]{};
    float medie_finala{};
    CicluStudii ciclu_studii{};

    static CicluStudii determina_ciclu_studii(const unsigned short clasa_) {
        if (clasa_ <= 4) return PRIMAR;
        if (clasa_ <= 8) return GIMNAZIAL;
        return LICEAL;
    }

public:
    Elev() = default;
    ~Elev() = default;
    Elev(unsigned int numar_matricol, const std::string& nume, const std::string& prenume, unsigned short clasa, const float medii[]) {
        this->numar_matricol = numar_matricol;
        this->nume = nume;
        this->prenume = prenume;
        this->clasa = clasa;
        for (int i = 0; i < 3; i++) {
            this->medii[i] = medii[i];
        }
        this->ciclu_studii = determina_ciclu_studii(clasa);
    }

    Elev(unsigned int numar_matricol, const std::string& nume, const std::string& prenume,
        unsigned short clasa, float medie1, float medie2, float medie3) {
        this->numar_matricol = numar_matricol;
        this->nume = nume;
        this->prenume = prenume;
        this->clasa = clasa;
        this->medii[0] = medie1;
        this->medii[1] = medie2;
        this->medii[2] = medie3;
        this->ciclu_studii = determina_ciclu_studii(clasa);
    }

    friend std::istream& operator>>(std::istream& is, Elev& elev) {
        std::cout << "Numar matricol: ";
        is >> elev.numar_matricol;
        std::cout << "Nume: ";
        is >> elev.nume;
        std::cout << "Prenume: ";
        is >> elev.prenume;
        std::cout << "Clasa: ";
        is >> elev.clasa;
        std::cout << "Medii: ";
        for (float& medie : elev.medii) {
            is >> medie;
        }
        elev.ciclu_studii = determina_ciclu_studii(elev.clasa);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Elev& elev) {
        os << "Numar matricol: " << elev.numar_matricol << "\n";
        os << "Nume si Prenume: " << elev.nume << " " << elev.prenume << "\n";
        os << "Clasa: " << elev.clasa << " - " << CicluStudii_toString.at(elev.ciclu_studii) << "\n";
        os << "Medii:\n";
        for (int i = 0; i < 3; i++) {
            os << "\tMedia " << (i + 1) << ": " << elev.medii[i] << "\n";
        }
        os << "Medie finala: " << elev.medie_finala << " - ";
        if (elev.medie_finala < 5) {
            os << "CORIJENT\n";
        } else {
            os << "PROMOVAT\n";
        }
        return os;
    }

    float calculeaza_medie_finala() {
        float res = 0;
        for (const float& medie : medii) {
            res += medie;
        }
        return res / 3.0f;
    }

    void set_medie_finala(const float medie_finala_) {
        this->medie_finala = medie_finala_;
    }

    [[nodiscard]] unsigned int get_numar_matricol() const {
        return numar_matricol;
    }

    [[nodiscard]] CicluStudii get_ciclu_studii() const {
        return ciclu_studii;
    }
};

class Catalog {
private:
    std::vector<Elev> elevi;

public:
    Catalog() = default;
    ~Catalog() = default;
    explicit Catalog(const std::vector<Elev>& elevi) {
        this->elevi = elevi;
    }

    friend std::istream& operator>>(std::istream& is, Catalog& catalog) {
        unsigned int nof_elevi;
        std::cout << "Numar de elevi: ";
        is >> nof_elevi;

        for (unsigned int i = 0; i < nof_elevi; i++) {
            Elev temp;
            std::cout << "Elev " << (i + 1) << "/" << nof_elevi << ":\n";
            is >> temp;
            catalog.elevi.push_back(temp);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Catalog& catalog) {
        os << "Numar total de elevi: " << catalog.elevi.size() << "\n";
        for (const Elev& elev : catalog.elevi) {
            os << elev;
            os << "-----------------------------------\n";
        }
        return os;
    }

    void adaugaElev(const Elev& elev) {
        this->elevi.push_back(elev);
    }

    void citesteElev() {
        Elev temp;
        std::cin >> temp;
        this->elevi.push_back(temp);
    }

    void calculeaza_medii_finale() {
        for (auto& elev : this->elevi) {
            elev.set_medie_finala(elev.calculeaza_medie_finala());
        }
    }

    void filtreaza_ciclu_studii(const CicluStudii& ciclu_studii) const {
        bool res = false;
        for (auto& elev : this->elevi) {
            if (elev.get_ciclu_studii() == ciclu_studii) {
                std::cout << elev;
                std::cout << "-----------------------------------\n";
                res = true;
            }
        }
        if (!res) {
            std::cout << "Niciun elev in ciclul de studii dat!\n";
        }
    }

    void cauta_elev(const unsigned int numar_matricol) const {
        for (auto& elev : this->elevi) {
            if (elev.get_numar_matricol() == numar_matricol) {
                std::cout << elev;
                return;
            }
        }
        std::cout << "Nu s-a gasit elevul cautat!\n";
    }
};

int main() {
    // Catalog c1;
    // std::cin >> c1;
    // c1.calculeaza_medii_finale();
    // std::cout << c1;

    std::cout << "\n===================================\n";
    
    Catalog c2;
    float medii_e21[3] = {9, 10, 7};
    const Elev e21(1, "Popescu", "Pop", 3, medii_e21);
    const Elev e22(2, "Ionescu", "Ion", 10, 3, 6, 2);
    c2.adaugaElev(e21);
    c2.adaugaElev(e22);
    c2.calculeaza_medii_finale();
    c2.filtreaza_ciclu_studii(PRIMAR);
    std::cout << "\n===================================\n";
    c2.filtreaza_ciclu_studii(GIMNAZIAL);
    std::cout << "\n===================================\n";
    c2.cauta_elev(2);
    std::cout << "\n===================================\n";
    c2.cauta_elev(3);
    return 0;
}