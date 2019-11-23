#include "building.hpp"
#include "redBlackTree.hpp"
#include "minHeap.hpp"
#include "util.hpp"
int calSubstrLen(string origin, string delimiter1, string delimiter2){
    return origin.find(delimiter2) - origin.find(delimiter1) - 1;
}
string getSubstr(string origin, string delimiter1, string delimiter2){
    return origin.substr(origin.find(delimiter1)+1, calSubstrLen(origin, delimiter1, delimiter2));
}
void readCommand(string command, string *arguments){
    arguments[0] = getSubstr(command, ":-]", ":");
    arguments[1] = getSubstr(command, " ", "(");
    if(command.find(",") != string::npos){
        arguments[2] = getSubstr(command, "(", ",");
        arguments[3] = getSubstr(command, ",", ")");
    }
    else{
        arguments[2] = getSubstr(command, "(", ")");
    }
}
bool constructBuild(){
    bool workingOnBuilding = true;
    return workingOnBuilding;
}
void insertBuilding(minHeap *heapCity, redBlackTree *rbtCity, int buildingNum, int totalTime){
    building newBuilding;
    newBuilding.buildingNum = buildingNum;
    newBuilding.executedTime = 0;
    newBuilding.totalTime = totalTime;
    heapCity->insertKey(newBuilding);
    //rbtCity.insert(newBuilding);
}
/*
void printBuilding(int buildingNum);
void printBuilding(int buildingNum1, int buildingNum2);
*/