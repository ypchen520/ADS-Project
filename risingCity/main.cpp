#include <iostream>
#include "minHeap.hpp"
#include "redBlackTree.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char *argv[]){
    int globalTime = 0;
    bool workingOnBuilding = false;
    bool fileFlag = false;
    minHeap *heapCity = new minHeap(2000);
    redBlackTree *rbtCity = new redBlackTree();
    string command;
    string *arguments = new string[4];
    ifstream inputFile(argv[1]);
    if (inputFile.is_open())
    {
        do{
            fileFlag = getline(inputFile,command);
            if(fileFlag){
                cout << command <<endl;
                readCommand(command, arguments);
                if(stoi(arguments[0]) == globalTime){
                    if(arguments[1][0] == 'I'){
                        cout << arguments[1] <<endl;
                        insertBuilding(heapCity, rbtCity, stoi(arguments[2]), stoi(arguments[3]));
                    }
                    else if(arguments[1][0] == 'P'){
                        cout << arguments[1] <<endl;
                    }
                    cout << heapCity->getMin().buildingNum << endl;
                }
            }
            // cout << arguments[0] <<endl;
            // cout << arguments[1] <<endl;
            // cout << arguments[2] <<endl;

            globalTime++;
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