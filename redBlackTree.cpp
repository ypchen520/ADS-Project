#include "redBlackTree.hpp"
#include <iostream>

node* redBlackTree::treeSearch(int pair){
    node *temp = getRoot();
    while(temp){
        if(pair == temp->data)
            return temp;
        else if(pair < temp->data)
            temp = temp->leftChild;
        else
            temp = temp->rightChild;
    }
    return nullptr;
}

void redBlackTree::insert(int pair){
    if(root == nullptr){
        root = new node();
        root->data = pair;
        root->color = "BLACK";
        root->parent = nullptr;
    }
    else{
        node *newNode = new node();
        newNode->data = pair;
        newNode->color = "RED";
        node *temp = getRoot();
        
        while(temp != nullptr){
            if(pair < temp->data){
                if(temp->leftChild == nullptr){
                    temp->leftChild = newNode;
                    newNode->parent = temp;
                    break;
                }
                else
                    temp = temp->leftChild;
            }
            else
            {
                if(temp->rightChild == nullptr){
                    temp->rightChild = newNode;
                    newNode->parent = temp;
                    break;
                }
                else
                    temp = temp->rightChild;
            }
        }
        insertBalance(newNode);
    }
}

void redBlackTree::insertBalance(node *p){
    while(p->parent->color == "RED"){
        node *pp = p->parent;
        node *gp = p->parent->parent;
        if(pp == gp->leftChild){
            if(gp->rightChild && gp->rightChild->color == "RED"){
                //color flip
                pp->color = "BLACK";
                gp->rightChild->color = "BLACK";
                gp->color = "RED";
                if(gp->data != root->data)
                    p = gp;
                else
                    break;
            }
            else if(p == pp->rightChild)//z: nullptr or BLACK --> LRb
                leftRotate(pp);
            else{//LLb
                pp->color = "RED";
                gp->color = "BLACK";
                rightRotate(gp);
                if(gp->data != root->data)
                    p = gp;
                else
                    break;
            }
        }
        else{
            if(gp->leftChild && gp->leftChild->color == "RED"){
                //color flip
                pp->color = "BLACK";
                gp->leftChild->color = "BLACK";
                gp->color = "RED";
                if(gp->data != root->data)
                    p = gp;
                else
                    break;
            }
            else if(p == pp->leftChild)//z: nullptr or BLACK --> RLb
                rightRotate(pp);
            else{//RRb
                pp->color = "RED";
                gp->color = "BLACK";
                leftRotate(gp);
                if(gp->data != root->data)
                    p = gp;
                else
                    break;
            }
        }
    }
    root->color="BLACK";
}

void redBlackTree::deleteNode(node *py, node *y, int pair){
    if(y == nullptr)
        return;
    if(y->data == pair){
        if(y->leftChild == nullptr && y->rightChild == nullptr){
            if(y->data == py->data)
                root = nullptr;
            else if(y == py->rightChild){
                removeBalance(y);
                py->rightChild = nullptr;
            }
            else{
                removeBalance(y);
                py->leftChild = nullptr;
            }
        }
        else if(y->leftChild != nullptr && y->rightChild == nullptr){
            int temp = y->data;
            y->data = y->leftChild->data;
            y->leftChild->data = temp;
            deleteNode(y, y->leftChild, pair);
        }
        else if(y->leftChild == nullptr && y->rightChild != nullptr){
            int tempPair = y->data;
            y->data = y->rightChild->data;
            y->rightChild->data = tempPair;
            deleteNode(y, y->rightChild, pair);
        }
        else{
            node* temp = y->rightChild;
            bool flag = false;
            //smallest in the right subtree
            while(temp->leftChild){
                py = temp;
                temp = temp->leftChild;
                flag = true;
            }
            if(flag == false)
                py = y;
            int tempPair = y->data;
            y->data = temp->data;
            temp->data = tempPair;
            deleteNode(py, temp, tempPair);
        }
    }
}
void redBlackTree::remove(int pair){
    node *temp = root;
    node *py = temp;
    bool flag = false;
    while(temp){
        if(pair == temp->data){
            deleteNode(py, temp, pair);
            flag = true;
            break;
        }
        else if(pair < temp->data){
            py = temp;
            temp = temp->leftChild;
        }
        else{
            py = temp;
            temp = temp->rightChild;
        }   
    }
    if(flag == false)
        cout << "No building matched\n";
}
void redBlackTree::removeBalance(node *y){
    while(y->color == "BLACK" && y->data != root->data){
        node *py = y->parent;
        if(y == py->leftChild){
            node* sibling = py->rightChild;
            if(sibling){
                if(sibling->color == "RED"){
                    //sibling->color = "BLACK";
                    //py->color = "RED";
                    leftRotate(py);
                    //y->parent->color = "BLACK";
                    sibling = y->parent->rightChild;
                }
                if(sibling->leftChild == nullptr && sibling->rightChild == nullptr){//n=0
                    sibling->color = "RED";
                    y = y->parent;
                }
                else if(sibling->leftChild->color == "BLACK" && sibling->rightChild->color == "BLACK"){
                    sibling->color = "RED";
                    y = y->parent;
                }
                else if(sibling->rightChild->color == "BLACK"){
                    //sibling->color = "BLACK";
                    //sibling->leftChild->color = "RED";
                    rightRotate(sibling);
                    //sibling->color = "RED";
                    sibling = y->parent->rightChild;
                }
                else{
                    //sibling->color = y->parent->color; //B->R
                    //y->parent->color = "BLACK"; //R->B
                    if(sibling->rightChild)
                        sibling->rightChild->color = "BLACK";
                    leftRotate(y->parent);
                    y = root;
                }
            }
        }
        else{
            node* sibling = py->leftChild;
            if(sibling){
                if(sibling->color == "RED"){
                    //sibling->color = "BLACK";
                    //py->color = "RED";
                    rightRotate(py);
                    //y->parent->color = "BLACK";
                    sibling = y->parent->leftChild;
                }
                if(sibling->leftChild == nullptr && sibling->rightChild == nullptr){//n=0
                    sibling->color = "RED";
                    y = y->parent;
                }
                else if(sibling->leftChild->color == "BLACK" && sibling->rightChild->color == "BLACK"){
                    sibling->color = "RED";
                    y = y->parent;
                }
                else if(sibling->leftChild->color == "BLACK"){
                    //sibling->color = "BLACK";
                    //sibling->leftChild->color = "RED";
                    leftRotate(sibling);
                    //sibling->color = "RED";
                    sibling = y->parent->leftChild;
                }
                else{
                    //sibling->color = y->parent->color; //B->R
                    //y->parent->color = "BLACK"; //R->B
                    if(sibling->leftChild)
                        sibling->leftChild->color = "BLACK";
                    rightRotate(y->parent);
                    y = root;
                }
            }
        }
    }
    y->color = "BLACK";
}

void redBlackTree::leftRotate(node *p){
    if(p->rightChild){
        node *newNode = new node();
        newNode->data = p->data;
        newNode->color = p->rightChild->color;
        newNode->leftChild = p->leftChild;
        newNode->rightChild = p->rightChild->leftChild;
        newNode->parent = p;
        if(newNode->leftChild)
            newNode->leftChild->parent = newNode;
        if(newNode->rightChild)
            newNode->rightChild->parent = newNode;

        p->data = p->rightChild->data;
        p->leftChild = newNode;
        p->rightChild = p->rightChild->rightChild;
        if(p->rightChild)
            p->rightChild->parent = p;  
    }
    else
        return;
}

void redBlackTree::rightRotate(node *p){
    if(p->leftChild){
        node *newNode = new node();
        newNode->data = p->data;
        newNode->color = p->leftChild->color;
        newNode->rightChild = p->rightChild;
        newNode->leftChild = p->leftChild->rightChild;
        newNode->parent = p;
        if(newNode->leftChild)
            newNode->leftChild->parent = newNode;
        if(newNode->rightChild)
            newNode->rightChild->parent = newNode;

        p->data = p->leftChild->data;
        p->rightChild = newNode;
        p->leftChild = p->leftChild->leftChild;
        if(p->leftChild)
            p->leftChild->parent = p;  
    }
    else
        return;
}