#ifndef SEARCH_ENGINE_WATSON_INTERFACE_H
#define SEARCH_ENGINE_WATSON_INTERFACE_H

#include <iostream>
#include "SearchEngine.h"

using namespace std;

//This class contains the interface that user interacts with to access the search engine.
class Interface {
private:
    SearchEngine engine;    //instance of the search engine

public:
    Interface();

    void launchEngine();
    void createIndex();
    void clearIndex();
    void searchIndex();
    void engineStats();
};


#endif //SEARCH_ENGINE_WATSON_INTERFACE_H
