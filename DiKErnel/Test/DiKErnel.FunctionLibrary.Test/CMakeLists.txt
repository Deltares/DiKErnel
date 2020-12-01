# Set executable name
set(EXENAME DiKErnel.FunctionLibrary.Test)

# Define sources
set(SOURCEFILES
  DummyTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} Catch2::Catch2)