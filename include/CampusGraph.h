#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

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
	
	public:
		// Constructor
		CampusGraph();
	
};