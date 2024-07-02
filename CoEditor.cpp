// Co-Editor.cpp
#include "BoundedBuffer.h"
#include "CoEditor.h"
#include <chrono>
#include <thread> 

// Function to simulate a co-editor
void coEditorFunction(BoundedBuffer& inputBuffer, BoundedBuffer& outputBuffer) {
    while (true) {
        std::string message = inputBuffer.remove(); // Remove message from input buffer
        if (message == "DONE") {
            outputBuffer.insert("DONE"); // Pass 'DONE' message to output buffer
            break; // Exit the loop
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate editing delay
        outputBuffer.insert(message); // Insert edited message into output buffer
    }
}
