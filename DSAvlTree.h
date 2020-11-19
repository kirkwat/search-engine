//
// Created by watso on 11/18/2020.
//

#ifndef SEARCH_ENGINE_WATSON_DSAVLTREE_H
#define SEARCH_ENGINE_WATSON_DSAVLTREE_H

using namespace std;

template <typename PlaceHolderType>
class DSAvlTree{
private:
    //node class
    class AvlNode{
    public:
        PlaceHolderType payload;
        AvlNode* left;
        AvlNode* right;
        int height;
        //default constructor
        AvlNode(){
            left=right=nullptr;
        }
        //overloaded constructor
        AvlNode (const PlaceHolderType& element,AvlNode* lt, AvlNode* rt, int h=0):payload(element),left(lt),right(rt),height(h) {};
    };
    //tree root
    AvlNode* root;
    //recursive copy function
    void copier(AvlNode*& to,const AvlNode* from) const{
        //if node does not exist
        if(from==nullptr){
            to=nullptr;
        }
        else{
            //copy node and elements
            to=new AvlNode;
            to->payload=from->payload;
            copier(to->left,from->left);
            copier(to->right,from->right);
        }
    }
    //recursive clear function
    void clear(AvlNode*& toDelete){
        //delete left node
        if (toDelete->left != nullptr){
            clear(toDelete->left);
        }
        //delete right node
        if (toDelete->right != nullptr){
            clear(toDelete->right);
        }
        delete toDelete;
    }
    //calculate height of node
    int height(AvlNode* head) const{
        return head==nullptr ? -1 : head->height;
    }
    //calculate max of node
    int max(int lhs, int rhs) const{
        return lhs>rhs?lhs:rhs;
    }
    //insert node recursive function
    void insert(const PlaceHolderType& toInsert,AvlNode*& head){
        //check if node at location exists
        if(head== nullptr){
            head=new AvlNode(toInsert,nullptr,nullptr);
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
            //TODO is this fine to deal with multiples
            //ignore nodes already in list
        else{}
        //get height of node
        head->height=max(height(head->left),height(head->right))+1;
    }
    //imbalanced tree case one
    void rotateLeftChild(AvlNode*& k2){
        //single rotation
        AvlNode* k1=k2->left;
        k2->left=k1->right;
        k1->right=k2;
        k2->height=max(height(k2->left),height(k2->right))+1;
        k1->height=max(height(k1->left),k2->height)+1;
        k2=k1;
    }
    //imbalanced tree case two
    void doubleRotateLeftChild(AvlNode*& k3){
        //double rotation
        rotateRightChild(k3->left);
        rotateLeftChild(k3);
    }
    //imbalanced tree case four
    void rotateRightChild(AvlNode*& k1){
        //single rotation
        AvlNode* k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;
        k1->height=max(height(k1->left),height(k1->right))+1;
        k2->height=max(height(k2->right),k1->height)+1;
        k1=k2;
    }
    //imbalanced tree case three
    void doubleRotateRightChild(AvlNode*& k1){
        //double rotation
        rotateLeftChild(k1->right);
        rotateRightChild(k1);
    }
    //recursive search function
    AvlNode* search(PlaceHolderType toFind, AvlNode* head){
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
        if (root == nullptr) {
            return;
        }
        else{
            clear(root);
        }
    }
    //insert element in tree
    void insert(const PlaceHolderType & x){
        insert(x,root);
    }
    //search  for element in tree and return pointer
    AvlNode* search(PlaceHolderType x){
        return search(x, root);
    }
    //search  for element in tree and return payload
    PlaceHolderType& searchPL(PlaceHolderType x){
        return search(x, root)->payload;
    }
};

#endif //SEARCH_ENGINE_WATSON_DSAVLTREE_H
