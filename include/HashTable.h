// Purpose: custom facility ID table with separate chaining. Author: Codex (AI assistance).
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>
#include <vector>
#include "FacilityRecords.h"
class HashTable {
private:
    struct HashNode { std::string key; Facility facility; };
    std::vector<std::list<HashNode>> table;
    std::size_t entries = 0, collisions = 0;
    // Polynomial string hash reduced after each character.
    std::size_t hashFunction(const std::string& key) const;
public:
    static constexpr std::size_t INITIAL_CAPACITY = 11;
    explicit HashTable(std::size_t capacity = INITIAL_CAPACITY);
    // Reject invalid/duplicate IDs; chains have no fixed entry limit.
    bool insert(const Facility& facility);
    // Normalize and search only the matching bucket.
    const Facility* find(const std::string& id) const;
    // Loading diagnostics.
    std::size_t getCapacity() const;
    std::size_t getEntries() const;
    std::size_t getCollisions() const;
};
#endif
