#include <iostream>

enum PizzaType {
    MARGHERITA,
    PEPPERONI
};

class Pizza {
public:
    Pizza() = default;

    virtual void display() = 0;
};

class MargheritaPizza : public Pizza {
public:
    MargheritaPizza() = default;

    void display() override {
        std::cout << "Pizza Margherita" << std::endl;
    }
};

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza() = default;

    void display() override {
        std::cout << "Pepperoni Pizza" << std::endl;
    }
};

class PizzaFactory {
public:
    PizzaFactory() = default;

    Pizza* createPizza(const PizzaType& type) {
        if (type == PizzaType::MARGHERITA) {
            return new MargheritaPizza;
        } else if (type == PizzaType::PEPPERONI) {
            return new PepperoniPizza;
        }
        return nullptr;
    }
};

int main() {
    PizzaFactory pizzaFactory;// = new PizzaFactory();
    Pizza* pizza;
    pizza = pizzaFactory.createPizza(MARGHERITA);
    pizza->display();

    pizza = pizzaFactory.createPizza(PEPPERONI);
    pizza->display();
    return 0;
}
