# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Integration.Test)

# Define sources
set(SOURCEFILES
  IntegrationTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.KernelWrapper.Json.Input
  DiKErnel.KernelWrapper.Json.Output
  DiKErnel.TestUtil
  gtest
)