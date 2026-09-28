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
    // TODO: Implement constructor to initialize default text, speed, and thread status
    Marquee();
    
    // TODO: Implement destructor to clean up threads and resources, ensuring the thread joins properly
    ~Marquee();

    // TODO: Implement logic to start the marquee animation thread (start_marquee command)
    void start();

    // TODO: Implement logic to stop the marquee animation thread safely (stop_marquee command)
    void stop();

    // TODO: Implement logic to update the text. Ensure thread-safe assignment. (set_text command)
    void setText(const std::string& newText);

    // TODO: Implement logic to set the refresh speed in milliseconds. Ensure thread-safe assignment. (set_speed command)
    void setSpeed(int milliseconds);

private:
    // TODO: Implement the worker function that runs in a separate thread. 
    // It should loop and continuously render the ASCII marquee based on the set speed.
    void animationLoop();

    // TODO: Implement a helper function to convert the standard string into an ASCII graphic 
    // and render the animation frame to the display.
    void renderAscii();

    // TODO: Declare necessary member variables for multithreading and state:
    // - std::string text (the current text to display)
    // - int speed (refresh rate in milliseconds)
    // - std::thread animationThread (the thread object)
    // - std::atomic<bool> isRunning (flag to control the thread loop)
    // - std::mutex mtx (mutex to protect read/write access to text and speed)
};

#endif // MARQUEE_H
