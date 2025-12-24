#include <iostream>
#include <list>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

class MySubject : public Subject {
private:
    std::list<Observer*> observers;
    std::string message;

public:
    virtual ~MySubject() {
        std::cout << "DESTRUCTOR - MySubject\n";
    }

    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.remove(observer);
    }

    void notify() {
        std::list<Observer*>::iterator it = observers.begin();
        getNOFObservers();
        while (it != observers.end()) {
            (*it)->update(message);
            ++it;
        }
    }

    void createMessage(const std::string& message) {
        this->message = message;
        notify();
    }

    void dummyLogic() {
        this->message = "Dummy Message";
        notify();
    }

    void getNOFObservers() {
        std::cout << "NOF Observers: " << observers.size() << "\n";
    }
};

class MyObserver : public Observer {
private:
    std::string message;
    Subject& subject;
    static int static_id;
    int id;

public:
    MyObserver(Subject& subject) : subject(subject) {
        this->subject.attach(this);
        std::cout << "CONSTRUCTOR - MyObserver " << ++static_id << "\n";
        this->id = static_id;
    }

    virtual ~MyObserver() {
        std::cout << "DESTRUCTOR - MyObserver " << id << "\n";
    }

    void update(const std::string& message) {
        this->message = message;
        printInfo();
    }

    void printInfo() {
        std::cout << "MyObserver " << id << " - " << message << "\n";
    }

    void remove() {
        subject.detach(this);
        std::cout << "MyObserver " << id << " - dezabonare!\n";
    }
};

int MyObserver::static_id = 0;

int main()
{
    MySubject* mySubject = new MySubject();
    MyObserver* myObserver1 = new MyObserver(*mySubject);
    MyObserver* myObserver2 = new MyObserver(*mySubject);
    MyObserver* myObserver3 = new MyObserver(*mySubject);
    MyObserver* myObserver4;
    MyObserver* myObserver5;

    mySubject->createMessage("Salut!");
    myObserver3->remove();

    mySubject->createMessage("Cati am mai ramas?");
    myObserver2->remove();

    myObserver4 = new MyObserver(*mySubject);
    mySubject->dummyLogic();

    myObserver5 = new MyObserver(*mySubject);
    mySubject->createMessage("Asta e ultimul meu mesaj");

    delete myObserver1;
    delete myObserver2;
    delete myObserver3;
    delete myObserver4;
    delete myObserver5;
    delete mySubject;

    return 0;
}
