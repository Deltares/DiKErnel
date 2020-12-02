# Set CMake variables
cmake_minimum_required (VERSION 3.8)

# Define project
project (DiKErnel)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("++ Building with code coverage")
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -static-libgcc -static-libstdc++")
  set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
else()
  message("++ Building without code coverage")
endif()

# Set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add directories
add_subdirectory(Src)
add_subdirectory(Test)