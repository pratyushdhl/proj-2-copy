#include "../include/CampusGraph.h"

using namespace std;

int main() {
	
	CampusGraph campusGraph;
	
	// Menu
	int choice;
	bool menuActive = true;
	while (menuActive) {
		
		// Display options
		cout << "1. View all facilities" << endl;
		cout << "2. Search facility by ID" << endl;
		cout << "3. Search facility by name" << endl;
		cout << "4. Search facility by category" << endl;
		cout << "5. View campus graph" << endl;
		cout << "6. Display graph counts and degrees" << endl;
		cout << "7. Find reachable buildings (BFS)" << endl;
		cout << "8. Find shortest path (BFS)" << endl;
		cout << "9. Add department" << endl;
		cout << "10. Search department" << endl;
		cout << "11. Display department hierarchy" << endl;
		cout << "12. Preorder traversal" << endl;
		cout << "13. Postorder traversal" << endl;
		cout << "14. Level-order traversal" << endl;
		cout << "15. Department statistics" << endl;
		cout << "16. Facility category report" << endl;
		cout << "17. Graph connectivity report" << endl;
		cout << "18. Exit" << endl;
		
		// Get choice
		cout << "\nEnter option(1-18): ";
		cin >> choice;
		while (choice < 1 || choice > 18) {
			cout << "\nInvalid input.\nEnter option(1-18): ";
			cin >> choice;
		}
		cout << endl;
		
		// Variables used in cases
		string name;
		Building* building = nullptr;
		Building* building2 = nullptr;
		
		// Process choice
		switch (choice) {
			case 1:
				// View all facilities
				break;
			case 2:
				// Search facility by ID
				break;
			case 3:
				// Search facility by name
				break;
			case 4:
				// Search facility by category
				break;
			case 5:
				// View campus graph
				campusGraph.DisplayAdjacencyList();
				break;
			case 6:
				// Display graph counts and degrees
				campusGraph.ViewGraphStats();
				break;
			case 7:
				// Find reachable buildings (BFS)
				cout << "Enter start building: ";
				cin.ignore();
				getline(cin, name);
				building = campusGraph.GetBuildingByName(name);
				if (building == nullptr) {
					// Invalid building, return to menu 
					cout << "\nInvalid building name.\n" << endl;
					break;
				}
				campusGraph.GetReachableBuildings(building);
				break;
			case 8:
				// Find shortest path (BFS)
				cout << "Enter start building: ";
				cin.ignore();
				getline(cin, name);
				building = campusGraph.GetBuildingByName(name);
				if (building == nullptr) {
					// Invalid building, return to menu 
					cout << "\nInvalid building name.\n" << endl;
					break;
				}
				cout << "Enter destination building: ";
				getline(cin, name);
				building2 = campusGraph.GetBuildingByName(name);
				if (building2 == nullptr) {
					// Invalid building, return to menu 
					cout << "\nInvalid building name.\n" << endl;
					break;
				}
				campusGraph.GetShortestPath(building, building2);
				break;
			case 9:
				// Add department
				break;
			case 10:
				// Search department
				break;
			case 11:
				// Display department hierarchy*
				break;
			case 12:
				// Preorder traversal**
				break;
			case 13:
				// Postorder traversal
				break;
			case 14:
				// Level-order traversal
				break;
			case 15:
				// Department statistics
				break;
			case 16:
				// Facility category report
				break;
			case 17:
				// Graph connectivity report
				break;
			case 18:
				// Exit
				menuActive = false;
				break;
			default:
				// Default case
				cout << "Main.cpp switch case invalid case." << endl;
		}
		
	}
	
	return 0;
}