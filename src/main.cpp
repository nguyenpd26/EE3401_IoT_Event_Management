#include <iostream>
#include "Event.h"
#include "SensorGenerator.h"

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   IoT Event Management System - Generator Test   " << std::endl;
    std::cout << "==================================================" << std::endl;

    SensorGenerator generator;

    for (int i = 1; i <= 5; ++i) {
        IoTEvent ev = generator.generate_random_event();
        std::cout << "Event #" << i 
                  << " | Device: " << ev.device_id 
                  << " | Val: " << ev.value 
                  << " | Severity: " << static_cast<int>(ev.severity) 
                  << std::endl;
    }

    std::cout << "==================================================" << std::endl;
    return 0;
}