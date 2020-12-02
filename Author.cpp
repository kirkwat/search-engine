//
// Created by watso on 11/27/2020.
//

#include "Author.h"

//default constructor
Author::Author(){
    last="NULL";
}
//overloaded constructor with last name
Author::Author(string l) {
    last=l;
}
//overloaded constructor with last name and id
Author::Author(string l,string id){
    last=l;
    addDoc(id);
}
//equal to operator with last name
bool Author::operator== (const Author& copy)const{
    return last == copy.last;
}
//greater than operator with last name
bool Author::operator> (const Author& copy)const{
    return last > copy.last;
}
//less than operator with last name
bool Author::operator< (const Author& copy)const{
    return last < copy.last;
}
//add document to set
void Author::addDoc(string doc){
    documentIDs.insert(doc);
}
//get last name
string Author::getLast()const{
    return last;
}
//get doc set
set<string> Author::getDocs()const{
    return documentIDs;
}