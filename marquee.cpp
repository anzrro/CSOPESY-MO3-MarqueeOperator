#include "marquee.h"
#include <iostream>
#include <chrono>
#include <windows.h> // Windows Console API for cursor manipulation

/**
 * Moves the console cursor to specific (X, Y) coordinates.
 * Used to draw the marquee box at row 0 without scrolling the terminal.
 */
static void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Retrieves the current cursor position.
 * Preserves the user's typing position so drawing does not disrupt input.
 */
static COORD getCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

Marquee::Marquee() {
    // Default values
    text = "CSOPESY";
    speed = 150;           // 150 ms default speed
    isRunning = false;     // Not running until user types 'start_marquee'
    xPos = 0;              // Start at the left
    direction = 1;         // Move right initially
}


Marquee::~Marquee() {
    // Make sure the thread is stopped before the object is destroyed
    stop();
}

void Marquee::start() {
    // Only starts if not already running
    if (!isRunning) {
        isRunning = true;
        // Start animationLoop on a new background thread
        animationThread = std::thread(&Marquee::animationLoop, this);
    }
}

void Marquee::stop() {
    // Only stop if currently running
    if (isRunning) {
        isRunning = false; // Tells the while loop in animationLoop() to stop
        if (animationThread.joinable()) {
            animationThread.join(); // Wait for the background thread to finish cleanly
        }
    }
}

void Marquee::setText(const std::string& newText) {
    // std::lock_guard locks the mutex upon creation and unlocks it on return
    std::lock_guard<std::mutex> lock(mtx);
    text = newText;
    xPos = 0; // Reset position to left edge
}

void Marquee::setSpeed(int milliseconds) {
    std::lock_guard<std::mutex> lock(mtx);
    // Don't allow speeds less than 1ms to prevent crashes
    if (milliseconds < 1) {
        speed = 1;
    } else {
        speed = milliseconds;
    }
}

void Marquee::animationLoop() {
    // This loop runs in the background as long as isRunning is true
    while (isRunning) {
        renderAscii();

        // Retrieve current speed safely using the mutex
        int currentSpeed;
        {
            std::lock_guard<std::mutex> lock(mtx);
            currentSpeed = speed;
        }

        // Pause for 'currentSpeed' milliseconds before drawing the next frame
        std::this_thread::sleep_for(std::chrono::milliseconds(currentSpeed));
    }
}

void Marquee::renderAscii() {
    // Safely copy text
    std::string currentText;
    {
        std::lock_guard<std::mutex> lock(mtx);
        currentText = text;
    }

    // Calculate bounce logic
    int maxPos = boxWidth - static_cast<int>(currentText.length()) - 2;
    if (maxPos < 0) {
        maxPos = 0;
    }

    // Update horizontal coordinate and bounce when hitting walls
    xPos += direction;
    if (xPos >= maxPos) {
        xPos = maxPos;
        direction = -1; // Hit right wall -> bounce left
    } else if (xPos <= 0) {
        xPos = 0;
        direction = 1;  // Hit left wall -> bounce right
    }

    // Remember where the user's cursor currently is (where they are typing)
    COORD savedPos = getCursorPosition();

    // Move cursor to row 0, 1, and 2 at the top of the terminal
    setCursorPosition(0, 0);
    std::cout << "+";
    for (int i = 0; i < boxWidth; ++i) std::cout << "-";
    std::cout << "+";

    setCursorPosition(0, 1);
    std::cout << "|";
    for (int i = 0; i < xPos; ++i) std::cout << " ";
    std::cout << currentText;
    for (int i = 0; i < (boxWidth - xPos - static_cast<int>(currentText.length())); ++i) {
        std::cout << " ";
    }
    std::cout << "|";

    setCursorPosition(0, 2);
    std::cout << "+";
    for (int i = 0; i < boxWidth; ++i) std::cout << "-";
    std::cout << "+";

    // Return the cursor back to the user's input line so typing is not interrupted
    setCursorPosition(savedPos.X, savedPos.Y);
    std::cout << std::flush;
}