#include "commands.h"
#include "console.h"
#include "marquee.h"
#include <iostream>

CommandInterpreter::CommandInterpreter(Marquee* m, Console* c) : marquee(m), console(c) {
}

CommandInterpreter::~CommandInterpreter() {
}

void CommandInterpreter::executeCommand(const std::string& command) {
    if (command == "exit") {
        exit();
    } else if (command == "help") {
        help();
    } else if (command == "start_marquee") {
        if (marquee) {
            marquee->start();
            std::cout << "Marquee started.\n";
        }
    } else if (command == "stop_marquee") {
        if (marquee) {
            marquee->stop();
            std::cout << "Marquee stopped.\n";
        }
    } else if (command.find("set_text ") == 0) {
        std::string text = command.substr(9);
        if (marquee) {
            marquee->setText(text);
            std::cout << "Text updated.\n";
        }
    } else if (command.find("set_speed ") == 0) {
        std::string speedStr = command.substr(10);
        try {
            int speed = std::stoi(speedStr);
            if (marquee) {
                marquee->setSpeed(speed);
                std::cout << "Speed updated.\n";
            }
        } catch (...) {
            std::cout << "Invalid speed value. Please provide an integer.\n";
        }
    } else {
        std::cout << "Unknown command. Type 'help' for options.\n";
    }
}

void CommandInterpreter::help() {
    std::cout << "Available commands:\n";
    std::cout << "start_marquee - starts the marquee animation\n";
    std::cout << "stop_marquee - stops the marquee animation\n";
    std::cout << "set_text <text> - accepts a text input and displays it as a marquee\n";
    std::cout << "set_speed <ms> - sets the marquee animation refresh in milliseconds\n";
    std::cout << "exit - terminates the console\n";
}

void CommandInterpreter::exit() {
    if (console) {
        console->stop();
    }
}
