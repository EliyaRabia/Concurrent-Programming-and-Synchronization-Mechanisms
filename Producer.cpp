#include "Producer.h"
#include <vector>
#include <string>
#include <cstdlib>

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer &buffer) {
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"};
    for (int i = 0; i < numberOfProducts; ++i) {
        std::string type = types[rand() % types.size()]; // Randomly select a type
        std::string item = "Producer " + std::to_string(producerId) + " " + type + " " + std::to_string(i);
        buffer.insert(item);
    }
    buffer.insert("DONE");
}
