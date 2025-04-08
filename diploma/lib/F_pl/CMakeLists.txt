cmake_minimum_required(VERSION 3.30)
project(F_pl)

set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку из модуля
add_library(fpl)

# Указываем, что это модуль (для CMake 3.28+)
target_sources(fpl
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
        FILES src/Fpl.ixx
)

#find_package(GTest REQUIRED)
#
target_link_libraries(fpl PRIVATE ntl gmp)
#
#add_compile_options("-g")
#add_executable(test_fpld test/test.cpp test/test_fpld.cpp)
#target_link_libraries(test_fpld PRIVATE GTest::Main field ntl gmp)

#include(GoogleTest)
#gtest_discover_tests(test_fpld)

add_executable(test_fpl main.cpp)
target_link_libraries(test_fpl fpl stdc++fs)