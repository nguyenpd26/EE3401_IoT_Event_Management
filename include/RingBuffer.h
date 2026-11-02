
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstdint>
#include <cstddef>
#include <mutex>
#include <vector>
#include "Event.h"

enum class OverflowPolicy {
    DropNew,
    OverwriteOldest
};

class RingBuffer {
private:
    std::vector<IoTEvent> buffer;

    const size_t capacity;
    const OverflowPolicy overflow_policy;

    size_t head;
    size_t tail;
    size_t count;

    uint64_t total_packets_received;
    uint64_t dropped_packets;
    uint64_t overwritten_packets;
    size_t peak_buffer_usage;

    mutable std::mutex mutex;

public:
    explicit RingBuffer(
        size_t capacity = 16,
        OverflowPolicy policy = OverflowPolicy::DropNew
    );

    bool push(const IoTEvent& event);
    bool pop(IoTEvent& event);

    bool is_full() const;
    bool is_empty() const;

    size_t get_count() const;
    size_t get_capacity() const;

    uint64_t get_total_packets_received() const;
    uint64_t get_dropped_packets() const;
    uint64_t get_overwritten_packets() const;
    uint64_t get_lost_packets() const;

    size_t get_peak_buffer_usage() const;
};

#endif
