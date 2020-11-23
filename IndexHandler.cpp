//
// Created by watso on 11/20/2020.
//

#include "IndexHandler.h"

//default constructor
IndexHandler::IndexHandler(){
    //create stopwords tree
    getStopWords();
}
//create index
void IndexHandler::createIndex(char* data){
    DIR *directory;
    struct dirent *entry;
    struct stat info;
    //open directory
    directory=opendir(data);
    //check if directory exists
    if(!directory){
        cout<<"Folder not found"<<endl;
        return;
    }
    //read directory
    while((entry=readdir(directory))!=nullptr){
        if(entry->d_name[0]!='.'){
            //get path
            string path=string(data)+"\\\\"+string(entry->d_name);
            //check if path is another directory
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                //open directory
                createIndex((char*)path.c_str());
            }
            //read path source if path is file
            else{
                readDoc(path);
            }
        }
    }
    //close directory
    closedir(directory);
}
//read file
void IndexHandler::readDoc(string path){
    FILE* file = fopen(path.c_str(), "rb"); // non-Windows use "r"
    //create stream
    char readBuffer[65536];
    FileReadStream is(file, readBuffer, sizeof(readBuffer));
    //parse document
    Document d;
    d.ParseStream(is);
    //get id and title
    cout<<"id = "<<d["paper_id"].GetString()<<endl;
    string id=d["paper_id"].GetString();
    cout<<"title = "<<d["metadata"].GetObject()["title"].GetString()<<endl;
    string title=d["metadata"].GetObject()["title"].GetString();
    parseText(title,id);
    /*get authors
    for (Value::ConstValueIterator itr = d["metadata"].GetObject()["authors"].Begin(); itr != d["metadata"].GetObject()["authors"].End(); ++itr){
        cout<<"author"<<endl;
        cout<<"\tfirst = "<<itr->GetObject()["first"].GetString()<<endl;
        cout<<"\tlast = "<<itr->GetObject()["last"].GetString()<<endl;
    }*/
    string word;
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        cout<<"abstract = "<<itr->GetObject()["text"].GetString()<<endl;
        parseText(itr->GetObject()["text"].GetString(),id);
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        cout<<"body text = "<<itr->GetObject()["text"].GetString()<<endl;
        parseText(itr->GetObject()["text"].GetString(),id);
    }
    //close file
    fclose(file);
    cout<<endl;
}
//find search word
void IndexHandler::findQuery(string query){
    //stem query
    string stemmedQuery=query;
    Porter2Stemmer::trim(stemmedQuery);
    Porter2Stemmer::stem(stemmedQuery);
    //search index for query
    AvlNode<Word>* findQuery=index.search(query);
    //if query was found
    if(findQuery!=nullptr){
        cout<<query<<" was found."<<endl;
        findQuery->payload.printDocs();
    }
    else{
        cout<<query<<" was not found."<<endl;
    }
}
//parse text
void IndexHandler::parseText(string text,string id){
    string word;
    stringstream ss;
    ss.str(text);
    //read stream
    while(ss>>word){
        if(word=="pandemics"){
            cout<<"HERE"<<endl;
        }
        //stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        //check if word is a stopword
        if(stopwords.find(word)==stopwords.end()){
            //check if word is in index
            AvlNode<Word>* findWord=index.search(word);
            if(findWord==nullptr){
                if(word=="pandemics"){
                    cout<<"HERE"<<endl;
                }
                index.insert(Word(word,id));
            }
            //if word exists, add id
            else{
                if(word=="pandemics"){
                    cout<<"HERE2"<<endl;
                }
                findWord->payload.addDoc(id);
            }
        }
    }
}
//create stopword list
void IndexHandler::getStopWords(){
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
    //close file
    readfile.close();
}