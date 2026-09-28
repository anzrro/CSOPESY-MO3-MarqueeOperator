#include "console.h"
#include <iostream>
#include <windows.h>

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
    // Clear console screen on Windows
    system("cls");

    // Move cursor down to Row 4 so the marquee has room at Rows 0-2
    COORD coord = { 0, 4 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    displayPrompt();
    isRunning = true;

    std::string command;
    while (isRunning) {
        std::cout << "Command> ";
        if (!std::getline(std::cin, command)) {
            break;
        }
        if (!command.empty()) {
            cmdInterpreter->executeCommand(command);
        }
    }
}

void Console::stop() {
    if (marqueeDisplay) {
        marqueeDisplay->stop();
    }
    isRunning = false;
}

void Console::displayPrompt() {
    std::cout << "Welcome to CSOPESY!\n\n";
    std::cout << "Group developer:\n";
    std::cout << "Romero, Aaron Zander\n"; 
    std::cout << "Tiangson, Ezekiel Martinez\n"; 
    std::cout << "Vito, Luis Andre\n"; 
    std::cout << "Laus, Rance Lenard\n\n"; 
    std::cout << "Version date: Sept 28, 2026\n\n";
}