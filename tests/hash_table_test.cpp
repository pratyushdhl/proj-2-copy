// Purpose: verify collision accounting and growing chains. Author: Codex (AI assistance).
#include "../include/HashTable.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
// Exercise public operations without recomputing the hash implementation.
int main() {
    HashTable table;
    assert(table.insert(Facility("f001", "Original", "Library", "Library")));
    assert(table.insert(Facility("F013", "Collision", "Library", "Library")));
    assert(table.getEntries() == 2 && table.getCollisions() == 1);
    assert(!table.insert(Facility(" F001 ", "Replacement", "Library", "Other")));
    assert(table.getEntries() == 2 && table.getCollisions() == 1);
    assert(table.find(" f001 ")->getName() == "Original");
    assert(table.find("F013")->getName() == "Collision");
    assert(!table.find("F999"));
    assert(!table.insert(Facility("BAD", "Invalid", "Library", "Other")));
    assert(table.getEntries() == 2 && table.getCollisions() == 1);
    for (int id = 100; id < 150; ++id) {
        std::ostringstream key;
        key << 'F' << std::setw(3) << std::setfill('0') << id;
        assert(table.insert(Facility(key.str(), "Growing chain", "Library", "Library")));
        assert(table.find(key.str()));
    }
    assert(table.getEntries() == 52 && table.getCapacity() == 11);
    std::cout << "Test 15: direct custom hash-table operations\n"
              << "Input: F001, F013, duplicate f001, invalid BAD, then F100-F149\n"
              << "Expected: two entries / one collision before and after duplicate; original retained; "
              << "invalid rejected; 52 entries in capacity 11; all lookups found\n"
              << "Actual: every assertion passed; chains grew beyond capacity without rejecting valid keys\n"
              << "Result: PASS\n";
}
