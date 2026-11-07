// Purpose: implement custom ID hashing and chains. Author: Codex (AI assistance).
#include "../include/HashTable.h"
#include "../include/FileUtils.h"
// A zero capacity argument uses the documented initial capacity.
HashTable::HashTable(std::size_t capacity) : table(capacity ? capacity : INITIAL_CAPACITY) {}
std::size_t HashTable::hashFunction(const std::string& key) const {
    std::size_t hash = 0;
    for (unsigned char c : key) hash = (31 * hash + c) % table.size();
    return hash;
}
// Count collisions only for accepted insertions into nonempty buckets.
bool HashTable::insert(const Facility& facility) {
    const std::string key = Input::key(facility.getID());
    if (!validFacilityID(key) || find(key)) return false;
    auto& bucket = table[hashFunction(key)];
    if (!bucket.empty()) ++collisions;
    bucket.push_back({key, facility});
    ++entries;
    return true;
}
const Facility* HashTable::find(const std::string& id) const {
    const std::string key = Input::key(id);
    for (const auto& node : table[hashFunction(key)])
        if (node.key == key) return &node.facility;
    return nullptr;
}
// Read diagnostics without modifying table state.
std::size_t HashTable::getCapacity() const { return table.size(); }
std::size_t HashTable::getEntries() const { return entries; }
std::size_t HashTable::getCollisions() const { return collisions; }
