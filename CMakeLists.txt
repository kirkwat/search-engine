cmake_minimum_required(VERSION 3.15)
project(search_engine_watson)
set(CMAKE_CXX_STANDARD 14)

#TODO SET UP COMMAND LINE

add_executable(search_engine_watson main.cpp porter2_stemmer.cpp DSAvlTree.h Word.cpp Word.h AvlNode.h)