#include <iostream>

/*
 * Student
 *      - Licenta
 *          - Mate (3 ani, licentiat in mate)
 *          - Info (3 ani, licentiat in info)
 *          - CTI  (4 ani, inginer)
 *      - Master
 *          - Mate
 *          - Info
 *      - Doctorat
 */

class Student {
protected:
    unsigned int numarMatricol{};
    std::string nume;
    std::string prenume;
    unsigned int numarAniDeStudii{};

public:
    Student() = default;
    Student(const unsigned int numar_matricol, const std::string &nume, const std::string &prenume,
        const unsigned int numar_ani_de_studii)
        : numarMatricol(numar_matricol),
          nume(nume),
          prenume(prenume),
          numarAniDeStudii(numar_ani_de_studii) {
    }
    ~Student() = default;

    void displayInfo() {
        std::cout << "Numar matricol:" << numarMatricol << std::endl;
        std::cout << "Nume: " << nume << std::endl;
        std::cout << "Prenume: " << prenume << std::endl;
        std::cout << "Numar ani de studii: " << numarAniDeStudii << std::endl;
    }

    virtual void displayTipStudent() = 0;
};


class StudentLicenta : public Student {
protected:
    std::string tipDiploma;

public:
    StudentLicenta() = default;
    StudentLicenta(const unsigned int numar_matricol, const std::string &nume, const std::string &prenume,
        const unsigned int numar_ani_de_studii, const std::string& tipDiploma)
        : Student(numar_matricol, nume, prenume, numar_ani_de_studii),
          tipDiploma(tipDiploma) {
    };
    ~StudentLicenta() = default;

    void displayInfo() {
        Student::displayInfo();
        std::cout << "Tip diploma: " << tipDiploma << std::endl;
    }

    // void displayTipStudent() {
    //     std::cout << "Acesta este un student de la licenta!\n";
    // }

};

class StudentLicentaMate : public StudentLicenta {
private:
    std::string ramuraMatematica;

public:
    StudentLicentaMate() = default;
    StudentLicentaMate(const unsigned int numar_matricol, const std::string &nume, const std::string &prenume,
        const unsigned int numar_ani_de_studii, const std::string& tipDiploma, const std::string& ramuraMatematica)
        : StudentLicenta(numar_matricol, nume, prenume, numar_ani_de_studii, tipDiploma),
          ramuraMatematica(ramuraMatematica) {}
    ~StudentLicentaMate() = default;

    void displayInfo() {
        Student::displayInfo();
        std::cout << "Ramura matematica: " << ramuraMatematica << std::endl;
    }

    void displayTipStudent() {
        std::cout << "Acesta este un student de la licenta - matematica!\n";
    }

};

class StudentLicentaInfo : public StudentLicenta {
private:
    bool iiPlaceAI;

public:
    StudentLicentaInfo() = default;
    StudentLicentaInfo(const unsigned int numar_matricol, const std::string &nume, const std::string &prenume,
        const unsigned int numar_ani_de_studii, const std::string& tipDiploma, bool iiPlaceAI)
        : StudentLicenta(numar_matricol, nume, prenume, numar_ani_de_studii, tipDiploma),
          iiPlaceAI(iiPlaceAI) {}
    ~StudentLicentaInfo() = default;

    void displayInfo() {
        Student::displayInfo();
        std::cout << "Ii place AI?: " << iiPlaceAI << std::endl;
    }

    void displayTipStudent() {
        std::cout << "Acesta este un student de la licenta - informatica!\n";
    }
};

class StudentLicentaCTI : public StudentLicenta {
private:
    bool iiPlaceMagurele;
};

class StudentMaster {

};

class StudentDoctorat {

};


int main() {
    Student* mat = new StudentLicentaMate(101, "Popescu", "Pop", 3, "licentiat in matematica", "algebra");
    Student* inf = new StudentLicentaInfo(101, "Ion", "Ion", 3, "licentiat in info", true);
    // Student* s = new StudentLicenta;
    // mat.displayInfo();
    // std::cout << "======================\n";
    mat->displayTipStudent();
    std::cout << "======================\n";
    inf->displayTipStudent();
    return 0;
}