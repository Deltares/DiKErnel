###########
# Project #
###########
set(EXENAME DiKErnelConsole)

###########
# Targets #
###########

# Sources
set (SOURCES
	Console.cpp
)

# Build executable
add_executable(${EXENAME} ${SOURCES})

# Link library
target_link_libraries(${EXENAME} LINK_PUBLIC DiKErnel)