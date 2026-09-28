#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

/**
 * CommandInterpreter handles the parsing and execution of user commands.
 */
class CommandInterpreter {
public:
    CommandInterpreter(class Marquee* m, class Console* c);
    ~CommandInterpreter();

    // TODO: Implement the logic to parse the user input and route it to the correct action.
    // Acceptable commands: "help", "start_marquee", "stop_marquee", "set_text", "set_speed", "exit"
    void executeCommand(const std::string& command);

private:
    // TODO: Implement the help command to display available commands and their descriptions
    void help();

    // TODO: Implement the exit command to gracefully terminate the console
    void exit();
    
    class Marquee* marquee;
    class Console* console;
};

#endif // COMMANDS_H
