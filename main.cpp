#include <iostream>
#include <string>

void printHeader() {
    std::cout << "Welcome to CSOPESY!\n";
    std::cout << "Group developers:\n";
    std::cout << "Romero, Aaron Zander\n"; 
    std::cout << "Tiangson, Ezekiel Martinez\n"; 
    std::cout << "Vito, Luis Andre\n"; 
    std::cout << "Laus, Rance\n"; 
}

int main() {
    printHeader();
    
    std::string command;
    bool isRunning = true;

    while (isRunning) {
        std::cout << "Command > "; 
        std::getline(std::cin, command);

        if (command == "exit") { 
            isRunning = false;
        } else if (command == "help") { 
            std::cout << "Available commands:\n";
            std::cout << "start_marquee - starts the marquee animation\n";
            std::cout << "stop_marquee - stops the marquee animation\n";
            std::cout << "set_text - accepts a text input and displays it as a marquee\n";
            std::cout << "set_speed - sets the marquee animation refresh in milliseconds\n";
            std::cout << "exit - terminates the console\n\n";
        } else {
            std::cout << "Unknown command. Type 'help' for options.\n\n";
        }
    }

    return 0;
}