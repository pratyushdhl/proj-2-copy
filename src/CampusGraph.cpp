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
	while (!fin.eof()) {
		getline(fin, inLine);
		// Ignore comments an blank lines
		if (inLine[0] != '#' && inLine != "") {
			// Ensure name is unused
			if (GetBuildingByName(inLine) == nullptr) {
				// Add to vector
				Building* building = new Building(inLine);
				buildings.push_back(building);
			}
		}
	}
	
	fin.close();
	
	// Load connections file data
	fin.open("../data/connections.txt");
	if (!fin.is_open()) {
		cout << "Failed to open connections.txt." << endl;
	}
	
	// Read connections line by line
	connectionCount = 0;
	string bnameA, bnameB;
	Building* buildingA;
	Building* buildingB;
	buildingA = nullptr;
	buildingB = nullptr;
	getline(fin, inLine);
	while (!fin.eof()) {
		// Ignore comments and blank lines
		if (inLine[0] != '#' && inLine != "") {
			// Split by bar
			stringstream ss(inLine);
			getline(ss, bnameA, '|');
			getline(ss, bnameB);
			// Find building objects
			buildingA = GetBuildingByName(bnameA);
			buildingB = GetBuildingByName(bnameB);
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
						connectionCount++;
						buildingA->AddAdjacent(buildingB);
						buildingB->AddAdjacent(buildingA);
					}
				}
			}
		}
		getline(fin, inLine);
	}
	
};

// Get building pointer using building name
Building* CampusGraph::GetBuildingByName(string name) {
	// Check each existing building
	for (int i = 0; i < buildings.size(); i++) {
		// Length equality check
		if (buildings[i]->GetName().length() == name.length()) {
			// String comparison with no case sense
			bool copy = true;
			for (int j = 0; j < buildings[i]->GetName().length(); j++) {
				if (tolower(buildings[i]->GetName()[j]) != tolower(name[j])) {
					copy = false;
					break;
				}
			}
			if (copy) return buildings[i];
		}
	}
	// No copy found
	return nullptr;
}

// Display adjacency list of graph 
void CampusGraph::DisplayAdjacencyList() {
	// Section header
	cout << "--------------- Adjacency List ---------------" << endl;
	// Check if buildings exist
	if (buildings.size() > 0) {
		// Display each building
		for (int i = 0; i < buildings.size(); i++) {
			cout << buildings[i]->GetName() << ':' << endl;
			// Check if adjacent exists
			if (buildings[i]->GetAdjacent().size() > 0) {
				// Display adjacency
				for (int j = 0; j < buildings[i]->GetAdjacent().size(); j++) {
					cout << "\t" << buildings[i]->GetAdjacent()[j]->GetName();
					if (j == buildings[i]->GetAdjacent().size()-1) {
						cout << "\n" << endl;
					}
					else {
						cout << ',' << endl;
					}
				}
			}
			else {
				// No adjacency
				cout << "\t(no connections)\n" << endl;
			}
		}
	}
	else {
		// No buildings exist
		cout << "No buildings exist." << endl;
	}
	cout << "----------------------------------------------" << endl;
}

void CampusGraph::ViewGraphStats() {
	// Find longest building name
	int nameLen = 0;
	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->GetName().length() > nameLen) {
			nameLen = buildings[i]->GetName().length();
		}
	}
	// Section header
	cout << "--------------- Graph counts and degrees ---------------\n" << endl;
	// Table header
	cout << left << setw(nameLen+1) << "Building" << "| Degree" << endl;
	for (int i = 0; i < nameLen+9; i++) {
		cout << '-';
	}
	cout << endl;
	// Display each building and degree
	for (int i = 0; i < buildings.size(); i++) {
		cout << setw(nameLen+1) << buildings[i]->GetName() << "| ";
		cout << buildings[i]->GetAdjacent().size() << endl;
	}
	for (int i = 0; i < nameLen+9; i++) {
		cout << '-';
	}
	// Building and connection count
	cout << "\nTotal buildings: " << buildings.size() << endl;
	cout << "Total connections: " << connectionCount << "\n" << endl;
	cout << "--------------------------------------------------------" << endl;
}

// Get reachable buildings using BFS
void CampusGraph::GetReachableBuildings(Building* start) {
	vector<Building*> visited;
	vector<int> distances;
	
	// Start at start and add it to vectors
	visited.push_back(start);
	distances.push_back(0);
	for (int i = 0; i < visited.size(); i++) {
		// Check each adjacent of ith building
		for (int j = 0; j < visited[i]->GetAdjacent().size(); j++) {
			// Check if visited
			bool isvisited = false;
			for (int k = 0; k < visited.size(); k++) {
				if (visited[k] == visited[i]->GetAdjacent()[j]) {
					isvisited = true;
					break;
				}
			}
			if (!isvisited) {
				// Unvisited; add to vectors
				visited.push_back(visited[i]->GetAdjacent()[j]);
				distances.push_back(distances[i]+1);
			}
		}
	}
	
	// Display results
	cout << "\nFrom " << start->GetName() << ":" << endl;
	for (int i = 0; i < visited.size(); i++) {
		cout << visited[i]->GetName() << " (distance " << distances[i] << ")" << endl;
	}
	cout << "\nReachable: " << visited.size() << " of " << buildings.size() << " buildings\n" << endl;
	
}

// Get shortest path using BFS
void CampusGraph::GetShortestPath(Building* start, Building* end) {
	
	vector<Building*> visited;
	vector<Building*> path;
	bool found = false;
	
	// Start at start and add it to vectors
	visited.push_back(start);
	for (int i = 0; i < visited.size() && !found; i++) {
		// Add ith building to path
		path.push_back(visited[i]);
		// Check each adjacent of ith building
		for (int j = 0; j < visited[i]->GetAdjacent().size(); j++) {
			// Check if end
			if (visited[i]->GetAdjacent()[j] == end) {
				// Ending building, end search
				path.push_back(visited[i]->GetAdjacent()[j]);
				found = true;
				break;
			}
			// Check if visited
			bool isvisited = false;
			for (int k = 0; k < visited.size(); k++) {
				if (visited[k] == visited[i]->GetAdjacent()[j]) {
					isvisited = true;
					break;
				}
			}
			if (!isvisited) {
				// Unvisited; add to visited
				visited.push_back(visited[i]->GetAdjacent()[j]);
			}
		}
	}
	
	// Path not found
	if (!found) {
		cout << "No path exists\n" << endl;
		return;
	}
	
	// Display path
	cout << "\n" << start->GetName() << " to " << end->GetName() << ":" << endl;
	for (int i = 0; i < path.size(); i++) {
		cout << path[i]->GetName() << endl;
	}
	cout << "Number of connections: " << path.size()-1 << "\n" << endl;
	
}