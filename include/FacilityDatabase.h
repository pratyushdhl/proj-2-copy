// Purpose: load and query accepted facilities. Author: Codex (AI assistance).
#ifndef FACILITY_DATABASE_H
#define FACILITY_DATABASE_H
#include "CampusGraph.h"
#include "HashTable.h"
class FacilityDatabase {
    std::vector<Facility> facilities;
    HashTable ids;
public:
    // Validate building references before accepting records.
    FacilityDatabase(const std::string& directory, CampusGraph& graph);
    // Display in file order or search by the custom ID table.
    void displayAll() const;
    void searchID(const std::string& input) const;
};
#endif
