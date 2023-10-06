cmake_minimum_required(VERSION 3.26)
project(lexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -g")

add_executable(lexicalAnalyzer
        Analyzer.cpp
        Analyzer.h
        avlTree.cpp
        avlTree.h
        main.cpp)
