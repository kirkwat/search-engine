//
// Created by watso on 11/26/2020.
//

#ifndef SEARCH_ENGINE_WATSON_ARTICLE_H
#define SEARCH_ENGINE_WATSON_ARTICLE_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Article {
private:
    double rank;
    string id;
    string author;
    string date;
    string title;
    string publication;

public:
    Article();
    Article(int);
    Article(string);
    Article(string, double);

    bool operator== (const Article&)const;
    bool operator> (const Article&)const;
    bool operator< (const Article&)const;

    void addInfo(string,string,string,string);
    void printInfo()const;

    double getRank();
    string getID()const;
};


#endif //SEARCH_ENGINE_WATSON_ARTICLE_H
