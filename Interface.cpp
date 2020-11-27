//
// Created by watso on 11/26/2020.
//

#include "Interface.h"

//default constructor
Interface::Interface(){}
//search engine menu
void Interface::launchEngine(){
    cout<<endl<<"Welcome to the Corona Virus Search Engine developed by Kirk Watson!"<<endl;
    bool enginePower=true;
    int option=0;
    while(enginePower){
        cout<<"Search Engine Menu"<<endl;
        cout<<"\t1. Search"<<endl;
        cout<<"\t2. Create Index"<<endl;
        cout<<"\t3. Clear Index"<<endl;
        cout<<"\t4. Search Engine Stats"<<endl;
        cout<<"\t5. End Search"<<endl;
        cout<<"Please enter the number corresponding the desired action: ";
        menuEntry:
        cin>>option;
        if(option==1){
            if(indexer.hasElements()){
                searchIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        else if(option==2){
            if(!indexer.hasElements()){
                createIndex();
            }
            else{
                cout<<endl<<"The search engine index has already been filled, please clear index before recreating the index."<<endl;
            }
        }
        else if(option==3){
            if(indexer.hasElements()){
                clearIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        else if(option==4){
            if(indexer.hasElements()){
                engineStats();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        else if(option==5){
            cout<<endl<<"Shutting down search engine.";
            enginePower=false;
        }
        else{
            cout<<endl<<"Invalid input. Please try again: "<<endl;
            goto menuEntry;
        }
        cout<<endl;
    }
}
//create index
void Interface::createIndex(){
    int input;
    cout<<endl<<"Select one of the following options."<<endl;
    cout<<"\t1. Parse the corpus."<<endl;
    cout<<"\t2. Open a persistence file."<<endl;
    cout<<"Please enter the number corresponding the desired action: ";
    inputEntry:
    cin>>input;
    if(input==1){
        cout<<endl<<"Creating index..."<<endl;
        indexer.createIndex("C:\\Users\\watso\\Downloads\\cs2341_project_data");
        cout<<"...Complete!"<<endl;
    }
    else if(input==2){
        //TODO WHAT DOES PERSISTENCE FILE MEAN
        cout<<endl<<"WIP"<<endl;
    }
    else{
        cout<<"Invalid input. Please try again: "<<endl;
        goto inputEntry;
    }
}
//clear index
void Interface::clearIndex(){
    cout<<endl<<"Clearing index..."<<endl;
    indexer.clearIndex();
    cout<<"...Complete!"<<endl;

}
//search engine
void Interface::searchIndex(){
    //TODO
}
//search engine stats
void Interface::engineStats(){
    cout<<endl<<"Search Engine Statistics"<<endl;
    cout<<"\tTotal number of individual articles indexed: "<<indexer.getCorpusSize()<<endl;
    cout<<"\tAverage number of words indexed per article: "<<indexer.getAverage()<<endl;
    cout<<"\tTotal number of unique words: "<<indexer.getIndexSize()<<endl;
    cout<<"\tTotal number of unique authors: "<<indexer.getAuthorCount()<<endl;
    cout<<"\tTop 50 most frequent words:"<<endl;
    indexer.displayFreqWords();
};