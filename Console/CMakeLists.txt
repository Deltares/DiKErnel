# Set executable name
set(EXENAME DiKErnel.Console)

# Add sources
set (SOURCES
  Console.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCES})

# Link dependencies
target_link_libraries(${EXENAME}
  DiKErnel
)