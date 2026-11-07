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

class HashTable {
private:
    struct HashNode {
      string key;
      Facility facility;
};
