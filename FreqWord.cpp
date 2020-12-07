//
// Created by watso on 12/6/2020.
//
#include "FreqWord.h"
//constructor
FreqWord::FreqWord(string w ,int f) {
    word = w;
    frequency = f;
}
//equal to operator with frequency
bool FreqWord::operator== (const FreqWord& copy)const{
    return frequency == copy.frequency;
}
//greater than operator with frequency
bool FreqWord::operator> (const FreqWord& copy)const{
    return frequency > copy.frequency;
}
//less than operator with frequency
bool FreqWord::operator< (const FreqWord& copy)const{
    return frequency < copy.frequency;
}
//return word
string FreqWord::getWord()const{
    return word;
}
//return frequency
int FreqWord::getFreq()const{
    return frequency;
}
