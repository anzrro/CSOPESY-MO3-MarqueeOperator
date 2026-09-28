#include "marquee.h"
#include <iostream>
#include <chrono>
#include <string>

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

bool Marquee::isActive() const {
    return isRunning.load();
}

void Marquee::animationLoop() {
    // This loop runs in the background as long as isRunning is true
    while (isRunning) {
        renderAscii();

        auto start_time = std::chrono::steady_clock::now();
        while (isRunning) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
            
            int currentSpeed;
            {
                std::lock_guard<std::mutex> lock(mtx);
                currentSpeed = speed;
            }
            
            if (elapsed >= currentSpeed) {
                break;
            }
            
            // Sleep in small chunks for cleaner interruptions and faster updates
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void Marquee::renderAscii() {
    std::string currentText;
    int currentXPos;

    // Protect shared marquee state
    {
        std::lock_guard<std::mutex> lock(mtx);

        currentText = text;

        // Calculate maximum valid position
        int maxPos = boxWidth - static_cast<int>(currentText.length());

        if (maxPos < 0) {
            maxPos = 0;
        }

        // Update horizontal position
        xPos += direction;

        if (xPos >= maxPos) {
            xPos = maxPos;
            direction = -1;
        }
        else if (xPos <= 0) {
            xPos = 0;
            direction = 1;
        }

        currentXPos = xPos;
    }

    // Build frame buffer to prevent screen tearing
    std::string frame = "\033[s\033[?25l"; // Save cursor, hide cursor
    
    // Top border
    frame += "\033[1;1H+";
    frame.append(boxWidth, '-');
    frame += "+\033[K";
    
    // Marquee text
    frame += "\033[2;1H|";
    frame.append(currentXPos, ' ');
    frame += "\033[32m" + currentText + "\033[0m";
    int remainingSpaces = boxWidth - currentXPos - static_cast<int>(currentText.length());
    if (remainingSpaces > 0) {
        frame.append(remainingSpaces, ' ');
    }
    frame += "|\033[K";
    
    // Bottom border
    frame += "\033[3;1H+";
    frame.append(boxWidth, '-');
    frame += "+\033[K";
    
    // Restore cursor and show cursor
    frame += "\033[u\033[?25h";
    
    // Output everything atomically to avoid tearing
    std::cout << frame << std::flush;
}