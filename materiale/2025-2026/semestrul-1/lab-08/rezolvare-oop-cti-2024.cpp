#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Proba{
protected:
    double metrica;
public:
    virtual ~Proba() = default;
    double getMetrica()
    {
        return metrica;
    }
    virtual void calculMetrica() = 0;
    virtual void afisare(ostream& os) const{
        os<<metrica<<'\n';
    }
    virtual void citire(istream& is) = 0;
    friend ostream& operator <<(ostream& os, const Proba& proba){
        proba.afisare(os);
        return os;
    }

    friend istream& operator >>(istream& is, Proba& proba){
        proba.citire(is);
        return is;
    }

};

class Sprint: public Proba{
private:
    double timp;
public:
    Sprint() = default;
    Sprint(double timp) : timp(timp){}
    void calculMetrica() override{
        if(timp < 10)
            metrica = 10;
        else metrica=90/timp;
    }
    void afisare(ostream& os) const override{
        Proba::afisare(os);
        os<<timp<<'\n';
    }
    void citire(istream& is) override{
        is>>timp;
    }
};

class Cros: public Proba{
private:
    double timp;
public:
    Cros() = default;
    Cros(double timp) : timp(timp){}
    void calculMetrica() override{
        if(timp < 30)
            metrica = 10;
        else metrica=120/timp;
    }
    void afisare(ostream& os) const override{
        Proba::afisare(os);
        os<<timp<<'\n';
    }
    void citire(istream& is) override{
        is>>timp;
    }
};

class Maraton: public Proba{
private:
    double distanta;
    bool esteSemiMaraton;
public:
    Maraton() = default;
    Maraton(double distanta, bool esteSemiMaraton) :
        distanta(distanta), esteSemiMaraton(esteSemiMaraton){}
    void calculMetrica() override{
        if(distanta > 50)
            metrica = 10;
        else metrica=distanta/5;
    }
    void afisare(ostream& os) const override{
        Proba::afisare(os);
        os<<distanta<<'\n'<<esteSemiMaraton<<'\n';
    }
    void citire(istream& is) override{
        is>>distanta>>esteSemiMaraton;
    }
};

class Candidat{
private:
    string nume;
    string prenume;
    string dataNasterii;
    Proba *proba;
public:
    Candidat() = default;
    Candidat(string nume, string prenume, string dataNasterii):
        nume(nume), prenume(prenume), dataNasterii(dataNasterii){}
    ~Candidat(){
        delete proba;
    }

    Proba* getProba(){
        return proba;
    }

    friend ostream& operator <<(ostream& os, const Candidat& candidat){
        os<<candidat.nume<<' '<<
        candidat.prenume<<' '<<
        candidat.dataNasterii<<'\n';

        candidat.proba->afisare(os);
        return os;
    }

    friend istream& operator >>(istream& is, Candidat& candidat){
        int tipProba;
        is>>candidat.nume>> candidat.prenume
        >>candidat.dataNasterii;

        is>>tipProba;
        if(tipProba == 1)
            candidat.proba = new Sprint();
        else if(tipProba == 2)
            candidat.proba = new Cros();
        else if(tipProba == 3)
            candidat.proba = new Maraton();
        candidat.proba->citire(is);
        return is;
    }
};

int descComp(Candidat* a, Candidat* b){
    return a->getProba()->getMetrica() > b->getProba()->getMetrica();
}

int main()
{
    int nrCandidati;
    vector<Candidat*> candidati;
    cin>>nrCandidati;
    for(int i = 0; i < nrCandidati; i++){
        Candidat *c = new Candidat();
        cin>>*c;
        c->getProba()->calculMetrica();
        candidati.push_back(c);
    }
    sort(candidati.begin(), candidati.end(), descComp);
    for(int i = 0; i < nrCandidati; i++){
        cout<<*(candidati[i])<<'\n'<<"---------------------------- \n";
    }

    return 0;
}
