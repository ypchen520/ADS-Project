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
void selectBuilding(minHeap *heapCity, building *selectedBuilding){
    //get the building with lowest executedTime
    *selectedBuilding = heapCity->extractMin();
    //return selectedBuilding;
}
bool constructBuilding(minHeap *heapCity, redBlackTree *rbtCity, building *selectedBuilding, int *constructingTime, int globalTime, ofstream& outputFile, bool *specialFlag){
    bool workingOnBuilding = false;
    //bool contructingFlag = true;
    int bn = selectedBuilding->buildingNum;
    int tt = selectedBuilding->totalTime;
    selectedBuilding->executedTime++;
    globalTime++;
    *constructingTime += 1;
    if(selectedBuilding->executedTime == tt){
        rbtCity->updateTime(bn, *constructingTime);
        //outputFile << "(" << bn << "," << globalTime << ")" << endl;
        *specialFlag = true;
        //rbtCity->rbtDelete(bn);
        *constructingTime = 0;
    } 
    else if(*constructingTime == 5){
        heapCity->insertKey(*selectedBuilding);
        int time = *constructingTime;
        rbtCity->updateTime(bn, time);
        //rbtCity->treeSearch(bn)->data.executedTime += constructingTime;
        *constructingTime = 0;
    }
    else
        workingOnBuilding = true;
    return workingOnBuilding;
}
void insertBuilding(minHeap *heapCity, redBlackTree *rbtCity, int buildingNum, int totalTime, building *rbtBuilding){
    building newBuilding;
    //Heap
    newBuilding.buildingNum = buildingNum;
    newBuilding.executedTime = 0;
    newBuilding.totalTime = totalTime;
    heapCity->insertKey(newBuilding);
    //RBT
    rbtBuilding->buildingNum = buildingNum;
    rbtBuilding->executedTime = 0;
    rbtBuilding->totalTime = totalTime;
    rbtCity->rbtInsert(rbtBuilding);
}

void printInorder(node *printingRoot, int buildingNum1, int buildingNum2, int selectedNum, int constructingTime, ofstream& outputFile, bool *delimiterFlag){
    if(printingRoot == nullptr)
        return;
    int rootBuildingNum = printingRoot->data->buildingNum;
    int rootExecutedTime =  printingRoot->data->executedTime;
    int rootTotalTime=  printingRoot->data->totalTime;
    if(rootBuildingNum == selectedNum){
        rootExecutedTime += constructingTime;
    }
    printInorder(printingRoot->left, buildingNum1, buildingNum2, selectedNum, constructingTime, outputFile, delimiterFlag);
    if(rootBuildingNum > buildingNum1 && rootBuildingNum < buildingNum2){
        if(*delimiterFlag)
            outputFile << ","; 
        outputFile << "(" << rootBuildingNum << "," << rootExecutedTime << "," << rootTotalTime << ")";
        *delimiterFlag = true;
    }
    else if(rootBuildingNum == buildingNum1){
        outputFile << "(" << rootBuildingNum << "," << rootExecutedTime << "," << rootTotalTime << ")"; 
        *delimiterFlag = true;
    }
    else if(rootBuildingNum == buildingNum2){
        outputFile << "," << "(" << rootBuildingNum << "," << rootExecutedTime << "," << rootTotalTime << ")" << endl;
        *delimiterFlag = false;
    }
    printInorder(printingRoot->right, buildingNum1, buildingNum2, selectedNum, constructingTime, outputFile, delimiterFlag);
}

void printBuilding(int buildingNum, redBlackTree *rbtCity, int constructingTime, building *selectedBuilding, ofstream& outputFile){
    node *printingNode = rbtCity->treeSearch(buildingNum);
    if(printingNode != nullptr){
        int executedTime = printingNode->data->executedTime;
        int totalTime = printingNode->data->totalTime;
        if(buildingNum == selectedBuilding->buildingNum)
            executedTime += constructingTime;
        outputFile << "(" << buildingNum << "," << executedTime << "," << totalTime << ")" << endl;
    }
    else
        outputFile << "(" << 0 << "," << 0 << "," << 0 << ")" << endl;        
}

void printBuilding(int buildingNum1, int buildingNum2, redBlackTree *rbtCity, int constructingTime, building *selectedBuilding, ofstream& outputFile){
    int selectedNum = selectedBuilding->buildingNum;
    node *printingRoot = rbtCity->printingRootSearch(buildingNum1, buildingNum2);
    bool delimiterFlag = false;
    if(printingRoot != nullptr){
        printInorder(printingRoot, buildingNum1, buildingNum2, selectedNum, constructingTime, outputFile, &delimiterFlag);
        if(delimiterFlag)
            outputFile << endl;
    }
    else{
        outputFile << "(" << 0 << "," << 0 << "," << 0 << ")" << endl;  
    }
}
