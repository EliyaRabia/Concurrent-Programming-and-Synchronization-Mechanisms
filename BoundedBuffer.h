#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class BoundedBuffer {
public:
    BoundedBuffer(size_t size);

    void insert(const std::string& item);

    std::string remove();

private:
    std::queue<std::string> buffer;
    size_t maxSize;
    std::mutex mtx;
    std::condition_variable cond;
};

#endif // BOUNDED_BUFFER_H
