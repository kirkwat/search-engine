//
// Created by watso on 11/27/2020.
//

#include "Author.h"

Author::Author(){
    first="NULL";
    last="NULL";
    combined="NULL";
}
//overloaded constructor with combined name
Author::Author(string fullName) {
    first="NULL";
    last="NULL";
    combined=fullName;
}
//overloaded constructor with combined name and id
Author::Author(string fullName, string id) {
    first="NULL";
    last="NULL";
    combined=fullName;
    addDoc(id);
}
//overloaded constructor with full name and id
Author::Author(string f,string l,string id){
    first=f;
    last=l;
    combined=last+","+first;
    addDoc(id);
}
//equal to operator with string
bool Author::operator== (const Author& copy)const{
    return combined == copy.combined;
}
//greater than operator with string
bool Author::operator> (const Author& copy)const{
    return combined > copy.combined;
}
//less than operator with string
bool Author::operator< (const Author& copy)const{
    return combined < copy.combined;
}
//add document to tree
void Author::addDoc(string doc){
    documentIDs.insert(doc);
}
//return string of word
string Author::getFullName()const{
    return combined;
}
//display docs
void Author::printDocs(){
    set<string, greater<>>::iterator itr;
    cout<<"Number of documents: "<<documentIDs.size()<<endl;
    cout<<"Document IDs:"<<endl;
    for (itr = documentIDs.begin();itr != documentIDs.end(); ++itr){
        cout<<"\t"<<*itr<<endl;
    }
}