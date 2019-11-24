#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
#include <string>
#include "building.hpp"

using namespace std;

struct node{
    //int data;
    building data;
    string color;
    node *leftChild;
    node *rightChild;
    node *parent;
};

class redBlackTree{
    node *root;
  public:
    redBlackTree() : root(nullptr) {}
    node* getRoot(){return root;}
    node* treeSearch(int buildingNum);
    //void insert(int pair);
    void insert(building pair);
    void insertBalance(node *p);
    //void deleteNode(node *py, node *y, int pair);
    void deleteNode(node *py, node *y, int buildingNum);
    //void remove(int pair);
    void remove(int buildingNum);
    void removeBalance(node *y);
    void leftRotate(node *p);
    void rightRotate(node *p);
};
#endif