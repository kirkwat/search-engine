//
// Created by watso on 12/6/2020.
//

#include "FreqWord.h"

FreqWord::FreqWord(string w ,int f) {
    word = w;
    frequency = f;
}
//equal to operator with string
bool FreqWord::operator== (const FreqWord& copy)const{
    return frequency == copy.frequency;
}
//greater than operator with string
bool FreqWord::operator> (const FreqWord& copy)const{
    return frequency > copy.frequency;
}
//less than operator with string
bool FreqWord::operator< (const FreqWord& copy)const{
    return frequency < copy.frequency;
}
string FreqWord::getWord()const{
    return word;
}
int FreqWord::getFreq()const{
    return frequency;
}
