#ifndef SEARCH_ENGINE_WATSON_AVLNODE_H
#define SEARCH_ENGINE_WATSON_AVLNODE_H

using namespace std;

template <typename PlaceHolderType>
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

#endif //SEARCH_ENGINE_WATSON_AVLNODE_H
