#include "Interface.h"

using namespace std;

int main(int argc, char** argv){

    Interface engine;
    engine.launchEngine();

    return 0;
}

//QUESTIONS
//should we have the path to corpus hardcoded into program
//what is a persistence file
//is the average number of words indexed by article just indexSize/corpusSize or is it the wordCountPerArticle/corpusSize
//will there be a search for multiple authors
//using metadata to ignore certain files

//TODO
//create hashtable
//parse authors

//ROAD MAP
//doc handler
//doc object
//author object