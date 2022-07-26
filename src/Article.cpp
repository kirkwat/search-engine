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
    int lineLength=0;
    string word;
    stringstream ss;
    ss<<title;
    while(ss>>word){
        lineLength+=word.length();
        cout<<word;
        //formatting
        if(lineLength>75){
            if(ss.rdbuf()->in_avail() != 0){
                cout<<"\n\t";
                lineLength=0;
            }
        }
        else{
            cout<<" ";
        }
    }
    cout<<"\n\t\t"<<author<<" - "<<date<<" - "<<publication<<endl;
}
//get rank
double Article::getRank(){
    return rank;
}
//get id
string Article::getID()const{
    return id;
}