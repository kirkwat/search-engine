#ifndef SEARCH_ENGINE_WATSON_AUTHOR_H
#define SEARCH_ENGINE_WATSON_AUTHOR_H

#include <string>
#include <set>
#include <iostream>

using namespace std;

//This class contains the characteristics of an author in the author index.
class Author {
private:
    string last;                //last name of an author
    set<string> documentIDs;    //documents written by an author

public:
    Author();
    Author(string);
    Author(string,string);

    bool operator== (const Author&)const;
    bool operator> (const Author&)const;
    bool operator< (const Author&)const;

    void addDoc(string);

    string getLast()const;
    set<string> getDocs()const;

};


#endif //SEARCH_ENGINE_WATSON_AUTHOR_H
