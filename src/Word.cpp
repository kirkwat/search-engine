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
    return word > copy.word;
}
//less than operator with string
bool Word::operator< (const Word& copy)const{
    return word < copy.word;
}
//add document to set
void Word::addDoc(string doc){
    documentIDs.insert(doc);
    appearances++;
}
//add document to set
void Word::addDoc2(string doc){
    documentIDs.insert(doc);
}
void Word::setAppearances(int a){
    appearances=a;
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