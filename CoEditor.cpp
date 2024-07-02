#include "CoEditor.h"
#include <iostream>

void coEditorFunction(BoundedBuffer& inputBuffer, BoundedBuffer& screenBuffer) {
    while (true) {
        std::string item = inputBuffer.remove();
        if (item == "DONE") {
            std::cout << "Co-Editor received DONE signal." << std::endl;
            screenBuffer.insert("DONE");
            break;
        }
        std::cout << "Co-Editor received: " << item << std::endl;
        screenBuffer.insert(item);
    }
}
