// Purpose: campus graph and BFS. Original graph: Ethan Rhodes; M1 updates: Codex (AI assistance).
#include "../include/CampusGraph.h"
#include "../include/FileUtils.h"
#include <algorithm>

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
CampusGraph::CampusGraph(string dataPath) : connectionCount(0) {
    Input::load(dataPath, "buildings.txt", [&](const vector<string>& f) -> string {
        if (!Input::validFields(f, 1)) return "expected one nonempty field";
        if (GetBuildingByName(f[0])) return "duplicate building: " + f[0];
        buildings.push_back(new Building(f[0]));
        return "";
    });
    Input::load(dataPath, "connections.txt", [&](const vector<string>& f) -> string {
        if (!Input::validFields(f, 2)) return "expected two nonempty fields";
        Building* a = GetBuildingByName(f[0]);
        Building* b = GetBuildingByName(f[1]);
        if (!a) return "unknown building: " + f[0];
        if (!b) return "unknown building: " + f[1];
        if (a == b) return "self-connection: " + f[0];
        const auto neighbors = a->GetAdjacent();
        if (find(neighbors.begin(), neighbors.end(), b) != neighbors.end())
            return "duplicate connection: " + f[0] + " | " + f[1];
        a->AddAdjacent(b);
        b->AddAdjacent(a);
        ++connectionCount;
        return "";
    });
}

// Release the graph's owned buildings; adjacency pointers are non-owning.
CampusGraph::~CampusGraph() {
    for (Building* building : buildings) delete building;
}

// Match ASCII case and outer whitespace, preserving internal spaces.
Building* CampusGraph::GetBuildingByName(string name) {
    const string key = Input::key(name);
    for (Building* building : buildings)
        if (Input::key(building->GetName()) == key) return building;
    return nullptr;
}

// Display adjacency list of graph 
void CampusGraph::DisplayAdjacencyList() {
	// Section header
	cout << "--------------- Adjacency List ---------------" << endl;
	// Check if buildings exist
	if (buildings.size() > 0) {
		// Display each building
		for (size_t i = 0; i < buildings.size(); i++) {
			cout << buildings[i]->GetName() << ':' << endl;
			// Check if adjacent exists
			if (buildings[i]->GetAdjacent().size() > 0) {
				// Display adjacency
				for (size_t j = 0; j < buildings[i]->GetAdjacent().size(); j++) {
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
	size_t nameLen = 8;
	for (size_t i = 0; i < buildings.size(); i++) {
		if (buildings[i]->GetName().length() > nameLen) {
			nameLen = buildings[i]->GetName().length();
		}
	}
	// Section header
	cout << "--------------- Graph counts and degrees ---------------\n" << endl;
	// Table header
	cout << left << setw(nameLen+1) << "Building" << "| Degree" << endl;
	for (size_t i = 0; i < nameLen+9; i++) {
		cout << '-';
	}
	cout << endl;
	// Display each building and degree
	for (size_t i = 0; i < buildings.size(); i++) {
		cout << setw(nameLen+1) << buildings[i]->GetName() << "| ";
		cout << buildings[i]->GetAdjacent().size() << endl;
	}
	for (size_t i = 0; i < nameLen+9; i++) {
		cout << '-';
	}
	// Building and connection count
	cout << "\nTotal buildings: " << buildings.size() << endl;
	cout << "Total connections: " << connectionCount << "\n" << endl;
	cout << "--------------------------------------------------------" << endl;
}

// Get reachable buildings using BFS
void CampusGraph::GetReachableBuildings(Building* start) {
    if (!start) {
        cout << "Unknown starting building.\n";
        return;
    }
    vector<Building*> visited;
    queue<pair<Building*, int>> pending;
    visited.push_back(start);
    pending.push({start, 0});
    cout << "\nFrom " << start->GetName() << ":\n";
    while (!pending.empty()) {
        const auto current = pending.front();
        pending.pop();
        cout << current.first->GetName() << " (distance " << current.second << ")\n";
        for (Building* neighbor : current.first->GetAdjacent()) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                // Mark on enqueue so cycles never enqueue a vertex twice.
                visited.push_back(neighbor);
                pending.push({neighbor, current.second + 1});
            }
        }
    }
    cout << "\nReachable: " << visited.size() << " of " << buildings.size() << " buildings\n\n";
}

// Get shortest path using BFS
void CampusGraph::GetShortestPath(Building* start, Building* end) {
	
	vector<Building*> visited;
	vector<Building*> path;
	bool found = false;
	
	// Case start = end
	if (start == end) {
		path.push_back(start);
		found = true;
	}
	
	// Start at start and add it to vectors
	visited.push_back(start);
	for (size_t i = 0; i < visited.size() && !found; i++) {
		// Add ith building to path
		path.push_back(visited[i]);
		// Check each adjacent of ith building
		for (size_t j = 0; j < visited[i]->GetAdjacent().size(); j++) {
			// Check if end
			if (visited[i]->GetAdjacent()[j] == end) {
				// Ending building, end search
				path.push_back(visited[i]->GetAdjacent()[j]);
				found = true;
				break;
			}
			// Check if visited
			bool isvisited = false;
			for (size_t k = 0; k < visited.size(); k++) {
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
	for (size_t i = 0; i < path.size(); i++) {
		cout << path[i]->GetName() << endl;
	}
	cout << "Number of connections: " << path.size()-1 << "\n" << endl;
	
}