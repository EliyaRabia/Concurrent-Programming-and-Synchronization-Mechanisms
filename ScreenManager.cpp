#include "ScreenManager.h"
#include <iostream>

void screenManagerFunction(BoundedBuffer& buffer) {
    while (true) {
        std::string item = buffer.remove();
        if (item == "DONE") {
            std::cout << "ScreenManager received DONE signal." << std::endl;
            break;
        }
        std::cout << "ScreenManager received: " << item << std::endl;
        std::cout << "Producer " << item << std::endl;
    }
}
