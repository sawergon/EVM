cmake_minimum_required(VERSION 3.30)
project(diploma)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/Unital)
add_subdirectory(lib/F_pld)
add_subdirectory(lib/PGpl2)
add_subdirectory(lib/PP)

add_executable(diploma main.cpp)
target_link_libraries(diploma flint gmp mpfr)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#add_custom_command(TARGET diploma POST_BUILD
#  COMMAND ${CMAKE_SOURCE_DIR}/tools/windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diploma.exe
#  COMMENT "Copying application resources")