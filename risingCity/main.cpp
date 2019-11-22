#include <iostream>
#include "minHeap.hpp"
#include "redBlackTree.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char *argv[]){
    int globalTime = 0;
    bool workingOnBuilding = false;
    string command;
    string *arguments = new string[4];
    ifstream inputFile(argv[1]);
    if (inputFile.is_open())
    {
        do
        {
            getline(inputFile,command);
            readCommand(command, arguments);
            if(arguments[0] == globalTime){

            }
            globalTime++;
        }while(workingOnBuilding || arguments[0] != "");
        inputFile.close();
    }
    else cout << "Unable to open file"; 
    return 0;
}