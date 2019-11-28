#include "redBlackTree.hpp"
#include <iostream>

void redBlackTree::leftRotate(node *p){
    node *newParent = p->right;

    if(p == root)
        root = newParent;

    newParent->parent = p->parent;

    if(p->parent != nullptr){
        if(p->isLeft())
             p->parent->left = newParent;
        else
            p->parent->right = newParent;
    }

    p->parent = newParent;

    p->right = newParent->left;
    if (newParent->left != nullptr)
        newParent->left->parent = p;

    newParent->left = p;
}

void redBlackTree::rightRotate(node *p){
    node *newParent = p->left;

    if (p == root)
        root = newParent;

    newParent->parent = p->parent;
    if(p->parent != NULL){
        if(p->isLeft())
            p->parent->left = newParent;
        else
            p->parent->right = newParent;
    }

    p->parent = newParent;
    p->left = newParent->right;
    if (newParent->right != NULL)
        newParent->right->parent = p;

    newParent->right = p;
}

void redBlackTree::nodeSwap(node *x, node *y){
    building *temp;
    temp = x->data;
    x->data = y->data;
    y->data = temp;
}

void redBlackTree::colorSwap(node *x, node *y){
    string tempColor;
    tempColor = x->color;
    x->color = y->color;
    y->color = tempColor;
}
node* redBlackTree::rightMost(node *x){
    node *temp = x;
    while(temp->right != nullptr)
        temp = temp->right;
    return temp;
}
void redBlackTree::insertFix(node *p){
    //if the current node is root node, then color it to black, and return
    if(p == root){
        p->color = "BLACK";
        return;
    }
    //find out the parent, grandparent, and parent's sibling
    node *pp = p->parent;
    node *gp = p->parent->parent;
    node *pps = p->parentSibling();
    //if parent is a black node, then do nothing
    if (pp->color != "BLACK"){
        if(pps != NULL && pps->color == "RED") {
            //if parent's sibling is "RED", then change the color, and set new current node to grandparent
            pp->color = "BLACK";
            gp->color = "RED";
            pps->color = "BLACK";
            insertFix(gp);
        } 
        else {
            //if parent's sibling is "BLACK", then there are four cases:
            //do LRb, LLb, RLb, RRb
            if(pp->isLeft()){
                if(p->isLeft()){
                    //for LLb
                    rightRotate(gp);
                    colorSwap(pp, gp);
                } 
                else{
                    //for LRb
                    leftRotate(pp);
                    rightRotate(gp);
                    colorSwap(p, gp);
                }
            } 
            else{
                if(p->isLeft()){
                    //RLb
                    rightRotate(pp);
                    leftRotate(gp);
                    colorSwap(p, gp);
                }
                else{
                    //RR
                    leftRotate(gp);
                    colorSwap(pp, gp);
                }
            }
        }
    }
}
//get the replaced node for deletedNode
node* redBlackTree::binarySearchTreeDel(node *x){
    if(x->left != nullptr && x->right != nullptr)
        return rightMost(x->left);

    if(x->left == nullptr && x->right == nullptr)
        return nullptr;

    if(x->left != nullptr)
        return x->left;
    else
        return x->right;
}

void redBlackTree::deleteNode(node *deletedNode){
    //first do BST delete to get the replaced node y
    node *y = binarySearchTreeDel(deletedNode);
    node *py = deletedNode->parent;  //parent of the deletedNode

    //deletedNode is a leaf
    if(y == nullptr){
        if(deletedNode == root){
            root = nullptr;
        } 
        else {
            //if deletedNode is a red node, no rebalancing needed
            if(deletedNode->color == "BLACK"){
                //fix the RBTree
                deleteFix(deletedNode);
            }

            //delete the deletedNode
            if(deletedNode->isLeft()){
                py->left = nullptr;
            } 
            else{
                py->right = nullptr;
            }
        }
        delete deletedNode;
        return;
    }
    //deletedNode has only one child
    if(deletedNode->left == nullptr || deletedNode->right == nullptr){
        //if deletedNode is root
        if(deletedNode == root){
            //assign y's content to root and delete y
            deletedNode->data = y->data;
            deletedNode->left = deletedNode->right = nullptr;
            delete y;
        }
        else{
            //delete deletedNode and replace it by y
            y->parent = py;
            if(deletedNode->isLeft())
                py->left = y;
            else
                py->right = y;
            delete deletedNode;

            if(deletedNode->color == "BLACK" && y->color == "BLACK"){
                deleteFix(y);
            }
            else{
                y->color = "BLACK";
            }
        }
        return;
    }
    //deletedNode has two children, swap deletedNode and y, and do delete y
    nodeSwap(y, deletedNode);
    deleteNode(y);
}

void redBlackTree::deleteFix(node *p){
    if (p == root)
        return;

    node *sibling = p->sibling();
    node *parent = p->parent;

    if(sibling == NULL){
        //the case that p is a black leaf, move up to py
        deleteFix(parent);
    }
    else{
        if(sibling->color == "RED"){
            //sibling is red
            parent->color = "RED";
            sibling->color = "BLACK";
            if(sibling->isLeft()) {
                rightRotate(parent);
            }
            else{
                leftRotate(parent);
            }
            deleteFix(p);
        }
        else{
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
                    }
                    else{
                        //RL
                        sibling->left->color = parent->color;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                }
                else{
                    if(sibling->isLeft()){
                        //RL
                        sibling->right->color = parent->color;
                        leftRotate(sibling);
                        rightRotate(parent);
                    }
                    else {
                        //RR
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = "BLACK";
            }
            else{
                //two black children for sibling
                sibling->color = "RED";
                if(parent->color == "BLACK")
                    deleteFix(parent); //Rb0,LB0, case 1, py is "BLACK"
                else
                    parent->color = "BLACK"; //Rb0,LB0, case 2, py is "RED"
            }
        }
    }
}
node* redBlackTree::treeSearch(int buildingNum){
    node *temp = root;
    while(temp != nullptr){
        if(buildingNum < temp->data->buildingNum) {
            if(temp->left == nullptr)
                return temp;
            else
                temp = temp->left;
        }
        else if(buildingNum == temp->data->buildingNum){
            return temp;
        }
        else{
            if(temp->right == NULL)
                return temp;
            else
                temp = temp->right;
        }
    }
    return temp;
}

node *redBlackTree::printingRootSearch(int bn1, int bn2){
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

void redBlackTree::rbtInsert(building *pair){
    node *newNode = new node();
    newNode->data = pair;
    if(root == NULL){
        newNode->color = "BLACK";
        root = newNode;
    }
    else{
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
        insertFix(newNode);
    }
}

void redBlackTree::rbtDelete(int buildingNum){
    if (root == NULL)
        return;
    node *target = treeSearch(buildingNum);
    if(target->data->buildingNum != buildingNum)
        return;
    deleteNode(target);
}

void redBlackTree::updateTime(int buildingNum, int value){
    node *selectedNode = treeSearch(buildingNum);
    selectedNode->data->executedTime += value;
}