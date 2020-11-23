###########
# Project #
###########
set(LIBNAME DiKErnel)

###########
# Targets #
###########

# Sources
set (SOURCES
	Main.cpp
)

# Build library
add_library(${LIBNAME} SHARED ${SOURCES})