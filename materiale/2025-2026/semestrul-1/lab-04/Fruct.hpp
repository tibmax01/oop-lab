//
// Created by Student on 10.11.2025.
//

#ifndef FRUCT_HPP
#define FRUCT_HPP

#include <string>

class Fruct {
private:
    std::string nume;
    std::string culoare;
    int greutate;
    std::string textura;

public:
    Fruct() = default;
    ~Fruct() = default;
    Fruct(const std::string &nume, const std::string &culoare, int greutate, const std::string &textura);

    std::string getNume() const;
    std::string getCuloare() const;
    int getGreutate() const;
    std::string getTextura() const;

    void setNume(const std::string &nume);
    void setCuloare(const std::string &culoare);
    void setGreutate(int greutate);
    void setTextura(const std::string &textura);

    friend std::ostream &operator<<(std::ostream &os, const Fruct &fruct);
};


#endif //FRUCT_HPP
