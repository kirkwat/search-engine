//
// Created by watso on 11/26/2020.
//

#include "Article.h"

//default constructor
Article::Article(){
    rank=-1;
    id="NULL";
}
//overloaded constructor with rank
Article::Article(int x){
    id="NULL";
    rank=x;
}
//overloaded constructor with id
Article::Article(string x){
    id=x;
    rank=-1;
}
//overloaded constructor with id and rank
Article::Article(string x, double y){
    rank=y;
    id=x;
}
//equal to operator with rank
bool Article::operator== (const Article& copy)const{
    return rank == copy.rank;
}
//greater than operator with rank
bool Article::operator> (const Article& copy)const{
    return rank > copy.rank;
}
//less than operator with rank
bool Article::operator< (const Article& copy)const{
    return rank < copy.rank;
}
//add info to article
void Article::addInfo(string titl,string dat,string auth,string pub){
    title=titl;
    date=dat;
    author=auth;
    publication=pub;
}
//print article info
void Article::printInfo()const{
    cout<<title<<endl;
    cout<<"\t\t"<<author<<" - "<<date<<" - "<<publication<<endl;
}
//get rank
double Article::getRank(){
    return rank;
}
//get id
string Article::getID()const{
    return id;
}