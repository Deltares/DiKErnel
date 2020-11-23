###########
# Project #
###########
set(LIBNAME DiKErnel)

###########
# Targets #
###########

# Sources
set (SOURCES
	DiKErnel.h
	DiKErnel.cpp
)

# Build library
add_library(${LIBNAME} STATIC ${SOURCES})

target_include_directories (${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})