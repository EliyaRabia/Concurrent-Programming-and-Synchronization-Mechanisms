#include "CoEditor.h"
#include <chrono>
#include <thread>

void coEditorFunction(BoundedBuffer& inputBuffer, BoundedBuffer& outputBuffer) {
    while (true) {
        std::string item = inputBuffer.remove();
        if (item == "DONE") {
            outputBuffer.insert("DONE");
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate editing delay
        outputBuffer.insert(item);
    }
}
