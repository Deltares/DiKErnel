###########
# Project #
###########
cmake_minimum_required (VERSION 3.8)
project (DiKErnel)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -static-libgcc -static-libstdc++")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

###########
# Targets #
###########
add_subdirectory(Src)
add_subdirectory(Test)
add_subdirectory(Console)