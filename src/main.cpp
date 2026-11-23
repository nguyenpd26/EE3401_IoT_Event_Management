#include <iostream>
#include <iomanip>
#include "../include/Event.h"
#include "../include/SensorGenerator.h"
#include "../include/RingBuffer.h"
#include "../include/EventQueue.h"
#include "../include/HashTable.h"

// Helper function to map severity enum to string for console output
std::string severity_to_string(EventSeverity severity) {
    switch (severity) {
        case EventSeverity::CRITICAL: return "CRITICAL";
        case EventSeverity::WARNING:  return "WARNING ";
        case EventSeverity::INFO:     return "INFO    ";
        default:                      return "UNKNOWN ";
    }
}

int main() {
    //Initialization & Configuration
    std::cout << "==================================================\n";
    std::cout << "    INITIALIZING IOT EVENT MANAGEMENT SYSTEM      \n";
    std::cout << "==================================================\n";

    SensorGenerator generator;
    RingBuffer ring_buffer(16, OverflowPolicy::DropNew);
    EventQueue event_queue;
    HashTable device_registry;

    if (ring_buffer.is_empty() && event_queue.is_empty()) {
        std::cout << "[SYSTEM] Memory structures initialized cleanly.\n\n";
    }

    const int TOTAL_SIMULATIONS = 20;

    //Pipeline Execution Loop
    for (int i = 1; i <= TOTAL_SIMULATIONS; i++) {
        std::cout << "--- Iteration " << i << " ---\n";

        IoTEvent generated_event = generator.generate_random_event();

        bool push_success = ring_buffer.push(generated_event);

        if (!push_success) {
            std::cout << "[INGESTION REJECTED] Buffer Full! Event dropped.\n";
            continue; 
        }

        IoTEvent extracted_event;
        if (ring_buffer.pop(extracted_event)) {
            event_queue.enqueue(extracted_event);
        }

        IoTEvent processing_event;
        if (event_queue.dequeue(processing_event)) {
            device_registry.insert_or_update(processing_event.device_id, processing_event);
            
            // Console Logging for Visual Feedback
            std::cout << "[PROCESSED] Device: " << processing_event.device_id 
                      << " | Val: " << std::fixed << std::setprecision(1) << processing_event.sensor_val 
                      << " | Sev: " << severity_to_string(processing_event.severity) << "\n";
        }
    }

    //Telemetry Reporting
    std::cout << "\n==================================================\n";
    std::cout << "           SYSTEM TELEMETRY SUMMARY               \n";
    std::cout << "==================================================\n";
    
    std::cout << "Total Packets Received : " << ring_buffer.get_total_packets_received() << "\n";
    std::cout << "Dropped Packets        : " << ring_buffer.get_dropped_packets() << "\n";
    std::cout << "Overwritten Packets    : " << ring_buffer.get_overwritten_packets() << "\n";
    std::cout << "Peak Buffer Usage      : " << ring_buffer.get_peak_buffer_usage() << " / " << ring_buffer.get_capacity() << "\n\n";

    // Test O(1) Lookup
    IoTEvent lookup_event;
    std::string test_key = "DEV_TEMP_001";
    if (device_registry.lookup(test_key, lookup_event)) {
        std::cout << "[REGISTRY] Latest state for " << test_key << ": " 
                  << lookup_event.sensor_val << "C (" 
                  << severity_to_string(lookup_event.severity) << ")\n";
    } else {
        std::cout << "[REGISTRY] No data received for " << test_key << " during this run.\n";
    }

    //Memory Verification
    if (ring_buffer.get_count() == 0 && event_queue.is_empty()) {
        std::cout << "[SYSTEM] Shutdown complete. No leaked events in pipeline.\n";
    }

    return 0;
}