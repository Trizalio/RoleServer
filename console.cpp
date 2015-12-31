#include "console.h"

void Console::run()
{
    std::cout << "First message" << std::endl;
    std::cout << "> " << std::flush;
    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readCommand()));
}

void Console::readCommand()
{
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof() || line == "quit") {
        std::cout << "Good bye!" << std::endl;
        emit quit();
    } else if (line == "send") {
        std::cout << "Sending music to all clients: "<< std::endl;
        std::cout << "> " << std::flush;
        emit send();
    } else if (line == "play") {
        std::cout << "Sending play issue to all clients: "<< std::endl;
        std::cout << "> " << std::flush;
        emit play();
    } else {
        std::cout << "Echo: " << line << std::endl;
        std::cout << "> " << std::flush;
    }
}
