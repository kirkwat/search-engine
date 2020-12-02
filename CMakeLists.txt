cmake_minimum_required(VERSION 3.15)
project(search_engine_watson)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_DEBUG “-O3”)

add_executable(search_engine_watson main.cpp porter2_stemmer.cpp DSAvlTree.h Word.cpp Word.h AvlNode.h IndexHandler.cpp IndexHandler.h Interface.cpp Interface.h DocHandler.cpp DocHandler.h Article.cpp Article.h SearchEngine.cpp SearchEngine.h Author.cpp Author.h)