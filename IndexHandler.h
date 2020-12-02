#ifndef SEARCH_ENGINE_WATSON_INDEXHANDLER_H
#define SEARCH_ENGINE_WATSON_INDEXHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <set>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "porter2_stemmer.h"
#include "DSAvlTree.h"
#include "AvlNode.h"
#include "Word.h"
#include "Author.h"

using namespace std;
using namespace rapidjson;

class IndexHandler {
private:
    DSAvlTree<Word> index;
    DSAvlTree<Author> authIndex;
    set<string> stopwords;
    int indexSize;
    int authorCount;
    int corpusSize;

public:
    IndexHandler();

    void createIndex(char*);
    AvlNode<Word>* findWord(string);
    AvlNode<Author>* findAuthor(string);
    void readDoc(string);
    void parseText(string,string);
    void addAuthor(string,string);
    void getStopWords();
    void displayFreqWords();
    void clearIndex();

    bool hasElements();
    int getIndexSize();
    int getCorpusSize();
    int getAuthorCount();
    double getAverage();
};


#endif //SEARCH_ENGINE_WATSON_INDEXHANDLER_H
