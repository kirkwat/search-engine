//
// Created by watso on 11/26/2020.
//

#include "SearchEngine.h"

SearchEngine::SearchEngine(){}

void SearchEngine::createIndex(){
    indexer.createIndex("C:\\Users\\watso\\Downloads\\cs2341_project_data");
}
void SearchEngine::clearIndex(){
    indexer.clearIndex();
}
bool SearchEngine::indexFull(){
    return indexer.hasElements();
}
void SearchEngine::displayStats(){
    cout<<endl<<"Search Engine Statistics"<<endl;
    cout<<"\tTotal number of individual articles indexed: "<<indexer.getCorpusSize()<<endl;
    cout<<"\tAverage number of words indexed per article: "<<indexer.getAverage()<<endl;
    cout<<"\tTotal number of unique words: "<<indexer.getIndexSize()<<endl;
    cout<<"\tTotal number of unique authors: "<<indexer.getAuthorCount()<<endl;
    cout<<"\tTop 50 most frequent words:"<<endl;
    indexer.displayFreqWords();
}
void SearchEngine::search(string){

}
void SearchEngine::displaySearch(){

}