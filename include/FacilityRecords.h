// Purpose: facility values and ID validation. Author: Codex (AI assistance).
#ifndef FACILITY_RECORDS
#define FACILITY_RECORDS
#include <string>
class Facility {
private:
    std::string name, id, building, category;
public:
    // Store a normalized ID and accepted display spellings.
    Facility(std::string i, std::string n, std::string b, std::string c);
    // Read-only field access.
    std::string getName() const;
    std::string getID() const;
    std::string getBuilding() const;
    std::string getCategory() const;
    // Display every field on one line.
    void display() const;
};
// Validate the normalized F followed by exactly three digits format.
bool validFacilityID(const std::string& id);
#endif
