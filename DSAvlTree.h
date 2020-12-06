#ifndef SEARCH_ENGINE_WATSON_DSAVLTREE_H
#define SEARCH_ENGINE_WATSON_DSAVLTREE_H
#include <iostream>
#include "AvlNode.h"

using namespace std;

template <typename PlaceHolderType>
class DSAvlTree{
private:
    //tree root
    AvlNode<PlaceHolderType>* root;
    //recursive copy function
    void copier(AvlNode<PlaceHolderType>*& to,const AvlNode<PlaceHolderType>* from) const{
        //if node does not exist
        if(from==nullptr){
            to=nullptr;
        }
        else{
            //copy node and elements
            to=new AvlNode<PlaceHolderType>;
            to->payload=from->payload;
            copier(to->left,from->left);
            copier(to->right,from->right);
        }
    }
    //recursive clear function
    void clear(AvlNode<PlaceHolderType>*& toDelete){
        //check if node exists
        if(toDelete!=nullptr){
            //clear left and right nodes
            clear(toDelete->left);
            clear(toDelete->right);
            delete toDelete;
            toDelete=nullptr;
        }
    }
    //calculate height of node
    int height(AvlNode<PlaceHolderType>* head) const{
        return head==nullptr ? -1 : head->height;
    }
    //calculate max of node
    int max(int lhs, int rhs) const{
        return lhs>rhs?lhs:rhs;
    }
    //insert node recursive function
    void insert(const PlaceHolderType& toInsert,AvlNode<PlaceHolderType>*& head){
        //check if node at location exists
        if(head== nullptr){
            head=new AvlNode<PlaceHolderType>(toInsert,nullptr,nullptr);
        }
            //if toInsert is less than head
        else if(toInsert<head->payload){
            insert(toInsert,head->left);
            //check for imbalance
            if(height(head->left)-height(head->right)==2){
                //case one
                if(toInsert<head->left->payload){
                    rotateLeftChild(head);
                }
                    //case two
                else{
                    doubleRotateLeftChild(head);
                }
            }
        }
            //if toInsert is greater than head
        else if(head->payload<toInsert){
            insert(toInsert,head->right);
            //check for imbalance
            if(height(head->right)-height(head->left)==2){
                //case four
                if(head->right->payload<toInsert){
                    rotateRightChild(head);
                }
                    //case three
                else{
                    doubleRotateRightChild(head);
                }
            }
        }
        //ignore nodes already in list
        else;
        //get height of node
        head->height=max(height(head->left),height(head->right))+1;
    }
    //imbalanced tree case one
    void rotateLeftChild(AvlNode<PlaceHolderType>*& k2){
        //single rotation
        AvlNode<PlaceHolderType>* k1=k2->left;
        k2->left=k1->right;
        k1->right=k2;
        k2->height=max(height(k2->left),height(k2->right))+1;
        k1->height=max(height(k1->left),k2->height)+1;
        k2=k1;
    }
    //imbalanced tree case two
    void doubleRotateLeftChild(AvlNode<PlaceHolderType>*& k3){
        //double rotation
        rotateRightChild(k3->left);
        rotateLeftChild(k3);
    }
    //imbalanced tree case four
    void rotateRightChild(AvlNode<PlaceHolderType>*& k1){
        //single rotation
        AvlNode<PlaceHolderType>* k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;
        k1->height=max(height(k1->left),height(k1->right))+1;
        k2->height=max(height(k2->right),k1->height)+1;
        k1=k2;
    }
    //imbalanced tree case three
    void doubleRotateRightChild(AvlNode<PlaceHolderType>*& k1){
        //double rotation
        rotateLeftChild(k1->right);
        rotateRightChild(k1);
    }
    //recursive search function
    AvlNode<PlaceHolderType>* search(PlaceHolderType toFind, AvlNode<PlaceHolderType>* head){
        //if element is or is not found
        if(head==nullptr||head->payload==toFind){
            return head;
        }
        //if element is greater than head
        if(head->payload<toFind){
            return search(toFind,head->right);
        }
        //if element is less than head
        else{
            return search(toFind,head->left);
        }
    }
public:
    //default constructor
    DSAvlTree(){
        root=nullptr;
    }
    //copy constructor
    DSAvlTree(const DSAvlTree & copy) {
        copier(this->root,copy.root);
    }
    //copy assignment operator
    DSAvlTree& operator=(const DSAvlTree& copy) {
        if (this != &copy) {
            if (root != nullptr) {
                clear(root);
            }
            copier(this->root,copy.root);
        }
        return *this;
    }
    //destructor
    ~DSAvlTree() {
        if (root != nullptr) {
            clear(root);
        }
    }
    //insert element in tree
    void insert(const PlaceHolderType & x){
        insert(x,root);
    }
    //search for element in tree and return pointer
    AvlNode<PlaceHolderType>* search(PlaceHolderType x){
        return search(x, root);
    }
    //clear avl tree
    void clear(){
        if(root!= nullptr){
            clear(root);
        }
    }
    //get root node
    AvlNode<PlaceHolderType>* getRoot(){
        return root;
    }
};

#endif //SEARCH_ENGINE_WATSON_DSAVLTREE_H
