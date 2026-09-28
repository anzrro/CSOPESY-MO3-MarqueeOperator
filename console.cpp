#include "console.h"
#include <iostream>

Console::Console() {
    marqueeDisplay = new Marquee();
    cmdInterpreter = new CommandInterpreter(marqueeDisplay, this);
    isRunning = false;
}

Console::~Console() {
    delete cmdInterpreter;
    delete marqueeDisplay;
}

void Console::run() {
    displayPrompt();
    isRunning = true;
    std::string command;
    while (isRunning) {
        std::cout << "Command > ";
        if (!std::getline(std::cin, command)) {
            break;
        }
        cmdInterpreter->executeCommand(command);
    }
}

void Console::stop() {
    isRunning = false;
}

void Console::displayPrompt() {
    std::cout << "Welcome to CSOPESY!\n";
    std::cout << "Group developers:\n";
    std::cout << "Romero, Aaron Zander\n"; 
    std::cout << "Tiangson, Ezekiel Martinez\n"; 
    std::cout << "Vito, Luis Andre\n"; 
    std::cout << "Laus, Rance\n"; 
}
