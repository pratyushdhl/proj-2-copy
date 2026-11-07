// Purpose: facility values and ID validation. Author: Codex (AI assistance).
#include "../include/FacilityRecords.h"
#include "../include/FileUtils.h"
Facility::Facility(std::string i, std::string n, std::string b, std::string c)
    : name(n), id(Input::key(i)), building(b), category(c) {}
// Read-only access to stored fields.
std::string Facility::getName() const { return name; }
std::string Facility::getID() const { return id; }
std::string Facility::getBuilding() const { return building; }
std::string Facility::getCategory() const { return category; }
// Print one accepted record.
void Facility::display() const {
    std::cout << id << " | " << name << " | " << building << " | " << category << '\n';
}
// Validate after the caller normalizes the ID.
bool validFacilityID(const std::string& id) {
    if (id.size() != 4 || id[0] != 'F') return false;
    for (std::size_t i = 1; i < id.size(); ++i)
        if (id[i] < '0' || id[i] > '9') return false;
    return true;
}
