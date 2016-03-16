cmake_minimum_required(VERSION 3.3)
project(E4Language_compilation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES E4main.cpp E4Regle.cpp E4Regle.h E4liste.h E4Regle.cpp E4Regle.h E4grammaire.cpp E4grammaire.h)
add_executable(E4Language_compilation ${SOURCE_FILES})