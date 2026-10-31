#include "RingBuffer.h"

// Initialize Ring Buffer
RingBuffer::RingBuffer() {
    head = 0;
    tail = 0;
    count = 0;
}

// Add an event
bool RingBuffer::push(const IoTEvent& event) {
    if (is_full()) {
        return false;
    }

    buffer[head] = event;

    head = (head + 1) % CAPACITY;
    count++;

    return true;
}

// Remove an event
bool RingBuffer::pop(IoTEvent& event) {
    if (is_empty()) {
        return false;
    }

    event = buffer[tail];

    tail = (tail + 1) % CAPACITY;
    count--;

    return true;
}

// Check if buffer is full
bool RingBuffer::is_full() const {
    return count == CAPACITY;
}

// Check if buffer is empty
bool RingBuffer::is_empty() const {
    return count == 0;
}

// Get number of events
size_t RingBuffer::get_count() const {
    return count;
}