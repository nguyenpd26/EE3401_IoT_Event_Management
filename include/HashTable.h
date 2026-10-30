#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include "Event.h"

struct HashNode {
    std::string key;      // device_id
    IoTEvent last_event;  // last recorded event status
    HashNode* next;
    HashNode(const std::string& k, const IoTEvent& ev) 
        : key(k), last_event(ev), next(nullptr) {}
};

class HashTable {
private:
    static const size_t TABLE_SIZE = 31;
    HashNode* table[TABLE_SIZE];
    size_t hash_function(const std::string& key) const;

public:
    HashTable();
    ~HashTable();
    void insert_or_update(const std::string& key, const IoTEvent& event);
    bool lookup(const std::string& key, IoTEvent& out_event) const;
};

#endif