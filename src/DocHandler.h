#ifndef SEARCH_ENGINE_WATSON_DOCHANDLER_H
#define SEARCH_ENGINE_WATSON_DOCHANDLER_H

#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include "../rapidjson/document.h"
#include "../rapidjson/istreamwrapper.h"
#include "porter2_stemmer.h"
#include "Article.h"
#include "Word.h"
#include "AvlNode.h"

using namespace std;
using namespace rapidjson;

//This class handles the documents that are results of a search.
class DocHandler {
private:
    set<Article>sortedDocs;                 //articles that are sorted by rank
    vector<AvlNode<Word>*> searchWords;     //words used in a search
    int corpusSize;                         //size of the corpus
    string corpusPath;                      //file path to corpus
    string metaPath;                        //file path to corpus metadata
    int wordCount;                          //word count of a document

public:
    DocHandler();
    void processDocs(set<string>,vector<AvlNode<Word>*>,string,int);
    void printTopDocs();
    double rankDoc(string);
    int parseText(string);
    void findMetaData(string);
    void viewDoc(int);
    void clearProcessor();
};


#endif //SEARCH_ENGINE_WATSON_DOCHANDLER_H
