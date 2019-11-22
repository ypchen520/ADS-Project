#ifndef MINHEAP_HPP_
#define MINHEAP_HPP_
#include <iostream>
#include "building.hpp"

class minHeap{
    int heapCapacity;
    int heapSize;
    int *heapArr;
  public:
    minHeap(int capacity);
    void minHeapify(int i);
    void insertKey(int key);
    void decreaseKey(int i, int newVal);
    int extractMin();
    void deleteKey(int i);
    int getMin() {return heapArr[0];}
    int parent(int i) {return (i-1)/2;}
    int leftChild(int i) {return (2 * i + 1);}
    int rightChild(int i) {return (2 * i + 2);}
};
#endif