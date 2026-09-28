#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
// TODO: Include necessary headers for your commands and marquee
// #include "commands.h"
// #include "marquee.h"

/**
 * Console is the main entry point interface for the OS emulator shell.
 */
class Console {
public:
    // TODO: Implement constructor to initialize the console UI, command interpreter, and marquee
    Console();
    
    // TODO: Implement destructor to clean up resources
    ~Console();

    // TODO: Implement the main loop that continuously prompts the user, 
    // accepts input, and passes it to the CommandInterpreter.
    void run();

private:
    // TODO: Implement a function to display the initial welcome message and the prompt (e.g., "Command> ")
    void displayPrompt();

    // TODO: Declare member variables to hold instances of your components
    // CommandInterpreter cmdInterpreter;
    // Marquee marqueeDisplay;
};

#endif // CONSOLE_H
