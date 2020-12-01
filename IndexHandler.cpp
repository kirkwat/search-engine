#include "IndexHandler.h"

//default constructor
IndexHandler::IndexHandler(){
    //create stopwords tree
    getStopWords();
    corpusSize=0;
    indexSize=0;
    authorCount=0;
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
            //ignore meta data file
            else if(path.find(".csv")!=string::npos){
                continue;
            }
            //read path source if path is file
            else{
                readDoc(path);
                corpusSize++;
            }
        }
    }
    //close directory
    closedir(directory);
}
//read file
void IndexHandler::readDoc(string path){
    ifstream readJSON(path);
    //create stream wrapper
    IStreamWrapper isw(readJSON);
    //parse document
    Document d;
    d.ParseStream(isw);
    //get id
    string id=d["paper_id"].GetString();
    //read title
    parseText(d["metadata"].GetObject()["title"].GetString(),id);
    //get authors
    for (Value::ConstValueIterator itr = d["metadata"].GetObject()["authors"].Begin(); itr != d["metadata"].GetObject()["authors"].End(); ++itr){
        addAuthor(itr->GetObject()["first"].GetString(),itr->GetObject()["last"].GetString(),id);
    }
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        parseText(itr->GetObject()["text"].GetString(),id);
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        parseText(itr->GetObject()["text"].GetString(),id);
    }
    //close file
    readJSON.close();
}
//find search word
AvlNode<Word>* IndexHandler::findWord(string query){
    //stem query
    string stemmedQuery=query;
    Porter2Stemmer::trim(stemmedQuery);
    Porter2Stemmer::stem(stemmedQuery);
    //search index for query
    return index.search(stemmedQuery);
}
//find author
AvlNode<Author>* IndexHandler::findAuthor(string lastName){
    //stem query
    string trimmedName=lastName;
    Porter2Stemmer::trim(trimmedName);
    //search index for query
    return authIndex.search(trimmedName);
}
//parse text
void IndexHandler::parseText(string text,string id){
    string word;
    stringstream ss;
    ss.str(text);
    //read stream
    while(ss>>word){
        //stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        //check if word is a stopword
        if(stopwords.find(word)==stopwords.end()){
            //check if word is in index
            AvlNode<Word>* findWord=index.search(word);
            if(findWord==nullptr){
                index.insert(Word(word,id));
                indexSize++;
            }
            //if word exists, add id
            else{
                findWord->payload.addDoc(id);
            }
        }
    }
}
void IndexHandler::addAuthor(string first,string last,string id){
    Porter2Stemmer::trim(first);
    Porter2Stemmer::trim(last);
    //check if author is in index
    AvlNode<Author>* findAuthor=authIndex.search(last);
    if(findAuthor==nullptr){
        authIndex.insert(Author(first,last,id));
        authorCount++;
    }
    //if author exists, add id
    else{
        findAuthor->payload.addDoc(id);
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
    //make stopword set
    string input;
    while(readfile>>input){
        stopwords.insert(input);
    }
    //close file
    readfile.close();
}
void IndexHandler::displayFreqWords(){
    //TODO
}
void IndexHandler::clearIndex(){
    index.clear();
    authIndex.clear();
}
//check to see if index has elements
bool IndexHandler::hasElements(){
    //return true if elements exist
    return index.getRoot()!=nullptr;
}
int IndexHandler::getIndexSize(){
    return indexSize;
}
int IndexHandler::getCorpusSize(){
    return corpusSize;
}
int IndexHandler::getAuthorCount(){
    return authorCount;
}
double IndexHandler::getAverage(){
    return double(indexSize)/double(corpusSize);
}
void IndexHandler::testIndex() {
    index.insert(Word("worda","01"));
    index.insert(Word("wordb","01"));
    index.insert(Word("wordc","02"));
    index.insert(Word("wordd","03"));
    index.insert(Word("worde","04"));
    index.insert(Word("wordf","05"));
    index.insert(Word("wordg","06"));
    index.insert(Word("wordh","06"));
    index.insert(Word("wordi","07"));
    authIndex.insert(Author("Kirk","watson","01"));
    authIndex.insert(Author("Robert","derl","07"));

}