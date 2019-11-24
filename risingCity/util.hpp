#include "building.hpp"
#include <fstream>
void readCommand(string command, string *arguments);
bool constructBuilding();
void insertBuilding(minHeap *heapCity, redBlackTree *rbtCity, int buildingNum, int totalTime);
void printBuilding(int buildingNum);
void printBuilding(int buildingNum1, int buildingNum2);