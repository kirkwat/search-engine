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
void SearchEngine::search(string query){
    int searchType=-1;
    string word;
    stringstream ss;
    ss.str(query);
    //read stream
    while(ss>>word){
        if(word=="AND"){
            searchType=0;
        }
        else if(word=="OR"){
            searchType=1;
        }
        else if(word=="NOT"){
            searchType=2;
        }
        else if(word=="AUTHOR"){
            searchType=3;
        }
        else{
            //search for author
            if(searchType==3){
                AvlNode<Author>* findAuth=indexer.findAuthor(word);
                //if query was found
                if(findAuth!=nullptr){
                    authDocs=findAuth->payload.getDocs();
                }
            }
            //search for word
            else{
                AvlNode<Word>* findQuery=indexer.findWord(word);
                //if query was found
                if(findQuery!=nullptr){
                    if(searchType==2){
                        notDocs.push_back(findQuery->payload.getDocs());
                    }
                    else{
                        conditionalDocs.push_back(findQuery->payload.getDocs());
                    }
                    //TODO SET DIFFERENCE
                    //SET INTERSECTION
                }
            }
        }
    }
}
void SearchEngine::displaySearch(){

}