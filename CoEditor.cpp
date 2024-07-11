#include "CoEditor.h"
#include <chrono>
#include <thread>

using std::string;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

void coEditorFunction(BoundedBuffer& inputBuffer, BoundedBuffer& outputBuffer) {
    while (true) {
        string item = inputBuffer.remove();
        if (item == "DONE") {
            outputBuffer.insert("DONE");
            break;
        }
        sleep_for(milliseconds(100));
        outputBuffer.insert(item);
    }
}
