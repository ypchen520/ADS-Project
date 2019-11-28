#ifndef UTIL_HPP_
#define UTIL_HPP_

#include "building.hpp"
#include <fstream>
void readCommand(string command, string *arguments);
void selectBuilding(minHeap *heapCity, building *selectedBuilding);
bool constructBuilding(minHeap *heapCity, redBlackTree *rbtCity, building *selectedBuilding, int *constructingTime, int globalTime, ofstream& outputFile, bool *specialFlag);
void insertBuilding(minHeap *heapCity, redBlackTree *rbtCity, int buildingNum, int totalTime, building* rbtBuilding);
void printInorder(node *printingRoot, int buildingNum1, int buildingNum2, int selectedNum, int constructingTime, ofstream& outputFile, bool *delimiterFlag);
void printBuilding(int buildingNum, redBlackTree *rbtCity, int constructingTime, building *selectedBuilding, ofstream& outputFile);
void printBuilding(int buildingNum1, int buildingNum2, redBlackTree *rbtCity, int constructingTime, building *selectedBuilding, ofstream& outputFile);
#endif