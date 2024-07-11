#include "ScreenManager.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

void screenManagerFunction(BoundedBuffer& buffer) {
    int doneCount = 0; // Counter for completed co-editors
    while (doneCount < 3) { // Loop until all three co-editors are done
        string message = buffer.remove(); // Remove message from buffer
        if (message == "DONE") {
            ++doneCount; // Increment done counter
        } else {
            cout << message << endl; // Print message to the screen
        }
    }
    cout << "DONE" << endl; // Print final 'DONE' message
}
