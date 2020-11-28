//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_SEARCHENGINE_H
#define SEARCH_ENGINE_WATSON_SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocHandler.h"

class SearchEngine {
private:
    IndexHandler indexer;
    DocHandler docProcessor;

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
