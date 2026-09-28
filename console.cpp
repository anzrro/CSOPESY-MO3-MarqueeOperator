#include "console.h"
#include <iostream>
#include <windows.h>
#include <string>

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
    // Enable ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
        SetConsoleMode(hOut, dwMode);
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    if (height < 10) height = 24; // fallback

    // Clear terminal screen and set scroll to be from line 5 and below
    std::cout << "\033[2J";
    std::cout << "\033[5;" << height << "r";

    // Move cursor to the bottom line
    std::cout << "\033[" << height << ";1H";

    displayPrompt();
    isRunning = true;

    std::string command;
    while (isRunning) {
        std::cout << "Command> \033[K";
        if (!std::getline(std::cin, command)) {
            break; // Handle EOF or unexpected input termination
        }
        if (!command.empty()) {
            cmdInterpreter->executeCommand(command);
        }
    }

    // Reset scrolling region and clear screen on exit
    std::cout << "\033[r\033[2J\033[H";
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