cmake_minimum_required(VERSION 3.15)
project(search_engine_watson)

set(CMAKE_CXX_STANDARD 14)

add_executable(search_engine_watson main.cpp porter2_stemmer.cpp)