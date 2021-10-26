# Set executable name
set(EXENAME DiKErnel.Core.Test)

# Define sources
set(SOURCEFILES
  CalculationOutputTest.cpp
  CalculatorTest.cpp
  CharacteristicPointTest.cpp
  LocationDependentOutputTest.cpp
  Main.cpp
  ProfilePointTest.cpp
  TimeDependentOutputTest.cpp
  ValidatorTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Core
  DiKErnel.Core.TestUtil
  DiKErnel.FunctionLibrary
  DiKErnel.TestUtil
  gmock
  gtest
)