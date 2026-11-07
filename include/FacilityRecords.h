#ifndef FACILITY_RECORDS
#define FACILITY_RECORDS

#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

class Facility {
private:
  string name;
  string id;
  string building;
  string category;

public:
  Facility(string i, string n, string b, string c);

string getName() const;
string getID () const;
string getBuilding const;
string getCategory() const;

void display() const;

};

#endif


