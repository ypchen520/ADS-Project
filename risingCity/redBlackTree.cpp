#include "redBlackTree.hpp"
#include <iostream>

void redBlackTree::nodeSwap(node *a, node *b){
    building *temp;
    temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void redBlackTree::colorSwap(node *a, node *b){
    string tempColor;
    tempColor = a->color;
    a->color = b->color;
    b->color = tempColor;
}

node* redBlackTree::rightMost(node *x){
    //get the rightMost child 
    node *temp = x;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp;
}

void redBlackTree::rbtInsert(building *pair){
    node *newNode = new node();
    newNode->data = pair;
    if(root == nullptr){
        newNode->color = "BLACK"; //root is always BLACK
        root = newNode;
    }
    else{
        node *temp = treeSearch(pair->buildingNum); //return the last visited node if not found
        if (temp->data->buildingNum == pair->buildingNum){                
            return;
        }
        //insert it as the child of the last visited node
        newNode->parent = temp;
        //buildingNum smaller: left 
        //otherwise: right
        if(pair->buildingNum < temp->data->buildingNum)
            temp->left = newNode;
        else
            temp->right = newNode;
        insertFix(newNode);
    }
}

void redBlackTree::insertFix(node *p){
    if(p == root){
        p->color = "BLACK";
        return;
    }
    node *pp = p->parent;
    node *gp = p->parent->parent;
    node *pu = p->uncle();
    if (pp->color == "RED"){ //Nothing to do if parent's color is BLACK
        if(pu != nullptr && pu->color == "RED") {
            //XYr --> color flip
            pp->color = "BLACK";
            pu->color = "BLACK";
            gp->color = "RED";
            //continue
            insertFix(gp);
        } 
        else {
            //BLACK uncle: LRb, LLb, RLb, RRb
            if(pp->isLeft()){
                if(p->isLeft()){
                    //LLb
                    rightRotate(gp);
                    colorSwap(pp, gp);
                } 
                else{
                    //LRb = RR + LL
                    leftRotate(pp);
                    rightRotate(gp);
                    colorSwap(p, gp);
                }
            } 
            else{
                if(p->isLeft()){
                    //RLb = LL + RR
                    rightRotate(pp);
                    leftRotate(gp);
                    colorSwap(p, gp);
                }
                else{
                    //RRb
                    leftRotate(gp);
                    colorSwap(pp, gp);
                }
            }
        }
    }
}

node* redBlackTree::binarySearchTreeDel(node *x){
    if(x->left != nullptr && x->right != nullptr) //2-degree node
        return rightMost(x->left); //the largest in the left subtree
    else if(x->left != nullptr)
        return x->left;
    else if(x->right != nullptr)
        return x->right;
    else
        return nullptr;
}

void redBlackTree::deleteNode(node *deletedNode){
    node *y = binarySearchTreeDel(deletedNode); //search for the replacing node
    node *py = deletedNode->parent;

    if(y == nullptr){ //deletedNode is a leaf
        if(deletedNode == root)
            root = nullptr;
        else {
            if(deletedNode->color != "RED")//RED deletedNode -> no need for rebalancing
                deleteFix(deletedNode);

            if(deletedNode->isLeft()){
                py->left = nullptr;
            } 
            else{
                py->right = nullptr;
            }
        }
        delete deletedNode; //free the space
        return;
    }
    if(deletedNode->left == nullptr || deletedNode->right == nullptr){ //deletedNode is a 1-degree node
        if(deletedNode == root){
            deletedNode->data = y->data; //y is the replacing node
            deletedNode->left = nullptr;
            deletedNode->right = nullptr;
            delete y;
        }
        else{
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
    nodeSwap(y, deletedNode); //deletedNode is a 2-degree node
    deleteNode(y);
}

void redBlackTree::rbtDelete(int buildingNum){
    //return if the tree is not there
    if (root == nullptr)
        return;
    //search for the node to be deleted
    node *deletingNode = treeSearch(buildingNum);
    //check if the building is in the city
    if(deletingNode->data->buildingNum != buildingNum)
        return;
    deleteNode(deletingNode);
}

void redBlackTree::deleteFix(node *p){
    if (p == root)
        return;

    node *sibling = p->sibling();
    node *parent = p->parent;

    if(sibling == nullptr){
        //the case that p is a black leaf, move up to py
        deleteFix(parent);
    }
    else{
        if(sibling->color == "RED"){ //sibling is RED
            //color flip
            sibling->color = "BLACK";
            parent->color = "RED";
            if(sibling->isLeft()) {
                rightRotate(parent); //LL
            }
            else{
                leftRotate(parent);  //RR
            }
            deleteFix(p); //continue
        }
        else{ //sibling is BLACK
            if(sibling->hasRed()){ //Xb1 or Xb2
                if(sibling->left != nullptr && sibling->left->color == "RED"){
                    if(sibling->isLeft()){
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(parent); //LL
                    }
                    else{
                        sibling->left->color = parent->color;
                        //RL = LL + RR
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                }
                else{ //symmetric
                    if(sibling->isLeft()){ 
                        sibling->right->color = parent->color;
                        //LR = RR + LL
                        leftRotate(sibling);
                        rightRotate(parent);
                    }
                    else {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);//RR
                    }
                }
                parent->color = "BLACK";
            }
            else{ //Xb0
                sibling->color = "RED";
                if(parent->color == "RED") //Xb0 case 2: py is RED
                    parent->color = "BLACK";
                else
                    deleteFix(parent);
            }
        }
    }
}

node* redBlackTree::treeSearch(int buildingNum){
    //if buildingNum is not found, return the last visited node
    node *temp = root;
    while(temp){
        if(buildingNum == temp->data->buildingNum){
            return temp;
        }
        else if(buildingNum < temp->data->buildingNum) {
            if(temp->left == nullptr)
                return temp;
            else
                temp = temp->left;
        }
        else{
            if(temp->right == nullptr)
                return temp;
            else
                temp = temp->right;
        }
    }
    return temp;
}

void redBlackTree::leftRotate(node *p){
    //for RR
    node *newParent = p->right;
    if(p == root)
        root = newParent;
    newParent->parent = p->parent;
    if(p->parent){
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
    //for LL //symmetric to RR
    node *newParent = p->left;
    if (p == root)
        root = newParent;
    newParent->parent = p->parent;
    if(p->parent){
        if(p->isLeft())
            p->parent->left = newParent;
        else
            p->parent->right = newParent;
    }

    p->parent = newParent;
    p->left = newParent->right;
    if (newParent->right != nullptr)
        newParent->right->parent = p;
    newParent->right = p;
}

node *redBlackTree::printingRootSearch(int bn1, int bn2){
    //search for the root of the subtree that covers the range of [buildingNum1,buildingNum2]
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

void redBlackTree::updateTime(int buildingNum, int value){
    node *selectedNode = treeSearch(buildingNum);
    selectedNode->data->executedTime += value;
}