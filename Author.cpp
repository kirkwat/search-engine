//
// Created by watso on 11/27/2020.
//

#include "Author.h"

Author::Author(){
    first="NULL";
    last="NULL";
}
//overloaded constructor with combined name
Author::Author(string l) {
    first="NULL";
    last=l;
}
//overloaded constructor with full name and id
Author::Author(string f,string l,string id){
    first=f;
    last=l;
    addDoc(id);
}
//equal to operator with string
bool Author::operator== (const Author& copy)const{
    return last == copy.last;
}
//greater than operator with string
bool Author::operator> (const Author& copy)const{
    return last > copy.last;
}
//less than operator with string
bool Author::operator< (const Author& copy)const{
    return last < copy.last;
}
//add document to tree
void Author::addDoc(string doc){
    documentIDs.insert(doc);
}
string Author::getLast()const{
    return last;
}
string Author::getFirst()const{
    return first;
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
set<string> Author::getDocs()const{
    return documentIDs;
}