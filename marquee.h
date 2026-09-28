#ifndef MARQUEE_H
#define MARQUEE_H

#include <string>
#include <thread>
#include <mutex>
#include <atomic>

/**
 * Marquee handles the multithreaded rendering of an ASCII graphics animation.
 */
class Marquee {
public:
    Marquee();
    ~Marquee();

    void start();
    void stop();
    void setText(const std::string& newText);
    void setSpeed(int milliseconds);

private:
    void animationLoop();
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