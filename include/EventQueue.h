#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "Event.h"

struct QueueNode {
    IoTEvent event;
    QueueNode* next;
    QueueNode(const IoTEvent& ev) : event(ev), next(nullptr) {}
};

class EventQueue {
private:
    QueueNode* front_ptr;
    QueueNode* rear_ptr;
    size_t queue_size;

public:
    EventQueue();
    ~EventQueue();
    void enqueue(const IoTEvent& event);
    bool dequeue(IoTEvent& event);
    bool is_empty() const;
    size_t size() const;
};

#endif