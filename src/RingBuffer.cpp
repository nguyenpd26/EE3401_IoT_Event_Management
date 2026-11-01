#include "RingBuffer.h"
#include <mutex>

// Initialize Ring Buffer
RingBuffer::RingBuffer() {
    head = 0;
    tail = 0;
    count = 0;

    total_packets_received = 0;
    dropped_packets = 0;
    peak_buffer_usage = 0;
}

// Add an event
bool RingBuffer::push(const IoTEvent& event) {
    std::lock_guard<std::mutex> lock(mutex);

    total_packets_received++;

    if (count == CAPACITY) {
        dropped_packets++;
        return false;
    }

    buffer[head] = event;

    head = (head + 1) % CAPACITY;
    count++;

    if (count > peak_buffer_usage) {
        peak_buffer_usage = count;
    }

    return true;
}

// Remove an event
bool RingBuffer::pop(IoTEvent& event) {
    std::lock_guard<std::mutex> lock(mutex);

    if (count == 0) {
        return false;
    }

    event = buffer[tail];

    tail = (tail + 1) % CAPACITY;
    count--;

    return true;
}

// Check if buffer is full
bool RingBuffer::is_full() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count == CAPACITY;
}

// Check if buffer is empty
bool RingBuffer::is_empty() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count == 0;
}

// Get number of events
size_t RingBuffer::get_count() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count;
}

// Get maximum buffer capacity
size_t RingBuffer::get_capacity() const {
    return CAPACITY;
}

// Get total received packets
uint64_t RingBuffer::get_total_packets_received() const {
    std::lock_guard<std::mutex> lock(mutex);
    return total_packets_received;
}

// Get dropped packets
uint64_t RingBuffer::get_dropped_packets() const {
    std::lock_guard<std::mutex> lock(mutex);
    return dropped_packets;
}

// Get peak buffer usage
size_t RingBuffer::get_peak_buffer_usage() const {
    std::lock_guard<std::mutex> lock(mutex);
    return peak_buffer_usage;
}
