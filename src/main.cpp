#include <iostream>
#include "Event.h"
#include "RingBuffer.h"
#include "EventQueue.h"
#include "HashTable.h"

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   IoT Event Management System - Driver Skeleton  " << std::endl;
    std::cout << "==================================================" << std::endl;

    // 1. Khởi tạo một dữ liệu sự kiện mẫu để test
    IoTEvent test_event{
        "DEV_TEMP_001",
        1700000000,
        1,
        45.2f,
        EventSeverity::CRITICAL
    };

    // 2. In thông số kiểm tra
    std::cout << "[SUCCESS] Build pipeline setup is working!" << std::endl;
    std::cout << "[DATA TEST] Device ID : " << test_event.device_id << std::endl;
    std::cout << "[DATA TEST] Sensor Val: " << test_event.value << " degC" << std::endl;
    std::cout << "[DATA TEST] Severity  : " 
              << (test_event.severity == EventSeverity::CRITICAL ? "CRITICAL" : "NORMAL") 
              << std::endl;

    std::cout << "==================================================" << std::endl;
    return 0;
}