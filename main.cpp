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

//TODO
//create hashtable
//multiple authors in search
//optimize relevancy
//add persistence file feature
//how do we ignore files that do not have full text
//fix create,clear,create crash bug
//comment and organize code