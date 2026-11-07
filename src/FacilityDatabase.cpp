// Purpose: facility loading, display, ID search. Author: Codex (AI assistance).
#include "../include/FacilityDatabase.h"
#include "../include/FileUtils.h"
FacilityDatabase::FacilityDatabase(const std::string& directory, CampusGraph& graph) {
    Input::load(directory, "facilities.txt", [&](const std::vector<std::string>& f) -> std::string {
        if (!Input::validFields(f, 4)) return "expected four nonempty fields";
        const std::string id = Input::key(f[0]);
        if (!validFacilityID(id)) return "invalid ID: expected F followed by exactly three digits";
        Building* building = graph.GetBuildingByName(f[2]);
        if (!building) return "unknown building: " + f[2];
        if (ids.find(id)) return "duplicate facility ID: " + id;
        std::string category = f[3];
        for (const auto& previous : facilities)
            if (Input::key(previous.getCategory()) == Input::key(category)) {
                category = previous.getCategory();
                break;
            }
        Facility facility(id, f[1], building->GetName(), category);
        ids.insert(facility);
        facilities.push_back(facility);
        return "";
    }, false);
    std::cout << " (hash capacity " << ids.getCapacity() << ", entries " << ids.getEntries()
              << ", collisions " << ids.getCollisions() << ")\n";
}
// Preserve the accepted file order, including duplicate names with different IDs.
void FacilityDatabase::displayAll() const {
    if (facilities.empty()) std::cout << "No facilities available.\n";
    for (const auto& facility : facilities) facility.display();
    std::cout << "Total facilities: " << facilities.size() << '\n';
}
// Distinguish invalid format, valid but absent, and found.
void FacilityDatabase::searchID(const std::string& input) const {
    const std::string id = Input::key(input);
    if (!validFacilityID(id)) {
        std::cout << "Invalid format: an ID is F followed by exactly three digits.\n";
        return;
    }
    const Facility* facility = ids.find(id);
    if (facility) facility->display();
    else std::cout << "Not found: no facility with ID " << id << '\n';
}
