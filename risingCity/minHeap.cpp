#include "minHeap.hpp"

void swap(building *a, building *b){
    building temp = *a;
    *a = *b;
    *b = temp;
}

minHeap::minHeap(int capacity){
    heapCapacity = capacity;
    heapSize = 0;
    heapArr = new building[heapCapacity];
}

void minHeap::minHeapify(int i){
    int left = leftChild(i);
    int right = rightChild(i);
    int minimum = i;
    //Handle the tie break
    if(heapSize > left){ 
        if(heapArr[left].executedTime < heapArr[i].executedTime)
            minimum = left;
        else if(heapArr[left].executedTime == heapArr[i].executedTime){
            if(heapArr[left].buildingNum < heapArr[i].buildingNum)
                minimum = left;
        }
    }
    if(heapSize > right){
        if(heapArr[right].executedTime < heapArr[minimum].executedTime)
            minimum = right;
        else if(heapArr[right].executedTime == heapArr[minimum].executedTime){
            if(heapArr[right].buildingNum < heapArr[minimum].buildingNum)
                minimum = right;
        }
    }
    if(minimum != i){
        swap(&heapArr[i], &heapArr[minimum]);
        minHeapify(minimum);
    }
}

void minHeap::insertKey(building key){
    if(heapSize == heapCapacity){
        std::cout << "No space left for additional buildings in the city";
        return;
    }
    heapSize++;
    int idx = heapSize-1;
    heapArr[idx] = key;
    //Handle the tie break
    while(heapArr[idx].executedTime <= heapArr[parent(idx)].executedTime && idx != 0){
        if(heapArr[idx].executedTime < heapArr[parent(idx)].executedTime){
            swap(&heapArr[idx], &heapArr[parent(idx)]);
            idx = parent(idx);
        }
        else if(heapArr[idx].executedTime == heapArr[parent(idx)].executedTime){
            if(heapArr[idx].buildingNum < heapArr[parent(idx)].buildingNum){            
                swap(&heapArr[idx], &heapArr[parent(idx)]);
                idx = parent(idx);
            }
            else{
                break;
            }
        }
    }
}

void minHeap::decreaseKey(int i, int newVal){
    heapArr[i].executedTime = newVal;
    //Handle the tie break
    while(heapArr[i].executedTime <= heapArr[parent(i)].executedTime && i != 0){
        if(heapArr[i].executedTime < heapArr[parent(i)].executedTime){
            swap(&heapArr[i], &heapArr[parent(i)]);
            i = parent(i);
        }
        else if(heapArr[i].executedTime == heapArr[parent(i)].executedTime){
            if(heapArr[i].buildingNum < heapArr[parent(i)].buildingNum){
                swap(&heapArr[i], &heapArr[parent(i)]);
                i = parent(i);
            } 
            else
                break;
        }
    }
}

building minHeap::extractMin(){
    if(heapSize <= 0){
        //return null building with bn = -1 as a flag to signal the end of the program
        building nullBuilding;
        nullBuilding.buildingNum = -1;
        nullBuilding.executedTime = INT32_MIN;
        nullBuilding.totalTime = INT32_MAX;
        return nullBuilding;
    }
    if(heapSize == 1){
        heapSize--;
        return heapArr[0];
    }
    building root = heapArr[0];
    heapArr[0] = heapArr[heapSize-1];
    heapSize--;
    minHeapify(0);
    return root;
}

void minHeap::deleteKey(int i){
    decreaseKey(i, INT32_MIN);
    extractMin();
}


