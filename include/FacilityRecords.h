#ifndef FACILITY_H
#define FACILITY_H

#include <string>

class Facility {
private:
    std::string id_;
    std::string name_;
    std::string building_;
    std::string category_;

public:
    Facility() = default;
    
    Facility(const std::string& id, const std::string& name, const std::string& building, const std::string& category)
        : id_(id), name_(name), building_(building), category_(category) {}

    std::string getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getBuilding() const { return building_; }
    std::string getCategory() const { return category_; }
};

#endif
