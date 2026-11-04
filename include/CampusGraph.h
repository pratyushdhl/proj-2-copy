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
		CampusGraph();
		
		// Get
		Building* GetBuildingByName(string name);
		void DisplayAdjacencyList();
		void ViewGraphStats();
		void GetReachableBuildings(Building* start);
		void GetShortestPath(Building* start, Building* end);
	
};

#endif