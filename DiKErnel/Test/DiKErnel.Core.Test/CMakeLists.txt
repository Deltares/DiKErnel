# Set executable name
set(EXENAME DiKErnel.Core.Test)

# Define sources
set(SOURCEFILES
  CalculationOutputTest.cpp
  CalculatorTest.cpp
  DeprecatedCalculatorTest.cpp
  LocationDependentOutputTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gtest gmock DiKErnel.TestUtil DiKErnel.FunctionLibrary DiKErnel.Core DiKErnel.Core.TestUtil)