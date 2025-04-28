cmake_minimum_required(VERSION 3.30)
project(Unital)

set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку из модуля
add_library(unital)

# Указываем, что это модуль (для CMake 3.28+)
target_sources(unital
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
        FILES src/Unital.ixx
)

target_link_libraries(unital pgpl2)

find_package(GTest REQUIRED)

add_executable(test_unital test/test.cpp test/test_unital.cpp)
target_link_libraries(test_unital GTest::Main)