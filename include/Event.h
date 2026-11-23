#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <cstdint>

enum class EventSeverity {
    INFO,
    WARNING,
    CRITICAL
};

struct IoTEvent {
    std::string device_id;
    uint64_t timestamp;
    int event_type;
    float sensor_val;
    EventSeverity severity;

    // 0-argument default constructor (for RingBuffer array allocation)
    IoTEvent() 
        : device_id("UNKNOWN"), 
          timestamp(0), 
          event_type(0), 
          sensor_val(0.0f), 
          severity(EventSeverity::INFO) {}

    // 5-argument constructor (for brace/list initialization)
    IoTEvent(std::string id, uint64_t ts, int type, float val, EventSeverity sev)
        : device_id(std::move(id)), 
          timestamp(ts), 
          event_type(type), 
          sensor_val(val), 
          severity(sev) {}
};

#endif