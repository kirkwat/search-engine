#include "Interface.h"

using namespace std;

int main(int argc, char** argv){

    Interface engine;
    engine.launchEngine();

    return 0;
}

//QUESTIONS
//what is a persistence file
//using metadata to ignore certain files
//should i have the user enter corpus path?

//TODO
//persistence file
//create hashtable
//fix create,clear,create crash bug
//print 50 top frequent words