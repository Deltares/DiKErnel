# Set CMake variables
cmake_minimum_required (VERSION 3.8)

# Set compiler flags
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -static-libgcc -static-libstdc++")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# Define project
project (DiKErnel)

# Add sources
add_subdirectory(Src)
add_subdirectory(Test)
add_subdirectory(Console)