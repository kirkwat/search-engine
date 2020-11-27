//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_INTERFACE_H
#define SEARCH_ENGINE_WATSON_INTERFACE_H

#include <iostream>
#include "IndexHandler.h"

using namespace std;

class Interface {
private:
    IndexHandler indexer;

public:
    Interface();
    void launchEngine();
    void createIndex();
    void clearIndex();
    void searchIndex();
    void engineStats();

};


#endif //SEARCH_ENGINE_WATSON_INTERFACE_H
