#include <thread>
#include <cstdlib>
#include <ctime>
#include "Producer.h"
#include <vector>

// Function to simulate a producer producing items
void producerFunction(int id, int numProducts, BoundedBuffer& buffer) {
    srand(time(0) + id); // Seed the random number generator
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"}; // Types of news

    for (int i = 0; i < numProducts; ++i) {
        std::string type = types[rand() % types.size()]; // Randomly select a type
        std::string message = "Producer " + std::to_string(id) + " " + type + " " + std::to_string(i); // Create message
        buffer.insert(message); // Insert message into buffer
    }
    buffer.insert("DONE"); // Insert 'DONE' message after producing all items
}
