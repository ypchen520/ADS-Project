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
    if(heapSize > left && heapArr[left].executedTime  < heapArr[i].executedTime)
        minimum = left;
    if(heapSize > right && heapArr[right].executedTime  < heapArr[minimum].executedTime)
        minimum = right;
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
    while(heapArr[idx].executedTime < heapArr[parent(idx)].executedTime && idx != 0){
        exchange(&heapArr[idx], &heapArr[parent(idx)]);
        idx = parent(idx);
    }

}

void minHeap::decreaseKey(int i, int newVal){
    heapArr[i].executedTime = newVal;
    while(heapArr[i].executedTime < heapArr[parent(i)].executedTime && i != 0){
        exchange(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

building minHeap::extractMin(){
    // if(heapSize <= 0)
    //     return INT_MAX;
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


