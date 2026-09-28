#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include "commands.h"
#include "marquee.h"

/**
 * Console is the main entry point interface for the OS emulator shell.
 */
class Console {
public:
    Console();
    
    ~Console();
    
    void stop();

    // TODO: Implement the main loop that continuously prompts the user, 
    // accepts input, and passes it to the CommandInterpreter.
    void run();

private:
    // TODO: Implement a function to display the initial welcome message and the prompt (e.g., "Command> ")
    void displayPrompt();

    CommandInterpreter* cmdInterpreter;
    Marquee* marqueeDisplay;
    bool isRunning;
};

#endif // CONSOLE_H
