#include "IndexHandler.h"
#include <time.h>

using namespace std;
//COMMAND ARGUMENT - "path query"
int main(int argc, char** argv){
    //timer
    clock_t beginning = clock();
    //create handler
    IndexHandler indexer=IndexHandler();
    //create index
    indexer.createIndex(argv[1]);
    //find query
    indexer.findQuery(argv[2]);

    //calculate run time
    clock_t ending = clock();
    double runTime = (double) (ending - beginning) / CLOCKS_PER_SEC;
    cout<<"Time elapsed: "<<runTime<<endl;

    return 0;
}