#include "Producer.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <map>

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer &buffer) {
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"};
    std::map<std::string, int> counts = {{"SPORTS", 0}, {"NEWS", 0}, {"WEATHER", 0}};
    
    for (int i = 0; i < numberOfProducts; ++i) {
        std::string type = types[rand() % types.size()]; // Randomly select a type
        std::string item = "Producer " + std::to_string(producerId) + " " + type + " " + std::to_string(counts[type]);
        counts[type]++; // Increment the count for the selected type
        buffer.insert(item);
    }
    buffer.insert("DONE");
}
