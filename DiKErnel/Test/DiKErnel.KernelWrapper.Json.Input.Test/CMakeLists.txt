# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Input.Test)

# Define sources
set(SOURCEFILES
  JsonInputComposerTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gtest DiKErnel.KernelWrapper.Json.Input)