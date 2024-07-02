#include "Dispatcher.h"
#include <iostream>

void dispatcherFunction(std::vector<BoundedBuffer*>& buffers, BoundedBuffer& coEditorBuffer) {
    while (true) {
        bool allDone = true;
        for (auto buffer : buffers) {
            std::string item = buffer->remove();
            if (item == "DONE") {
                buffer->insert("DONE"); // Reinsert to ensure other consumers know it's done
                continue;
            }
            allDone = false;
            std::cout << "Dispatcher received: " << item << std::endl;
            coEditorBuffer.insert(item);
        }
        if (allDone) {
            std::cout << "Dispatcher received DONE signal." << std::endl;
            coEditorBuffer.insert("DONE");
            break;
        }
    }
}
