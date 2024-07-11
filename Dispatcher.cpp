#include "Dispatcher.h"
#include <vector>
#include <string>
#include <optional>

using std::vector;
using std::string;
using std::optional;

void dispatcherFunction(vector<BoundedBuffer*>& producerBuffers, 
                        BoundedBuffer& sportsBuffer, 
                        BoundedBuffer& newsBuffer, 
                        BoundedBuffer& weatherBuffer) {
    vector<bool> doneFlags(producerBuffers.size(), false); // Flags to check if producers are done
    int doneCount = 0; // Counter for completed producers
    
    while (doneCount < producerBuffers.size()) { // Loop until all producers are done
        for (size_t i = 0; i < producerBuffers.size(); ++i) {
            if (!doneFlags[i]) { // Check if producer i is not done
                auto messageOpt = producerBuffers[i]->tryRemove(); // Attempt to remove message from producer buffer
                if (messageOpt.has_value()) { // Check if a message was retrieved
                    string message = messageOpt.value();
                    if (message == "DONE") {
                        doneFlags[i] = true; // Mark producer as done
                        ++doneCount; // Increment done counter
                    } else {
                        // Dispatch message to appropriate co-editor buffer
                        if (message.find("SPORTS") != string::npos) {
                            sportsBuffer.insert(message);
                        } else if (message.find("NEWS") != string::npos) {
                            newsBuffer.insert(message);
                        } else if (message.find("WEATHER") != string::npos) {
                            weatherBuffer.insert(message);
                        }
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
