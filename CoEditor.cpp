#include "CoEditor.h"

void coEditorFunction(BoundedBuffer& inputBuffer, BoundedBuffer& outputBuffer) {
    while (true) {
        std::string item = inputBuffer.remove();
        if (item == "DONE") {
            outputBuffer.insert("DONE");
            break;
        }
        outputBuffer.insert(item);
    }
}
