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
void IndexHandler::createIndex(string data){
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
        addAuthor(itr->GetObject()["last"].GetString(),id);
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
//add author to author index
void IndexHandler::addAuthor(string last,string id){
    Porter2Stemmer::trim(last);
    //check if author is in index
    AvlNode<Author>* findAuthor=authIndex.search(last);
    if(findAuthor==nullptr){
        authIndex.insert(Author(last,id));
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
    readfile.open("../src/stopwords.txt");
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
//find and display 50 most frequent words
void IndexHandler::displayFreqWords(){
    //fill freqWords set
    getFreqWords(index.getRoot());
    //print in top order
    int counter=0;
    set<FreqWord>::reverse_iterator itr;
    for (itr = freqWords.rbegin();itr != freqWords.rend(); itr++){
        //skip space
        if(counter==0){
            counter++;
            continue;
        }
        //end at 50 words
        if(counter==51){
            break;
        }
        //formatting
        if(counter>9){
            cout<<"\t\t"<<counter<<". ";
        }
        else{
            cout<<"\t\t"<<counter<<".  ";
        }
        //print info
        cout<<itr->getWord()<<" - "<<itr->getFreq();
        //formatting
        if(counter!=50){
            cout<<endl;
        }
        counter++;
    }
    //clear freqWords list;
    freqWords.clear();
    cout<<endl;
}
//go through index recursively
void IndexHandler::getFreqWords(AvlNode<Word>* c){
    if(c!=nullptr){
        //add word to set sorted by frequency
        freqWords.insert(FreqWord(c->payload.getWord(),c->payload.getAppearances()));
        //go to other nodes
        getFreqWords(c->left);
        getFreqWords(c->right);
    }
}
//reset and clear index
void IndexHandler::clearIndex(){
    index.clear();
    authIndex.clear();
    corpusSize=0;
    indexSize=0;
    authorCount=0;
}
//save index to persistence file
void IndexHandler::saveIndex(string outputFile){
    ofstream file(outputFile);
    //check if it was opened properly
    if (!file.is_open()) {
        cout << "Could not open file "<<outputFile<<"." << endl;
        return;
    }
    //save stats
    file<<corpusSize<<endl;
    //iterate through and save word and docs
    saveWord(index.getRoot(),file);
    //iterate through and save word and docs
    file<<"AUTHORS"<<endl;
    saveAuthor(authIndex.getRoot(),file);
    //close file
    file.close();
}
//go through index recursively
void IndexHandler::saveWord(AvlNode<Word>* c, ofstream& fout){
    if(c!=nullptr){
        //save word and docs
        fout<<c->payload.getWord()<<":";
        //save number of appearances
        fout<<c->payload.getAppearances()<<":";
        //get words
        set<string>docs=c->payload.getDocs();
        //save docs
        set<string>::iterator itr;
        int counter=0;
        for (itr = docs.begin();itr != docs.end(); itr++){
            if(counter==0){
                fout<<*itr;
            }
            else{
                fout<<","<<*itr;
            }
            counter++;
        }
        fout<<endl;
        //go to other nodes
        saveWord(c->left,fout);
        saveWord(c->right,fout);
    }
}
//go through index recursively
void IndexHandler::saveAuthor(AvlNode<Author>* c, ofstream& fout){
    if(c!=nullptr){
        //save word and docs
        fout<<c->payload.getLast()<<":";
        //get authors
        set<string>docs=c->payload.getDocs();
        //save docs
        set<string>::iterator itr;
        int counter=0;
        for (itr = docs.begin();itr != docs.end(); itr++){
            if(counter==0){
                fout<<*itr;
            }
            else{
                fout<<","<<*itr;
            }
            counter++;
        }
        fout<<endl;
        //go to other nodes
        saveAuthor(c->left,fout);
        saveAuthor(c->right,fout);
    }
}
//create index from persistence file
void IndexHandler::loadIndex(string file){
    ifstream readFile;
    //open setA file
    readFile.open(file);
    //check if opened properly
    if (!readFile.is_open()) {
        cout << "Could not open file "<<file<<"." << endl;
        return;
    }
    //false if word, true if author
    bool wordVauthor=false;
    string input;
    //read file
    readFile>>corpusSize;
    while(readFile>>input){
        //switch to authors mode
        if(input=="AUTHORS"){
            wordVauthor=true;
        }
        //load authors
        else if(wordVauthor){
            loadAuthor(input);
            authorCount++;
        }
        //load word
        else{
            loadWord(input);
            indexSize++;
        }
    }
}
//load word and its info
void IndexHandler::loadWord(string input){
    //get word
    Word temp=Word(input.substr(0,input.find(':')));
    //remove word
    input=input.substr(input.find(':')+1,input.size()-input.find(':')-1);
    //get appearances
    string num=input.substr(0,input.find(':'));
    stringstream ss(num);
    int appearances;
    ss>>appearances;
    temp.setAppearances(appearances);
    //remove appearances
    input=input.substr(input.find(':')+1,input.size()-input.find(':')-1);
    //get docs
    while(input.find(',')!=string::npos){
        //add doc
        temp.addDoc2(input.substr(0,input.find(',')));
        //remove doc
        input=input.substr(input.find(',')+1,input.size()-input.find(',')-1);
    }
    //add last doc
    temp.addDoc2(input);
    //add word to index
    index.insert(temp);
}
//load author and its info
void IndexHandler::loadAuthor(string input){
    //get author
    Author temp=Author(input.substr(0,input.find(':')));
    //remove author
    input=input.substr(input.find(':')+1,input.size()-input.find(':')-1);
    //get docs
    while(input.find(',')!=string::npos){
        //add doc
        temp.addDoc(input.substr(0,input.find(',')));
        //remove doc
        input=input.substr(input.find(',')+1,input.size()-input.find(',')-1);
    }
    //add last doc
    temp.addDoc(input);
    //add author to index
    authIndex.insert(temp);
}
//check to see if index has elements
bool IndexHandler::hasElements(){
    //return true if elements exist
    return index.getRoot()!=nullptr&&indexSize>0;
}
//get size of index
int IndexHandler::getIndexSize(){
    return indexSize;
}
//get size of corpus
int IndexHandler::getCorpusSize(){
    return corpusSize;
}
//get author count
int IndexHandler::getAuthorCount(){
    return authorCount;
}
//get average of words indexed per article
double IndexHandler::getAverage(){
    return double(indexSize)/double(corpusSize);
}