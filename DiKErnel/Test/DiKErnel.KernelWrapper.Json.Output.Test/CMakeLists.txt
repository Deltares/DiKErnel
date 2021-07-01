# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Output.Test)

# Define sources
set(SOURCEFILES
  JsonOutputComposerTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gmock gtest DiKErnel.Core DiKErnel.Core.TestUtil DiKErnel.KernelWrapper.Json DiKErnel.KernelWrapper.Json.Output DiKErnel.TestUtil)