#include <iostream>

class Logger {
private:
    Logger(const std::string& value) : value(value) {};
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* instance;

    std::string value;
public:
    static Logger* getInstance(const std::string& value) {
        if (instance == nullptr) {
            instance = new Logger(value);
        }
        return instance;
    }

    void log(const std::string& message) {
        std::cout << value << " - " << message << std::endl;
    }
};

Logger* Logger::instance = nullptr;

int main() {
    Logger* logger = Logger::getInstance("ABC");
    logger->log("Hello World!");
    Logger::getInstance("DEF")->log("Hello World 2!");
    return 0;
}
