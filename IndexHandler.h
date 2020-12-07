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
#include "FreqWord.h"

using namespace std;
using namespace rapidjson;

class IndexHandler {
private:
    DSAvlTree<Word> index;
    DSAvlTree<Author> authIndex;
    set<string> stopwords;
    set<FreqWord> freqWords;
    int indexSize;
    int authorCount;
    int corpusSize;

public:
    IndexHandler();

    void createIndex(string);
    AvlNode<Word>* findWord(string);
    AvlNode<Author>* findAuthor(string);
    void readDoc(string);
    void parseText(string,string);
    void addAuthor(string,string);
    void getStopWords();
    void displayFreqWords();
    void getFreqWords(AvlNode<Word>*);
    void clearIndex();
    void saveIndex(string);
    void saveWord(AvlNode<Word>*,ofstream&);
    void saveAuthor(AvlNode<Author>*,ofstream&);
    void loadIndex(string);
    void loadWord(string);
    void loadAuthor(string);

    bool hasElements();
    int getIndexSize();
    int getCorpusSize();
    int getAuthorCount();
    double getAverage();
};


#endif //SEARCH_ENGINE_WATSON_INDEXHANDLER_H
