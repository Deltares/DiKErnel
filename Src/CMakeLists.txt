###########
# Project #
###########
set(LIBNAME DiKErnel)

###########
# Targets #
###########

# Sources
set (SOURCES
	Calculator.h
	Calculator.cpp
	Controller.h
	Controller.cpp
	InputComposer.h
	InputComposer.cpp
	OutputComposer.h
	OutputComposer.cpp
)

# Build library
add_library(${LIBNAME} STATIC ${SOURCES})

# Make sure the compiler can find include files
target_include_directories (${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})