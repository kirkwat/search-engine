#include "IndexHandler.h"
#include "Interface.h"

using namespace std;
//COMMAND ARGUMENT - "path query"
int main(int argc, char** argv){
    /*
    //create handler
    IndexHandler indexer=IndexHandler();
    //create index
    indexer.createIndex(argv[1]);
    //find query
    indexer.findQuery(argv[2]);
     */
    Interface engine;
    engine.launchEngine();

    return 0;
}

//QUESTIONS
//should we have the path to corpus hardcoded into program
//what is a persistence file
//is the average number of words indexed by article just indexSize/corpusSize or is it the wordCountPerArticle/corpusSize

//TODO
//create hashtable
//parse authors