# Set executable name
set(EXENAME DiKErnel.FunctionLibrary.Test)

# Define sources
set(SOURCEFILES
  GenericTest.cpp
  GrassRevetmentWaveImpactTest.cpp
  HydraulicLoadTest.cpp
  Main.cpp
  NaturalStoneRevetmentTest.cpp
  RevetmentTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} gtest DiKErnel.FunctionLibrary)