//
// Created by watso on 12/6/2020.
//

#ifndef SEARCH_ENGINE_WATSON_FREQWORD_H
#define SEARCH_ENGINE_WATSON_FREQWORD_H

#include <string>

using namespace std;

class FreqWord {
private:
    string word;
    int frequency;

public:
    FreqWord(string,int);

    bool operator== (const FreqWord&)const;
    bool operator> (const FreqWord&)const;
    bool operator< (const FreqWord&)const;

    string getWord()const;
    int getFreq()const;
};


#endif //SEARCH_ENGINE_WATSON_FREQWORD_H
