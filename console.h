#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include "commands.h"
#include "marquee.h"

/**
 * Main shell interface managing initialization, user prompts, and command routing.
 */
class Console {
public:
    Console();
    ~Console();

    // Starts the main shell read-eval-print loop
    void run();

    // Halts the shell loop and stops running sub-processes
    void stop();

private:
    // Prints banner, authors, and initial system information
    void displayPrompt();

    CommandInterpreter* cmdInterpreter;
    Marquee* marqueeDisplay;
    bool isRunning;
};

#endif // CONSOLE_H
