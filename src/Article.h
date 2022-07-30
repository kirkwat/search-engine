#ifndef SEARCH_ENGINE_WATSON_ARTICLE_H
#define SEARCH_ENGINE_WATSON_ARTICLE_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//This class contains the characteristics of a research article.
class Article {
private:
    double rank;            //rank of article in a search
    string id;              //article identifier
    string author;          //author of article
    string date;            //date of publication
    string title;           //title of article
    string publication;     //publisher of article

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
