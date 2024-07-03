#include "Dispatcher.h"

void dispatcherFunction(std::vector<BoundedBuffer*>& producerBuffers, 
                        BoundedBuffer& sportsBuffer, 
                        BoundedBuffer& newsBuffer, 
                        BoundedBuffer& weatherBuffer) {
    std::vector<bool> doneFlags(producerBuffers.size(), false); // Flags to check if producers are done
    int doneCount = 0; // Counter for completed producers
    
    while (doneCount < producerBuffers.size()) { // Loop until all producers are done
        for (size_t i = 0; i < producerBuffers.size(); ++i) {
            if (!doneFlags[i]) { // Check if producer i is not done
                std::string message = producerBuffers[i]->remove(); // Remove message from producer buffer
                if (message == "DONE") {
                    doneFlags[i] = true; // Mark producer as done
                    ++doneCount; // Increment done counter
                } else {
                    // Dispatch message to appropriate co-editor buffer
                    if (message.find("SPORTS") != std::string::npos) {
                        sportsBuffer.insert(message);
                    } else if (message.find("NEWS") != std::string::npos) {
                        newsBuffer.insert(message);
                    } else if (message.find("WEATHER") != std::string::npos) {
                        weatherBuffer.insert(message);
                    }
                }
            }
        }
    }
    // Send 'DONE' to all co-editor buffers
    sportsBuffer.insert("DONE");
    newsBuffer.insert("DONE");
    weatherBuffer.insert("DONE");
}
