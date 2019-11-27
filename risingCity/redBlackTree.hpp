#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
#include <string>
#include "building.hpp"

using namespace std;

class node{
public:
    building *data;     //Point to the data Node
    string color;
    node *left;
    node *right;
    node *parent;
    
    node(void){
        parent = left = right = nullptr;
        data = nullptr;
        color = "RED";
    }
    
    // check the node is the left child of its parent
    bool isLeft(void){
        return this == parent->left; 
    }
    
    //get sibling
    node *sibling(void){
        // sibling null if no parent
        if(parent == NULL)
            return NULL;
        
        //it is a left child of its parent, so it's sibling is the right child of its parent
        if(isLeft())
            return parent->right;

        return parent->left;
    }

    node *parentSibling(void){
        //must have parent and grandparent
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;

        //parent is grandparent's left child
        if (parent->isLeft())
            return parent->parent->right;

        return parent->parent->left;
    }

    bool hasRed(void){
        return (left != nullptr && left->color == "RED") || (right != nullptr && right->color == "RED");
    }

};

class redBlackTree {
    node *root;

    //left rotation (RR)
    void leftRotate(node *current){
        //new parent will be current node's right child
        node *newParent = current->right;

        //check if the current node is the root
        if(current == root)
            root = newParent;

        //let new parent's parent be current node's parent
        newParent->parent = current->parent;
        //set current node's parent's left/right child to new parent
        if(current->parent != nullptr){
            if(current->isLeft())
                current->parent->left = newParent;
            else
                current->parent->right = newParent;
        }
        //reset current node's parent to new parent
        current->parent = newParent;

        //current node's right child will be new parent's left child
        current->right = newParent->left;
        if (newParent->left != nullptr)
            newParent->left->parent = current;

        //new parent's left child will be the current node
        newParent->left = current;
    }

    //right rotation (LL)
    //it is the similar to the left rotation function
    void rightRotate(node *current){
        node *newParent = current->left;

        if (current == root)
            root = newParent;

        newParent->parent = current->parent;
        if(current->parent != NULL){
            if(current->isLeft())
                current->parent->left = newParent;
            else
                current->parent->right = newParent;
        }

        current->parent = newParent;
        current->left = newParent->right;
        if (newParent->right != NULL)
            newParent->right->parent = current;

        newParent->right = current;
    }

    void colorSwap(node *x, node *y){
        string temp_color;
        temp_color = x->color;
        x->color = y->color;
        y->color = temp_color;
    }

    void nodeSwap(node *x, node *y){
        building *temp;
        temp = x->data;
        x->data = y->data;
        y->data = temp;
    }

    //fix the tree after insert
    void insertFix(node *current){
        //if the current node is root node, then color it to black, and return
        if(current == root){
            current->color = "BLACK";
            return;
        }

        //find out the parent, grandparent, and parent's sibling
        node *pp = current->parent;
        node *gp = current->parent->parent;
        node *pps = current->parentSibling();

        //if parent is a black node, then do nothing
        if (pp->color != "BLACK"){
            if(pps != NULL && pps->color == "RED") {
                //if parent's sibling is "RED", then change the color, and set new current node to grandparent
                pp->color = "BLACK";
                gp->color = "RED";
                pps->color = "BLACK";
                insertFix(gp);
            } else {
                //if parent's sibling is "BLACK", then there are four cases:
                //do LRb, LLb, RLb, RRb
                if(pp->isLeft()){
                    if(current->isLeft()){
                        //for LLb
                        rightRotate(gp);
                        colorSwap(pp, gp);
                    } else {
                        //for LRb
                        leftRotate(pp);
                        rightRotate(gp);
                        colorSwap(current, gp);
                    }
                } else {
                    if (current->isLeft()) {
                        //RLb
                        rightRotate(pp);
                        leftRotate(gp);
                        colorSwap(current, gp);
                    } else {
                        //RR
                        leftRotate(gp);
                        colorSwap(pp, gp);
                    }
                }
            }
        }//end of if
    }

    //find the rightmost node in the given subtree (which has the biggest reference)
    node *rightMost(node *x){
        node *temp = x;
        while(temp->right != nullptr)
            temp = temp->right;
        return temp;
    }

    //get the replaced node for delNode
    node *binarySearchTreeDel(node *x){
        //if it has two children, replace it with the rightmost node in it's left subtree
        if(x->left != nullptr && x->right != nullptr)
            return rightMost(x->left);

        //if it has no child, no need for replacement, return NULL
        if(x->left == nullptr && x->right == nullptr)
            return nullptr;

        //if it has only one child, return that child
        if(x->left != nullptr)
            return x->left;
        else
            return x->right;
    }

    //delete the given node in the tree
    void deleteNode(node *delNode){
        //first do BST delete to get the replaced node y
        node *y = binarySearchTreeDel(delNode);
        node *py = delNode->parent;  //parent of the delNode

        //delNode is a leaf
        if(y == nullptr){
            if(delNode == root){
                root = nullptr;
            } else {
                //if delNode is a red node, no rebalancing needed
                if(delNode->color == "BLACK"){
                    //fix the RBTree
                    rebalanceRBT(delNode);
                }

                //delete the delNode
                if(delNode->isLeft()){
                    py->left = nullptr;
                } else {
                    py->right = nullptr;
                }
            }
            delete delNode;
            return;
        }

        //delNode has only one child
        if(delNode->left == nullptr || delNode->right == nullptr){
            //if delNode is root
            if(delNode == root){
                //assign y's content to root and delete y
                delNode->data = y->data;
                delNode->left = delNode->right = nullptr;
                delete y;
            } else {
                //delete delNode and replace it by y
                y->parent = py;
                if(delNode->isLeft())
                    py->left = y;
                else
                    py->right = y;

                delete delNode;

                if (delNode->color == "BLACK" && y->color == "BLACK"){
                    //fix the RBTree
                    rebalanceRBT(y);
                } else {
                    //just let y be "BLACK"
                    y->color = "BLACK";
                }
            }
            return;
        }

        //delNode has two children, swap delNode and y, and do delete y
        nodeSwap(y, delNode);
        deleteNode(y);
    }

    void rebalanceRBT(node *x){
        if (x == root)
            return;

        node *sibling = x->sibling(),
                *parent = x->parent;

        if(sibling == NULL){
            //the case that x is a black leaf, move up to py
            rebalanceRBT(parent);
        } else {
            if(sibling->color == "RED"){
                //sibling is red
                parent->color = "RED";
                sibling->color = "BLACK";
                if(sibling->isLeft()) {
                    rightRotate(parent);
                } else {
                    leftRotate(parent);
                }
                rebalanceRBT(x);
            } else {
                //if sibling is black
                if(sibling->hasRed()){
                    //at least one red child
                    if(sibling->left != nullptr && sibling->left->color == "RED"){
                        //might be a red left child or both
                        if(sibling->isLeft()){
                            //LL
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        } else {
                            //RL
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    } else {
                        if(sibling->isLeft()){
                            //RL
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        } else {
                            //RR
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = "BLACK";
                } else {
                    //two black children for sibling
                    sibling->color = "RED";
                    if(parent->color == "BLACK")
                        //Rb0,LB0, case 1, py is "BLACK"
                        rebalanceRBT(parent);
                    else
                        //Rb0,LB0, case 2, py is "RED"
                        parent->color = "BLACK";
                }
            }
        }
    }

public:
    //constructor
    redBlackTree(void){
        root = nullptr;
    }

    //search for the node by reference (building number)
    //if it is found, then return the node, if not found, return the last node while searching
    node *treeSearch(int bn){
        node *temp = root;
        //if the tree is empty, return root(NULL)
        //if(temp == NULL)
         //   return root;

        while(temp != nullptr){
            if(bn < temp->data->buildingNum) {
                if(temp->left == nullptr)
                    return temp;
                else
                    temp = temp->left;
            } else if(bn == temp->data->buildingNum){
                return temp;
            } else {
                if(temp->right == NULL)
                    return temp;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    node *printingRootSearch(int bn1, int bn2){
        node *temp = root;
        int tempBuildingNum = temp->data->buildingNum;
        while(temp != nullptr){
            if(bn1 > tempBuildingNum){
                if(temp->right == nullptr)
                    return nullptr;
                else
                    temp = temp->right;
            }
            else if(bn1 <= tempBuildingNum && bn2 >= tempBuildingNum){
                break;
            }
            else{
                if(temp->left == nullptr)
                    return nullptr;
                else
                    temp = temp->left;
            }
        }
        return temp;
    }


    
    //insert new data node in RBTree
    void rbtInsert(building *pair){
        node *newNode = new node();
        //newNode pointer point to the new data node
        newNode->data = pair;
        
        if(root == NULL){
            //if the RBTree is empty
            newNode->color = "BLACK";
            root = newNode;
        } else {
            //search where the new node should be inserted, reference: building Number
            node *temp = treeSearch(pair->buildingNum);
            
            if (temp->data->buildingNum == pair->buildingNum){                
                return;
            }

            //insert it as a child
            newNode->parent = temp;
            //determine if newNode is a left child or a right child
            if(pair->buildingNum < temp->data->buildingNum)
                temp->left = newNode;
            else
                temp->right = newNode;

            //Now, we need to fix the RBTree, if the newNode's parent is a red node
            //possible fixes: XYr and XYb
            insertFix(newNode);
        }
    }

    //delete the node in RBTree
    void rbtDelete(int bn){
        if (root == NULL)
            return;

        //first make sure bn can be found in the RBTree
        node *target = treeSearch(bn);
        if(target->data->buildingNum != bn)
            return;

        deleteNode(target);
    }
    void updateTime(int buildingNum, int value){
        node *selectedNode = treeSearch(buildingNum);
        selectedNode->data->executedTime += value;
    }
};
/*
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
    node* printingRootSearch(int bn1, int bn2);
    //inorderTraversal(int buildingNumStart, int buildingNumEnd);
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
    void updateTime(int buildingNum, int value);
};
*/
#endif