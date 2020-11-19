//
// Created by watso on 11/18/2020.
//

#ifndef SEARCH_ENGINE_WATSON_WORD_H
#define SEARCH_ENGINE_WATSON_WORD_H


#include <string>
#include "DSAvlTree.h"

using namespace std;

class Word {
private:
    string word;
    DSAvlTree<string> documentIDs;

public:
    Word();
    Word(char[]);
    Word(string);
    Word(string,string);

    bool operator== (const Word&)const;
    bool operator> (const Word&)const;
    bool operator< (const Word&)const;

    void addDoc(string);

    string getWord()const;
    DSAvlTree<string> getDocs();
};


#endif //SEARCH_ENGINE_WATSON_WORD_H
