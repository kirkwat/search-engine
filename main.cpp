#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <dirent.h>
#include <sys/stat.h>
#include "DSAvlTree.h"
#include "Word.h"
#include "IndexHandler.h"
#include <set>

using namespace std;
using namespace rapidjson;

int main(int argc, char** argv){
    /*
    //create handler
    IndexHandler indexer=IndexHandler();
    //create index
    indexer.createIndex(argv[1]);
    //find query
    indexer.findQuery(argv[2]);

    string word="hospital";
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    cout<<word<<endl;

    word="hospitals";
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    cout<<word<<endl;

    word="MathPose";
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    cout<<word<<endl;

    word="SMILES";
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    cout<<word<<endl;
*/


    ifstream readfile;
    //open file
    readfile.open("../stopwords.txt");
    //check if it was opened properly
    if (!readfile.is_open()) {
        cout << "Could not open file stopwords.txt." << endl;
        return 1;
    }
    //make stopword tree
    //set<string,greater<>> stopwords;
    DSAvlTree<string> stopwords;
    string input;
    while(readfile>>input){
        stopwords.insert(input);
    }
    //close file
    readfile.close();

    //open article and index
    DSAvlTree<Word> index;
    //TODO ABSOLUTE PATH
    FILE* fp = fopen("../00eb9220dc8cd351393b6b035323d350f103f8c6.json", "rb"); // non-Windows use "r"
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
    string word;
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        cout<<"abstract = "<<itr->GetObject()["text"].GetString()<<endl;
        stringstream ss;
        ss.str(itr->GetObject()["text"].GetString());
        while(ss>>word){
            //stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            //check if word is a stopword
            if(stopwords.search(word)!=nullptr){
                continue;
            }
            else{
            }
            //check if word is in index
            if(index.search(word)==nullptr){
                index.insert(Word(word,id));
            }
            //if word exists, add id
            else{
                index.searchPL(word).addDoc(id);
            }
        }
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        cout<<"body text = "<<itr->GetObject()["text"].GetString()<<endl;
        stringstream ss;
        ss.str(itr->GetObject()["text"].GetString());
        while(ss>>word){
            //stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            //check if word is a stopword
            if(stopwords.search(word)!=nullptr){
                continue;
            }
            //check if word is in index
            if(index.search(word)==nullptr){
                index.insert(Word(word,id));
            }
            //if word exists, add id
            else{
                index.searchPL(word).addDoc(id);
            }
        }
    }
    fclose(fp);
    //search for word
    string word1="pandemic";
    Porter2Stemmer::trim(word1);
    Porter2Stemmer::stem(word1);
    if(index.search(word1)!=nullptr){
        cout<<"WORD 1 FOUND"<<endl;
    }
    else{
        cout<<"NOT FOUND"<<endl;
    }
    string word2="poop";
    Porter2Stemmer::trim(word2);
    Porter2Stemmer::stem(word2);
    if(index.search(word2)!=nullptr){
        cout<<"WORD 2 FOUND"<<endl;
    }
    else{
        cout<<"NOT FOUND"<<endl;
    }







/*
    auto pos=stopwords.find("the");
    if(pos==stopwords.end()){
        cout<<"element not found"<<endl;
    }
*/

/*
    //open article and index
    DSAvlTree<Word> index;

    //FILE* fp = fopen("../c63c4d58d170136b8d3b5a66424b5ac3f73a92d9.json", "rb"); // non-Windows use "r"
    FILE* fp = fopen("../00eb9220dc8cd351393b6b035323d350f103f8c6.json", "rb"); // non-Windows use "r"

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
    }//TODO HERE
    string word;
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        cout<<"abstract = "<<itr->GetObject()["text"].GetString()<<endl;
        stringstream ss;
        ss.str(itr->GetObject()["text"].GetString());
        while(ss>>word){
            //stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            //check if word is a stopword
            if(stopwords.search(word)==nullptr){
                continue;
            }
            //check if word is in index
            if(index.search(word)==nullptr){
                index.insert(Word(word,id));
            }
            //if word exists, add id
            else{
                index.searchPL(word).addDoc(id);
            }
        }
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        cout<<"body text = "<<itr->GetObject()["text"].GetString()<<endl;
        stringstream ss;
        ss.str(itr->GetObject()["text"].GetString());
        while(ss>>word){
            //stem words
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            //check if word is a stopword
            if(stopwords.search(word)==nullptr){
                continue;
            }
            //check if word is in index
            if(index.search(word)==nullptr){
                index.insert(Word(word,id));
            }
            //if word exists, add id
            else{
                index.searchPL(word).addDoc(id);
            }
        }
    }
    fclose(fp);
    //search for word
    string word1="pandemic";
    Porter2Stemmer::trim(word1);
    Porter2Stemmer::stem(word1);
    if(index.search(word1)!=nullptr){
        cout<<"WORD 1 FOUND"<<endl;
    }
    else{
        cout<<"NOT FOUND"<<endl;
    }
    string word2="psychiatric";
    Porter2Stemmer::trim(word2);
    Porter2Stemmer::stem(word2);
    if(index.search(word2)!=nullptr){
        cout<<"WORD 2 FOUND"<<endl;
    }
    else{
        cout<<"NOT FOUND"<<endl;
    }
*/
return 0;
}
//TODO ABSOLUTE PATH
/*
    //read article
    cout<<"Reading here2.txt..."<<endl;
    //C:\\Users\\watso\\Downloads\\cs2341_project_data\\cs2341_data
    //"C:\\Users\\watso\\Downloads\\cs2341_project_data\\cs2341_data\\metadata-cs2341.csv"
    //open users table file
    readfile.open(argv[1]);
    //check if it was opened properly
    if (!readfile.is_open()) {
        cout << "Could not open file here2.txt." << endl;
        return 1;
    }
    string hello;
    readfile>>hello;
    cout<<hello<<endl;
    cout<<argv[2]<<endl;
    cout<<"...Success"<<endl<<endl;
    readfile.close();
*/
//TODO STEMMER TEST
/*
    string to_stem="(((((Abandonment";
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