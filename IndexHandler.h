//
// Created by watso on 11/20/2020.
//

#ifndef SEARCH_ENGINE_WATSON_INDEXHANDLER_H
#define SEARCH_ENGINE_WATSON_INDEXHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <set>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "porter2_stemmer.h"
#include "DSAvlTree.h"
#include "AvlNode.h"
#include "Word.h"

using namespace std;
using namespace rapidjson;

class IndexHandler {
private:
    DSAvlTree<Word> index;
    set<string> stopwords;


public:
    IndexHandler();
    void createIndex(char*);
    void findQuery(string);
    void readDoc(string);
    void parseText(string,string);
    void getStopWords();

};


#endif //SEARCH_ENGINE_WATSON_INDEXHANDLER_H
