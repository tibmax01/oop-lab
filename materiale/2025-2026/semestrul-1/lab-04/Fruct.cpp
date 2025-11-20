//
// Created by Student on 10.11.2025.
//

#include "Fruct.hpp"

Fruct::Fruct(const std::string &nume, const std::string &culoare, int greutate, const std::string &textura) {
    this->nume = nume;
    this->culoare = culoare;
    this->greutate = greutate;
    this->textura = textura;
}

std::string Fruct::getNume() const {
    return nume;
}

std::string Fruct::getCuloare() const {
    return culoare;
}

int Fruct::getGreutate() const {
    return greutate;
}

std::string Fruct::getTextura() const {
    return textura;
}

void Fruct::setNume(const std::string &nume) {
    this->nume = nume;
}

void Fruct::setCuloare(const std::string &culoare) {
    this->culoare = culoare;
}

void Fruct::setGreutate(int greutate) {
    this->greutate = greutate;
}

void Fruct::setTextura(const std::string &textura) {
    this->textura = textura;
}


