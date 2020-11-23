//
// Created by watso on 11/18/2020.
//

#ifndef SEARCH_ENGINE_WATSON_WORD_H
#define SEARCH_ENGINE_WATSON_WORD_H

#include <iostream>
#include <iterator>
#include <string>
#include <set>

using namespace std;

class Word {
private:
    string word;
    set<string, greater<>> documentIDs;

public:
    Word();
    Word(string);
    Word(string,string);

    bool operator== (const Word&)const;
    bool operator> (const Word&)const;
    bool operator< (const Word&)const;

    void addDoc(string);
    void printDocs();

    string getWord()const;

};


#endif //SEARCH_ENGINE_WATSON_WORD_H
