#include "IndexHandler.h"

using namespace std;
//COMMAND ARGUMENT - "path query"
int main(int argc, char** argv){
    //create handler
    IndexHandler indexer=IndexHandler();
    //create index
    indexer.createIndex(argv[1]);
    //find query
    indexer.findQuery(argv[2]);

    return 0;
}
//delete comments in indexhandler.cpp
//delete not used files
    //DocHandler
//test with 1000 files
    //check time
    //less than a minute is good
//test with 12000 files
    //3 minutes is good