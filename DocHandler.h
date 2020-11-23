//
// Created by watso on 11/20/2020.
//

#ifndef SEARCH_ENGINE_WATSON_DOCHANDLER_H
#define SEARCH_ENGINE_WATSON_DOCHANDLER_H

#include <string>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class DocHandler {
private:
    char* dirPath;
    string metaPath;

public:
    DocHandler();
    DocHandler(char*);
    string getDocLoc();
    void findMetaData();
    void findMetaData(char*);

};


#endif //SEARCH_ENGINE_WATSON_DOCHANDLER_H
