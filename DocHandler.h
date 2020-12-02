//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_DOCHANDLER_H
#define SEARCH_ENGINE_WATSON_DOCHANDLER_H

#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "porter2_stemmer.h"
#include "Article.h"
#include "Word.h"
#include "AvlNode.h"

using namespace std;
using namespace rapidjson;

class DocHandler {
private:
    set<Article>sortedDocs;
    vector<AvlNode<Word>*> searchWords;
    int corpusSize;
    string corpusPath;
    string metaPath;
    int wordCount;

public:
    DocHandler();
    void processDocs(set<string>,vector<AvlNode<Word>*>,string,int);
    void printTopDocs();
    double rankDoc(string);
    int parseText(string);
    void findMetaData(string);

};


#endif //SEARCH_ENGINE_WATSON_DOCHANDLER_H
