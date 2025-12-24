#include <iostream>

class Button {
public:
    Button() = default;

    virtual void renderButton() = 0;
};

class CheckBox {
public:
    CheckBox() = default;

    virtual void renderCheckBox() = 0;
};

class WinButton : public Button {
public:
    WinButton() = default;

    void renderButton() override {
        std::cout << "Windows Button!" << std::endl;
    }
};

class WinCheckBox : public CheckBox {
public:
    WinCheckBox() = default;

    void renderCheckBox() override {
        std::cout << "Windows CheckBox!" << std::endl;
    }
};

class MacButton : public Button {
public:
    MacButton() = default;

    void renderButton() override {
        std::cout << "Mac Button!" << std::endl;
    }
};

class MacCheckBox : public CheckBox {
public:
    MacCheckBox() = default;

    void renderCheckBox() override {
        std::cout << "Mac CheckBox!" << std::endl;
    }
};

class GUIFactory {
protected:
    Button* button;
    CheckBox* checkBox;
public:
    GUIFactory() = default;

    virtual void createButton() = 0;
    virtual void createCheckBox() = 0;

    virtual void renderGUI() {
        if (button != nullptr) button->renderButton();
        if (checkBox != nullptr) checkBox->renderCheckBox();
    }
};

class WindowsGUIFactory : public GUIFactory {
public:
    WindowsGUIFactory() = default;

    virtual void createButton() override {
        button = new WinButton();
    }

    virtual void createCheckBox() override {
        checkBox = new WinCheckBox();
    }
};

class MacGUIFactory : public GUIFactory {
public:
    MacGUIFactory() = default;

    virtual void createButton() override {
        button = new MacButton();
    }

    virtual void createCheckBox() override {
        checkBox = new MacCheckBox();
    }
};

int main() {
    GUIFactory* guiFactory = new MacGUIFactory();
    guiFactory->createButton();
    guiFactory->createCheckBox();
    guiFactory->renderGUI();
    return 0;
}
