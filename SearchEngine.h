//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_SEARCHENGINE_H
#define SEARCH_ENGINE_WATSON_SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocHandler.h"
#include "porter2_stemmer.h"
#include <set>
#include <list>

class SearchEngine {
private:
    IndexHandler indexer;
    DocHandler docProcessor;
    set<string> authDocs;
    list<set<string>> notDocs;
    list<set<string>> conditionalDocs;




public:
    SearchEngine();

    void createIndex();
    void clearIndex();
    bool indexFull();
    void displayStats();
    void search(string);
    void displaySearch();
};


#endif //SEARCH_ENGINE_WATSON_SEARCHENGINE_H
