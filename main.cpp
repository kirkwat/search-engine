#include "Interface.h"

using namespace std;

int main(int argc, char** argv){

    Interface engine;
    engine.launchEngine();

/*
    set<string> set1;
    set1.insert("01");
    //set1.insert("02");

    set<string> set2;
    set2.insert("02");

    set<string> result;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),inserter(result, result.end()));

    set<string>::iterator itr;
    for (itr = result.begin(); itr != result.end(); ++itr){
        cout<<"\t"<<*itr<<endl;
    }

*/
    return 0;
}

//QUESTIONS
//should we have the path to corpus hardcoded into program
//what is a persistence file
//is the average number of words indexed by article just indexSize/corpusSize or is it the wordCountPerArticle/corpusSize
//will there be a search for multiple authors

//TODO
//create hashtable
//parse authors

//ROAD MAP
//doc handler
//doc object
//author object