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
include_directories(include/ConfigParser)
include_directories(include/Kuznechik)
include_directories(include)
include_directories(include/blome)

set(SRC
        include/json.hpp
        include/ConfigParser/ConfigParser.hpp
        src/ConfigParser/ConfigParser.cpp
        include/Model.hpp
        src/Model.cpp

        include/objects/Node.hpp
        include/objects/Router.hpp
        include/objects/Coordinator.hpp

        src/objects/Node.cpp
        src/objects/Router.cpp
        src/objects/Coordinator.cpp

        include/Kuznechik/Kuznechik.hpp
        src/Kuznechick/Kuznechick.cpp

        src/functions/parser.cpp
        include/functions/parser.hpp

#        src/functions/stribog256.cpp
#        include/functions/stribog256.hpp
        include/blome/BlomePolinome.hpp
        src/blome/BlomePolinome.cpp
        include/functions/Stribog512.hpp
        src/functions/Stribog512.cpp
)

add_executable(diploma
        src/main.cpp
        ${SRC}
)
target_link_libraries(diploma
        PRIVATE
        unital
#        fpld
        pgpl2
        ppdn
#        fpl
#        Boost::system
#        Boost::filesystem
#        Boost::program_options
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

add_executable(test_kuz
        test_kuz.cpp
        include/Kuznechik/Kuznechik.hpp
        src/Kuznechick/Kuznechick.cpp
)

target_link_libraries(test
        PRIVATE
        GTest::Main
        unital
        pgpl2
        ppdn
)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#add_custom_command(TARGET diploma POST_BUILD
#  COMMAND ${CMAKE_SOURCE_DIR}/tools/windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diploma.exe
#  COMMENT "Copying application resources")