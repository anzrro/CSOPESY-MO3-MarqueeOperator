#include "commands.h"
#include "console.h"
#include "marquee.h"
#include <iostream>
#include <sstream>

CommandInterpreter::CommandInterpreter(Marquee* m, Console* c) 
    : marquee(m), console(c) {
}

CommandInterpreter::~CommandInterpreter() {
}

void CommandInterpreter::executeCommand(const std::string& command) {
    // Read the first word of the command
    std::istringstream iss(command);
    std::string baseCmd;
    iss >> baseCmd;

    if (baseCmd == "exit") {
        exit();
    } else if (baseCmd == "help") {
        help();
    } else if (baseCmd == "start_marquee") {
        if (marquee) {
            marquee->start();
            std::cout << "Marquee animation started.\n";
        }
    } else if (baseCmd == "stop_marquee") {
        if (marquee) {
            marquee->stop();
            std::cout << "Marquee animation stopped.\n";
        }
    } else if (baseCmd == "set_text") {
        std::string newText;
        // Read the rest of the line after 'set_text'
        std::getline(iss >> std::ws, newText);

        // If the user just typed 'set_text' with no parameters, ask them:
        if (newText.empty()) {
            std::cout << "Enter text: ";
            std::getline(std::cin, newText);
        }

        if (marquee) {
            marquee->setText(newText);
            std::cout << "Text updated to: " << newText << "\n";
        }
    } else if (baseCmd == "set_speed") {
        int newSpeed = 0;
        // Try reading the number from the command line
        if (!(iss >> newSpeed)) {
            std::cout << "Enter speed in milliseconds: ";
            std::cin >> newSpeed;
            // Clear leftover newline character from buffer
            std::string temp;
            std::getline(std::cin, temp);
        }

        if (marquee) {
            marquee->setSpeed(newSpeed);
            std::cout << "Speed set to " << newSpeed << " ms.\n";
        }
    } else {
        std::cout << "Unknown command. Type 'help' for options.\n";
    }
}

// Displays a list of available commands and their descriptions
void CommandInterpreter::help() {
    std::cout << "Available commands:\n";
    std::cout << "  help           - displays the commands and its description\n";
    std::cout << "  start_marquee  - starts the marquee \"animation\"\n";
    std::cout << "  stop_marquee   - stops the marquee \"animation\"\n";
    std::cout << "  set_text       - accepts a text input and displays it as a marquee\n";
    std::cout << "  set_speed      - sets the marquee animation refresh in milliseconds\n";
    std::cout << "  exit           - terminates the console\n";
}

void CommandInterpreter::exit() {
    if (console) {
        console->stop();
    }
}