#include "Producer.h"

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer &buffer) {
    for (int i = 0; i < numberOfProducts; ++i) {
        std::string item = "Producer " + std::to_string(producerId) + " " + std::to_string(i);
        std::cout << "Generated: " << item << std::endl;
        buffer.insert(item);
    }
    buffer.insert("DONE");
    std::cout << "Producer " << producerId << " finished." << std::endl;
}
