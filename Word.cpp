//
// Created by watso on 11/18/2020.
//

#include "Word.h"

using namespace std;
//default constructor
Word::Word(){
    word="NULL";
}
//overloaded constructor with cstring
Word::Word(char input[]){
    word=input;
}
//overloaded constructor with string
Word::Word(string input){
    word=input;
}
//overloaded constructor with string and id
Word::Word(string input,string id){
    word=input;
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
//add document to tree
void Word::addDoc(string doc){
    documentIDs.insert(doc);
}
//return string of word
string Word::getWord()const{
    return word;
}
//get docs
DSAvlTree<string> Word::getDocs(){
    return documentIDs;
}
