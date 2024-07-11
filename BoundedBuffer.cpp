#include "BoundedBuffer.h"

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::string;
using std::optional;
using std::lock_guard;

BoundedBuffer::BoundedBuffer(size_t size) : maxSize(size) {}

void BoundedBuffer::insert(const std::string& item) {
    unique_lock<mutex> lock(mtx);
    cond.wait(lock, [this]() { return buffer.size() < maxSize; });
    buffer.push(item);
    cond.notify_all();
}

std::string BoundedBuffer::remove() {
    unique_lock<mutex> lock(mtx);
    cond.wait(lock, [this]() { return !buffer.empty(); });
    string item = buffer.front();
    buffer.pop();
    cond.notify_all();
    return item;
}

std::optional<std::string> BoundedBuffer::tryRemove() {
    lock_guard<mutex> lock(mtx);
    if (buffer.empty()) {
        return std::nullopt; // Return an empty optional if the buffer is empty
    }
    string item = buffer.front();
    buffer.pop();
    cond.notify_all();
    return item;
}
