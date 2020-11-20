//
// Created by watso on 11/20/2020.
//

#ifndef SEARCH_ENGINE_WATSON_DOCHANDLER_H
#define SEARCH_ENGINE_WATSON_DOCHANDLER_H

#include <string>

using namespace std;

class DocHandler {
private:
    string path;

public:
    DocHandler();
    DocHandler(char*);
    string getDocLoc();
    void findMetaData();

};


#endif //SEARCH_ENGINE_WATSON_DOCHANDLER_H
