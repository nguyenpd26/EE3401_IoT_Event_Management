
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <mutex>
#include "Event.h"

class RingBuffer {
private:
    static const size_t CAPACITY = 16;

    IoTEvent buffer[CAPACITY];

    size_t head;
    size_t tail;
    size_t count;

    uint64_t total_packets_received;
    uint64_t dropped_packets;
    size_t peak_buffer_usage;

    // Mutex for thread synchronization
    mutable std::mutex mutex;

public:
    RingBuffer();

    bool push(const IoTEvent& event);
    bool pop(IoTEvent& event);

    bool is_full() const;
    bool is_empty() const;

    size_t get_count() const;
    size_t get_capacity() const;

    uint64_t get_total_packets_received() const;
    uint64_t get_dropped_packets() const;
    size_t get_peak_buffer_usage() const;
};

#endif
