#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
#include <string>
#include "building.hpp"

using namespace std;

struct node{
    int data;
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
    node* treeSearch(int pair);
    void insert(int pair);
    void insertBalance(node *p);
    void deleteNode(node *py, node *y, int pair);
    void remove(int pair);
    void removeBalance(node *y);
    void leftRotate(node *p);
    void rightRotate(node *p);
};
#endif