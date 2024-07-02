#include "ScreenManager.h"
#include <iostream>

// Function to simulate the screen manager
void screenManagerFunction(BoundedBuffer& buffer) {
    int doneCount = 0; // Counter for completed co-editors
    while (doneCount < 3) { // Loop until all three co-editors are done
        std::string message = buffer.remove(); // Remove message from buffer
        if (message == "DONE") {
            ++doneCount; // Increment done counter
        } else {
            std::cout << message << std::endl; // Print message to the screen
        }
    }
    std::cout << "DONE" << std::endl; // Print final 'DONE' message
}
