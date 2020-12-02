//
// Created by watso on 11/26/2020.
//

#include "Article.h"

Article::Article(){
    rank=-1;
    id="NULL";
}
Article::Article(string x){
    id=x;
    rank=-1;
}
Article::Article(int x){
    id="NULL";
    rank=x;
}
Article::Article(string x, double y){
    rank=y;
    id=x;
}
//equal to operator with string
bool Article::operator== (const Article& copy)const{
    return rank == copy.rank;
}
//greater than operator with string
bool Article::operator> (const Article& copy)const{
    return rank > copy.rank;
}
//less than operator with string
bool Article::operator< (const Article& copy)const{
    return rank < copy.rank;
}
void Article::addInfo(string titl,string dat,string auth,string pub){
    title=titl;
    date=dat;
    author=auth;
    publication=pub;
}
double Article::getRank(){
    return rank;
}
string Article::getID()const{
    return id;
}
void Article::printInfo()const{
    cout<<"\t\t"<<title<<endl;
    cout<<"\t\t"<<author<<endl;
    cout<<"\t\t"<<date<<" - "<<publication<<endl;
}