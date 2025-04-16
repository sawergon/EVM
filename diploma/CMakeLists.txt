cmake_minimum_required(VERSION 3.30)
project(diploma)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/Unital)
add_subdirectory(lib/F_pld)
add_subdirectory(lib/PGpl2)
add_subdirectory(lib/PP)
add_subdirectory(lib/F_pl)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

include_directories(include/functions)
include_directories(include/objects)
include_directories(include/interfaces)
include_directories(include/Network)
include_directories(include/objects/Nodes)
include_directories(include)

set(SRC src/functions/stribog256.cpp
        include/functions/stribog256.hpp
        include/objects/TrustCenter.hpp
        src/objects/TrustCenter.cpp
        include/objects/Nodes/Node.hpp
        include/objects/Nodes/TCNode.hpp
        src/objects/Nodes/TCNode.cpp
        src/objects/Nodes/CommonNode.cpp
        include/objects/Nodes/CommonNode.hpp
)

add_executable(diploma
        main.cpp
        ${SRC}
)
target_link_libraries(diploma
        PRIVATE
        unital
        fpld
        pgpl2
        pp
        fpl
        Boost::system
        Boost::filesystem
        Boost::program_options
)

find_package(GTest REQUIRED)
include_directories(test)

set(SRC_TEST test/test.cpp
        test/test.hpp
        test/functions/test_stribog256.cpp)

add_executable(test
        ${SRC_TEST}
        ${SRC}
)
target_link_libraries(test PRIVATE GTest::Main)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#add_custom_command(TARGET diploma POST_BUILD
#  COMMAND ${CMAKE_SOURCE_DIR}/tools/windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diploma.exe
#  COMMENT "Copying application resources")