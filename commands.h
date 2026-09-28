#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

/**
 * Parses user input commands and directs them to the Console or Marquee modules.
 */
class CommandInterpreter {
public:
    CommandInterpreter(class Marquee* m, class Console* c);
    ~CommandInterpreter();

    // Parses input string and triggers the appropriate action
    void executeCommand(const std::string& command);

private:
    // Displays all supported shell commands and usage
    void help();

    // Requests console shutdown
    void exit();
    
    class Marquee* marquee;
    class Console* console;
};

#endif // COMMANDS_H
