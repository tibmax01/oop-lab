#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Element {
protected:
    static int nextId;
    const int id;

public:
    Element() : id(++nextId) {}
    virtual ~Element() = default;

    [[nodiscard]] virtual double costUpgrade() const = 0;
    virtual void upgrade() = 0;

    virtual void print(std::ostream& os) const {
        os << "Element(" << id << ")\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Element& element) {
        element.print(os);
        return os;
    }

    [[nodiscard]] int getId() const {
        return id;
    }
};

int Element::nextId = 0;

class Zid final : public Element {
private:
    double latime;
    double lungime;
    double grosime;

public:
    Zid() : latime(1), lungime(1), grosime(0.5) {}

    [[nodiscard]] double costUpgrade() const override {
        return 100 * latime * lungime * grosime;
    }

    void upgrade() override {
        latime  += 1;
        lungime += 1;
        grosime += 1;
    }

    void print(std::ostream& os) const override {
        os << "ZID\n";
        Element::print(os);
        os << "latime: " << latime << "\n";
        os << "lungime: " << lungime << "\n";
        os << "grosime: " << grosime << "\n";
    }
};

class Turn final : public Element {
private:
    int putereLaser;

public:
    Turn() : putereLaser(1000) {}

    [[nodiscard]] double costUpgrade() const override {
        return 500 * putereLaser;
    }

    void upgrade() override {
        putereLaser += 500;
    }

    void print(std::ostream& os) const override {
        os << "TURN\n";
        Element::print(os);
        os << "putereLaser: " << putereLaser << "\n";
    }
};

class Robot : public Element {
protected:
    int damage;
    int lvl;
    int viata;

public:
    Robot() : damage(100), lvl(1), viata(100) {}

    [[nodiscard]] double costUpgrade() const override = 0;
    void upgrade() override = 0;

    void print(std::ostream& os) const override {
        os << "ROBOT\n";
        Element::print(os);
        os << "damage: " << damage << "\n";
        os << "lvl: " << lvl << "\n";
        os << "viata: " << viata << "\n";
    }
};

class RobotAerian final : public Robot {
private:
    int autonomieZbor;

public:
    RobotAerian() : autonomieZbor(10) {}

    [[nodiscard]] double costUpgrade() const override {
        return 50 * autonomieZbor;
    }

    void upgrade() override {
        autonomieZbor   += 1;
        lvl             += 1;
        damage          += 25;
    }

    void print(std::ostream& os) const override {
        os << "ROBOT AERIAN\n";
        Robot::print(os);
        os << "autonomieZbor: " << autonomieZbor << "\n";
    }
};

class RobotTerestru final : public Robot {
private:
    int numarGloante;
    bool areScut;

public:
    RobotTerestru() : numarGloante(500), areScut(false) {}

    [[nodiscard]] double costUpgrade() const override {
        return 10 * numarGloante;
    }

    void upgrade() override {
        numarGloante    += 100;
        lvl             += 1;
        damage          += 50;

        if (lvl == 5) {
            areScut = true;
            viata   += 50;
        }
    }

    void print(std::ostream& os) const override {
        os << "ROBOT TERESTRU\n";
        Robot::print(os);
        os << "numarGloante: " << numarGloante;
        os << "areScut: " << areScut;
    }
};

enum TipElement {
    ZID             = 1,
    TURN            = 2,
    ROBOT_AERIAN    = 3,
    ROBOT_TERESTRU  = 4
};

class PuncteInsuficiente final : std::exception {
private:
    int numarCurentPuncte;
    int numarMinimPuncte;

public:
    PuncteInsuficiente(int numarCurentPuncte, int numarMinimPuncte)
        : numarCurentPuncte(numarCurentPuncte), numarMinimPuncte(numarMinimPuncte) {}

    [[nodiscard]] const char* what() const noexcept override {
        return ("Puncte Insuficiente - este nevoie de un numar de " + std::to_string(numarMinimPuncte)
            + " puncte. Disponibil doar " + std::to_string(numarCurentPuncte) + " puncte.\n").c_str();
    }
};

class TipInvalid : std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Acest tip de element este invalid!\n";
    }
};

class OptiuneInvalida : std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Aceasta optiune este invalida!\n";
    }
};

class ElementInexistent : std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Element inexistent!\n";
    }
};

bool comp(const std::shared_ptr<Element>& a, const std::shared_ptr<Element>& b) {
    return a->costUpgrade() > b->costUpgrade();
}

class Inventar {
private:
    int puncte;
    std::vector<std::shared_ptr<Element>> elemente;

    static Inventar* instance;

    Inventar() : puncte(50000) {}
public:
    Inventar(const Inventar&)            = delete;
    Inventar& operator=(const Inventar&) = delete;

    static Inventar* getInstance() {
        if (instance == nullptr) {
            instance = new Inventar();
        }
        return instance;
    }

    void adaugaElement(const TipElement& tipElement) {
        if (tipElement == ZID) {
            if (puncte >= 300) {
                puncte -= 300;
                elemente.push_back(std::make_shared<Zid>());
            } else throw PuncteInsuficiente(puncte, 300);
        } else if (tipElement == TURN) {
            if (puncte >= 500) {
                puncte -= 500;
                elemente.push_back(std::make_shared<Turn>());
            } else throw PuncteInsuficiente(puncte, 500);
        } else if (tipElement == ROBOT_AERIAN) {
            if (puncte >= 100) {
                puncte -= 100;
                elemente.push_back(std::make_shared<RobotAerian>());
            } else throw PuncteInsuficiente(puncte, 100);
        } else if (tipElement == ROBOT_TERESTRU) {
            if (puncte >= 50) {
                puncte -= 50;
                elemente.push_back(std::make_shared<RobotTerestru>());
            } else throw PuncteInsuficiente(puncte, 50);
        } else throw TipInvalid();
    }

    void upgradeElement(const int id) {
        Element* tempElement = nullptr;
        for (const auto& element : elemente) {
            if (element->getId() == id) {
                tempElement = element.get();
                break;
            }
        }

        if (tempElement == nullptr) throw ElementInexistent();

        const double cost = tempElement->costUpgrade();
        if (puncte < cost) throw PuncteInsuficiente(puncte, static_cast<int>(cost));

        puncte -= static_cast<int>(cost);
        tempElement->upgrade();
    }

    void vindeElement(const int id) {
        for (auto it = elemente.begin(); it != elemente.end(); ++it) {
            if ((*it)->getId() == id) {
                elemente.erase(it);
                puncte += 500;
                std::cout << "S-a vandut elementul cu id: " << id << "\n";
                return;
            }
        }
        throw ElementInexistent();
    }

    void afisareDupaCostUpgrade() const {
        std::vector<std::shared_ptr<Element>> tempElemente = elemente;
        std::sort(tempElemente.begin(), tempElemente.end(), comp);

        std::cout << "Numar puncte: " << puncte << "\n";
        for (const auto& element : tempElemente) {
            std::cout << *element << "\n";
            std::cout << "COST UPGRADE: " << element->costUpgrade() << "\n\n\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    void afisareDupaCostUpgradeV2() const {
        std::vector<std::shared_ptr<Element>> tempElemente = elemente;
        std::sort(tempElemente.begin(), tempElemente.end(), [](const std::shared_ptr<Element>& a, const std::shared_ptr<Element>& b) -> bool {
            return a->costUpgrade() > b->costUpgrade();
        });

        std::cout << "Numar puncte: " << puncte << "\n";
        for (const auto& element : tempElemente) {
            std::cout << *element << "\n";
            std::cout << "COST UPGRADE: " << element->costUpgrade() << "\n\n\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    struct ComparatorCostUpgrade {
        bool operator()(const std::shared_ptr<Element>& a, const std::shared_ptr<Element>& b) const {
            return a->costUpgrade() > b->costUpgrade();
        }
    };

    void afisareDupaCostUpgradeV3() const {
        std::vector<std::shared_ptr<Element>> tempElemente = elemente;
        std::sort(tempElemente.begin(), tempElemente.end(), ComparatorCostUpgrade());

        std::cout << "Numar puncte: " << puncte << "\n";
        for (const auto& element : tempElemente) {
            std::cout << *element << "\n";
            std::cout << "COST UPGRADE: " << element->costUpgrade() << "\n\n\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    void afisareDupaCostUpgradeV4() const {
        std::vector<std::shared_ptr<Element>> tempElemente = elemente;
        std::ranges::sort(tempElemente, ComparatorCostUpgrade());

        std::cout << "Numar puncte: " << puncte << "\n";
        for (const auto& element : tempElemente) {
            std::cout << *element << "\n";
            std::cout << "COST UPGRADE: " << element->costUpgrade() << "\n\n\n";
        }
        std::cout << "--------------------------------------------\n";
    }

    void afiseazaRoboti() const {
        std::cout << "Robotii din inventar sunt: \n";
        for (const auto& element : elemente) {
            if (dynamic_cast<RobotAerian*>(element.get()) || dynamic_cast<RobotTerestru*>(element.get())) {
                std::cout << *element << "\n";
            }
        }
        std::cout << "--------------------------------------------\n";
    }

    void afiseazaInventar() const {
        std::cout << "Numar puncte: " << puncte << "\n";
        for (const auto& element : elemente) {
            std::cout << *element << "\n";
            std::cout << "COST UPGRADE: " << element->costUpgrade() << "\n\n\n";
        }
        std::cout << "--------------------------------------------\n";
    }
};

Inventar* Inventar::instance = nullptr;

int main() {
    try {
        Inventar* inventar = Inventar::getInstance();
        int optiune, tip, id;
        do {
            std::cout << "Selecteaza o optiune:\n";
            std::cout << "1. Adaugare Element\n";
            std::cout << "2. Upgrade Element\n";
            std::cout << "3. Afisare Dupa Cost Upgrade\n";
            std::cout << "4. Afisare Roboti\n";
            std::cout << "5. Vinde Element\n";
            std::cout << "6. Afisare Inventar\n";
            std::cout << "0. Iesire\n";

            std::cin >> optiune;

            switch (optiune) {
                case 1: {
                    std::cout << "Selecteaza Tip Element - 1 (ZID), 2 (TURN), 3 (ROBOT AERIAN), 4 (ROBOT TERESTRU): ";
                    std::cin >> tip;
                    inventar->adaugaElement(static_cast<TipElement>(tip));
                    break;
                }
                case 2: {
                    std::cout << "Citeste ID: ";
                    std::cin >> id;
                    inventar->upgradeElement(id);
                    break;
                }
                case 3: inventar->afisareDupaCostUpgrade(); break;
                case 4: inventar->afiseazaRoboti(); break;
                case 5: {
                    std::cout << "Citeste ID: ";
                    std::cin >> id;
                    inventar->vindeElement(id);
                    break;
                }
                case 6: inventar->afiseazaInventar(); break;
                case 0: break;
                default: throw OptiuneInvalida();
            }
        } while (optiune != 0);
    } catch (const PuncteInsuficiente& e) {
        std::cout << e.what() << "\n";
    } catch (const TipInvalid& e) {
        std::cout << e.what() << "\n";
    } catch (const ElementInexistent& e) {
        std::cout << e.what() << "\n";
    } catch (...) {
        std::cout << "Eroare necunoscuta!\n";
    }

    return 0;
}