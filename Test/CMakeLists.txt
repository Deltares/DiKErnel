###########
# Project #
###########
set(LIBNAME DiKErnel.Test)

###########
# Targets #
###########

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -static-libgcc")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# Sources
set (SOURCES
	DiKErnelTest.cpp
)

# Build library
add_executable(${LIBNAME} ${SOURCES})

###############
# Third Party #
###############
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.3)

FetchContent_MakeAvailable(Catch2)

# Link Catch to the executable
target_link_libraries(${LIBNAME} Catch2::Catch2)