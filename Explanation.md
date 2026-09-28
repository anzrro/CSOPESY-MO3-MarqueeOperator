# Code Explanation

This document explains the functionality of the `console`, `commands`, and `main` components for the CSOPESY-MO3-MarqueeOperator project.

## Architecture Overview

The system is composed of several components working together:
1. **Console (`console.h` & `console.cpp`)**: Acts as the main application interface. It handles user input looping and displays the prompt.
2. **CommandInterpreter (`commands.h` & `commands.cpp`)**: Parses and executes commands received from the Console.
3. 3. **Marquee (`marquee.h` & `marquee.cpp`)**: Handles the multithreaded marquee animation. It maintains the displayed text, refresh interval, position, and direction while a background worker thread continuously renders the marquee independently of the main command interface.
4. **Main (`main.cpp`)**: The entry point of the program that instantiates the Console and runs it.

## How It Works

### Main Component
The `main.cpp` simply instantiates a `Console` object and calls its `run()` method. This delegates the entire control flow to the Console class.

### Console Component
The `Console` constructor initializes a `Marquee` instance and a `CommandInterpreter` instance.
The `run()` method displays the initial welcome prompt (developed by the listed group members) and enters a `while(isRunning)` loop.
In each iteration, it waits for `std::getline(std::cin, command)` and passes the result to `cmdInterpreter->executeCommand(command)`.

### CommandInterpreter Component
The `CommandInterpreter` receives commands as strings. It checks the command against a known list using `if-else` blocks (e.g., `"start_marquee"`, `"stop_marquee"`, `"set_text"`, `"set_speed"`, `"help"`, `"exit"`).
- `exit`: Calls `console->stop()` which terminates the while loop in `Console`.
- `set_text` & `set_speed`: Extracts the string arguments, converts them if necessary (like string to integer for speed), and passes them to the `Marquee` object.
- `help`: Outputs the list of valid commands to `std::cout`.
- Other commands are routed to their respective `Marquee` methods.

### Dependency Injection
To allow the components to interact with one another, pointers are used. The `Console` creates the `Marquee` and the `CommandInterpreter`. It passes a pointer to the `Marquee` and a pointer to itself (`this`) to the `CommandInterpreter`. This enables the `CommandInterpreter` to stop the console (on `exit`) and control the marquee (on `start_marquee`, etc.).
