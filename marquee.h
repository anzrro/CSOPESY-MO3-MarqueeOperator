#ifndef MARQUEE_H
#define MARQUEE_H

#include <string>
#include <thread>
#include <mutex>
#include <atomic>

/**
 * Handles the multithreaded rendering of an ASCII graphics marquee animation.
 * The animation bounces text back and forth within a border box at the top of the terminal.
 */
class Marquee {
public:
    // Initializes default text, refresh rate, and state variables
    Marquee();

    // Ensures the animation thread is safely stopped and joined upon destruction
    ~Marquee();

    // Spawns the background animation thread
    void start();

    // Stops the background animation thread
    void stop();

    // Updates the displayed text
    void setText(const std::string& newText);

    // Updates the refresh interval in milliseconds
    void setSpeed(int milliseconds);

private:
    // Worker loop running on the background thread
    void animationLoop();

    // Calculates coordinates and draws the ASCII border and text
    void renderAscii();

    // Variables for Multithreading
    std::string text;             // The text currently displayed in the marquee
    int speed;                    // How many milliseconds to wait between frames
    std::thread animationThread;  // The background worker thread
    std::atomic<bool> isRunning;  // Thread-safe true/false flag to keep the loop going
    std::mutex mtx;               // Protects 'text' and 'speed' from being read & written at the same time

    // Variables for Animation Position
    int xPos;                     // Current horizontal position of the text
    int direction;                // 1 = moving right, -1 = moving left
    const int boxWidth = 50;      // Total width of the marquee box
};

#endif // MARQUEE_H