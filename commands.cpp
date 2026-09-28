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
    std::istringstream iss(command);
    std::string baseCmd;
    iss >> baseCmd;

    // EXIT
    if (baseCmd == "exit") {
        std::string extra;
        if (iss >> extra) {
            std::cout << "Usage: exit\n";
            return;
        }

        exit();
    }

    // HELP
    else if (baseCmd == "help") {
        std::string extra;
        if (iss >> extra) {
            std::cout << "Usage: help\n";
            return;
        }

        help();
    }

    // START MARQUEE
    else if (baseCmd == "start_marquee") {
        std::string extra;
        if (iss >> extra) {
            std::cout << "Usage: start_marquee\n";
            return;
        }

        if (marquee) {
            if (marquee->isActive()) {
                std::cout << "Marquee animation is already running.\n";
            } else {
                marquee->start();
                std::cout << "Marquee animation started.\n";
            }
        }
    }

    // STOP MARQUEE
    else if (baseCmd == "stop_marquee") {
        std::string extra;
        if (iss >> extra) {
            std::cout << "Usage: stop_marquee\n";
            return;
        }

        if (marquee) {
            if (!marquee->isActive()) {
                std::cout << "Marquee animation is already stopped.\n";
            } else {
                marquee->stop();
                std::cout << "Marquee animation stopped.\n";
            }
        }
    }

    // SET TEXT
    else if (baseCmd == "set_text") {
        std::string newText;

        // Read everything after set_text
        std::getline(iss >> std::ws, newText);

        // If no inline text was provided, prompt the user
        if (newText.empty()) {
            std::cout << "Enter text: ";
            std::getline(std::cin, newText);
        }

        // Reject empty input
        if (newText.empty()) {
            std::cout << "Error: marquee text cannot be empty.\n";
            return;
        }

        // Box width is 50, so text cannot exceed 50 characters
        if (newText.length() > 50) {
            std::cout << "Error: marquee text cannot exceed 50 characters.\n";
            return;
        }

        if (marquee) {
            marquee->setText(newText);
            std::cout << "Text updated to: " << newText << "\n";
        }
    }

    // SET SPEED
    else if (baseCmd == "set_speed") {
        std::string speedInput;

        // Read parameter if provided
        if (!(iss >> speedInput)) {
            std::cout << "Enter speed in milliseconds: ";
            std::getline(std::cin, speedInput);
        }

        // Reject additional arguments
        std::string extra;
        if (iss >> extra) {
            std::cout << "Usage: set_speed <milliseconds>\n";
            return;
        }

        // Convert string to integer safely
        int newSpeed;

        try {
            size_t processedCharacters;
            newSpeed = std::stoi(speedInput, &processedCharacters);

            // Reject values such as "100abc"
            if (processedCharacters != speedInput.length()) {
                throw std::invalid_argument("Invalid number");
            }
        }
        catch (...) {
            std::cout << "Error: speed must be a valid integer.\n";
            return;
        }

        // Reject zero and negative values
        if (newSpeed < 1) {
            std::cout << "Error: speed must be at least 1 millisecond.\n";
            return;
        }

        if (marquee) {
            marquee->setSpeed(newSpeed);
            std::cout << "Speed set to " << newSpeed << " ms.\n";
        }
    }

    // UNKNOWN COMMAND
    else {
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