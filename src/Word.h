#ifndef SEARCH_ENGINE_WATSON_WORD_H
#define SEARCH_ENGINE_WATSON_WORD_H

#include <iostream>
#include <iterator>
#include <string>
#include <set>

using namespace std;

//This class contains the characteristics of a word in the word index.
class Word {
private:
    string word;                //word
    set<string> documentIDs;    //documents containing a given word
    int appearances;            //amount of times that a word has appeared

public:
    Word();
    Word(string);
    Word(string,string);

    bool operator== (const Word&)const;
    bool operator> (const Word&)const;
    bool operator< (const Word&)const;

    void addDoc(string);
    void addDoc2(string);

    string getWord()const;
    set<string> getDocs()const;
    int getDocCount()const;
    void setAppearances(int);
    int getAppearances()const;

};


#endif //SEARCH_ENGINE_WATSON_WORD_H
