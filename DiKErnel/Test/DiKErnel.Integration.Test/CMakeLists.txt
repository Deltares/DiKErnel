# Set executable name
set(EXENAME DiKErnel.Integration.Test)

# Set folder names
SET(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(PUBLIC_DATA_OUTPUT_FOLDER ${PUBLIC_DATA_FOLDER}/Output)
set(PULIC_EXCEPTIONS_FOLDER ${PUBLIC_FOLDER}/Exceptions)
set(INTERNAL_DATA_FOLDER Internal/Data)
set(INTERNAL_HELPERS_FOLDER Internal/Helpers)

# Define sources
set(SOURCEFILES_ROOT
  Main.cpp
)

set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/RevetmentCalculationInputBuilderTest.cpp
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/AsphaltRevetmentWaveImpactLocationConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_FOLDER}/GrassRevetmentWaveImpactLocationConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_FOLDER}/GrassRevetmentWaveRunupLocationConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_FOLDER}/GrassRevetmentWaveRunupRayleighLocationConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_FOLDER}/NaturalStoneRevetmentLocationConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_FOLDER}/RevetmentLocationConstructionPropertiesBaseTest.cpp
)

set(SOURCEFILES_PUBLIC_DATA_OUTPUT
  ${PUBLIC_DATA_OUTPUT_FOLDER}/AsphaltRevetmentWaveImpactLocationDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/AsphaltRevetmentWaveImpactTimeDependentOutputConstructionPropertiesTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/AsphaltRevetmentWaveImpactTimeDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/GrassRevetmentWaveImpactLocationDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/GrassRevetmentWaveImpactTimeDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/GrassRevetmentWaveRunupRayleighLocationDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/GrassRevetmentWaveRunupRayleighTimeDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/NaturalStoneRevetmentLocationDependentOutputTest.cpp
  ${PUBLIC_DATA_OUTPUT_FOLDER}/NaturalStoneRevetmentTimeDependentOutputTest.cpp
)

set(SOURCEFILES_PUBLIC_EXCEPTIONS
  ${PULIC_EXCEPTIONS_FOLDER}/RevetmentCalculationInputBuilderExceptionTest.cpp
)

set(SOURCEFILES_INTERNAL_DATA
  ${INTERNAL_DATA_FOLDER}/ProfileDataTest.cpp
)

set(SOURCEFILES_INTERNAL_HELPERS
  ${INTERNAL_HELPERS_FOLDER}/ValidationHelperTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_DATA}
  ${SOURCEFILES_PUBLIC_DATA_OUTPUT}
  ${SOURCEFILES_PUBLIC_EXCEPTIONS}
  ${SOURCEFILES_INTERNAL_DATA}
  ${SOURCEFILES_INTERNAL_HELPERS}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_DATA_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA})
source_group(${PUBLIC_DATA_OUTPUT_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA_OUTPUT})
source_group(${PULIC_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_PUBLIC_EXCEPTIONS})
source_group(${INTERNAL_DATA_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA})
source_group(${INTERNAL_HELPERS_FOLDER} FILES ${SOURCEFILES_INTERNAL_HELPERS})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Core.TestUtil
  DiKErnel.Integration
  DiKErnel.Integration.TestUtil
  DiKErnel.TestUtil
  gtest
)