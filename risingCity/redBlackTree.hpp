#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
#include <string>
#include "building.hpp"

using namespace std;

class node{
  public:
    building *data;    
    string color;
    node *left;
    node *right;
    node *parent;
    node(void){
        parent = left = right = nullptr;
        data = nullptr;
        color = "RED";
    }
    bool isLeft(void) {return this == parent->left;}
    bool hasRed(void){ return (left != nullptr && left->color == "RED") || (right != nullptr && right->color == "RED");}
    node *sibling(void){
        if(parent == NULL)
            return NULL;
        if(isLeft())
            return parent->right;
        return parent->left;
    }
    node *parentSibling(void){
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;
        if (parent->isLeft())
            return parent->parent->right;
        return parent->parent->left;
    }
};

class redBlackTree {
    node *root;
    void leftRotate(node *p);
    void rightRotate(node *p);
    void nodeSwap(node *x, node *y);
    void colorSwap(node *x, node *y);
    node *rightMost(node *x);
    void insertFix(node *p);
    node *binarySearchTreeDel(node *x);
    void deleteNode(node *deletedNode);
    void deleteFix(node *p);
  public:
    redBlackTree() : root(nullptr) {}
    node *treeSearch(int buildingNum);
    node *printingRootSearch(int bn1, int bn2);
    void rbtInsert(building *pair);
    void rbtDelete(int buildingNum);
    void updateTime(int buildingNum, int value);
};
#endif