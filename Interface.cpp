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
            if(engine.indexFull()){
                searchIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        else if(option==2){
            if(!engine.indexFull()){
                createIndex();
            }
            else{
                cout<<endl<<"The search engine index has already been filled, please clear index before recreating the index."<<endl;
            }
        }
        else if(option==3){
            if(engine.indexFull()){
                clearIndex();
            }
            else{
                cout<<endl<<"The search engine index is empty, please create the index."<<endl;
            }
        }
        else if(option==4){
            if(engine.indexFull()){
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
        engine.createIndex();
        cout<<"...Complete!"<<endl;
    }
    else if(input==2){
        engine.testIndex();
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
    engine.clearIndex();
    cout<<"...Complete!"<<endl;

}
//search engine
void Interface::searchIndex(){
    cout<<endl<<"Please enter your query below using the proper formatting."<<endl;
    cout<<"Note: Please enter operators in all caps"<<endl;
    string input;
    cin.ignore();
    getline(cin, input);
    cout<<"Searching..."<<endl<<endl;
    engine.search(input);
    engine.displaySearch();
    engine.clearSearch();
}
//search engine stats
void Interface::engineStats(){
    engine.displayStats();
};