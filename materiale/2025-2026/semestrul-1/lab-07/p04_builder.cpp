#include <iostream>

class Pizza {
private:
    std::string blat;
    std::string sos;
    std::string topping;

public:
    Pizza()  = default;

    void setBlat(const std::string &blat) {
        this->blat = blat;
    }

    void setSos(const std::string &sos) {
        this->sos = sos;
    }

    void setTopping(const std::string &topping) {
        this->topping = topping;
    }

    void display() {
        std::cout << "Pizza cu blat " << blat << ", sos " << sos << " si topping " << topping << "\n";
    }
};

class PizzaBuilder {
protected:
    Pizza* pizza;

    virtual void buildBlat() = 0;
    virtual void buildSos() = 0;
    virtual void buildTopping() = 0;
public:
    PizzaBuilder() {
        pizza = new Pizza;
    }

    virtual void buildPizza() = 0;

    [[nodiscard]] Pizza * getPizza() const {
        return pizza;
    }
};

class MargheritaPizzaBuilder : public PizzaBuilder {
private:
    void buildBlat() override {
        pizza->setBlat("subtire");
    }

    void buildSos() override {
        pizza->setSos("dulce");
    }

    void buildTopping() override {
        pizza->setTopping("mozzarela");
    }

public:
    MargheritaPizzaBuilder() = default;

    void buildPizza() override {
        buildBlat();
        buildSos();
        buildTopping();
    }
};

class PepperoniPizzaBuilder : public PizzaBuilder {
private:
    void buildBlat() override {
        pizza->setBlat("italian");
    }

    void buildSos() override {
        pizza->setSos("picant");
    }

    void buildTopping() override {
        pizza->setTopping("pepperoni");
    }

public:
    PepperoniPizzaBuilder() = default;

    void buildPizza() override {
        buildBlat();
        // buildSos();
        buildTopping();
    }
};

class Director {
private:
    PizzaBuilder *pizzaBuilder;

public:
    Director() = default;

    void setPizzaBuilder(PizzaBuilder *pizzaBuilder) {
        this->pizzaBuilder = pizzaBuilder;
    }

    void buildPizza() {
        pizzaBuilder->buildPizza();
    }

    Pizza* getPizza() {
        return pizzaBuilder->getPizza();
    }
};

int main() {
    Director director;
    PizzaBuilder *pizzaBuilder = new MargheritaPizzaBuilder();
    director.setPizzaBuilder(pizzaBuilder);
    director.buildPizza();
    Pizza *pizza = director.getPizza();
    pizza->display();

    director.setPizzaBuilder(new PepperoniPizzaBuilder());
    director.buildPizza();
    pizza = director.getPizza();
    pizza->display();
    return 0;
}
