// Purpose: campus graph declarations. Original graph: Ethan Rhodes; M1 updates: Codex (AI assistance).
#ifndef CAMPUS_GRAPH
#define CAMPUS_GRAPH

#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

class Building {

	private:
		string name;
		vector<Building*> adjacent;
		
	public:
		// Constructors
		Building();
		Building(string name);
		
		// Get
		string GetName();
		vector<Building*> GetAdjacent();
		
		// Set
		void SetName(string name);
		void AddAdjacent(Building* building);
	
};

class CampusGraph {
	
	private:
		vector<Building*> buildings;
		int connectionCount;
	
	public:
		// Constructor
		CampusGraph(string dataPath);
		// Buildings are owned by this graph, so copying is disabled.
		~CampusGraph();
		CampusGraph(const CampusGraph&) = delete;
		CampusGraph& operator=(const CampusGraph&) = delete;
		
		// Get
		Building* GetBuildingByName(string name);
		void DisplayAdjacencyList();
		void ViewGraphStats();
		void GetReachableBuildings(Building* start);
		void GetShortestPath(Building* start, Building* end);
	
};

#endif