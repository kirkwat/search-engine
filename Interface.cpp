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
    //loop until user terminates program
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
        //search index
        if(option==1){
            //check if index has been created
            if(engine.indexFull()){
                searchIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        //create index
        else if(option==2){
            //check if index is empty
            if(!engine.indexFull()){
                createIndex();
            }
            else{
                cout<<endl<<"The search engine index has already been filled, please clear index before recreating the index."<<endl;
            }
        }
        //clear index
        else if(option==3){
            //check if index has been created
            if(engine.indexFull()){
                clearIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        //engine stats
        else if(option==4){
            //check if index has been created
            if(engine.indexFull()){
                engineStats();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        //end program
        else if(option==5){
            cout<<endl<<"Shutting down search engine.";
            enginePower=false;
        }
        //user input error
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
    //create index menu
    cout<<endl<<"Select one of the following options."<<endl;
    cout<<"\t1. Parse the corpus."<<endl;
    cout<<"\t2. Open a persistence file."<<endl;
    cout<<"Please enter the number corresponding the desired action: ";
    inputEntry:
    cin>>input;
    //parse corpus
    if(input==1){
        cout<<endl<<"Creating index..."<<endl;
        engine.createIndex();
        cout<<"...Complete!"<<endl;
    }
    //persistence file
    else if(input==2){
        cout<<endl<<"Loading persistence file and creating index..."<<endl;
        engine.loadIndex("../persistenceFile.txt");
        cout<<"...Complete!"<<endl;
    }
    //user input error
    else{
        cout<<"Invalid input. Please try again: "<<endl;
        goto inputEntry;
    }
}
//clear index
void Interface::clearIndex(){
    int input;
    //clear index menu
    cout<<endl<<"Select one of the following options."<<endl;
    cout<<"\t1. Clear index."<<endl;
    cout<<"\t2. Save and clear index."<<endl;
    cout<<"Please enter the number corresponding the desired action: ";
    inputEntry:
    cin>>input;
    //only clear index
    if(input==1){
        cout<<endl<<"Clearing index..."<<endl;
        engine.clearIndex();
        cout<<"...Complete!"<<endl;
    }
    //save and clear index
    else if(input==2){
        cout<<endl<<"Loading persistence file and clearing index..."<<endl;
        //save index
        engine.saveIndex("../persistenceFile.txt");
        //clear index
        engine.clearIndex();
        cout<<"...Complete!"<<endl;
    }
    //user input error
    else{
        cout<<"Invalid input. Please try again: "<<endl;
        goto inputEntry;
    }
}
//search engine
void Interface::searchIndex(){
    cout<<endl<<"Please enter your query below using the proper formatting."<<endl;
    cout<<"Note: Please enter operators in all caps"<<endl;
    //read user search
    string input;
    cin.ignore();
    getline(cin, input);
    cout<<endl<<"Searching..."<<endl<<endl;
    //search
    engine.search(input);
    //show results
    engine.displaySearch();
    //clear search
    engine.clearSearch();
}
//search engine stats
void Interface::engineStats(){
    engine.displayStats();
};