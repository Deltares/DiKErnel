# Set executable name
set(EXENAME DiKErnel.Integration.Test)

# Set folder names
set(DATA_FOLDER Data)
set(DATA_OUTPUT_FOLDER ${DATA_FOLDER}/Output)
set(EXCEPTIONS_FOLDER Exceptions)

# Define sources
set(SOURCEFILES_ROOT
  Main.cpp
  RevetmentCalculationInputBuilderTest.cpp
)

set(SOURCEFILES_DATA
  ${DATA_FOLDER}/AsphaltRevetmentWaveImpactLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/GrassRevetmentWaveImpactLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/GrassRevetmentWaveRunupLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/GrassRevetmentWaveRunupRayleighLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/NaturalStoneRevetmentLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/RevetmentLocationConstructionPropertiesBaseTest.cpp
)

set(SOURCEFILES_DATA_OUTPUT
  ${DATA_OUTPUT_FOLDER}/AsphaltRevetmentWaveImpactTimeDependentOutputTest.cpp
  ${DATA_OUTPUT_FOLDER}/GrassRevetmentWaveImpactTimeDependentOutputTest.cpp
  ${DATA_OUTPUT_FOLDER}/GrassRevetmentWaveRunupRayleighTimeDependentOutputTest.cpp
  ${DATA_OUTPUT_FOLDER}/NaturalStoneRevetmentTimeDependentOutputTest.cpp
)

set(SOURCEFILES_EXCEPTIONS
  ${EXCEPTIONS_FOLDER}/RevetmentCalculationInputBuilderExceptionTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_DATA}
  ${SOURCEFILES_DATA_OUTPUT}
  ${SOURCEFILES_EXCEPTIONS}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${DATA_FOLDER} FILES ${SOURCEFILES_DATA})
source_group(${DATA_OUTPUT_FOLDER} FILES ${SOURCEFILES_DATA_OUTPUT})
source_group(${EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_EXCEPTIONS})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Integration
  DiKErnel.Integration.TestUtil
  DiKErnel.TestUtil
  gtest
)