#include "../include/HashTable.h" // <-- FIXED: Relative path for

// Constructor
HashTable::HashTable() {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

// Destructor
HashTable::~HashTable() {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
}

// Hash Function - DJB2
size_t HashTable::hash_function(const std::string& key) const {
    size_t value = 5381;

    for (unsigned char ch : key) {
        value = ((value << 5) + value) + ch;
    }

    return value % TABLE_SIZE;
}

// Insert or Update
void HashTable::insert_or_update(
    const std::string& key,
    const IoTEvent& event
) {
    if (key.empty()) {
        return;
    }

    size_t index = hash_function(key);

    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            current->last_event = event;
            return;
        }

        current = current->next;
    }

    HashNode* new_node = new HashNode(key, event);
    new_node->next = table[index];
    table[index] = new_node;
}

// Lookup
bool HashTable::lookup(
    const std::string& key,
    IoTEvent& out_event
) const {
    if (key.empty()) {
        return false;
    }

    size_t index = hash_function(key);

    const HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            out_event = current->last_event;
            return true;
        }

        current = current->next;
    }

    return false;
}
