# Set executable name
set(EXENAME DiKErnel.DomainLibrary.Test)

# Define sources
set(SOURCEFILES
  ConstantsTest.cpp
  GrassRevetmentWaveImpactClosedSodDefaultsTest.cpp
  GrassRevetmentWaveImpactOpenSodDefaultsTest.cpp
  HydraulicLoadsDefaultsTest.cpp
  Main.cpp
  NordicStoneRevetmentDefaultsTest.cpp
  RevetmentDefaultsTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} gtest DiKErnel.DomainLibrary)