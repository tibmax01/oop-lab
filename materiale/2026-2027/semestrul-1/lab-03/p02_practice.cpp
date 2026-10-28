#include <iostream>
//clasa pt valute, euro, lire, dolari
//conversie(EUR, RON, 100) -> 500 RON

enum class Valuta {
    EUR, RON, USD, GBP
};

class ConversieValutara {
    double rataEUR, rataUSD, rataGBP;
    const double rataRON = 1;
public:
    ConversieValutara() = default;
    ~ConversieValutara() = default;
    ConversieValutara(double rataEUR, double rataUSD, double rataGBP) {
        this->rataEUR = rataEUR;
        this->rataUSD = rataUSD;
        this->rataGBP = rataGBP;
    }
    friend std::ostream& operator<<(std::ostream& os, const ConversieValutara& obj) {
        os << "rataEUR: " << obj.rataEUR << std::endl;
        os << "rataUSD: " << obj.rataUSD << std::endl;
        os << "rataGBP: " << obj.rataGBP << std::endl;

        return os;
    }

    [[nodiscard]] double get_rata_eur() const {
        return rataEUR;
    }

    void set_rata_eur(const double rata_eur) {
        rataEUR = rata_eur;
    }

    [[nodiscard]] double get_rata_usd() const {
        return rataUSD;
    }

    void set_rata_usd(const double rata_usd) {
        rataUSD = rata_usd;
    }

    [[nodiscard]] double get_rata_gbp() const {
        return rataGBP;
    }

    void set_rata_gbp(const double rata_gbp) {
        rataGBP = rata_gbp;
    }

    double conversie(const Valuta &from, const Valuta &to, double amount) {
        if (from == to) {
            return amount;
        }
        if (from == Valuta::EUR) {
            switch (to) {
                case Valuta::RON: return amount * rataEUR / rataRON; break;
                case Valuta::USD: return amount * rataEUR / rataUSD; break;
                case Valuta::GBP: return amount * rataEUR / rataGBP; break;
                default: return -1; break;
            }
        }
        if (from == Valuta::USD) {
            switch (to) {
                case Valuta::RON: return amount * rataUSD / rataRON; break;
                case Valuta::EUR: return amount * rataUSD / rataEUR; break;
                case Valuta::GBP: return amount * rataUSD / rataGBP; break;
                default: return -1; break;

            }
        }
        if (from == Valuta::GBP) {
            switch (to) {
                case Valuta::RON: return amount * rataGBP / rataRON; break;
                case Valuta::EUR: return amount * rataGBP / rataEUR; break;
                case Valuta::USD: return amount * rataGBP / rataUSD; break;
                default: return -1; break;
            }
        }
        if (from == Valuta::RON) {
            switch (to) {
                case Valuta::EUR: return amount * rataRON / rataEUR; break;
                case Valuta::USD: return amount * rataRON / rataUSD; break;
                case Valuta::GBP: return amount * rataRON / rataGBP; break;
                default: return -1; break;
            }
        }
        return -1;
    }
};
int main() {
    ConversieValutara obj1(5.3, 4.6, 6);
    std::cout << obj1 << std::endl;
    std::cout << obj1.conversie(Valuta::EUR, Valuta::RON, 100) << std::endl;
    std::cout << obj1.conversie(Valuta::GBP, Valuta::EUR, 100) << std::endl;
    std::cout << obj1.conversie(Valuta::USD, Valuta::GBP, 100) << std::endl;
    return 0;
}