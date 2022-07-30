#ifndef SEARCH_ENGINE_WATSON_INDEXHANDLER_H
#define SEARCH_ENGINE_WATSON_INDEXHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <set>
#include "../rapidjson/document.h"
#include "../rapidjson/istreamwrapper.h"
#include "porter2_stemmer.h"
#include "DSAvlTree.h"
#include "DSHashTable.h"
#include "AvlNode.h"
#include "Word.h"
#include "Author.h"
#include "FreqWord.h"

using namespace std;
using namespace rapidjson;

//This class controls the search index allowing for creation and search queries.
class IndexHandler {
private:
    DSAvlTree<Word> index;                          //index storing words parsed from articles
    DSHashTable<Author, string> authIndexHash;      //index storing authors parsed from articles
    DSAvlTree<Author> authIndex;                    //index storing authors parsed from articles
    set<string> stopwords;                          //set of common words to be ignored while parsing articles
    set<FreqWord> freqWords;                        //set of most frequent words used in the corpus
    int indexSize;                                  //size of the word index
    int authorCount;                                //amount of authors in the author index
    int corpusSize;                                 //size of the article corpus

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
