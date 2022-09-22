# Set executable name
set(EXENAME DiKErnel.System.Test)

# Define sources
set(SOURCEFILES
  AsphaltRevetmentWaveImpactCalculationTest.cpp
  GrassRevetmentOvertoppingCalculationTest.cpp
  Main.cpp
  ValidationSystemTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Integration
  DiKErnel.Util.TestUtil
  DiKErnel.TestUtil
  gtest
)