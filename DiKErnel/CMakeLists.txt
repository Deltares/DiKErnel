# Set CMake variables
cmake_minimum_required (VERSION 3.18)

# Define project
project (DiKErnel)

# Define options
option(BUILD_WITH_TESTS "Build with tests" ON)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("Building with code coverage")
  set(CMAKE_CXX_FLAGS "-g -Og -Wall -fprofile-arcs -ftest-coverage -fno-elide-constructors -static-libgcc")
  set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
else()
  message("Building without code coverage")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add directories
add_subdirectory(Src)

if (BUILD_WITH_TESTS)
  add_subdirectory(Test)
endif()