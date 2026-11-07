#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Facility.h"

using namespace std;

class HashTable {
private:
    struct HashNode {
      string key;
      Facility facility;
    };

    vector <list<HashNode>> table;
    int capacity;
    int entries;
    int hashFunction const;

    public:

    int getCapacity();
    int getEntries;

};

#endif
