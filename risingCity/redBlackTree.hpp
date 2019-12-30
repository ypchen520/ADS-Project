#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
#include <string>
#include "building.hpp"

using namespace std;

class node{
  public:
    building *data;    
    string color;
    node *parent;
    node *left;
    node *right;
    node() : parent(nullptr), left(nullptr), right(nullptr), data(nullptr), color("RED") {} //always insert a RED node
    //determine if the node is a left child of its parent
    bool isLeft(void) {return this == parent->left;}
    //determine if the node has red child (for delete fix)
    bool hasRed(void){ return (left != nullptr && left->color == "RED") || (right != nullptr && right->color == "RED");}
    node *sibling(void){
        if(parent == nullptr)
            return nullptr;
        if(isLeft())
            return parent->right;
        return parent->left;
    }
    node *uncle(void){ //sibling of the parent
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;
        if (parent->isLeft())
            return parent->parent->right; //if parent is the left of the grandparent -> uncle is the right 
        return parent->parent->left;
    }
};

class redBlackTree {
    node *root;
    void nodeSwap(node *a, node *b);
    void colorSwap(node *a, node *b);
    node *rightMost(node *x);
    void insertFix(node *p); //insert
    node *binarySearchTreeDel(node *x); //delete
    void deleteNode(node *deletedNode); //delete
    void deleteFix(node *p); //delete
    void leftRotate(node *p); //RR
    void rightRotate(node *p); //LL
  public:
    redBlackTree() : root(nullptr) {}
    node *treeSearch(int buildingNum);
    void rbtInsert(building *pair); //insert
    void rbtDelete(int buildingNum); //delete
    node *printingRootSearch(int bn1, int bn2); //util
    void updateTime(int buildingNum, int value); //util
};
#endif