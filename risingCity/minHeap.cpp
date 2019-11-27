#include "minHeap.hpp"

void exchange(building *a, building *b){
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
        exchange(&heapArr[i], &heapArr[minimum]);
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
    // while(heapArr[idx].executedTime < heapArr[parent(idx)].executedTime && idx != 0){
    //     exchange(&heapArr[idx], &heapArr[parent(idx)]);
    //     idx = parent(idx);
    // }
    while(heapArr[idx].executedTime <= heapArr[parent(idx)].executedTime && idx != 0){
        // std::cout << "HERE?" <<std::endl;
        // std::cout << "idx: " <<idx<<std::endl;
        //         std::cout << "bn_ch: " << heapArr[idx].buildingNum << std::endl;
        //         std::cout << "et_ch: " << heapArr[idx].executedTime << std::endl;
        //         std::cout << "bn_parent: " << heapArr[parent(idx)].buildingNum << std::endl;
        //         std::cout << "et_parent: " << heapArr[parent(idx)].executedTime << std::endl;
        //         std::cout << "bn_gp: " << heapArr[parent(parent(idx))].buildingNum << std::endl;
        //         std::cout << "et_gp: " << heapArr[parent(parent(idx))].executedTime << std::endl;
        //         std::cout << "bn_9: " << heapArr[8].buildingNum << std::endl;
        //         std::cout << "et_9: " << heapArr[8].executedTime << std::endl;
        //         std::cout << "bn_ggp: " << heapArr[parent(parent(parent(idx)))].buildingNum << std::endl;
        //         std::cout << "et_ggp: " << heapArr[parent(parent(parent(idx)))].executedTime << std::endl;
        if(heapArr[idx].executedTime < heapArr[parent(idx)].executedTime){
            // if(heapArr[idx].buildingNum == 13257)
            //     std::cout << "HERE??" <<std::endl;
            // std::cout << "before case: <: " <<std::endl;
            //     std::cout << "idx: " <<idx<<std::endl;
            //     std::cout << "bn_ch: " << heapArr[idx].buildingNum << std::endl;
            //     std::cout << "et_ch: " << heapArr[idx].executedTime << std::endl;
            //     std::cout << "bn_parent: " << heapArr[parent(idx)].buildingNum << std::endl;
            exchange(&heapArr[idx], &heapArr[parent(idx)]);
            idx = parent(idx);
        }
        else if(heapArr[idx].executedTime == heapArr[parent(idx)].executedTime){
            if(heapArr[idx].buildingNum < heapArr[parent(idx)].buildingNum){
                // std::cout << "before: " <<std::endl;
                // std::cout << "idx: " <<idx<<std::endl;
                // std::cout << "bn_ch: " << heapArr[idx].buildingNum << std::endl;
                // std::cout << "et_ch: " << heapArr[idx].executedTime << std::endl;
                // std::cout << "bn_parent: " << heapArr[parent(idx)].buildingNum << std::endl;
                exchange(&heapArr[idx], &heapArr[parent(idx)]);
                idx = parent(idx);
                // std::cout << "after: " <<std::endl;
                // std::cout << "idx: " <<idx<<std::endl;
                // std::cout << "bn_ch: " << heapArr[idx].buildingNum << std::endl;
                // std::cout << "et_ch: " << heapArr[idx].executedTime << std::endl;
                // std::cout << "bn_parent: " << heapArr[parent(idx)].buildingNum << std::endl;
            }
            else{
                // if(heapArr[idx].buildingNum == 13257)
                //     std::cout << "HERE??" <<std::endl;
                break;
            }
        }
    }
}

void minHeap::decreaseKey(int i, int newVal){
    heapArr[i].executedTime = newVal;
    while(heapArr[i].executedTime <= heapArr[parent(i)].executedTime && i != 0){
        if(heapArr[i].executedTime < heapArr[parent(i)].executedTime){
            exchange(&heapArr[i], &heapArr[parent(i)]);
            i = parent(i);
        }
        else if(heapArr[i].executedTime == heapArr[parent(i)].executedTime){
            if(heapArr[i].buildingNum < heapArr[parent(i)].buildingNum){
                exchange(&heapArr[i], &heapArr[parent(i)]);
                i = parent(i);
            } 
            else
                break;
        }
    }
}

building minHeap::extractMin(){
    if(heapSize <= 0){
        building nullBuilding;
        nullBuilding.buildingNum = -1;
        nullBuilding.executedTime = INT_MIN;
        nullBuilding.totalTime = INT_MAX;
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
    decreaseKey(i, INT_MIN);
    extractMin();
}


