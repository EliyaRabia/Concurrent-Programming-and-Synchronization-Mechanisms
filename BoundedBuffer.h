// BoundedBuffer.h
#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>

// Class to implement a thread-safe bounded buffer
class BoundedBuffer {
public:
    // Constructor to initialize buffer with a given size
    BoundedBuffer(int size);

    // Method to insert an item into the buffer
    void insert(const std::string& item);

    // Method to remove an item from the buffer
    std::string remove();

private:
    std::vector<std::string> buffer; // Vector to hold buffer items
    size_t maxSize; // Maximum size of the buffer
    size_t count; // Current number of items in the buffer
    size_t in; // Index for the next insert position
    size_t out; // Index for the next remove position
    std::mutex mtx; // Mutex for synchronizing access
    std::condition_variable not_full; // Condition variable for full buffer
    std::condition_variable not_empty; // Condition variable for empty buffer
};

#endif // BOUNDED_BUFFER_H
