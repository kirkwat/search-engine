//
// Created by watso on 11/26/2020.
//

#include "DocHandler.h"

//default constructor
DocHandler::DocHandler() {
    corpusSize=0;
}
//process docs
void DocHandler::processDocs(set<string> docs,vector<AvlNode<Word>*> words,string path,int corpus) {
    //add info
    searchWords=words;
    corpusSize=corpus;
    corpusPath=path;
    findMetaData(corpusPath);
    //read metadata file
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
        //info to save
        //title, first author, publication, date published
        //cord_uid
        getline(readfile,input,',');
        //sha
        getline(readfile,input,',');
        //if document is found
        auto it=docs.find(input);
        if(it!=docs.end()){
            //source_x
            getline(readfile,input,',');
            //title
            getline(readfile,input,',');
            string title=input;
            if(input[0]=='"'){
                title=input.substr(1,input.length()-1)+",";
                getline(readfile,input,'"');
                title+=input;
                getline(readfile,input,',');
            }
            //doi
            getline(readfile,input,',');
            //pmcid
            getline(readfile,input,',');
            //pubmed_id
            getline(readfile,input,',');
            //license
            getline(readfile,input,',');
            //abstract
            getline(readfile,input,',');
            if(input[0]=='"'){
                getline(readfile,input,'"');
                getline(readfile,input,',');
            }
            //date
            getline(readfile,input,',');
            string date=input;
            //authors
            getline(readfile,input,',');
            string tempstr;
            string author;
            if(input[0]=='"'){
                tempstr=input.substr(1,input.length()-1)+",";
                getline(readfile,input,'"');
                tempstr+=input;
                if(tempstr.find(";")!=string::npos){
                    author=tempstr.substr(0,tempstr.find(";"));
                }
                else{
                    author=tempstr;
                }
                getline(readfile,input,',');
            }
            //journal
            getline(readfile,input,',');
            string publication=input;
            if(input[0]=='"'){
                publication=input.substr(1,input.length()-1)+",";
                getline(readfile,input,'"');
                publication+=input;
                getline(readfile,input,',');
            }
            //remainder of line
            getline(readfile,input);
            //open doc
            string filePath=corpusPath+"\\\\"+*it+".json";
            //create article and get rank
            Article temp=Article(*it,rankDoc(filePath));
            //add info
            temp.addInfo(title,date,author,publication);
            //add article to set
            sortedDocs.insert(temp);
        }
        //skip line if doc is not found
        else{
            getline(readfile,input);
        }
    }
    readfile.close();
}
//print top 15 documents
void DocHandler::printTopDocs(){
    int counter=1;
    //print in top order
    set<Article>::reverse_iterator itr;
    for (itr = sortedDocs.rbegin();itr != sortedDocs.rend(); itr++){
        //end at 15 docs
        if(counter==16){
            break;
        }
        //formatting
        if(counter>9){
            cout<<"\t"<<counter<<". ";
        }
        else{
            cout<<"\t "<<counter<<". ";
        }
        //print info
        itr->printInfo();
        //formatting
        if(counter!=15){
            cout<<endl;
        }
        counter++;
    }
}
//rank doc
double DocHandler::rankDoc(string path){
    wordCount=0;
    ifstream readJSON(path);
    //create stream wrapper
    IStreamWrapper isw(readJSON);
    //parse document
    Document d;
    d.ParseStream(isw);
    //increase score
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
    //calculate rank
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
            //add to score if search word is found
            if(word==searchWords[x]->payload.getWord()){
                score++;
            }
        }
        wordCount++;
    }
    return score;
}
//find metadata file
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
            //get metadata path
            else if(path.find(".csv")!=string::npos){
                metaPath=path;
                break;
            }
        }
    }
    //close directory
    closedir(directory);
}
//preview document
void DocHandler::viewDoc(int docNum){
    int counter=1;
    //find requested doc
    set<Article>::reverse_iterator itr;
    for (itr = sortedDocs.rbegin();itr != sortedDocs.rend(); itr++){
        if(docNum==counter){
            //get path
            string filePath=corpusPath+"\\\\"+itr->getID()+".json";
            //open file
            ifstream readJSON(filePath);
            //create stream wrapper
            IStreamWrapper isw(readJSON);
            //parse document
            Document d;
            d.ParseStream(isw);
            //read title
            cout<<endl<<"Title: "<<d["metadata"].GetObject()["title"].GetString()<<endl;
            //read body text
            int wordCount=0;
            int lineLength=0;
            cout<<"300 Word Preview: \n\t";
            for (Value::ConstValueIterator itr = d["body_text"].Begin(); itr != d["body_text"].End(); ++itr){
                string word;
                stringstream ss;
                ss.str(itr->GetObject()["text"].GetString());
                while(ss>>word){
                    wordCount++;
                    lineLength+=word.length();
                    cout<<word;
                    //formatting
                    if(lineLength>75){
                        cout<<"\n\t";
                        lineLength=0;
                    }
                    else{
                        cout<<" ";
                    }
                    //end at 300 words
                    if(wordCount==299){
                        cout<<"..."<<endl;
                        break;
                    }
                }
                if(wordCount==299) {
                    break;
                }
            }
            //close file
            readJSON.close();
            break;
        }
        counter++;
    }
}
//clear search info
void DocHandler::clearProcessor(){
    sortedDocs.clear();
    searchWords.clear();
    corpusSize=0;
    corpusPath="NULL";
    metaPath="NULL";
    wordCount=0;
}