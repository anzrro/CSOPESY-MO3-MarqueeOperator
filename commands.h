#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

/**
 * CommandInterpreter handles the parsing and execution of user commands.
 */
class CommandInterpreter {
public:
    // TODO: Implement constructor and destructor to initialize any needed resources
    CommandInterpreter();
    ~CommandInterpreter();

    // TODO: Implement the logic to parse the user input and route it to the correct action.
    // Acceptable commands: "help", "start_marquee", "stop_marquee", "set_text", "set_speed", "exit"
    void executeCommand(const std::string& command);

private:
    // TODO: Implement the help command to display available commands and their descriptions
    void help();

    // TODO: Implement the exit command to gracefully terminate the console
    void exit();
    
    // TODO: Add any necessary references or pointers to the Marquee or Console 
    // to allow commands to control them.
};

#endif // COMMANDS_H
