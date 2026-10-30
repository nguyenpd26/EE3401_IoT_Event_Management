#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "Event.h"
#include <cstddef>

class RingBuffer {
private:
    static const size_t CAPACITY = 16;
    IoTEvent buffer[CAPACITY];
    size_t head;
    size_t tail;
    size_t count;

public:
    RingBuffer();
    bool push(const IoTEvent& event); // Add event to buffer
    bool pop(IoTEvent& event);        // Remove event from buffer
    bool is_full() const;
    bool is_empty() const;
    size_t get_count() const;
};

#endif