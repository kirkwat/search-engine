//
// Created by watso on 11/20/2020.
//

#ifndef SEARCH_ENGINE_WATSON_INDEXER_H
#define SEARCH_ENGINE_WATSON_INDEXER_H

#include <iostream>
#include <fstream>
#include "DSAvlTree.h"
#include "Word.h"
#include "DocHandler.h"

class Indexer {
private:
    DSAvlTree<Word> index;
    DSAvlTree<string> stopwords;
    DocHandler handler;


public:
    Indexer();
    void createIndex(char*);
    void findQuery(string);
    void readDoc();
    void getStopWords();
    string filterWord();

};


#endif //SEARCH_ENGINE_WATSON_INDEXER_H
