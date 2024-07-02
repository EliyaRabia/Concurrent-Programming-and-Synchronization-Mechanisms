// BoundedBuffer.cpp
#include "BoundedBuffer.h"

// Constructor to initialize buffer with a given size
BoundedBuffer::BoundedBuffer(int size) : maxSize(size), count(0), in(0), out(0) {
    buffer.resize(size); // Resize the buffer
}

// Method to insert an item into the buffer
void BoundedBuffer::insert(const std::string& item) {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    not_full.wait(lock, [this]() { return count < maxSize; }); // Wait if buffer is full

    buffer[in] = item; // Insert item at 'in' position
    in = (in + 1) % maxSize; // Update 'in' position
    count++; // Increase item count

    not_empty.notify_all(); // Notify that buffer is not empty
}

// Method to remove an item from the buffer
std::string BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    not_empty.wait(lock, [this]() { return count > 0; }); // Wait if buffer is empty

    std::string item = buffer[out]; // Get item from 'out' position
    out = (out + 1) % maxSize; // Update 'out' position
    count--; // Decrease item count

    not_full.notify_all(); // Notify that buffer is not full
    return item; // Return the removed item
}
