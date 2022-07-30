#ifndef SEARCH_ENGINE_WATSON_SEARCHENGINE_H
#define SEARCH_ENGINE_WATSON_SEARCHENGINE_H

#include "IndexHandler.h"
#include "DocHandler.h"
#include "porter2_stemmer.h"
#include <set>
#include <vector>
#include <algorithm>

//This class processes search queries and displays results and stats from the corpus.
class SearchEngine {
private:
    string filePath=R"(../dataset)";        //file path to corpus of research articles
    IndexHandler indexer;                   //instance of the index handler
    DocHandler docProcessor;                //instance of doc handler for displaying articles
    set<string> authDocs;                   //set of documents that match an AUTHOR query
    vector<set<string>> notDocs;            //set of documents that match a NOT query
    vector<set<string>> conditionalDocs;    //set of documents that match a AND or OR query
    set<string> finalDocs;                  //final set of documents that match the search query
    vector<AvlNode<Word>*> searchWords;     //words in search query

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
