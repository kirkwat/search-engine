//
// Created by watso on 11/18/2020.
//

#include "Word.h"

using namespace std;
//default constructor
Word::Word(){
    word="NULL";
    appearances=0;
}
//overloaded constructor with string
Word::Word(string input){
    word=input;
    appearances=0;
}
//overloaded constructor with string and id
Word::Word(string input,string id){
    word=input;
    appearances=0;
    addDoc(id);
}
//equal to operator with string
bool Word::operator== (const Word& copy)const{
    return word == copy.word;
}
//greater than operator with string
bool Word::operator> (const Word& copy)const{
    return word > copy.getWord();
}
//less than operator with string
bool Word::operator< (const Word& copy)const{
    return word < copy.getWord();
}
//add document to set
void Word::addDoc(string doc){
    documentIDs.insert(doc);
    appearances++;
}
//return string of word
string Word::getWord()const{
    return word;
}
//get doc set
set<string> Word::getDocs()const{
    return documentIDs;
}
//get doc count
int Word::getDocCount()const{
    return documentIDs.size();
}
//get word frequency
int Word::getAppearances()const{
    return appearances;
}