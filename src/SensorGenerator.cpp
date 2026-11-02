#include "SensorGenerator.h"
#include <cstdlib>
#include <ctime>

SensorGenerator::SensorGenerator() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    device_ids = {"DEV_TEMP_001", "DEV_TEMP_002", "DEV_PRESS_101", "DEV_DOOR_202"};
}

IoTEvent SensorGenerator::generate_random_event() {
    std::string dev_id = device_ids[std::rand() % device_ids.size()];
    uint64_t current_time = static_cast<uint64_t>(std::time(nullptr));
    uint8_t type = (std::rand() % 3) + 1; // Event types 1, 2, or 3
    float sensor_val = 20.0f + static_cast<float>(std::rand() % 600) / 10.0f; // 20.0 to 80.0
    
    EventSeverity sev = EventSeverity::INFO;
    if (sensor_val > 70.0f) {
        sev = EventSeverity::CRITICAL;
    } else if (sensor_val > 50.0f) {
        sev = EventSeverity::WARNING;
    }

    return IoTEvent{dev_id, current_time, type, sensor_val, sev};
}