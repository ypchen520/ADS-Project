#ifndef MINHEAP_HPP_
#define MINHEAP_HPP_
#include <iostream>
#include "building.hpp"

class minHeap{
    int heapCapacity;
    int heapSize;
    building *heapArr;
  public:
    minHeap(int capacity);
    void minHeapify(int i);
    void insertKey(building key);
    void decreaseKey(int i, int newVal);
    building extractMin();
    void deleteKey(int i);
    building getMin() {return heapArr[0];}
    int parent(int i) {return (i-1)/2;}
    int leftChild(int i) {return (2 * i + 1);}
    int rightChild(int i) {return (2 * i + 2);}
};
#endif