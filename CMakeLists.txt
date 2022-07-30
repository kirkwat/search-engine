cmake_minimum_required(VERSION 3.15)
project(search_engine)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_DEBUG “-O3”)

add_executable(search_engine src/main.cpp src/porter2_stemmer.cpp src/DSAvlTree.h src/Word.cpp src/Word.h src/AvlNode.h src/IndexHandler.cpp src/IndexHandler.h src/Interface.cpp src/Interface.h src/DocHandler.cpp src/DocHandler.h src/Article.cpp src/Article.h src/SearchEngine.cpp src/SearchEngine.h src/Author.cpp src/Author.h src/DSHashTable.h src/FreqWord.cpp src/FreqWord.h)