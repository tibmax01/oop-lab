#include <iostream>
#include <vector>

class Cerc;
class Patrat;

class Visitor {
public:
    virtual void visit(Patrat* patrat) = 0;
    virtual void visit(Cerc* cerc) = 0;
    virtual ~Visitor() = default;
};

class Forma {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Forma() = default;
};

class Cerc : public Forma {
public:
    float raza;
    Cerc(float raza) : raza(raza) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

class Patrat : public Forma {
public:
    float latura;
    Patrat(float latura) : latura(latura) {}
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

class VisitorArie : public Visitor {
public:
    void visit(Cerc* cerc) override {
        float arie = 3.14f * cerc->raza * cerc->raza;
        std::cout << "Aria cercului: " << arie << std::endl;
    }

    void visit(Patrat *patrat) override {
        float arie = patrat->latura * patrat->latura;
        std::cout << "Aria patratului: " << arie << std::endl;
    }
};

class VisitorPerimetru : public Visitor {
    void visit(Cerc* cerc) override {
        float perimetru = 2 * 3.14f * cerc->raza;
        std::cout << "Perimetrul cercului: " << perimetru << std::endl;
    }

    void visit(Patrat *patrat) override {
        float perimetru = 4 * patrat->latura;
        std::cout << "Perimetrul patratului: " << perimetru << std::endl;
    }
};

int main()
{
    std::vector<Forma*> forme;
    forme.push_back(new Cerc(5.0f));
    forme.push_back(new Patrat(3.0f));

    VisitorArie visitorArie;
    VisitorPerimetru visitorPerimetru;

    std::cout << "CALCUL ARII -------------\n";
    for (Forma* forma : forme) {
        forma->accept(&visitorArie);
    }

    std::cout << "CALCUL PERIMETRE -------------\n";
    for (Forma* forma : forme) {
        forma->accept(&visitorPerimetru);
    }

    for (Forma* forma : forme) {
        delete forma;
    }
    return 0;
}
