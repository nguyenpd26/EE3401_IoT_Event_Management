#include "../include/RingBuffer.h"
#include <stdexcept>

// Initialize Ring Buffer
RingBuffer::RingBuffer(size_t capacity, OverflowPolicy policy)
    : buffer(capacity),
      capacity(capacity),
      overflow_policy(policy),
      head(0),
      tail(0),
      count(0),
      total_packets_received(0),
      dropped_packets(0),
      overwritten_packets(0),
      peak_buffer_usage(0) {

    if (capacity == 0) {
        throw std::invalid_argument(
            "Ring Buffer capacity must be greater than zero"
        );
    }
}

// Add an event
bool RingBuffer::push(const IoTEvent& event) {
    std::lock_guard<std::mutex> lock(mutex);

    total_packets_received++;

    if (count == capacity) {

        // Drop the new event
        if (overflow_policy == OverflowPolicy::DropNew) {
            dropped_packets++;
            return false;
        }

        // Overwrite the oldest event
        buffer[head] = event;

        head = (head + 1) % capacity;
        tail = (tail + 1) % capacity;

        overwritten_packets++;

        return true;
    }

    buffer[head] = event;

    head = (head + 1) % capacity;
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

    tail = (tail + 1) % capacity;
    count--;

    return true;
}

// Check if buffer is full
bool RingBuffer::is_full() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count == capacity;
}

// Check if buffer is empty
bool RingBuffer::is_empty() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count == 0;
}

// Get current number of events
size_t RingBuffer::get_count() const {
    std::lock_guard<std::mutex> lock(mutex);
    return count;
}

// Get maximum buffer capacity
size_t RingBuffer::get_capacity() const {
    return capacity;
}

// Get total received packets
uint64_t RingBuffer::get_total_packets_received() const {
    std::lock_guard<std::mutex> lock(mutex);
    return total_packets_received;
}

// Get rejected new packets
uint64_t RingBuffer::get_dropped_packets() const {
    std::lock_guard<std::mutex> lock(mutex);
    return dropped_packets;
}

// Get overwritten old packets
uint64_t RingBuffer::get_overwritten_packets() const {
    std::lock_guard<std::mutex> lock(mutex);
    return overwritten_packets;
}

// Get total packets lost
uint64_t RingBuffer::get_lost_packets() const {
    std::lock_guard<std::mutex> lock(mutex);
    return dropped_packets + overwritten_packets;
}

// Get peak buffer usage
size_t RingBuffer::get_peak_buffer_usage() const {
    std::lock_guard<std::mutex> lock(mutex);
    return peak_buffer_usage;
}
