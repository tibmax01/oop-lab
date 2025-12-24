#include <iostream>
#include <string>
#include <algorithm>

class InterfataCompatibila {
public:
    virtual ~InterfataCompatibila() = default;

    virtual std::string display() {
        return "InterfataCompatibila: Acesta este un mesaj compatibil.\n";
    }
};

class InterfartaIncompatibila {
public:
    virtual std::string displayIncompatibil() {
        return ".libitapmocni jasem nu etse atsecA :alibitapmocnIatafretnI\n";
    }
};

class Adapter : public InterfataCompatibila {
private:
    InterfartaIncompatibila *interfartaIncompatibila;

public:
    Adapter(InterfartaIncompatibila *interfartaIncompatibila) : interfartaIncompatibila(interfartaIncompatibila) {}

    std::string display() override {
        std::string message = interfartaIncompatibila->displayIncompatibil();
        std::reverse(message.begin(), message.end());
        return "ADAPTER: " + message;
    }
};


int main() {
    InterfataCompatibila *interfataCompatibila = new InterfataCompatibila();
    std::cout << interfataCompatibila->display();

    InterfartaIncompatibila *interfartaIncompatibila = new InterfartaIncompatibila();
    std::cout << interfartaIncompatibila->displayIncompatibil();

    Adapter *adapter = new Adapter(interfartaIncompatibila);
    std::cout << adapter->display();
    return 0;
}
