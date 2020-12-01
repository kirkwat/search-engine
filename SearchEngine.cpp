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
    int searchOperator=-1;
    string word;
    stringstream ss;
    ss.str(query);
    //read stream
    while(ss>>word){
        if(word=="AND"){
            searchOperator=0;
        }
        else if(word=="OR"){
            searchOperator=1;
        }
        else if(word=="NOT"){
            searchType=0;
        }
        else if(word=="AUTHOR"){
            searchType=1;
        }
        else{
            //search for author
            if(searchType==1){
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
                    if(searchType==0){
                        notDocs.push_back(findQuery->payload.getDocs());
                    }
                    else{
                        conditionalDocs.push_back(findQuery->payload.getDocs());
                    }
                }
            }
        }
    }
    int wordVecSize=conditionalDocs.size();
    //if searching by word
    if(wordVecSize!=0){
        //if searching by bool operator aka multiple words
        if(wordVecSize>1){
            //AND operator
            if(searchOperator==0){
                for(int x=1;x<conditionalDocs.size();x++){
                    set<string> result;
                    set_intersection(conditionalDocs[0].begin(), conditionalDocs[0].end(), conditionalDocs[x].begin(), conditionalDocs[x].end(),inserter(result, result.end()));
                    conditionalDocs[0]=result;
                }
            }
            //OR operator
            else{
                for(int x=1;x<conditionalDocs.size();x++){
                    set<string> result;
                    set_union(conditionalDocs[0].begin(), conditionalDocs[0].end(), conditionalDocs[x].begin(), conditionalDocs[x].end(),inserter(result, result.end()));
                    conditionalDocs[0]=result;
                }
            }
        }
        //if there are not words
        int notVecSize=notDocs.size();
        //if there are not words
        if(notVecSize!=0){
            //if there are multiple words
            if (notVecSize > 1){
                for(int x=1;x<notDocs.size();x++){
                    set<string> result;
                    set_union(notDocs[0].begin(), notDocs[0].end(), notDocs[x].begin(), notDocs[x].end(),inserter(result, result.end()));
                    notDocs[0]=result;
                }
            }
            set<string> result;
            set_difference(conditionalDocs[0].begin(), conditionalDocs[0].end(), notDocs[0].begin(), notDocs[0].end(),inserter(result, result.end()));
            conditionalDocs[0]=result;
        }
        //if there is an author
        if(!authDocs.empty()){
            set<string> result;
            set_intersection(conditionalDocs[0].begin(), conditionalDocs[0].end(), authDocs.begin(), authDocs.end(),inserter(result, result.end()));
            conditionalDocs[0]=result;
        }
        finalDocs=conditionalDocs[0];
    }
    //if searching by author
    else{
        finalDocs=authDocs;
    }
    //or - combine all unique docs together
    //and - remove docs except for matching docs
    //if there are not sets - remove matching docs
    //if there is author - remove docs without author
}
void SearchEngine::displaySearch(){
    if(!finalDocs.empty()){
        set<string>::iterator itr;
        cout<<"Number of documents: "<<finalDocs.size()<<endl;
        cout<<"Document IDs:"<<endl;
        for (itr = finalDocs.begin();itr != finalDocs.end(); ++itr){
            cout<<"\t"<<*itr<<endl;
        }
    }
    else{
        cout<<"No documents were found"<<endl;
    }
}
void SearchEngine::clearSearch() {
    authDocs.clear();
    finalDocs.clear();
    for(int x=0;x<conditionalDocs.size();x++){
        conditionalDocs[x].clear();
    }
    conditionalDocs.clear();
    for(int x=0;x<notDocs.size();x++){
        notDocs[x].clear();
    }
    notDocs.clear();
}

void SearchEngine::testIndex() {
    indexer.testIndex();
}