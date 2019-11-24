#include <iostream>
#include "minHeap.hpp"
#include "redBlackTree.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char *argv[]){
    int globalTime = 0;
    bool workingOnBuilding = false;
    bool fileFlag = false;
    bool readFileLine = true;
    int commandTime = -1;
    int constructingTime = 0;
    buidling selectedBuilding;
    minHeap *heapCity = new minHeap(2000);
    redBlackTree *rbtCity = new redBlackTree();
    string command;
    string *arguments = new string[4];
    ifstream inputFile(argv[1]);
    if (inputFile.is_open())
    {
        do{
            if(readFileLine)
                fileFlag = getline(inputFile,command);
                readCommand(command, arguments);
                commandTime = stoi(arguments[0]);
            if(fileFlag){
                cout << command <<endl;
                //do command
                //commandTime should not be smaller than globalTime
                if(commandTime == globalTime){
                    if(arguments[1][0] == 'I'){
                        cout << arguments[1] <<endl;
                        insertBuilding(heapCity, rbtCity, stoi(arguments[2]), stoi(arguments[3]));
                    }
                    else if(arguments[1][0] == 'P'){
                        cout << arguments[3] <<endl;
                        cout << arguments[1] <<endl;
                    }
                    cout << "heap root: " << heapCity->getMin().buildingNum << endl;
                    cout << "rbt root: " << rbtCity->treeSearch(stoi(arguments[2]))->data.buildingNum << endl;
                    readFileCommand = true;
                }
                else if(commandTime > globalTime){
                    readFileLine = false;
                }
                else{
                    cout << "constructing..." << endl;
                }
                if(!workingOnBuilding || constructingTime == 5){
                    selectBuilding(heapCity, &selectedBuilding);
                    workingOnBuilding = true;
                }
                if(workingOnBuilding && contructingTime < 5)
                    workingOnBuilding = constructBuilding(heapCity, rbtCity, selectedBuilding, &constructingTime, globalTime);
            }
            globalTime++;
            // globalTime += 3;
            // cout << globalTime << endl;
            // cout << "workingOnBuilding: " << workingOnBuilding <<endl;
        }while(workingOnBuilding == true || fileFlag);
        inputFile.close();
    }
    else cout << "Unable to open file"; 
    delete [] arguments;
    delete heapCity;
    delete rbtCity;
    return 0;
}