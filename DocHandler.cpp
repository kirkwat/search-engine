//
// Created by watso on 11/20/2020.
//

#include "DocHandler.h"

using namespace std;

//default constructor
DocHandler::DocHandler(){
    dirPath="NULL";
}
//overloaded constructor
DocHandler::DocHandler(char* input){
    dirPath=input;
    findMetaData();
}
string DocHandler::getDocLoc(){

}
void DocHandler::findMetaData(){
    findMetaData(dirPath);
}
void DocHandler::findMetaData(char* dirName) {
    DIR *dir;
    struct dirent *entry;
    struct stat info;

    dir=opendir(dirName);
    if(!dir){
        cout<<"Folder not found"<<endl;
        return;
    }
    while((entry=readdir(dir))!=nullptr){
        if(entry->d_name[0]!='.'){
            string fullPath=string(dirName)+"\\\\"+string(entry->d_name);
            if(fullPath.find(".csv")!=string::npos){
                cout<<"FOUND"<<endl;
                cout<<fullPath<<endl;
                metaPath=fullPath;
                break;
            }
            //cout<<"Entry = "<<fullPath<<endl;
            stat(fullPath.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                findMetaData((char*)fullPath.c_str());
            }
        }
    }
    closedir(dir);
}