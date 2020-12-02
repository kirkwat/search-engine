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
    char* filePath="C:\\Users\\watso\\Downloads\\cs2341_project_data";

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
    bool indexFull();
    void displayStats();
    void search(string);
    void displaySearch();
    void clearSearch();

    void testIndex();
};


#endif //SEARCH_ENGINE_WATSON_SEARCHENGINE_H
