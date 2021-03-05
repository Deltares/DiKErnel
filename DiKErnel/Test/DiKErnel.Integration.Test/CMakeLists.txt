# Set executable name
set(EXENAME DiKErnel.Integration.Test)

# Define sources
set(SOURCEFILES
  CalculationInputTest.cpp
  LocationDependentDataTest.cpp
  Main.cpp
  NaturalStoneRevetmentLocationConstructionPropertiesTest.cpp
  NaturalStoneRevetmentLocationDependentDataTest.cpp
  RevetmentCalculationInputBuilderExceptionTest.cpp
  RevetmentCalculationInputBuilderTest.cpp
  TimeDependentDataTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gtest DiKErnel.Integration DiKErnel.Integration.TestUtil DiKErnel.TestUtil)