#ifndef SEARCH_ENGINE_WATSON_DSHASHTABLE_H
#define SEARCH_ENGINE_WATSON_DSHASHTABLE_H

#include<functional>
#include <set>
#include <ostream>

using namespace std;

//This class implements a hashtable data structure to hold the author index.
template<typename K, typename V>
class DSHashTable{
private:
    struct HashNode{
        K key;
        set<V> values;
        HashNode* next;

        HashNode(const K& k, const V& v): key(k), next(nullptr){
            values.insert(v);
        }
    };
    int size;
    HashNode** arr;
    int uniqueSize;

public:
    //create new table
    DSHashTable(): size(100003), uniqueSize(0){
        arr = new HashNode* [size];
    }
    void insert(const K& key, const V& val){
        //hash key
        size_t hashValue = hash<K>{}(key);
        int loc = hashValue % size;

        //get bucket
        HashNode* bucket = arr[loc];
        HashNode* prev = nullptr;

        //get to bucket that has same key
        while(bucket!=nullptr && bucket->key!=key){
            prev = bucket;
            bucket = bucket->next;
        }

        //if key not found
        if(bucket==nullptr){
            bucket = new HashNode(key, val);
            //start list
            if(prev == nullptr)
                arr[loc] = bucket;
            //or add to list
            else
                prev->next = bucket;
            uniqueSize++;
        }
        else
            bucket->values.insert(val);

    }
    set<V>* get(const K& key){
        //hash key
        size_t hashValue = hash<K>{}(key);
        int loc = hashValue % size;

        //get bucket
        HashNode* bucket = arr[loc];

        while(bucket!=nullptr){
            if(bucket->key==key){
                return &bucket->values;
            }
            bucket = bucket->next;
        }
        return nullptr;
    }
    int getUniqueSize(){return uniqueSize;};
    ~DSHashTable() {
        //destroy all buckets one by one
        for (int i=0; i < size; i++) {
            HashNode* curr = arr[i];
            while (curr != nullptr) {
                HashNode* prev = curr;
                curr = curr->next;
                delete prev;
            }
            arr[i] = nullptr;
        }
        //destroy hash table
        delete[]arr;
    }
    void output(ostream& out){
        for(int i=0;i<size;i++){
            HashNode* bucket = arr[i];
            if(bucket==nullptr) continue;
            else{
                while(bucket!=nullptr){
                    out<<bucket->key;
                    for(const auto& e: bucket->values){
                        out<<","<<e;
                    }
                    bucket = bucket->next;
                }
            }
            out<<endl;
        }
    }
    void clear(){
        //destroy all buckets one by one
        for (int i=0; i < size; i++) {
            HashNode* curr = arr[i];

            while (curr != nullptr) {
                HashNode* prev = curr;
                curr = curr->next;
                delete prev;
            }
            arr[i] = nullptr;
        }
        uniqueSize=0;
    }
};

#endif //SEARCH_ENGINE_WATSON_DSHASHTABLE_H
