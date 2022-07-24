//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_SEARCHENGINE_H
#define SEARCH_ENGINE_WATSON_SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocHandler.h"
#include "porter2_stemmer.h"
#include <set>
#include <vector>
#include <algorithm>

class SearchEngine {
private:
    //PLACE CORPUS PATH HERE
    //EXAMPLE:
    //C:\Users\Kirk\Documents\GitHub\search-engine\dataset
    string filePath=R"(C:\Users\Kirk\Documents\GitHub\search-engine\dataset)";
    IndexHandler indexer;
    DocHandler docProcessor;
    set<string> authDocs;
    vector<set<string>> notDocs;
    vector<set<string>> conditionalDocs;
    set<string> finalDocs;
    vector<AvlNode<Word>*> searchWords;

public:
    SearchEngine();

    void createIndex();
    void clearIndex();
    void displayStats();
    void search(string);
    void displaySearch();
    void clearSearch();
    bool indexFull();
    void loadIndex(string);
    void saveIndex(string);
};


#endif //SEARCH_ENGINE_WATSON_SEARCHENGINE_H
