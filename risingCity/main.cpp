#include <iostream>
#include "minHeap.hpp"
#include "redBlackTree.hpp"
#include "util.hpp"

using namespace std;
int main(int argc, char *argv[]){
    int globalTime = 0;
    bool buildingCity = true;
    bool workingOnBuilding = false;
    bool fileFlag = false;
    bool readFileLine = true;
    bool specialFlag = false;
    int commandTime = -1;
    int constructingTime = 0;
    building selectedBuilding;
    minHeap *heapCity = new minHeap(2000);
    redBlackTree *rbtCity = new redBlackTree();
    string command;
    //string *arguments = new string[4];
    string arguments[] = {"-1", "-1", "-1", "-1"};
    selectedBuilding.buildingNum = -1;
    ifstream inputFile(argv[1]);
    ofstream outputFile("output_file.txt");
    if (inputFile.is_open() && outputFile.is_open())
    {
        do{
            if(readFileLine){
                fileFlag = getline(inputFile,command);
                readCommand(command, arguments);
                if(arguments[0] != ""){
                    commandTime = stoi(arguments[0]);
                    readFileLine = false;
                }
            }
            if(fileFlag){
                //do command
                //commandTime should not be smaller than globalTime
                if(commandTime == globalTime){
                    int arg2 = stoi(arguments[2]);
                    int arg3 = stoi(arguments[3]);
                    if(arguments[1][0] == 'I'){
                        if(specialFlag){
                            outputFile << "(" << selectedBuilding.buildingNum << "," << globalTime << ")" << endl;
                            rbtCity->rbtDelete(selectedBuilding.buildingNum);
                            specialFlag = false;
                        }
                        building *rbtBuilding = new building;
                        insertBuilding(heapCity, rbtCity, arg2, arg3, rbtBuilding);
                    }
                    else if(arguments[1][0] == 'P'){
                        //Selected: bn
                        if(arg3 == -1)
                            printBuilding(arg2, rbtCity, constructingTime, &selectedBuilding, outputFile);
                        else
                            printBuilding(arg2, arg3, rbtCity, constructingTime, &selectedBuilding, outputFile);
                        if(specialFlag){
                            outputFile << "(" << selectedBuilding.buildingNum << "," << globalTime << ")" << endl;
                            rbtCity->rbtDelete(selectedBuilding.buildingNum);
                            specialFlag = false;
                        }
                    }
                    readFileLine = true;
                }
                else if(commandTime > globalTime){
                    readFileLine = false;
                    if(specialFlag){
                        outputFile << "(" << selectedBuilding.buildingNum << "," << globalTime << ")" << endl;
                        rbtCity->rbtDelete(selectedBuilding.buildingNum);
                        specialFlag = false;
                    }
                    //cout << "readFileLine: " << readFileLine <<endl;
                }
            }
            if(specialFlag){
                outputFile << "(" << selectedBuilding.buildingNum << "," << globalTime << ")" << endl;
                rbtCity->rbtDelete(selectedBuilding.buildingNum);
                specialFlag = false;
            }
            if(!workingOnBuilding){
                //rbtCity->rbtDelete(selectedBuilding.buildingNum);
                selectBuilding(heapCity, &selectedBuilding);
                workingOnBuilding = true;
                if(selectedBuilding.buildingNum == -1){
                    buildingCity = false;
                    break;
                }
                constructingTime = 0;
            }
            if(workingOnBuilding && constructingTime < 5){
                workingOnBuilding = constructBuilding(heapCity, rbtCity, &selectedBuilding, &constructingTime, globalTime, outputFile, &specialFlag);
                if(selectedBuilding.buildingNum == 40 && selectedBuilding.executedTime == 225){
                    cout << specialFlag <<endl;
                }
            }
            globalTime++;
        }while(buildingCity == true || fileFlag);
        inputFile.close();
        outputFile.close();
    }
    else cout << "Unable to open file"; 
    //delete [] arguments;
    delete heapCity;
    delete rbtCity;
    return 0;
}