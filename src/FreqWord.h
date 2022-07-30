#ifndef SEARCH_ENGINE_WATSON_FREQWORD_H
#define SEARCH_ENGINE_WATSON_FREQWORD_H

#include <string>

using namespace std;

//This class contains the frequency of words parsed from the corpus.
class FreqWord {
private:
    string word;        //word
    int frequency;      //amount of times that the word has appeared

public:
    FreqWord(string,int);

    bool operator== (const FreqWord&)const;
    bool operator> (const FreqWord&)const;
    bool operator< (const FreqWord&)const;

    string getWord()const;
    int getFreq()const;
};


#endif //SEARCH_ENGINE_WATSON_FREQWORD_H
