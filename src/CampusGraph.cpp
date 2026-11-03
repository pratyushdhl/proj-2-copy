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
vector<Building*> Building::GetAdjacent() {
	return adjacent;
}

// Set
void Building::SetName(string name) {
	this->name = name;
}
void Building::AddAdjacent(Building* building) {
	adjacent.push_back(building);
}

// ----- CampusGraph -----
// Constructor
CampusGraph::CampusGraph() {
	
	// Load buildings file data
	ifstream fin;
	fin.open("../data/buildings.txt");
	if (!fin.is_open()) {
		cout << "Failed to open buildings.txt." << endl;
	}
	
	// Read buildings line by line
	string inLine;
	getline(fin, inLine);
	while (!fin.eof()) {
		// Ignore comments
		if (inLine[0] != '#') {
			// Ensure name is unused
			bool used = false;
			for (int i = 0; i < buildings.size(); i++) {
				// Length equality check
				if (buildings[i]->GetName().length() == inLine.length()) {
					// String comparison with no case sense
					bool copy = true;
					for (int j = 0; j < buildings[i]->GetName().length(); j++) {
						if (buildings[i]->GetName()[j] != inLine[j]) {
							copy = false;
						}
					}
					if (copy) used = true;
				}
			}
			if (!used) {
				// Add to vector
				Building* building = new Building(inLine);
				buildings.push_back(building);
			}
		}
		getline(fin, inLine);
	}
	
	fin.close();
	
	// Load connections file data
	fin.open("../data/connections.txt");
	if (!fin.is_open()) {
		cout << "Failed to open connections.txt." << endl;
	}
	
	// Read connections line by line
	string bnameA, bnameB;
	Building* buildingA;
	Building* buildingB;
	buildingA = nullptr;
	buildingB = nullptr;
	getline(fin, inLine);
	while (!fin.eof()) {
		// Ignore comments
		if (inLine[0] != '#') {
			// Split by bar
			stringstream ss(inLine);
			getline(ss, bnameA, '|');
			getline(ss, bnameB);
			// Find building objects
			buildingA = nullptr;
			buildingB = nullptr;
			for (int i = 0; i < buildings.size(); i++) {
				// Length equality check
				if (buildings[i]->GetName().length() == bnameA.length()) {
					// String comparison with no case sense
					bool copy = true;
					for (int j = 0; j < buildings[i]->GetName().length(); j++) {
						if (buildings[i]->GetName()[j] != bnameA[j]) {
							copy = false;
						}
					}
					if (copy) {
						buildingA = buildings[i];
						break;
					}
				}
			}
			for (int i = 0; i < buildings.size(); i++) {
				// Length equality check
				if (buildings[i]->GetName().length() == bnameB.length()) {
					// String comparison with no case sense
					bool copy = true;
					for (int j = 0; j < buildings[i]->GetName().length(); j++) {
						if (buildings[i]->GetName()[j] != bnameB[j]) {
							copy = false;
						}
					}
					if (copy) {
						buildingB = buildings[i];
						break;
					}
				}
			}
			// Ensure both buildings found
			if (buildingA != nullptr && buildingB != nullptr) {
				// Check if self connection
				if (buildingA != buildingB) {
					// Check if connection exists already
					bool copy = false;
					for (int i = 0; i < buildingA->GetAdjacent().size(); i++) {
						if (buildingA->GetAdjacent()[i] == buildingB) {
							copy = true;
							break;
						}
					}
					if (!copy) {
						buildingA->AddAdjacent(buildingB);
						buildingB->AddAdjacent(buildingA);
					}
				}
			}
		}
		getline(fin, inLine);
	}
	
	for (int i = 0; i < buildings.size(); i++) {
		cout << buildings[i]->GetName() << endl;
		for (int j = 0; j < buildings[i]->GetAdjacent().size(); j++) {
			cout << "\t" << buildings[i]->GetAdjacent()[j]->GetName() << endl;
		}
	}
	
};