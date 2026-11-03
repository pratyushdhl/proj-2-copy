#include "../include/CampusGraph.h"

using namespace std;

// ----- Building -----
// Constructors
Building::Building() {
	this->name = "";
}

Building::Building(string name) {
	this->name = name;
}

// Get
string Building::GetName() {
	return name;
}
vector<Building> Building::GetAdjacent() {
	return adjacent;
}

// Set
void Building::SetName(string name) {
	this->name = name;
}
void Building::AddAdjacent(Building building) {
	adjacent.push_back(building);
}

// ----- CampusGraph -----
// Constructor
CampusGraph::CampusGraph() {
	
	// Load buildings file data
	ifstream bfile;
	bfile.open("../data/buildings.txt");
	if (!bfile.is_open()) {
		cout << "Failed to open buildings.txt." << endl;
	}
	
	// Read buildings line by line
	string bName;
	getline(bfile, bName);
	while (!bfile.eof()) {
		// Ignore comments
		if (bName[0] != '#') {
			// Ensure name is unused
			bool used = false;
			for (int i = 0; i < buildings.size(); i++) {
				// Length equality check
				if (buildings[i].GetName().length() == bName.length()) {
					// String comparison with no case sense
					bool copy = true;
					for (int j = 0; j < buildings[i].GetName().length(); j++) {
						if (buildings[i].GetName()[j] != bName[j]) {
							copy = false;
						}
					}
					if (copy) used = true;
				}
			}
			if (!used) {
				// Add to vector
				Building building(bName);
				buildings.push_back(building);
			}
		}
		getline(bfile, bName);
	}
	
};