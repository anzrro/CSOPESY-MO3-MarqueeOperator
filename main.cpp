#include "console.h"

/**
 * Entry point of the OS emulator.
 * Initializes the main Console instance and starts the interactive loop with the user.
 */
int main() {
    Console console;
    console.run();
    return 0;
}