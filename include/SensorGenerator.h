#ifndef SENSOR_GENERATOR_H
#define SENSOR_GENERATOR_H

#include "Event.h"
#include <vector>
#include <string>

class SensorGenerator {
private:
    std::vector<std::string> device_ids;

public:
    SensorGenerator();
    IoTEvent generate_random_event();
};

#endif