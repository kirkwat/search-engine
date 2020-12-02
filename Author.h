//
// Created by watso on 11/27/2020.
//

#ifndef SEARCH_ENGINE_WATSON_AUTHOR_H
#define SEARCH_ENGINE_WATSON_AUTHOR_H

#include <string>
#include <set>
#include <iostream>

using namespace std;

class Author {
private:
    string last;
    set<string> documentIDs;

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
