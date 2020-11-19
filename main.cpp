#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "DSAvlTree.h"

using namespace std;
using namespace rapidjson;

int main(int argc, char** argv){
    ifstream readJSON;
    //read article
    cout<<"Reading test.json..."<<endl;
    //open users table file
    readJSON.open("C:\\Users\\watso\\Downloads\\cs2341_project_data\\cs2341_data\\metadata-cs2341.csv");
    //check if it was opened properly
    if (!readJSON.is_open()) {
        cout << "Could not open file test.json." << endl;
        return 1;
    }
    cout<<"...Success"<<endl<<endl;
    readJSON.close();

    FILE* fp = fopen("../c63c4d58d170136b8d3b5a66424b5ac3f73a92d9.json", "rb"); // non-Windows use "r"

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    assert(d.IsObject());
    assert(d.HasMember("paper_id"));
    //get id and title
    cout<<"id = "<<d["paper_id"].GetString()<<endl;
    string id=d["paper_id"].GetString();
    cout<<"title = "<<d["metadata"].GetObject()["title"].GetString()<<endl;
    string title=d["metadata"].GetObject()["title"].GetString();
    /*
    //get authors
    for (Value::ConstValueIterator itr = d["metadata"].GetObject()["authors"].Begin(); itr != d["metadata"].GetObject()["authors"].End(); ++itr){
        cout<<"author"<<endl;
        cout<<"\tfirst = "<<itr->GetObject()["first"].GetString()<<endl;
        cout<<"\tlast = "<<itr->GetObject()["last"].GetString()<<endl;
    }*/
    stringstream ss;
    string word;
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        cout<<"abstract = "<<itr->GetObject()["text"].GetString()<<endl;
        ss.str(itr->GetObject()["text"].GetString());
        //while(ss>>word){

        //}
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        cout<<"body text = "<<itr->GetObject()["text"].GetString()<<endl;
    }
    fclose(fp);

/*
    string to_stem="(((((abandonment";
    string stemmed="abandon";
    std::string orig = to_stem;
    Porter2Stemmer::trim(to_stem);
    Porter2Stemmer::stem(to_stem);
    if (to_stem != stemmed)
    {
        std::cout << "  incorrect!" << std::endl
                  << std::endl
                  << "to stem:  " << orig    << std::endl
                  << "stemmed:  " << to_stem << std::endl
                  << "expected: " << stemmed << std::endl;
    }
    else{
        cout<<"O:"<<orig<<endl;
        cout<<"B:"<<to_stem<<endl;
        cout<<"A:"<<stemmed<<endl;
    }*/
return 0;
}