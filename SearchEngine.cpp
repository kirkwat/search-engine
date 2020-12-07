//
// Created by watso on 11/26/2020.
//

#include "SearchEngine.h"

//default constructor
SearchEngine::SearchEngine(){}
//create index
void SearchEngine::createIndex(){
    indexer.createIndex(filePath);
}
//clear index
void SearchEngine::clearIndex(){
    indexer.clearIndex();
}
//print engine stats
void SearchEngine::displayStats(){
    cout<<endl<<"Search Engine Statistics"<<endl;
    cout<<"\tTotal number of individual articles indexed: "<<indexer.getCorpusSize()<<endl;
    cout<<"\tAverage number of words indexed per article: "<<indexer.getAverage()<<endl;
    cout<<"\tTotal number of unique words: "<<indexer.getIndexSize()<<endl;
    cout<<"\tTotal number of unique authors: "<<indexer.getAuthorCount()<<endl;
    cout<<"\tTop 50 most frequent words:"<<endl;
    cout<<"\t\tWord - # of Appearances"<<endl;
    indexer.displayFreqWords();
}
//search query
void SearchEngine::search(string query){
    int searchType=-1;
    int searchOperator=-1;
    //read query as stream
    string word;
    stringstream ss;
    ss.str(query);
    //read stream
    while(ss>>word){
        //set AND operator
        if(word=="AND"){
            searchOperator=0;
        }
        //set OR operator
        else if(word=="OR"){
            searchOperator=1;
        }
        //add NOT search
        else if(word=="NOT"){
            searchType=0;
        }
        //add AUTHOR search
        else if(word=="AUTHOR"){
            searchType=1;
        }
        //get documents for query and add to proper set
        else{
            //search for author
            if(searchType==1){
                AvlNode<Author>* findAuth=indexer.findAuthor(word);
                //if author was found
                if(findAuth!=nullptr){
                    //add to author set
                    authDocs=findAuth->payload.getDocs();
                }
                else{
                    set<string> result;
                    finalDocs=result;
                    return;
                }
            }
            //search for word
            else{
                AvlNode<Word>* findQuery=indexer.findWord(word);
                //if query was found
                if(findQuery!=nullptr){
                    //if NOT search
                    if(searchType==0){
                        //add to NOT set vector
                        notDocs.push_back(findQuery->payload.getDocs());
                    }
                    //normal word search
                    else{
                        //add to word set vector
                        conditionalDocs.push_back(findQuery->payload.getDocs());
                        searchWords.push_back(findQuery);
                    }
                }
                //if AND search but query not found
                else if(searchOperator==0){
                    set<string> result;
                    finalDocs=result;
                    return;
                }
            }
        }
    }
    //or - combine all unique docs together
    //and - remove docs except for matching docs
    //if there are not sets - remove matching docs
    //if there is author - remove docs without author
    int wordVecSize=conditionalDocs.size();
    //if searching by word
    if(wordVecSize!=0){
        //if searching by bool operator aka multiple words
        if(wordVecSize>1){
            //AND operator
            if(searchOperator==0){
                //get intersections for docs of every search word
                for (int x = 1; x < conditionalDocs.size(); x++) {
                    set<string> result;
                    set_intersection(conditionalDocs[0].begin(), conditionalDocs[0].end(),conditionalDocs[x].begin(), conditionalDocs[x].end(),inserter(result, result.end()));
                    conditionalDocs[0] = result;
                }
            }
            //OR operator
            else{
                //combine docs of every search word
                for(int x=1;x<conditionalDocs.size();x++){
                    set<string> result;
                    set_union(conditionalDocs[0].begin(), conditionalDocs[0].end(), conditionalDocs[x].begin(), conditionalDocs[x].end(),inserter(result, result.end()));
                    conditionalDocs[0]=result;
                }
            }
        }
        //if there are NOT words
        int notVecSize=notDocs.size();
        if(notVecSize!=0){
            //if there are multiple NOT words
            if (notVecSize > 1){
                //combine docs of every search word
                for(int x=1;x<notDocs.size();x++){
                    set<string> result;
                    set_union(notDocs[0].begin(), notDocs[0].end(), notDocs[x].begin(), notDocs[x].end(),inserter(result, result.end()));
                    notDocs[0]=result;
                }
            }
            //remove NOT word doc set from search word doc set
            set<string> result;
            set_difference(conditionalDocs[0].begin(), conditionalDocs[0].end(), notDocs[0].begin(), notDocs[0].end(),inserter(result, result.end()));
            conditionalDocs[0]=result;
        }
        //if there is an author
        if(!authDocs.empty()){
            //get intersections for search word doc set and author doc set
            set<string> result;
            set_intersection(conditionalDocs[0].begin(), conditionalDocs[0].end(), authDocs.begin(), authDocs.end(),inserter(result, result.end()));
            conditionalDocs[0]=result;
        }
        //add to final set
        finalDocs=conditionalDocs[0];
    }
    //if searching by only author
    else{
        //add to final set
        finalDocs=authDocs;
    }
}
//display results
void SearchEngine::displaySearch(){
    //see if any docs were found
    if(!finalDocs.empty()){
        //print results
        cout<<"Results"<<endl;
        cout<<"   Number of documents found: "<<finalDocs.size()<<endl;
        //rank results
        docProcessor.processDocs(finalDocs,searchWords,filePath,indexer.getCorpusSize());
        //print top 15 docs
        cout<<"   Top 15 results:"<<endl;
        docProcessor.printTopDocs();
        //allow user to view a document
        int option=-1;
        cout<<endl<<"If you wish to view a document, please enter the number corresponding the result,\nor enter 0 to return to the main menu: ";
        menuEntry:
        cin>>option;
        //view doc
        if(option>0&&option<16){
            docProcessor.viewDoc(option);
        }
        //user input error
        else if(option!=0){
            cout<<endl<<"Invalid input. Please try again: ";
            goto menuEntry;
        }
    }
    //if no docs were found
    else{
        cout<<"No results were found :/"<<endl;
    }
}
//clear search
void SearchEngine::clearSearch() {
    //clear sets
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
    searchWords.clear();
    //clear dochandler info
    docProcessor.clearProcessor();
}
//check if index has elements
bool SearchEngine::indexFull(){
    return indexer.hasElements();
}
//load persistence file to create index
void SearchEngine::loadIndex(string iPath){
    indexer.loadIndex(iPath);
}
//save index to a persistence file
void SearchEngine::saveIndex(string oPath){
    indexer.saveIndex(oPath);
}