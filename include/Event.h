#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <cstdint>

// Mức độ nghiêm trọng của sự kiện IoT
enum class EventSeverity {
    INFO,
    WARNING,
    CRITICAL
};

// Cấu trúc dữ liệu gói tin sự kiện IoT
struct IoTEvent {
    std::string device_id;     // ID thiết bị (dùng làm khóa cho Hash Table)
    uint64_t timestamp;        // Thời gian ghi nhận (Unix timestamp ms)
    uint8_t event_type;        // Loại cảm biến (1: Nhiệt độ, 2: Áp suất, 3: Chuyển động)
    float value;               // Giá trị đọc từ cảm biến
    EventSeverity severity;    // Mức độ ưu tiên để lọc/xử lý
};

#endif // EVENT_H