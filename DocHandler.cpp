//
// Created by watso on 11/26/2020.
//

#include "DocHandler.h"

DocHandler::DocHandler() {
    corpusSize=0;
}
void DocHandler::processDocs(set<string> docs,vector<AvlNode<Word>*> words,string path,int corpus) {
    searchWords=words;
    corpusSize=corpus;
    corpusPath=path;
    findMetaData(corpusPath);

    ifstream readfile;
    //open file
    readfile.open(metaPath);
    //check if it was opened properly
    if (!readfile.is_open()) {
        cout << "Could not open file " << metaPath<<endl;
        return;
    }
    string input;
    getline(readfile,input);
    while(!readfile.eof()){
        //info to print
        //title, first author, publication, date published

        getline(readfile,input,',');
        getline(readfile,input,',');

        auto it=docs.find(input);
        if(it!=docs.end()){
            getline(readfile,input,',');
            getline(readfile,input,',');
            string title=input;
            getline(readfile,input,'"');
            getline(readfile,input,'"');
            getline(readfile,input,',');
            getline(readfile,input,',');
            string date=input;
            getline(readfile,input,'"');
            getline(readfile,input,'"');
            string author;
            if(input.find(";")!=string::npos){
                author=input.substr(0,input.find(";"));
            }
            else{
                author=input;
            }
            getline(readfile,input,',');
            getline(readfile,input,',');
            string publication=input;
            getline(readfile,input);

            string filePath=corpusPath+"\\\\"+*it+".json";
            rankDoc(filePath);
            Article temp=Article(*it,rankDoc(filePath));
            temp.addInfo(title,date,author,publication);
            sortedDocs.insert(temp);
        }
        else{
            getline(readfile,input);
        }
    }
    readfile.close();



    set<string>::iterator itr;
    for (itr = docs.begin();itr != docs.end(); ++itr){
        string filePath=corpusPath+"\\\\"+*itr+".json";
        rankDoc(filePath);
    }
}
void DocHandler::printTopDocs(){
    ifstream readfile;
    //open file
    readfile.open(metaPath);
    //check if it was opened properly
    if (!readfile.is_open()) {
        cout << "Could not open file " << metaPath<<endl;
        return;
    }
    string input;
    getline(readfile,input);

    int counter=1;
    set<Article>::iterator itr;
    for (itr = sortedDocs.begin();itr != sortedDocs.end(); ++itr){
        if(counter==16){
            break;
        }
        cout<<"\t "<<counter<<". ";
        itr->printInfo();
        cout<<endl;

        counter++;
    }
}
double DocHandler::rankDoc(string path){
    wordCount=0;
    ifstream readJSON(path);
    //create stream wrapper
    IStreamWrapper isw(readJSON);
    //parse document
    Document d;
    d.ParseStream(isw);

    int score=0;
    //get id
    string id=d["paper_id"].GetString();
    //read title
    score+=parseText(d["metadata"].GetObject()["title"].GetString());
    //read abstract
    for (Value::ConstValueIterator itr = d["abstract"].Begin(); itr != d["abstract"].End(); ++itr){
        score+=parseText(itr->GetObject()["text"].GetString());
    }
    //read body text
    for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
        score+=parseText(itr->GetObject()["text"].GetString());
    }
    //close file
    readJSON.close();

    double docAppearances=0;
    for(int x=0;x<searchWords.size();x++){
        docAppearances+=searchWords[x]->payload.getDocCount();
    }
    return (double(score)/double(wordCount))*log(double(corpusSize)/docAppearances);
}
//parse text
int DocHandler::parseText(string text){
    int score=0;
    string word;
    stringstream ss;
    ss.str(text);
    //read stream
    while(ss>>word){
        //stem words
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        //check if word is search word
        for(int x=0;x<searchWords.size();x++){
            if(word==searchWords[x]->payload.getWord()){
                score++;
            }
        }
        wordCount++;
    }
    return score;
}
//create index
void DocHandler::findMetaData(string data){
    DIR *directory;
    struct dirent *entry;
    struct stat info;
    //open directory
    directory=opendir(data.c_str());
    //check if directory exists
    if(!directory){
        cout<<"Folder not found"<<endl;
        return;
    }
    //read directory
    while((entry=readdir(directory))!=nullptr){
        if(entry->d_name[0]!='.'){
            //get path
            string path=data+"\\\\"+string(entry->d_name);
            //check if path is another directory
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                //open directory
                findMetaData(path);
            }
            //open meta data file
            else if(path.find(".csv")!=string::npos){
                metaPath=path;
                break;
            }
        }
    }
    //close directory
    closedir(directory);
}