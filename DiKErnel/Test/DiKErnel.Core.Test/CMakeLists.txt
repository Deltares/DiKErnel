# Set executable name
set(EXENAME DiKErnel.Core.Test)

# Set folder names
set(DATA_FOLDER Data)

# Define sources
set(SOURCEFILES_ROOT
  CalculatorTest.cpp
  Main.cpp
  ValidatorTest.cpp
)

set(SOURCEFILES_DATA
  ${DATA_FOLDER}/CalculationOutputTest.cpp
  ${DATA_FOLDER}/CharacteristicPointTest.cpp
  ${DATA_FOLDER}/LocationDependentOutputTest.cpp
  ${DATA_FOLDER}/ProfilePointTest.cpp
  ${DATA_FOLDER}/ProfileSegmentTest.cpp
  ${DATA_FOLDER}/TimeDependentOutputConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/TimeDependentOutputTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_DATA}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${DATA_FOLDER} FILES ${SOURCEFILES_DATA})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Core
  DiKErnel.Core.TestUtil
  DiKErnel.FunctionLibrary
  DiKErnel.TestUtil
  DiKErnel.Util.TestUtil
  gmock
  gtest
)