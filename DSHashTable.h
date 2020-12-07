//
// Created by watso on 12/2/2020.
//
//TODO incomplete :/
#ifndef SEARCH_ENGINE_WATSON_DSHASHTABLE_H
#define SEARCH_ENGINE_WATSON_DSHASHTABLE_H

#include <list>

template <typename key, typename value>
class DSHashTable{/*
private:
    int size;
    int insertions;
    list<pair<key, value>>* table;

public:
    DSHashTable(int i){
        size=i;
        table=new list<pair<key, value>>[size];
    }
    DSHashTable(const DSHashTable& other){
        *this = other;
    }
    DSHashTable& operator=(const DSHashTable& other){
        if(this = &other){
            return *this;
        }
        if(!isEmpty()){
            clear();
        }
        copyTable(other);
        return *this;
    }
    ~DSHashTable(){
        clear();
    }
    void insert(key& k, value& v){
        insertions++;
        if(insertions==size){
            resize();
        }
        //table[hashIndex(key)].push_back((k,v));
    }
    void resize(){

    }
    int hashIndex(key& k){
        //return hash(k);
    }
    //bool remove(const KeyType& deleteKey);
    //bool retrieve(const KeyType& searchKey, DataType& returnItem) const;
    void clear(){}

    bool isEmpty() const{}*/

};

#endif //SEARCH_ENGINE_WATSON_DSHASHTABLE_H
