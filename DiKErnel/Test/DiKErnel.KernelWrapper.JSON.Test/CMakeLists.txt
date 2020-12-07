# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Test)

# Define sources
set(SOURCEFILES
  InputComposerTest.cpp
  Main.cpp
  OutputComposerTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} Catch2::Catch2 DiKErnel.TestUtil DiKErnel.KernelWrapper.Json)