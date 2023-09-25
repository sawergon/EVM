cmake_minimum_required(VERSION 3.23)
project(avlTree)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -g")

add_executable(avlTree main.cpp avlTree.cpp consoleWork.cpp)
