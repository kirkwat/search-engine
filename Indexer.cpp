//
// Created by watso on 11/20/2020.
//

#include "Indexer.h"

//default constructor
Indexer::Indexer(){}
//create index
void Indexer::createIndex(char* data){
    //create stopwords tree
    getStopWords();
    //create doc handler
    handler=DocHandler(data);
}
//find search word
void Indexer::findQuery(string){

}
//create stopword list
void Indexer::getStopWords(){
    ifstream readfile;
    //open file
    readfile.open("../stopwords.txt");
    //check if it was opened properly
    if (!readfile.is_open()) {
        cout << "Could not open file stopwords.txt." << endl;
        return;
    }
    //make stopword tree
    string input;
    while(readfile>>input){
        stopwords.insert(input);
    }
    readfile.close();
}